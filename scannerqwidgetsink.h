#ifndef SCANNERQWIDGETSINK_H
#define SCANNERQWIDGETSINK_H

#include <QWidget>
#include <QTimer>
#include <QSemaphore>

#include <gst/app/gstappsink.h>
#include <gst/gst.h>

#include "viewfinderwidget.h"

class ScannerQWidgetSink : public QObject
{
    Q_OBJECT

public:
    ScannerQWidgetSink(ViewfinderWidget *sinkWidget, QString vidSrc);
    ~ScannerQWidgetSink();

    void StartRender();
    void StopRender();
    void ExitRender();
    void CopyFrameData(QByteArray &dest);
    bool WaitForFrameData();

    static uint CAPTURE_WIDTH;
    static uint CAPTURE_HEIGHT;

private slots:
    void Rendering();

private:
    bool GstPipelineInit(QString source);
    void GstPipelineUnInit();

    ViewfinderWidget *widget2Sink;
    QTimer *renderTimer;
    bool bRendering;
    bool bExiting;
    GstElement *mysink;
    GstElement *pipeline;
    GstBus *bus;
    QByteArray imgBuffer;
    QSemaphore sem;
};

#endif // SCANNERQWIDGETSINK_H
