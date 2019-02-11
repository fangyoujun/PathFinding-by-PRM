#include "myagent.h"
#include <QGraphicsItem>
#include <QDebug>
#include <qmath.h>

myAgent::myAgent()
{
    setPixmap(QPixmap(":/car/car.jpg"));

    //set the origin of car to be the center of it; the car size is about 40x16
    setOffset(-20,-8);
    setFlags(QGraphicsItem::ItemIsMovable);

}

myAgent::~myAgent()
{
    delete timer;
}

static int pointId = 0;
void myAgent::advance()
{
    if (this->pos() == path[path.size()-1])
        timer->stop();

    if (this->pos() == path[pointId])
    {
        //rotate
        qreal PI = 3.1415926;
        qreal dx = path[pointId+1].x() - path[pointId].x();
        qreal dy = path[pointId+1].y() - path[pointId].y();
        if (dx == 0)
        {
            if (dy < 0)
                this->setRotation(-90);
            else
                this->setRotation(90);
        }
        else
        {
            qreal angle = qAtan(dy/dx)*180/PI;
            if ((dy >= 0 && angle >= 0) || (dy < 0 && angle < 0) )
                this->setRotation(angle);
            else if ((dy >= 0 && angle < 0) || (dy < 0 && angle > 0))
                this->setRotation(180+angle);
        }

        pointId++;

    }

    //go ahead
    qreal slope;
    if (path[pointId].x() != this->pos().x())
    {
        slope =  (path[pointId].y() - this->pos().y()) / (path[pointId].x() - this->pos().x());
        qreal stepX = (path[pointId].x() - this->pos().x()) / abs(path[pointId].x() - this->pos().x());
        moveBy(stepX, stepX * slope);
    }
    else
    {
        qreal stepY = (path[pointId].y() - this->pos().y()) / abs(path[pointId].y() - this->pos().y());
        moveBy(0,stepY);
    }
}

void myAgent::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setFocus();
    setCursor(Qt::ClosedHandCursor);
}


void myAgent::goHome()
{
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this, SLOT(advance()));
    timer->start(20);
}


