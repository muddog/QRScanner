#ifndef VIEWFINDERWIDGET_H
#define VIEWFINDERWIDGET_H

#include <QWidget>
#include <QImage>

class ViewfinderWidget : public QWidget
{
public:
    ViewfinderWidget(QWidget *parent);
    ~ViewfinderWidget();
    void LoadImageBuffer(const QByteArray &, int width, int height);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QImage *image;
};

#endif // VIEWFINDERWIDGET_H
