#ifndef GRID_H
#define GRID_H
#include "node.h"
#include <vector>
#include <QRect>
#include <set>
#include <map>
#include <QGraphicsScene>
#include <QGraphicsItem>

using namespace std;

class Grid
{
public:
    Grid();

    /*edge length of a node*/
    const int edge = 20;

    /*map size*/
    const int top_left_x = 0, top_left_y = 0;
    const int max_x = 1000, max_y = 1000;

    /*taille of the grid*/
    static const int num_col = 50, num_row = 50;

    Node GridNode[num_col][num_row];

    set<Node,std::less<Node> > shortest_path;

    vector<Node> neighbors(const Node& node);

    Node start;
    Node end;

    map<Node, Node> came_from;
    map<Node, int> cost_so_far;
    int cost(Node n1, Node n2);
};

#endif // GRID_H
