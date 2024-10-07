#ifndef ASTAR_HPP
#define ASTAR_HPP

#include <queue>
#include <vector>

#include "common/grid_navigator.hpp"
#include "common/position.hpp"

class AStar : public GridNavigator {
public:
  AStar(const std::vector<std::vector<char>> &map) : GridNavigator(map) {}

  Position<int> find_path(const Position<int> &start, const Position<int> &end) {
    std::priority_queue<Position<int>> open_list;

    int g = 0;
    int h = heuristic(start.x, start.y, end.x, end.y);
    int f = g + h;
    Position<int>::AStar astar_params(g, h, f);

    Position<int> start_pos(start.x, start.y, astar_params, { { start.x, start.y } });
    open_list.push(start_pos);

    while (!open_list.empty()) {
      Position<int> current = open_list.top();
      open_list.pop();

      // 이미 방문한 위치인 경우
      if (visited[current.x][current.y]) continue;

      // 방문한 위치로 표시
      visited[current.x][current.y] = true;

      // 목표 위치에 도달했을 때
      if (current.x == end.x && current.y == end.y) return current;

      // 네 방향 탐색
      for (int i = 0; i < 4; ++i) {
        int next_x = current.x + direction_x[i];
        int next_y = current.y + direction_y[i];

        // 이동 가능한 위치인지 확인
        if (is_valid_move(next_x, next_y)) {
          int next_g = current.g + 1;
          int next_h = heuristic(next_x, next_y, end.x, end.y);
          int next_f = next_g + next_h;
          Position<int>::AStar next_astar_params(next_g, next_h, next_f);

          std::vector<std::pair<int, int>> next_path = current.path;
          next_path.push_back({ next_x, next_y });

          Position<int> next(next_x, next_y, next_astar_params, next_path);
          open_list.push(next);
        }
      }
    }

    // 경로를 찾지 못한 경우
    Position<int>::AStar missed_astar_params(0, 0, 0);
    return Position<int>(-1, -1, missed_astar_params, {});
  }
};

#endif