#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include <stdlib.h>
#include <time.h>
#include <QGraphicsEllipseItem>
#include <QGraphicsPathItem>
#include <QGraphicsLineItem>
#include <QGraphicsRectItem>
#include <qmath.h>


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setMouseTracking(true);


    scene = new myscene();
    scene->setSceneRect(0,0,1000,1000);

    ui->graphicsView->setScene(scene);

    /*add the car: start point of shortest path*/
    agent = new myAgent();
    agent->setPos(200,200);
    agent->setZValue(10);  //make the agent appear in the most front of view
    scene->addItem(agent);

    /*add the home: end point of shortest path*/
    home = new QGraphicsPixmapItem(QPixmap(":/house/house.jpg"));
    home->setOffset(-20,-20);
    home->setPos(800,800);
    home->setFlags(QGraphicsItem::ItemIsMovable);
    home->setZValue(5);  //make the agent appear in the 2nd front of view
    scene->addItem(home);

    connect(ui->sample_Slider,SIGNAL(valueChanged(int)),ui->label_sample,SLOT(setNum(int)));
    connect(ui->distance_Slider,SIGNAL(valueChanged(int)),ui->label_distance,SLOT(setNum(int)));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_Obs_checkBox_stateChanged(int arg1)
{
    scene->drawObs = !scene->drawObs;
}


void Dialog::on_BuildRoadmap_clicked()
{

    /*randomly select points and construct the graph*/
    int numPoint = ui->sample_Slider->value();
    graph = new Graph(numPoint,agent->pos(),home->pos());

    int minDist = ui->distance_Slider->value();

    static int id = 2;
    for (int i = 0; i < numPoint; i++)
    {
        double x = qrand()%1000, y = qrand()%1000;

        if (scene->contains(scene->allObs,x,y))
            numPoint++; //because p is in obs so be rejetted, so increase numPoint to ensure total num is as specified by user
        else
        {
            QPointF p(x,y);
            AdjListNode* newNode = new AdjListNode(p,id);
            graph->addVertex(newNode);

            for (int i = 0; i < id && graph->vec[i] != nullptr && i != newNode->id; i++)
            {
                QPointF p1 = graph->vec[i]->point;
                QPointF p2 = newNode->point;
                if (dist(p1,p2) <= minDist &&
                    scene->nonCollide(scene->allObs,p1.x(),p1.y(),p2.x(),p2.y()))
                    graph->addEdge(i,newNode->id);
            }
            id++;
        }
    }

    /*draw the graph*/
    for (auto v : graph->vec)
    {

        QPen pen(Qt::gray);
        QBrush brush(Qt::gray);
        qreal r = 5; //radius for drawing randomly selected points
        AdjListNode* head = v;

        scene->addEllipse(head->point.x()-r,head->point.y()-r,2*r,2*r,pen,brush);

        AdjListNode* curr = head->next;
        while (curr != nullptr)
        {
            scene->addEllipse(curr->point.x()-r,curr->point.y()-r,2*r,2*r,pen,brush);
            scene->addLine(head->point.x(),head->point.y(),curr->point.x(),curr->point.y(),pen);
            curr = curr->next;
        }
    }
}

extern void Astar(Graph*, AdjListNode*, AdjListNode*, double);
void Dialog::on_FindWayButton_clicked()
{
    //find the shortest path by A*
    Astar(graph, graph->start, graph->end, ui->e_spin->value());

    //store the shortest path in agent->path
    int id = graph->end->id;
    while (id > graph->start->id)
    {
        agent->path.push_back(graph->vec[id]->point);
        id = graph->came_from[id];
    }
    agent->path.push_back(graph->start->point);
    std::reverse(agent->path.begin(), agent->path.end());

    //draw the path
    QPen pen(Qt::red);
    QBrush brush(Qt::red);
    qreal r = 5;
    int pathLen = agent->path.size();
    for (int i = 0; i < pathLen-1; i++)
    {
        scene->addEllipse(agent->path[i].x()-r,agent->path[i].y()-r,2*r,2*r,pen,brush);
        scene->addLine(agent->path[i].x(),agent->path[i].y(),agent->path[i+1].x(),agent->path[i+1].y(),pen);
    }
    scene->addEllipse(agent->path[pathLen-1].x()-r,agent->path[pathLen-1].y()-r,2*r,2*r,pen,brush);


    //shortcut the path
    if (agent->shortCut)
    {

    }

    //draw the shortcutted path

}



void Dialog::on_Path_shortcut_stateChanged(int arg1)
{
    agent->shortCut = !agent->shortCut;
}

void Dialog::on_Run_Button_clicked()
{
    agent->goHome();
}
