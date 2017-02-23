#include "viewfinderwidget.h"
#include <QPainter>

ViewfinderWidget::ViewfinderWidget(QWidget *parent) :
                QWidget(parent), image(0)
{
}

ViewfinderWidget::~ViewfinderWidget()
{
    if (image)
        delete image;
}

void ViewfinderWidget::LoadImageBuffer(
        const QByteArray &buffer, int width, int height)
{
    image = new QImage((const uchar *)buffer.data(),
                       width, height,
                       QImage::Format_RGB16);
}

void ViewfinderWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect target = rect();
    QRect source = image->rect();

    if (!image->isNull())
        painter.drawImage(target, *image, source);
}
