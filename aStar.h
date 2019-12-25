#ifndef ASTAR_H
#define ASTAR_H
#include <set>
#include <unordered_map>
#include "modelworld.h"
#include <algorithm>
#include "world.h"
#include <math.h>
struct Node
{
    std::pair<int,int> pos;
    const Node * parent;
    float hCost;
    float gCost;
    float fCost;
    Node(int x,int y)
    {
        pos.first = x;
        pos.second = y;
    }
    Node(){}
};

struct APtrComp
{
  bool operator()(const Node* lhs, const Node* rhs) const  { return (lhs)->fCost < (rhs)->fCost; }
};




class aStar : public World{
public :

    aStar(std::vector<std::vector<std::shared_ptr<MyTile>>> &tiles);

    std::vector<std::vector<std::shared_ptr<MyTile>>> map;

    std::vector <Node*> closedlist; // inneficient for now
    std::set<Node*,APtrComp> openList;

    std::vector <Node> solution;

    std::vector<Node> runAlgo(Node* player, Node* dest);
    double calculateH(int x, int y, Node dest);
    bool isValid(int x , int y);
    bool isDestination(int x, int y, Node dest);



};
#endif // ASTAR_H
