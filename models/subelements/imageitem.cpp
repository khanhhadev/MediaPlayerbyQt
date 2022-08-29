#include "imageitem.h"
#include <QDebug>
#include <QPainter>

ImageItem::ImageItem(QQuickItem *parent):QQuickPaintedItem(parent)
{
//    qDebug() << Q_FUNC_INFO << "initializing new item, parent is: " << parent;
    setImage(QImage(":/resources/images/logo.png"));
}

QImage ImageItem::image() const
{
//    qDebug() << Q_FUNC_INFO << "image requested...";
    return mImage;
}

void ImageItem::setImage(const QImage &image)
{
//    qDebug() << Q_FUNC_INFO << "setting new image...";
    if(image == mImage)
        return;
    mImage = image;

    emit imageChanged();
    update();
}

void ImageItem::paint(QPainter *painter)
{
    if(mImage.isNull())
        return;
//    qDebug() << Q_FUNC_INFO << "paint requested...";
    painter->setRenderHint(QPainter::SmoothPixmapTransform/*QPainter::Antialiasing*/);
    QRectF bounding_rect = boundingRect();
    QImage scaled = mImage.scaledToHeight(bounding_rect.height());
    QPointF center = bounding_rect.center() - scaled.rect().center();

    if (center.x() < 0)
        center.setX(0);
    if (center.y() < 0)
        center.setY(0);
    painter->drawImage(center, scaled);
}
