#ifndef BFS_HPP
#define BFS_HPP

#include <queue>
#include <vector>

#include "common/grid_navigator.hpp"
#include "common/position.hpp"

class BFS : public GridNavigator {
public:
  BFS(const std::vector<std::vector<char>> &map) : GridNavigator(map) {}

  Position<int> find_path(const Position<int> &start) {
    std::queue<Position<int>> q;

    int distance = 0;
    Position<int>::BFS bfs_params(distance);

    Position<int> start_pos(start.x, start.y, bfs_params, { { start.x, start.y } });

    q.push(start_pos);
    visited[start.x][start.y] = true;

    while (!q.empty()) {
      Position<int> current = q.front();
      q.pop();

      // 'E'에 도달하면 경로 반환
      if (map[current.x][current.y] == 'E') return current;

      // 네 방향 탐색
      for (int i = 0; i < 4; ++i) {
        int next_x = current.x + direction_x[i];
        int next_y = current.y + direction_y[i];

        // 이동 가능한 위치인지 확인
        if (is_valid_move(next_x, next_y)) {
          // 이동 가능한 위치를 큐에 추가 (. 또는 E, 공백인 경우)
          if (map[next_x][next_y] == '.' || map[next_x][next_y] == 'E' || map[next_x][next_y] == ' ') {
            visited[next_x][next_y] = true;

            int next_distance = current.distance + 1;
            Position<int>::BFS next_bfs_params(next_distance);

            std::vector<std::pair<int, int>> next_path = current.path;
            next_path.push_back({ next_x, next_y });

            Position<int> next(next_x, next_y, next_bfs_params, next_path);
            q.push(next);
          }
        }
      }
    }

    // 경로를 찾지 못한 경우
    Position<int>::BFS missed_bfs_params(-1);
    return Position<int>(-1, -1, missed_bfs_params, {});
  }
};

#endif