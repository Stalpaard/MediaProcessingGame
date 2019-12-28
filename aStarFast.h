#ifndef ASTARFAST_H
#define ASTARFAST_H

#include <unordered_map>
#include <unordered_set>
#include <array>
#include <vector>
#include <utility>
#include <queue>
#include <tuple>
#include <algorithm>
#include <cstdlib>
#include <math.h>
#include "mytile.h"
#include <iostream>
#include <QElapsedTimer>

struct GridLocation {
  int x, y;
};



template<typename T, typename priority_t>
struct PriorityQueue {
  typedef std::pair<T, priority_t> PQElement;
  std::priority_queue<PQElement, std::vector<PQElement>,
                 std::greater<PQElement>> elements;

  inline bool empty() const {
     return elements.empty();
  }

  inline void put(T item, priority_t priority) {
    elements.emplace(item, priority);
  }

  inline T get() {
    T best_item = elements.top().second;
    elements.pop();
    return best_item;
  }
};


inline bool operator == (GridLocation a, GridLocation b) {
  return a.x == b.x && a.y == b.y;
}

inline bool operator != (GridLocation a, GridLocation b) {
  return !(a == b);
}

inline bool operator < (GridLocation a, GridLocation b) {
  return std::tie(a.x, a.y) < std::tie(b.x, b.y);
}

class aStarFast{
public :
    aStarFast(std::vector<std::shared_ptr<MyTile>> *tiles, int cols , int rows, float stepCost, float hWeight) : map(tiles),cols(cols),rows(rows),stepCost(stepCost),hWeight(hWeight){}

    std::vector<std::shared_ptr<MyTile>> * map;
    int cols,rows;
    int size = cols*rows;
    float stepCost,hWeight;

    std::unordered_map<int,int> came_from;
    std::unordered_map<int,float> cost_so_far;

    inline std::vector<int> neighbors(int id) const {
        std::vector<int> results;

        //UP
        if(id>=cols)//in Bounds
            if(map->at(id-cols)->getValue() != std::numeric_limits<float>::infinity())//passable
                results.push_back(id-cols);
        //DOWN
        if(id<size-(cols+1))
            if(map->at(id+cols)->getValue() != std::numeric_limits<float>::infinity())
                results.push_back(id+cols);
        //LEFT
        if(id%cols!=0)
            if(map->at(id-1)->getValue() != std::numeric_limits<float>::infinity())
                results.push_back(id-1);
        //RIGHT
        if(id%cols!=cols-1)
            if(map->at(id+1)->getValue() != std::numeric_limits<float>::infinity())
                results.push_back(id+1);

        return results;
    }

    inline float heuristic(int s,int ex, int ey) {
        int sx = s%cols;
        int sy = (s-sx)/cols;
      return std::abs(sx - ex) + std::abs(sy - ey);
    }



    inline void a_star_search
      (
       int start,
       int goal
      )
    {
      QElapsedTimer timer;
      timer.start();
      std::vector<bool> seen(size);

          for(int i = 0; i < size; i++)
          {
              seen[i]=false;
          }


      int goalx = goal%cols;
      int goaly = (goal-goalx)/cols;
      PriorityQueue<float, int> frontier;
      frontier.put(0, start);

      came_from[start]=start;
      cost_so_far[start] = 0;

      while (!frontier.empty()) {
        int current = frontier.get();

        if (current == goal) {
            std::cout<<"The search operation took :"<< timer.elapsed()<< "milliseconds"<<std::endl;
            break;
        }

        for (int next : neighbors(current)) {
          float new_cost = cost_so_far[current] + std::abs(map->at(current)->getValue() - map->at(next)->getValue()) + stepCost;
          if (seen[next]==false
              || new_cost < cost_so_far[next]) {
            cost_so_far[next] = new_cost;
            seen[next]=true;
            float priority = new_cost + hWeight*heuristic(next, goalx,goaly);
            frontier.put(priority, next);
            came_from[next] = current;
          }
        }
      }
    }

    inline GridLocation convertIntToGrid (int i)
    {
        GridLocation g;
        g.x = i%cols;
        g.y = (i-g.x)/cols;
        return g;
    }

    inline std::vector<std::pair<int,int>> reconstruct_path(
       int start, int goal,
       std::unordered_map<int, int> came_from
    ) {
      QElapsedTimer timer;
      timer.start();

      std::vector<std::pair<int,int>> path;
      GridLocation gl,strt;
      gl.x = goal%cols;
      gl.y = (goal-gl.x)/cols;
      strt.x = start%cols;
      strt.y = (start-strt.x)/cols;
      int current = goal;
      while (current != start) {
        GridLocation currentg = convertIntToGrid(current);
        path.push_back(std::make_pair(currentg.x,currentg.y));
        current = came_from[current];
      }
      path.push_back(std::make_pair(strt.x,strt.y)); // optional
      std::reverse(path.begin(), path.end());
      std::cout<<"The path reconstruction operation took :"<< timer.elapsed()<< "milliseconds"<<std::endl;
      return path;
    }
};


#endif // ASTARFAST_H
