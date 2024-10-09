#ifndef DFS_HPP
#define DFS_HPP

#include <vector>

#include "common/grid_navigator.hpp"
#include "common/position.hpp"

class DFS : public GridNavigator {
public:
  DFS(const std::vector<std::vector<char>> &map) : GridNavigator(map) {
    // 방문 기록 배열 초기화
    visited = std::vector<std::vector<bool>>(map.size(), std::vector<bool>(map[0].size(), false));
  }

  Position<int> find_path(const Position<int> &start) {
    Position<int>::DFS dfs_params;
    std::vector<std::pair<int, int>> path = { { start.x, start.y } };

    // 시작 위치를 방문한 상태로 설정하고 재귀 호출 시작
    visited[start.x][start.y] = true;
    return dfs_recursive(start.x, start.y, path);
  }

private:
  Position<int> dfs_recursive(int x, int y, std::vector<std::pair<int, int>> &path) {
    // 도착 지점 'E'에 도달한 경우 현재 경로를 반환
    if (map[x][y] == 'E') {
      Position<int>::DFS dfs_params;
      return Position<int>(x, y, dfs_params, path);
    }

    // 네 방향으로 탐색
    for (int i = 0; i < 4; ++i) {
      int next_x = x + direction_x[i];
      int next_y = y + direction_y[i];

      // 유효한 이동인지 확인
      if (is_valid_move(next_x, next_y) && !visited[next_x][next_y]) {
        visited[next_x][next_y] = true; // 방문 처리
        path.push_back({ next_x, next_y }); // 경로에 추가

        // 재귀적으로 다음 위치 탐색
        Position<int> result = dfs_recursive(next_x, next_y, path);
        if (result.x != -1 && result.y != -1) {
          return result; // 경로를 찾은 경우 바로 반환
        }

        // 경로가 유효하지 않다면 경로에서 제거
        path.pop_back();
      }
    }

    // 경로를 찾지 못한 경우 (-1, -1 반환)
    Position<int>::DFS dfs_params;
    return Position<int>(-1, -1, dfs_params, {});
  }

  std::vector<std::vector<bool>> visited;
};

#endif
