#ifndef BFS_HPP
#define BFS_HPP

#include <queue>
#include <vector>

#include "common/grid_navigator.hpp"
#include "common/position.hpp"

class BFS : public GridNavigator {
public:
  BFS(const std::vector<std::vector<char>> &inputMap) : GridNavigator(inputMap) {}

  Position<int> findPath(Position<int> start) {
    std::queue<Position<int>> q;

    q.push(start);
    visited[start.x][start.y] = true;

    while (!q.empty()) {
      Position<int> current = q.front();
      q.pop();

      // 'E'에 도달하면 경로 반환
      if (map[current.x][current.y] == 'E') return current;

      // 네 방향 탐색
      for (int i = 0; i < 4; ++i) {
        int nX = current.x + dx[i];
        int nY = current.y + dy[i];

        // 이동 가능한 위치인지 확인
        if (isValidMove(nX, nY)) {
          // 이동 가능한 위치를 큐에 추가 (. 또는 E, 공백인 경우)
          if (map[nX][nY] == '.' || map[nX][nY] == 'E' || map[nX][nY] == ' ') {
            visited[nX][nY] = true;
            Position<int> next = { nX, nY, current.distance + 1, current.path };
            next.path.push_back({ nX, nY }); // 다음 위치 추가
            q.push(next);                    // 다음 위치를 큐에 추가
          }
        }
      }
    }

    return { -1, -1, -1, {} }; // 경로를 찾지 못한 경우
  }
};

#endif