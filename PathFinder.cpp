#include "graph.h"
#include <vector>
#include <unistd.h>
#include <queue>
#include <QDebug>

void Astar(Graph* graph, AdjListNode* start, AdjListNode* end, double e)
{
    typedef pair<int, AdjListNode*> weightedNode;
    auto cmp = [](weightedNode n1, weightedNode n2){return n1.first > n2.first;};
    std::priority_queue<weightedNode,vector<weightedNode>, decltype(cmp)> frontier(cmp);

    frontier.push(weightedNode(0,start));

    graph->came_from[start->id] = start->id;
    graph->cost_so_far[start->id] = 0;

    while (!frontier.empty())
    {
        int currId = frontier.top().second->id;
        frontier.pop();

        AdjListNode* head = graph->vec[currId];

        if (head == end)
            break;

        AdjListNode* curr = head->next;

        while (curr != nullptr)
        {
            if (curr == end)
            {
                graph->came_from[end->id] = head->id;
                return;
            }
            int new_cost = graph->cost_so_far[head->id] + e * dist(head->point, curr->point);
            int total_cost = new_cost;

            if (graph->cost_so_far.find(curr->id) == graph->cost_so_far.end() ||
                    new_cost < graph->cost_so_far[curr->id])
            {
                graph->cost_so_far[curr->id] = new_cost;
                graph->came_from[curr->id] = head->id;
                total_cost = new_cost + dist(curr->point, end->point);
                frontier.push(weightedNode(total_cost, curr));
            }
            curr = curr->next;
        }
    }
}
