#ifndef JPS_HPP
#define JPS_HPP

#include <queue>
#include <vector>

#include "common/grid_navigator.hpp"
#include "common/position.hpp"

class JPS : GridNavigator {
public:
  JPS(const std::vector<std::vector<char>> &map) : GridNavigator(map) {}

  Position<int> find_path(const Position<int> &start, const Position<int> &end) {
    std::priority_queue<Position<int>> open_list;

    int g = 0;
    int h = heuristic(start.x, start.y, end.x, end.y);
    int f = 0;
    Position<int>::AStar jps_params(g, h, f);

    Position<int> start_pos(start.x, start.y, jps_params, { { start.x, start.y } });
    open_list.push(start_pos);

    while (!open_list.empty()) {
      Position<int> current = open_list.top();
      open_list.pop();

      if (visited[current.x][current.y]) { continue; }

      visited[current.x][current.y] = true;

      // 목표 위치에 도달했을 때
      if (current.x == end.x && current.y == end.y) { return current; }

      // 네 방향으로 점프 시도 (대각선 제외)
      for (int i = 0; i < 4; ++i) {
        Position<int> next = jump(current, i, end);
        if (next.x != -1) {
          next.f = next.g + heuristic(next.x, next.y, end.x, end.y);
          open_list.push(next);
        }
      }
    }

    // 경로를 찾지 못한 경우
    Position<int>::AStar missed_jps_params(0, 0, 0);
    return Position<int>(-1, -1, missed_jps_params, {}); // 경로를 찾지 못한 경우
  }

private:
  // 강제 이웃 감지 함수 (X축 (대각선 제외))
  bool has_forced_neighbor_in_x(int next_x, int next_y, int current_y) const {
    return (next_x > 0 && is_valid_move(next_x - 1, next_y) && !is_valid_move(next_x - 1, current_y)) ||
           (next_x < map.size() - 1 && is_valid_move(next_x + 1, next_y) && !is_valid_move(next_x + 1, current_y));
  }

  // 강제 이웃 감지 함수 (Y축 (대각선 제외))
  bool has_forced_neighbor_in_y(int next_x, int next_y, int current_x) const {
    return (next_y > 0 && is_valid_move(next_x, next_y - 1) && !is_valid_move(current_x, next_y - 1)) ||
           (next_y < map[0].size() - 1 && is_valid_move(next_x, next_y + 1) && !is_valid_move(current_x, next_y + 1));
  }

  // 점프 함수
  Position<int> jump(const Position<int> &current, int direction, const Position<int> &end) {
    int next_x = current.x + direction_x[direction];
    int next_y = current.y + direction_y[direction];

    // 이동 가능 여부 체크
    if (!is_valid_move(next_x, next_y)) {
      Position<int>::AStar next_jps_params(0, 0, 0);
      return Position<int>(-1, -1, next_jps_params, {}); // 유효하지 않은 이동
    }

    // 목표에 도달했을 경우
    if (map[next_x][next_y] == 'E') {
      std::vector<std::pair<int, int>> new_path = current.path;
      new_path.push_back({ next_x, next_y });
      Position<int>::AStar next_jps_params(current.g + 1, 0, 0);
      return Position<int>(next_x, next_y, next_jps_params, new_path);
    }

    // 강제 이웃이 있는 경우 (X축)
    if ((direction == 2 || direction == 3) && has_forced_neighbor_in_x(next_x, next_y, current.y)) {
      std::vector<std::pair<int, int>> new_path = current.path;
      new_path.push_back({ next_x, next_y });
      Position<int>::AStar next_jps_params(current.g + 1, 0, 0);
      return Position<int>(next_x, next_y, next_jps_params, new_path);
    }

    // 강제 이웃이 있는 경우 (Y축)
    if ((direction == 0 || direction == 1) && has_forced_neighbor_in_y(next_x, next_y, current.x)) {
      std::vector<std::pair<int, int>> new_path = current.path;
      new_path.push_back({ next_x, next_y });
      Position<int>::AStar next_jps_params(current.g + 1, 0, 0);
      return Position<int>(next_x, next_y, next_jps_params, new_path);
    }

    // 현재 위치를 방문 처리
    visited[next_x][next_y] = true;

    // 계속해서 현재 방향으로 점프
    Position<int>::AStar next_jps_params(current.g + 1, 0, 0);
    Position<int> next = jump(Position<int>(next_x, next_y, next_jps_params, current.path), direction, end);
    if (next.x != -1) next.path.push_back({ next_x, next_y });
    return next;
  }
};

#endif