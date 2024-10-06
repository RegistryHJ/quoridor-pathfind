#ifndef BFS_HPP
#define BFS_HPP

#include <queue>
#include <vector>

#include "common/grid_navigator.hpp"
#include "common/position.hpp"

class BFS : public GridNavigator {
public:
  BFS(const std::vector<std::vector<char>> &inputMap)
      : GridNavigator(inputMap) {}

  Position<int> findPath(const Position<int> &start) {
    std::queue<Position<int>> q;

    int distance = 0;
    Position<int>::BFS bfsParams(distance);

    Position<int> startPos(start.x, start.y, bfsParams, {{start.x, start.y}});

    q.push(startPos);
    visited[start.x][start.y] = true;

    while (!q.empty()) {
      Position<int> current = q.front();
      q.pop();

      // 'E'에 도달하면 경로 반환
      if (map[current.x][current.y] == 'E')
        return current;

      // 네 방향 탐색
      for (int i = 0; i < 4; ++i) {
        int nX = current.x + dx[i];
        int nY = current.y + dy[i];

        // 이동 가능한 위치인지 확인
        if (isValidMove(nX, nY)) {
          // 이동 가능한 위치를 큐에 추가 (. 또는 E, 공백인 경우)
          if (map[nX][nY] == '.' || map[nX][nY] == 'E' || map[nX][nY] == ' ') {
            visited[nX][nY] = true;

            int nDistance = current.distance + 1;
            Position<int>::BFS nextBfsParams(nDistance);

            std::vector<std::pair<int, int>> nextPath = current.path;
            nextPath.push_back({nX, nY});

            Position<int> next(nX, nY, nextBfsParams, nextPath);
            q.push(next);
          }
        }
      }
    }

    // 경로를 찾지 못한 경우
    Position<int>::BFS missedBfsParams(-1);
    return Position<int>(-1, -1, missedBfsParams, {});
  }
};

#endif