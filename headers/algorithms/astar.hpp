#ifndef ASTAR_HPP
#define ASTAR_HPP

#include <queue>
#include <vector>

#include "common/grid_navigator.hpp"
#include "common/position.hpp"

class AStar : public GridNavigator {
public:
  AStar(const std::vector<std::vector<char>> &map) : GridNavigator(map) {}

  Position<int> findPath(const Position<int> &start, const Position<int> &end) {
    std::priority_queue<Position<int>> openList;

    int g = 0;
    int h = heuristic(start.x, start.y, end.x, end.y);
    int f = g + h;
    Position<int>::AStar astarParams(g, h, f);

    Position<int> startPos(start.x, start.y, astarParams, {{start.x, start.y}});
    openList.push(startPos);

    while (!openList.empty()) {
      Position<int> current = openList.top();
      openList.pop();

      // 이미 방문한 위치인 경우
      if (visited[current.x][current.y])
        continue;

      // 방문한 위치로 표시
      visited[current.x][current.y] = true;

      // 목표 위치에 도달했을 때
      if (current.x == end.x && current.y == end.y)
        return current;

      // 네 방향 탐색
      for (int i = 0; i < 4; ++i) {
        int nX = current.x + dx[i];
        int nY = current.y + dy[i];

        // 이동 가능한 위치인지 확인
        if (isValidMove(nX, nY)) {
          int nG = current.g + 1;
          int nH = heuristic(nX, nY, end.x, end.y);
          int nF = nG + nH;
          Position<int>::AStar nextAStarParams(nG, nH, nF);

          std::vector<std::pair<int, int>> nextPath = current.path;
          nextPath.push_back({nX, nY});

          Position<int> next(nX, nY, nextAStarParams, nextPath);
          openList.push(next);
        }
      }
    }

    // 경로를 찾지 못한 경우
    Position<int>::AStar missedAStarParams(0, 0, 0);
    return Position<int>(-1, -1, missedAStarParams, {});
  }
};

#endif