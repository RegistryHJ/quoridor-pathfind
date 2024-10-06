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
  DStarLite(const std::vector<std::vector<char>> &input_map,
            const Position<double> &start, const Position<double> &end)
      : GridNavigator(input_map), start(start), end(end) {
    int rows = map.size();
    int cols = map[0].size();
    gValue = std::vector<std::vector<double>>(
        rows,
        std::vector<double>(cols, std::numeric_limits<double>::infinity()));
    rhsValue = std::vector<std::vector<double>>(
        rows,
        std::vector<double>(cols, std::numeric_limits<double>::infinity()));
    visited =
        std::vector<std::vector<bool>>(rows, std::vector<bool>(cols, false));

    rhsValue[end.x][end.y] = 0;

    double g = gValue[end.x][end.y];
    double rhs = rhsValue[end.x][end.y];
    std::array<double, 2> key = calculateKey({end.x, end.y});
    Position<double>::DStarLite dstarLiteParams{g, rhs, key};
    openList.push(Position<double>(end.x, end.y, dstarLiteParams));
  }

  void computeShortestPath() {
    while (!openList.empty()) {
      Position<double> current = openList.top();
      openList.pop();

      if (visited[current.x][current.y])
        continue;
      visited[current.x][current.y] = true;

      if (gValue[current.x][current.y] > rhsValue[current.x][current.y]) {
        gValue[current.x][current.y] = rhsValue[current.x][current.y];

        for (int i = 0; i < 4; ++i) {
          int nX = current.x + dx[i];
          int nY = current.y + dy[i];
          if (isValidMove(nX, nY))
            updateVertex({nX, nY});
        }
      } else {
        gValue[current.x][current.y] = std::numeric_limits<double>::infinity();
        updateVertex(current);

        for (int i = 0; i < 4; ++i) {
          int nX = current.x + dx[i];
          int nY = current.y + dy[i];
          if (isValidMove(nX, nY))
            updateVertex({nX, nY});
        }
      }
    }
  }

  std::vector<std::pair<int, int>> findPath() {
    std::vector<std::pair<int, int>> path;
    Position<double> current = start;

    while (!(current.x == end.x && current.y == end.y)) {
      path.push_back({current.x, current.y});
      double min_cost = std::numeric_limits<double>::infinity();
      Position<double> next = current;

      for (int i = 0; i < 4; ++i) {
        int nX = current.x + dx[i];
        int nY = current.y + dy[i];
        if (isValidMove(nX, nY) && gValue[nX][nY] < min_cost) {
          min_cost = gValue[nX][nY];

          double nG = gValue[nX][nY];
          double nRhs = rhsValue[nX][nY];
          std::array<double, 2> nKey = calculateKey({nX, nY});
          Position<double>::DStarLite nextDStarLiteParams(nG, nRhs, nKey);

          next = Position<double>(nX, nY, nextDStarLiteParams);
        }
      }
      if (next.x == current.x && current.y == next.y) {
        std::cout << "No path to the end found." << std::endl;
        return {};
      }

      current = next;
    }
    path.push_back({end.x, end.y});
    return path;
  }

private:
  Position<double> start;
  Position<double> end;

  std::vector<std::vector<double>> gValue;
  std::vector<std::vector<double>> rhsValue;

  std::priority_queue<Position<double>, std::vector<Position<double>>,
                      std::greater<Position<double>>>
      openList;

  std::array<double, 2> calculateKey(const Position<double> &s) {
    double min_cost = std::min(gValue[s.x][s.y], rhsValue[s.x][s.y]);
    return {min_cost + heuristic(s.x, s.y, end.x, end.y), min_cost};
  }

  bool isValidMove(int x, int y) const override {
    return (x >= 0 && x < map.size() && y >= 0 && y < map[0].size() &&
            map[x][y] != '+' && map[x][y] != '-' && map[x][y] != '|');
  }

  void updateVertex(Position<double> u) {
    if (u.x != end.x || u.y != end.y) {
      double min_rhs = std::numeric_limits<double>::infinity();
      for (int i = 0; i < 4; ++i) {
        int nX = u.x + dx[i];
        int nY = u.y + dy[i];
        if (isValidMove(nX, nY)) {
          min_rhs = std::min(min_rhs, gValue[nX][nY] + 1);
        }
      }
      rhsValue[u.x][u.y] = min_rhs;
    }

    if (gValue[u.x][u.y] != rhsValue[u.x][u.y]) {
      u.key = calculateKey(u);
      u.g = gValue[u.x][u.y];
      u.rhs = rhsValue[u.x][u.y];
      openList.push(u);
    }
  }
};

#endif