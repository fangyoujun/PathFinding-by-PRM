#include "grid.h"

Grid::Grid()
{

    for (int x = top_left_x; x < max_x; x+=edge)
    {
        for (int y = top_left_y; y < max_y; y+=edge)
        {
            Node* node = new Node();
            GridNode[x/edge][y/edge] = *node;
        }
    }
}

vector<Node> Grid::neighbors(const Node& node)
{
    std::vector<Node> neighbors;
    signed int node_id_x = node.x() / edge;
    signed int node_id_y = node.y() / edge;

    std::vector<vector<int> > Direction = {{1,0},   //left
                                           {1,1},   //left-bottom
                                           {0,1},   //bottom
                                           {-1,1},  //right-bottom
                                           {-1,0},  //right
                                           {-1,-1}, //right-up
                                           {0,-1},  //up
                                           {1,-1}}; //left-up

    for (vector<int> dir : Direction)
    {
        signed int id_x = node_id_x + dir[0];
        signed int id_y = node_id_y + dir[1];
        if (id_x >= 0
            && id_x <= num_col-1
            && id_y >= 0
            && id_y <= num_row-1
            && GridNode[id_x][id_y].walkable)
            neighbors.push_back(GridNode[id_x][id_y]);
     }
    return neighbors;
}

int Grid::cost(Node n1, Node n2)
{
    return std::abs(n1.center().x()-n2.center().x()) +
            std::abs(n1.center().y()-n2.center().y());
}
