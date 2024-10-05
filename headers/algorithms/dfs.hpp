#ifndef DFS_HPP
#define DFS_HPP

#include <stack>
#include <vector>

#include "common/grid_navigator.hpp"
#include "common/position.hpp"

class DFS : public GridNavigator {
public:
  DFS(const std::vector<std::vector<char>> &inputMap) : GridNavigator(inputMap) {}

  Position<int> findPath(Position<int> start) {
    std::stack<Position<int>> s;

    // 시작 지점 추가 및 방문 표시
    s.push(start);
    visited[start.x][start.y] = true;

    while (!s.empty()) {
      Position<int> current = s.top();
      s.pop();

      // 'E'에 도달한 경우 경로 반환
      if (map[current.x][current.y] == 'E') return current;

      // 네 방향 탐색
      for (int i = 0; i < 4; ++i) {
        int nX = current.x + dx[i];
        int nY = current.y + dy[i];

        // 이동 가능한 위치인지 확인
        if (isValidMove(nX, nY)) {
          visited[nX][nY] = true;
          Position<int> next = { nX, nY, current.path };
          next.path.push_back({ nX, nY }); // 다음 위치 추가
          s.push(next);                    // 다음 위치를 스택에 추가
        }
      }
    }

    // 경로를 찾지 못한 경우
    return { -1, -1, {} };
  }
};

#endif