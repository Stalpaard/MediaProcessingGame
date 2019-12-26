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
#include "modelworld.h"


struct GridLocation {
  int x, y;
};

namespace std {
/* implement hash function so we can put GridLocation into an unordered_set */
template <> struct hash<GridLocation> {
  typedef GridLocation argument_type;
  typedef std::size_t result_type;
  std::size_t operator()(const GridLocation& id) const noexcept {
    return std::hash<int>()(id.x ^ (id.y << 4));
  }
};
}

template<typename T, typename priority_t>
struct PriorityQueue {
  typedef std::pair<priority_t, T> PQElement;
  std::priority_queue<PQElement, std::vector<PQElement>,
                 std::greater<PQElement>> elements;

  inline bool empty() const {
     return elements.empty();
  }

  inline void put(T item, priority_t priority) {
    elements.emplace(priority, item);
  }

  T get() {
    T best_item = elements.top().second;
    elements.pop();
    return best_item;
  }
};


bool operator == (GridLocation a, GridLocation b) {
  return a.x == b.x && a.y == b.y;
}

bool operator != (GridLocation a, GridLocation b) {
  return !(a == b);
}

bool operator < (GridLocation a, GridLocation b) {
  return std::tie(a.x, a.y) < std::tie(b.x, b.y);
}

class aStarFast{
public :
    aStarFast(std::vector<std::vector<std::shared_ptr<MyTile>>> tiles, int cols , int rows) : map(tiles),cols(cols),rows(rows){}

    std::vector<std::vector<std::shared_ptr<MyTile>>> map;
    int cols,rows;
    std::unordered_map<GridLocation, GridLocation> came_from;
    std::unordered_map<GridLocation, double> cost_so_far;

    bool in_bounds(GridLocation id) const {
        return 0 <= id.x && id.x < cols
            && 0 <= id.y && id.y < rows;
      }

    bool passable(GridLocation id) const {
        return map.at(id.y).at(id.x)->getValue() != std::numeric_limits<float>::infinity();
      }

    std::vector<GridLocation> neighbors(GridLocation id) const {
        std::vector<GridLocation> results;

        for (GridLocation dir : DIRS) {
          GridLocation next{id.x + dir.x, id.y + dir.y};
          if (in_bounds(next) && passable(next)) {
            results.push_back(next);
          }
        }
        return results;
      }

    std::array<GridLocation, 4> DIRS =
      {GridLocation{1, 0}, GridLocation{0, -1}, GridLocation{-1, 0}, GridLocation{0, 1}};

    inline double heuristic(GridLocation a, GridLocation b) {
      return std::abs(a.x - b.x) + std::abs(a.y - b.y);
    }



    void a_star_search
      (
       GridLocation start,
       GridLocation goal
      )
    {
      PriorityQueue<GridLocation, double> frontier;
      frontier.put(start, 0);

      came_from[start] = start;
      cost_so_far[start] = 0;

      while (!frontier.empty()) {
        GridLocation current = frontier.get();

        if (current == goal) {
          break;
        }

        for (GridLocation next : neighbors(current)) {
          float new_cost = cost_so_far[current] + map.at(next.y).at(next.x)->getValue();
          if (cost_so_far.find(next) == cost_so_far.end()
              || new_cost < cost_so_far[next]) {
            cost_so_far[next] = new_cost;
            float priority = new_cost + heuristic(next, goal);
            frontier.put(next, priority);
            came_from[next] = current;
          }
        }
      }
    }


    std::vector<std::pair<int,int>> reconstruct_path(
       GridLocation start, GridLocation goal,
       std::unordered_map<GridLocation, GridLocation> came_from
    ) {
      std::vector<std::pair<int,int>> path;
      GridLocation current = goal;
      while (current != start) {
        path.push_back(std::make_pair(current.x,current.y));
        current = came_from[current];
      }
      path.push_back(std::make_pair(start.x,start.y)); // optional
      std::reverse(path.begin(), path.end());
      return path;
    }

};


#endif // ASTARFAST_H
