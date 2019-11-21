
#include "Node.h"



void Node::createSuccessors()
{
    /*
     * if(getTile(x-1,y)< valuefornotpassable
     *
     *
     * */
}

bool Node::isValid(int x , int y)
{
    if(x >= 0 && x <= getRows() && y >= 0 && y <= getCols() ){return true;}
    else {return false;}
}

/*bool Node::isUnblocked(int x, int y)
{
    if(getTiles())
}*/



