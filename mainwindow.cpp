#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPropertyAnimation>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    // Remove titlebar and boarder
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    ui->setupUi(this);

    // Start the animation of the scan bar
    QPropertyAnimation *animation = new QPropertyAnimation(ui->frame_6, "geometry");
    animation->setDuration(4000);
    animation->setStartValue(QRect(4, 1, 192, 4));
    animation->setEndValue(QRect(4, 192, 192, 4));
    animation->setLoopCount(-1);
    animation->start();

    // Init the gst and prepare for sink
    sink = new ScannerQWidgetSink(ui->widget,
                                  QString("v4l2src device=/dev/video1"));
    // start the decoder thread
    decThread = new DecoderThread(this);
    // attache the sink and label UI widget to thread
    decThread->AttachWidgetSink(sink, ui->scanresult);
    //connect(decThread, &DecoderThread::resultReady, this, &handleResults);
    connect(decThread, &DecoderThread::finished, decThread, &QObject::deleteLater);
    decThread->start();
}

MainWindow::~MainWindow()
{
    // stop and exit the rendering
    sink->StopRender();
    sink->ExitRender();
    // wait for decoder thread exit
    decThread->wait();

    delete sink;
    delete ui;
}

void MainWindow::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    sink->StartRender();
}

void MainWindow::hideEvent(QHideEvent *event)
{
    sink->StopRender();
    QWidget::hideEvent(event);
}

void MainWindow::on_pushButton_clicked()
{
    this->close();
}
