#include "myscene.h"
#include <QDebug>


myscene::myscene()
{
}

void myscene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    topLeft = event->scenePos();
    MousePressed = true;
    update();
}

void myscene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (MousePressed && drawObs)
    {
        addLine(topLeft.x(),topLeft.y(),event->scenePos().x(),topLeft.y(), QPen(Qt::black));
        addLine(topLeft.x(),topLeft.y(),topLeft.x(),event->scenePos().y(), QPen(Qt::black));
    }
}

void myscene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (drawObs)
    {
        qreal w, h;
        w = abs(event->scenePos().x()-topLeft.x());
        h = abs(event->scenePos().y()-topLeft.y());
        rect.setRect(topLeft.x(),topLeft.y(),w,h);
        addRect(rect, QPen(Qt::black), QBrush(Qt::black));
        obs = new Obstacle(topLeft.x(),topLeft.y(),w,h);

        allObs.push_back(obs);
        MousePressed = false;
        update();
    }
}

bool myscene::contains(vector<Obstacle *> allObs, qreal x, qreal y)
{
    for (auto obs : allObs)
    {
        qreal marginLeft = obs->pos().x() - 10;
        qreal marginRight = marginLeft + obs->rect().width() + 20;
        qreal marginTop = obs->pos().y() - 10;
        qreal marginBottom = marginTop + obs->rect().height() + 20;
        if (x >= marginLeft && x <= marginRight && y >= marginTop && y <= marginBottom)
            return true;
    }
    return false;
}

bool myscene::nonCollide(vector<Obstacle *> allObs, qreal x1, qreal y1, qreal x2, qreal y2)
{
    bool res = true;

    qreal frac = float(1) / 32;

    if (x1 == x2)
    {
        while (frac < 1)
        {
            res = !contains(allObs, x1, y1 + (y2 - y1) * frac);
            if (!res) return res;
            frac += float(1) / 32;
        }
    }
    else
    {
        while (frac < 1)
        {
            qreal x = x1 + (x2 - x1) * frac;
            qreal y = (y2 - y1) / (x2 - x1) * (x - x1) + y1;
            res = !contains(allObs, x, y);
            if (!res) return res;
            frac += float(1) / 32;
        }
    }
    return res;
}
