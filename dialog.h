#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include "myagent.h"
#include <QTimer>
#include <QPainter>
#include "graph.h"
#include "obstacle.h"
#include <vector>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "myscene.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();


    
private slots:
    void on_FindWayButton_clicked();

    void on_BuildRoadmap_clicked();

//    void on_ObsButton_clicked();

    void on_Obs_checkBox_stateChanged(int arg1);

    void on_Path_shortcut_stateChanged(int arg1);

    void on_Run_Button_clicked();

private:
    Ui::Dialog *ui;
    myscene *scene;

    myAgent *agent;
    QGraphicsPixmapItem* home;

    QPointF topLeft;
    QGraphicsRectItem *rect;



    QTimer *timer;
    Graph *graph;
    bool pathFound = false;

protected:
//    void mousePressEvent(QMouseEvent *);
//    void mouseMoveEvent(QMouseEvent *);
//    void mouseReleaseEvent(QMouseEvent *);

};

#endif // DIALOG_H
