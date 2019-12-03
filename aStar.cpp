#include <queue>
#include <unordered_map>
#include "Node.h"
#include "modelworld.h"

#define currPos ((currentNode.y)-1)*w->getCols() + currentNode.x
#define NORTH currPos //HIER BEN IK GEEINDIGD!!!

class Compare
{
public:
    bool operator() (Node n1 , Node n2)
    {
        return n1.finalCost < n2.finalCost ;
    }
};

bool operator == (Node &n1, Node &n2){return n1.x == n2.x && n1.y == n2.y;}
bool operator != (Node &n1, Node &n2){return n1.x != n2.x || n1.y != n2.y;}



class aStar  {
public :

    aStar(ModelWorld * w);
    ModelWorld *w;


    //!!!!!!!!!!!!!!!!!!!!!! CONSIDER USING UNIQUE POINTERS TO NODES INSTEAD OF THE NODES ITSELF !!!!!!!!!!!!!!
    std::priority_queue <Node,std::vector<Node>,Compare> openlist;
    //std::unordered_map <Node> closedlist;  For later
    std::vector <Node> closedlist; // inneficient for now

    std::vector <Node> solution;

    std::vector<Node> runAlgo(int startx, int starty, int endx, int endy);
    double calcHeuristic (int x , int y , int xend , int yend);

};

aStar::aStar(ModelWorld *w)
{
    this->w = w;
}

std::vector<Node> aStar::runAlgo(int startx, int starty, int endx, int endy)
{
    solution.clear();

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

        //if currentNode's x and y are equal to the goalPoint, then
        if(currentNode.x == endx && currentNode.y == endy)
        {
            /* Note: we can traverse through the parents of currentNode
            - push the nodes that are part of the path in to solution*/
            while (currentNode != root)
            {
                solution.push_back(currentNode);
                currentNode = *currentNode.partentPointer;
            }
            //- break from step 3
            return solution;
        }


        // Note: a node has 8 points around it which can be used to create min of 0 and
        //       max of 8 successor
        //for every nearbyPoint around the currentNode do the following

        //NORTH
        if(w->getTiles().at())
        /*1)if this nearbyPoint is in a spot that is illegal such as a wall, then
            - skip to the next nearbyPoint*/

    }

    throw "Destination unreachable";

}



double aStar::calcHeuristic(int x, int y, int xend, int yend)
{
    return( (double) sqrt((x-xend)*(x-xend)+(y-yend)*(y-yend)));
}



