#ifndef DFS_HPP
#define DFS_HPP

#include <stack>
#include <vector>

#include "common/grid_navigator.hpp"
#include "common/position.hpp"

class DFS : public GridNavigator {
public:
  DFS(const std::vector<std::vector<char>> &map) : GridNavigator(map) {}

  Position<int> find_path(const Position<int> &start) {
    std::stack<Position<int>> s;

    Position<int>::DFS dfs_params;

    // 시작 지점 추가 및 방문 표시
    Position<int> start_pos(start.x, start.y, dfs_params, { { start.x, start.y } });
    s.push(start_pos);
    visited[start.x][start.y] = true;

    while (!s.empty()) {
      Position<int> current = s.top();
      s.pop();

      // 'E'에 도달한 경우 경로 반환
      if (map[current.x][current.y] == 'E') return current;

      // 네 방향 탐색
      for (int i = 0; i < 4; ++i) {
        int next_x = current.x + direction_x[i];
        int next_y = current.y + direction_y[i];

        // 이동 가능한 위치인지 확인
        if (is_valid_move(next_x, next_y)) {
          visited[next_x][next_y] = true;

          Position<int>::DFS next_dfs_params;

          std::vector<std::pair<int, int>> next_path = current.path;
          next_path.push_back({ next_x, next_y });

          Position<int> next(next_x, next_y, next_dfs_params, next_path);
          s.push(next); // 다음 위치를 스택에 추가
        }
      }
    }

    // 경로를 찾지 못한 경우
    Position<int>::DFS missed_dfs_params;
    return Position<int>(-1, -1, missed_dfs_params, {});
  }
};

#endif