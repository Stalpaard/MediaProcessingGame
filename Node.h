#ifndef NODE_H
#define NODE_H
#pragma once

#include "world.h"
#include <math.h>

class Node : public World {

public:
    //  The positie van de node
    int x;
    int y;
    double finalCost;

    // Pointer to the parent
    Node * partentPointer;

    // Constructor
    Node(int px, int py){x = px ; y = py;finalCost=0;}

    //
    void createSuccessors();
    bool isValid(int x  , int y);
    bool isUnblocked(int x , int y);


};

#endif // NODE_H
