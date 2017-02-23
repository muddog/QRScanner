#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "scannerqwidgetsink.h"
#include "decoderthread.h"
#include <QWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    ScannerQWidgetSink *sink;
    DecoderThread *decThread;
};

#endif // MAINWINDOW_H
