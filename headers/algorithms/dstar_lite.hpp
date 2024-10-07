#ifndef DSTAR_LITE_HPP
#define DSTAR_LITE_HPP

#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

#include "common/grid_navigator.hpp"
#include "common/position.hpp"

class DStarLite : public GridNavigator {
public:
  DStarLite(const std::vector<std::vector<char>> &map, const Position<double> &start, const Position<double> &end)
    : GridNavigator(map), start(start), end(end) {
    int rows = map.size();
    int cols = map[0].size();
    g_value =
      std::vector<std::vector<double>>(rows, std::vector<double>(cols, std::numeric_limits<double>::infinity()));
    rhs_value =
      std::vector<std::vector<double>>(rows, std::vector<double>(cols, std::numeric_limits<double>::infinity()));
    visited = std::vector<std::vector<bool>>(rows, std::vector<bool>(cols, false));

    rhs_value[end.x][end.y] = 0;

    double g = g_value[end.x][end.y];
    double rhs = rhs_value[end.x][end.y];
    std::array<double, 2> key = calculate_key({ end.x, end.y });
    Position<double>::DStarLite dstar_lite_params{ g, rhs, key };
    open_list.push(Position<double>(end.x, end.y, dstar_lite_params));
  }

  void compute_shortest_path() {
    while (!open_list.empty()) {
      Position<double> current = open_list.top();
      open_list.pop();

      if (visited[current.x][current.y]) continue;
      visited[current.x][current.y] = true;

      if (g_value[current.x][current.y] > rhs_value[current.x][current.y]) {
        g_value[current.x][current.y] = rhs_value[current.x][current.y];

        for (int i = 0; i < 4; ++i) {
          int next_x = current.x + direction_x[i];
          int next_y = current.y + direction_y[i];
          if (is_valid_move(next_x, next_y)) update_vertex({ next_x, next_y });
        }
      } else {
        g_value[current.x][current.y] = std::numeric_limits<double>::infinity();
        update_vertex(current);

        for (int i = 0; i < 4; ++i) {
          int next_x = current.x + direction_x[i];
          int next_y = current.y + direction_y[i];
          if (is_valid_move(next_x, next_y)) update_vertex({ next_x, next_y });
        }
      }
    }
  }

  std::vector<std::pair<int, int>> find_path() {
    std::vector<std::pair<int, int>> path;
    Position<double> current = start;

    while (!(current.x == end.x && current.y == end.y)) {
      path.push_back({ current.x, current.y });
      double min_cost = std::numeric_limits<double>::infinity();
      Position<double> next = current;

      for (int i = 0; i < 4; ++i) {
        int next_x = current.x + direction_x[i];
        int next_y = current.y + direction_y[i];
        if (is_valid_move(next_x, next_y) && g_value[next_x][next_y] < min_cost) {
          min_cost = g_value[next_x][next_y];

          double next_g = g_value[next_x][next_y];
          double next_rhs = rhs_value[next_x][next_y];
          std::array<double, 2> next_key = calculate_key({ next_x, next_y });
          Position<double>::DStarLite next_dstar_lite_params(next_g, next_rhs, next_key);

          next = Position<double>(next_x, next_y, next_dstar_lite_params);
        }
      }
      if (next.x == current.x && current.y == next.y) {
        std::cout << "No path to the end found." << std::endl;
        return {};
      }

      current = next;
    }
    path.push_back({ end.x, end.y });
    return path;
  }

private:
  Position<double> start;
  Position<double> end;

  std::vector<std::vector<double>> g_value;
  std::vector<std::vector<double>> rhs_value;

  std::priority_queue<Position<double>, std::vector<Position<double>>, std::greater<Position<double>>> open_list;

  std::array<double, 2> calculate_key(const Position<double> &s) {
    double min_cost = std::min(g_value[s.x][s.y], rhs_value[s.x][s.y]);
    return { min_cost + heuristic(s.x, s.y, end.x, end.y), min_cost };
  }

  bool is_valid_move(int x, int y) const override {
    return (x >= 0 && x < map.size() && y >= 0 && y < map[0].size() && map[x][y] != '+' && map[x][y] != '-' &&
            map[x][y] != '|');
  }

  void update_vertex(Position<double> u) {
    if (u.x != end.x || u.y != end.y) {
      double min_rhs = std::numeric_limits<double>::infinity();
      for (int i = 0; i < 4; ++i) {
        int next_x = u.x + direction_x[i];
        int next_y = u.y + direction_y[i];
        if (is_valid_move(next_x, next_y)) { min_rhs = std::min(min_rhs, g_value[next_x][next_y] + 1); }
      }
      rhs_value[u.x][u.y] = min_rhs;
    }

    if (g_value[u.x][u.y] != rhs_value[u.x][u.y]) {
      u.g = g_value[u.x][u.y];
      u.rhs = rhs_value[u.x][u.y];
      u.key = calculate_key(u);
      open_list.push(u);
    }
  }
};

#endif