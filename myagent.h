#ifndef MYAGENT_H
#define MYAGENT_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <vector>
#include <QCursor>

using namespace std;

class myAgent : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    myAgent();
    ~myAgent();
    vector<QPointF> path;
    bool shortCut = false;
    void goHome();

public slots:
    void advance();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    QTimer* timer;
};


#endif // MYAGENT_H
