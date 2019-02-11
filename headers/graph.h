#ifndef GRAPH_H
#define GRAPH_H
#include <unordered_map>
#include <stdlib.h>
#include <iostream>
#include <list>
#include <vector>
#include <QPoint>
#include <QHash>
#include <QMap>
#include <map>
#include "myscene.h"

using namespace std;

typedef struct AdjListNode
{
    int id;
    QPointF point;
    AdjListNode *next;
    AdjListNode(QPointF p, int i)
    {
        id = i;
        point = p;
        next = nullptr;
    }
} AdjListNode;


class Graph
{
private:
    int numVertex;

public:
    Graph();

    Graph(int num, QPointF startP, QPointF endP);

    ~Graph();

    AdjListNode* start;

    AdjListNode* end;

    vector<AdjListNode*> vec;


    void addVertex(AdjListNode* newNode);
    void addEdge(int id1, int id2);

    map<int, int> came_from;   //both int: AdjListNode id
    map<int, int> cost_so_far; //1st int: AdjListNode id; 2nd int: cost


};

double dist(QPointF p1, QPointF p2);

void push_node_back(AdjListNode* &head, AdjListNode* newNode);



#endif // GRAPH_H
