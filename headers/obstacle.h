#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <QGraphicsRectItem>

class Obstacle : public QGraphicsRectItem
{
private:
    qreal topLeftX;
    qreal topLeftY;
    qreal width;
    qreal height;

public:
    Obstacle();
    Obstacle(qreal x, qreal y, qreal w, qreal h);
    QRectF boundingRect();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    qreal getTopLeftX(){return topLeftX;}
    qreal getTopLeftY(){return topLeftY;}
    qreal getTopRightX(){return topLeftX+width;}
    qreal getTopRightY(){return topLeftY;}
    qreal getBottomLeftX(){return topLeftX;}
    qreal getBottomLeftY(){return topLeftY+height;}
    qreal getBottomRightX(){return topLeftX+width;}
    qreal getBottomRightY(){return topLeftY+height;}

};

#endif // OBSTACLE_H
