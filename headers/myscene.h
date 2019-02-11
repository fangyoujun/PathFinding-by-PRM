#ifndef MYSCENE_H
#define MYSCENE_H
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include "obstacle.h"
#include <vector>
#include <QLine>

using namespace std;

class myscene : public QGraphicsScene
{
public:
    myscene();
    QPointF topLeft;
    QRectF rect;
    Obstacle* obs;
    vector<Obstacle*> allObs;
    bool MousePressed;

    bool drawObs;

    /*if a point(x,y) is within the area(incl margin) of any obs*/
    bool contains(vector<Obstacle*> allObs, qreal x, qreal y);

    /*if a line (x1,y1)-(x2,y2) is collide with any obs*/
    bool nonCollide(vector<Obstacle*> allObs, qreal x1, qreal y1, qreal x2, qreal y2);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // MYSCENE_H
