#include <queue>
#include <unordered_map>
#include "Node.h"


class Compare
{
public:
    bool operator() (Node n1 , Node n2)
    {
        return n1.finalCost < n2.finalCost ;
    }
};


class aStar {
public :

    //!!!!!!!!!!!!!!!!!!!!!! CONSIDER USING UNIQUE POINTERS TO NODES INSTEAD OF THE NODES ITSELF !!!!!!!!!!!!!!
    std::priority_queue <Node,std::vector<Node>,Compare> openlist;
    //std::unordered_map <Node> closedlist;  For later
    std::vector <Node> closedlist; // inneficient for now

    void runAlgo(int startx, int starty, int endx, int endy);
    double calcHeuristic (int x , int y , int xend , int yend);

};

void aStar::runAlgo(int startx, int starty, int endx, int endy)
{
    // Create root node
    Node root = Node(startx,starty);
    root.partentPointer = nullptr;
    root.finalCost = 0 + calcHeuristic(root.x , root.y , endx , endy);

    // Push root into openlist
    openlist.push(root);

    // main loop
    while(!openlist.empty())
    {
        // pop the node with the best finalCost from open and assign it to currentNode
        Node currentNode = openlist.top();
        openlist.pop();
    }

}

double aStar::calcHeuristic(int x, int y, int xend, int yend)
{
    return( (double) sqrt((x-xend)*(x-xend)+(y-yend)*(y-yend)));
}



