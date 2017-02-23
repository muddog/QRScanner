#ifndef DECODERTHREAD_H
#define DECODERTHREAD_H

#include <QObject>
#include <QThread>
#include <QLabel>

#include "scannerqwidgetsink.h"
#include "QZXing.h"

class DecoderThread : public QThread
{
    Q_OBJECT

public:
    DecoderThread(QObject *parent);
    void AttachWidgetSink(ScannerQWidgetSink *sink, QLabel *label);

public slots:
    void run() Q_DECL_OVERRIDE;

signals:
    void resultReady(const QString &result);

private:
    ScannerQWidgetSink *widgetSink;
    QByteArray imgData;
    QZXing zxing;
    QLabel *resultLabel;
};

#endif // DECODERTHREAD_H
