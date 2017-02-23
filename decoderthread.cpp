#include "decoderthread.h"

DecoderThread::DecoderThread(QObject *parent) :
                QThread(parent),
                zxing(QZXing::DecoderFormat_QR_CODE, this)
{
    int size = ScannerQWidgetSink::CAPTURE_WIDTH *
            ScannerQWidgetSink::CAPTURE_HEIGHT * 2;
    imgData.resize(size);
}

void DecoderThread::AttachWidgetSink(ScannerQWidgetSink *sink, QLabel *label)
{
    widgetSink = sink;
    resultLabel = label;
}

void DecoderThread::run()
{
    QString result;
    QString decodeResult;

    while (1) {
        // wait for the semaphore release by sink
        if (!widgetSink->WaitForFrameData()) {
            // sink is destroying? Then we exit
            break;
        }

        // copy image buffer
        widgetSink->CopyFrameData(imgData);
        QImage *image = new QImage((uchar *)imgData.data(),
                            ScannerQWidgetSink::CAPTURE_WIDTH,
                            ScannerQWidgetSink::CAPTURE_HEIGHT,
                            QImage::Format_RGB16);
#ifdef DEBUG
        qDebug() << QTime::currentTime().toString() << "Buffer is ready";
#endif
        decodeResult = zxing.decodeImage(*image, 640, 480, false);
        if (decodeResult.size())
            resultLabel->setText(decodeResult);
#ifdef DEBUG
        qDebug() << QTime::currentTime().toString() << "QZXing work done:" << decodeResult;
#endif
        delete image;
    }
    emit resultReady(result);
}
