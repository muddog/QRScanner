#include "scannerqwidgetsink.h"
#include <QDebug>

uint ScannerQWidgetSink::CAPTURE_HEIGHT = 480;
uint ScannerQWidgetSink::CAPTURE_WIDTH = 640;

ScannerQWidgetSink::ScannerQWidgetSink(ViewfinderWidget *sinkWidget, QString vidSrc):
                    bRendering(false),
                    bExiting(false),
                    pipeline(NULL),
                    sem(0)
{
    widget2Sink = sinkWidget;
    GstPipelineInit(vidSrc);
}

ScannerQWidgetSink::~ScannerQWidgetSink()
{
    if (bRendering)
        StopRender();
    if (!bExiting)
        ExitRender();
    if (pipeline)
        GstPipelineUnInit();
    delete renderTimer;
}

bool ScannerQWidgetSink::GstPipelineInit(QString source)
{
    // init the gstreamer
    gst_init(NULL, NULL);

    // create pipeline from parser
    GError *error = NULL;
    QString resolution;
    resolution.sprintf("width=%d,height=%d",
                       ScannerQWidgetSink::CAPTURE_WIDTH,
                       ScannerQWidgetSink::CAPTURE_HEIGHT);
    QString launchCmd = source +
                    " ! video/x-raw,format=YUY2,framerate=20/1," + resolution +
#ifdef LINUX_HOST
                    " ! videoconvert"
#else
                    " ! imxvideoconvert_pxp"
#endif
                    " ! video/x-raw,format=RGB16 ! appsink name=\"mysink\"";
    pipeline = gst_parse_launch(launchCmd.toLocal8Bit().constData(), &error);
    if (!pipeline) {
        qDebug() << "Failed to create pipeline:" << launchCmd.toLocal8Bit().constData();
        return false;
    }

    // get appsink
    mysink = gst_bin_get_by_name(GST_BIN(pipeline), "mysink");
    g_signal_connect(pipeline, "deep-notify", G_CALLBACK(gst_object_default_deep_notify), NULL);
    gst_app_sink_set_emit_signals((GstAppSink *)mysink, true);
    gst_app_sink_set_drop((GstAppSink *)mysink, true);
    gst_app_sink_set_max_buffers((GstAppSink *)mysink, 1);
    gst_element_set_state(pipeline, GST_STATE_PLAYING);
    bus = gst_element_get_bus(pipeline);

    // init the buffer size for QImage
    // RGB565 takes 2Bytes per pixel
    int imgSize = ScannerQWidgetSink::CAPTURE_HEIGHT *
                ScannerQWidgetSink::CAPTURE_WIDTH * 2;
    imgBuffer.resize(imgSize);

    widget2Sink->LoadImageBuffer(imgBuffer,
                                 ScannerQWidgetSink::CAPTURE_WIDTH,
                                 ScannerQWidgetSink::CAPTURE_HEIGHT);

    renderTimer = new QTimer(this);
    connect(renderTimer, SIGNAL(timeout()), this, SLOT(Rendering()));

    return true;
}

void ScannerQWidgetSink::GstPipelineUnInit()
{
    if (pipeline) {
        gst_element_set_state(pipeline, GST_STATE_NULL);
        gst_object_unref(mysink);
        gst_object_unref(pipeline);
        gst_object_unref(bus);
        pipeline = NULL;
    }
}

void ScannerQWidgetSink::StartRender()
{
    renderTimer->start(50);
    bRendering = true;
}

void ScannerQWidgetSink::StopRender()
{
    bRendering = false;
    renderTimer->stop();
}

void ScannerQWidgetSink::ExitRender()
{
    bExiting = true;
    sem.release(3);
}

void ScannerQWidgetSink::CopyFrameData(QByteArray &dest)
{
    memcpy(dest.data(), imgBuffer.constData(), imgBuffer.size());
}

bool ScannerQWidgetSink::WaitForFrameData()
{
    sem.acquire(1);

    if (bExiting)
        return false;

    return true;
}

void ScannerQWidgetSink::Rendering()
{
    if(!pipeline || !bRendering)
        return;

    static int renderCnt = 0;

    // polling
    GstSample *sample = gst_app_sink_pull_sample((GstAppSink *)mysink);
    // get RGB565 buffer
    GstBuffer *gstImageBuffer = gst_sample_get_buffer(sample);
    GstCaps *cap = gst_sample_get_caps(sample);
    const GstStructure *str = gst_caps_get_structure (cap, 0);
    gint width, height;

    if (!gst_structure_get_int (str, "width", &width) ||
        !gst_structure_get_int (str, "height", &height)) {
        qDebug() << "can not get WxH in the caps";
    } else {
        gst_buffer_extract(gstImageBuffer, 0, imgBuffer.data(), imgBuffer.size());
        widget2Sink->update();
        // release semaphore for decoder thread access buffer
        if (renderCnt ++ >= 10) {
            renderCnt = 0;
            sem.release(1);
        }
    }
    //gst_buffer_unref(gstImageBuffer);
    gst_sample_unref(sample);
}
