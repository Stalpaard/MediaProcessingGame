

#include "aStar.h"


inline std::pair<int,int> operator + (const std::pair<int,int>& lhs , const std::pair<int,int> &rhs )
{
    std::pair<int,int> result;
    result.first = lhs.first+rhs.first;
    result.second = lhs.second+rhs.second;
    return result;
}

struct find_by_pos {
    find_by_pos(const std::pair<int,int> & pos) : pos(pos) {}
    bool operator()(const Node * node) {
        return (*node).pos == pos;
    }
private:
    std::pair<int,int> pos;
};




bool operator == (Node &n1, Node &n2){return n1.pos == n2.pos;}
bool operator != (Node &n1, Node &n2){return n1.pos != n2.pos;}


aStar::aStar(std::vector<std::vector<std::shared_ptr<MyTile>>> &tiles)
{
    map = tiles;
}

std::vector<Node> aStar::runAlgo(Node* player, Node* dest)
{


    std::vector<std::pair<int,int>> dirs;
    dirs.emplace_back(std::make_pair(1,0));
    dirs.emplace_back(std::make_pair(-1,0));
    dirs.emplace_back(std::make_pair(0,1));
    dirs.emplace_back(std::make_pair(0,-1));

    std::vector<Node> empty;
        if (isValid((*dest).pos.first, (*dest).pos.second) == false) {
            std::cout << "Destination is an obstacle" << std::endl;
            return empty;
            //Destination is invalid
        }
        if (isDestination((*player).pos.first, (*player).pos.second, (*dest))) {
            std::cout << "You are the destination" << std::endl;
            return empty;
            //You clicked on yourself
        }


        player->fCost = 0;
        player->parent = nullptr;

        openList.insert(player);

        while(!openList.empty())
        {
            auto itNode = openList.begin();
            Node * currentNode = *itNode;
            openList.erase(itNode);


            if((*currentNode).pos==(*dest).pos) // The dest has been found
            {
                while((*currentNode).parent!=nullptr)// Push the solution
                {
                    (*currentNode) = *(*currentNode).parent;
                    solution.push_back(*currentNode);

                }
                return solution;

            }



            for(auto it = std::begin(dirs); it != std::end(dirs); it++) // For each neighbor
            {
                if(isValid((*currentNode).pos.first+it->first,(*currentNode).pos.second+it->second))
                {
                    Node * successorNode = new Node();
                    (*successorNode).pos = (*currentNode).pos + *it;
                    (*successorNode).parent =  currentNode;
                    (*successorNode).gCost = (*currentNode).gCost + map.at((*successorNode).pos.first).at((*successorNode).pos.second)->getValue();
                    (*successorNode).hCost = calculateH((*successorNode).pos.first,(*successorNode).pos.second,(*dest));
                    (*successorNode).fCost = (*successorNode).gCost+(*successorNode).hCost;


                    std::pair<int,int> neigborPos = (*currentNode).pos + *it;
                    float ngCost = (*currentNode).gCost + map.at(neigborPos.first).at(neigborPos.second)->getValue();

                   auto result = std::find_if(openList.begin(), openList.end(),
                                                                  find_by_pos(neigborPos)); //checks if neigbor in openlist
                    if(result != openList.end()) {
                        // we found something now check if better

                        if((*result)->gCost > ngCost) // if neighbor is a better node
                        {
                            openList.erase(result);
                        }
                        else{continue;}

                    }
                    auto smth = std::find_if(closedlist.begin(), closedlist.end(), find_by_pos(neigborPos));
                    // Check if in closedlist
                    if(smth != closedlist.end())
                    {
                        if((*smth)->gCost > ngCost)
                        {// if neighbor is a better node
                            /* v contains x */
                            closedlist.erase(smth);
                        }
                        else{continue;}
                    }

                    openList.insert(successorNode);

                }

            }
            closedlist.emplace_back(currentNode);




        }
        std::cout<<"Goal is unreachable"<<std::endl;
    return empty;
}


inline double aStar::calculateH(int x, int y, Node dest) {
    double H = (sqrt((x - dest.pos.first)*(x - dest.pos.first)
        + (y - dest.pos.second)*(y - dest.pos.second)));
    return H;
}


bool aStar::isValid(int x , int y)
{
    if(x >= 0 && x <= getRows() && y >= 0 && y <= getCols() && map.at(x).at(y)->getValue()!=1.0f){return true;}
    else {return false;}
}


bool aStar::isDestination(int x, int y, Node dest) {
    if (x == dest.pos.first && y == dest.pos.second) {
        return true;
    }
    return false;
}

