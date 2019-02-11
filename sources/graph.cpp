#include "graph.h"
#include <qmath.h>
#include <QDebug>

Graph::Graph()
{
}

Graph::Graph(int num, QPointF startP, QPointF endP)
{
    numVertex = num;
    vec.resize(numVertex+2);

    //set the id of start as 1st item of vec
    start = new AdjListNode(startP, 0);
    vec[0] = start;

    //set the id of end as 2nd item of vec
    end = new AdjListNode(endP, 1);
    vec[1] = end;

    //the 3rd to (numVertex+2)th items are vertex to be added; initially all are nullptr
    for (int i = 2; i < numVertex+2; i++)
    {
        vec[i] = nullptr;
    }
}

Graph::~Graph()
{
}

//static int num = 2;

void Graph::addVertex(AdjListNode* newNode)
{
    vec[newNode->id] = newNode;
}


void Graph::addEdge(int id1, int id2)
{
    push_node_back(vec[id1],vec[id2]);
    push_node_back(vec[id2],vec[id1]);
}


double dist(QPointF p1, QPointF p2)
{
    return sqrt(pow((p1.x()-p2.x()),2)+pow((p1.y()-p2.y()),2));
}

void push_node_back(AdjListNode* &head, AdjListNode* newNode)
{
    AdjListNode* temp = head;
    while (temp->next != nullptr)
    {
        temp = temp->next;
    }
    temp->next = new AdjListNode(newNode->point,newNode->id);
}
