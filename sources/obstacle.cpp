#include "obstacle.h"
#include <QPainter>

Obstacle::Obstacle()
{
    topLeftX = topLeftY = 0;
    width = 100;
    height = 200;
    setPos(topLeftX, topLeftY);
    setRect(topLeftX, topLeftY, width, height);
    setFlags(QGraphicsItem::ItemIsMovable);
}

Obstacle::Obstacle(qreal x, qreal y, qreal w, qreal h):
    topLeftX(x),topLeftY(y),width(w),height(h)
{
    setPos(topLeftX, topLeftY);
    setRect(topLeftX, topLeftY, width, height);
    setFlags(QGraphicsItem::ItemIsMovable);
}

QRectF Obstacle::boundingRect()
{
    qreal penWidth = 1;
    return QRectF(topLeftX-penWidth/2, topLeftY-penWidth, width+penWidth, height+penWidth);
}

void Obstacle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush brush(Qt::black);
    painter->setBrush(brush);
    painter->drawRect(this->boundingRect());
}


