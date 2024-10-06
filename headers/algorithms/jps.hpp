#ifndef JPS_HPP
#define JPS_HPP

#include <queue>
#include <vector>

#include "common/grid_navigator.hpp"
#include "common/position.hpp"

class JPS : GridNavigator {
public:
  JPS(const std::vector<std::vector<char>> &inputMap)
      : GridNavigator(inputMap) {}

  Position<int> findPath(const Position<int> &start, const Position<int> &end) {
    std::priority_queue<Position<int>> openList;

    int g = 0;
    int h = heuristic(start.x, start.y, end.x, end.y);
    int f = 0;
    Position<int>::AStar jpsParams(g, h, f);

    Position<int> startPos(start.x, start.y, jpsParams, {{start.x, start.y}});
    openList.push(startPos);

    while (!openList.empty()) {
      Position<int> current = openList.top();
      openList.pop();

      if (visited[current.x][current.y]) {
        continue;
      }

      visited[current.x][current.y] = true;

      // 목표 위치에 도달했을 때
      if (current.x == end.x && current.y == end.y) {
        return current;
      }

      // 네 방향으로 점프 시도 (대각선 제외)
      for (int i = 0; i < 4; ++i) {
        Position<int> next = jump(current, i, end);
        if (next.x != -1) {
          next.f = next.g + heuristic(next.x, next.y, end.x, end.y);
          openList.push(next);
        }
      }
    }

    // 경로를 찾지 못한 경우
    Position<int>::AStar missedJpsParams(0, 0, 0);
    return Position<int>(-1, -1, missedJpsParams, {}); // 경로를 찾지 못한 경우
  }

private:
  // 강제 이웃 감지 함수 (X축 (대각선 제외))
  bool hasForcedNeighborInX(int nX, int nY, int currentY) const {
    return (nX > 0 && isValidMove(nX - 1, nY) &&
            !isValidMove(nX - 1, currentY)) ||
           (nX < map.size() - 1 && isValidMove(nX + 1, nY) &&
            !isValidMove(nX + 1, currentY));
  }

  // 강제 이웃 감지 함수 (Y축 (대각선 제외))
  bool hasForcedNeighborInY(int nX, int nY, int currentX) const {
    return (nY > 0 && isValidMove(nX, nY - 1) &&
            !isValidMove(currentX, nY - 1)) ||
           (nY < map[0].size() - 1 && isValidMove(nX, nY + 1) &&
            !isValidMove(currentX, nY + 1));
  }

  // 점프 함수
  Position<int> jump(const Position<int> &current, int direction,
                     const Position<int> &end) {
    int nX = current.x + dx[direction];
    int nY = current.y + dy[direction];

    // 이동 가능 여부 체크
    if (!isValidMove(nX, nY)) {
      Position<int>::AStar nextJpsParams(0, 0, 0);
      return Position<int>(-1, -1, nextJpsParams, {}); // 유효하지 않은 이동
    }

    // 목표에 도달했을 경우
    if (map[nX][nY] == 'E') {
      std::vector<std::pair<int, int>> newPath = current.path;
      newPath.push_back({nX, nY});
      Position<int>::AStar nextJpsParams(current.g + 1, 0, 0);
      return Position<int>(nX, nY, nextJpsParams, newPath);
    }

    // 강제 이웃이 있는 경우 (X축)
    if ((direction == 2 || direction == 3) &&
        hasForcedNeighborInX(nX, nY, current.y)) {
      std::vector<std::pair<int, int>> newPath = current.path;
      newPath.push_back({nX, nY});
      Position<int>::AStar nextJpsParams(current.g + 1, 0, 0);
      return Position<int>(nX, nY, nextJpsParams, newPath);
    }

    // 강제 이웃이 있는 경우 (Y축)
    if ((direction == 0 || direction == 1) &&
        hasForcedNeighborInY(nX, nY, current.x)) {
      std::vector<std::pair<int, int>> newPath = current.path;
      newPath.push_back({nX, nY});
      Position<int>::AStar nextJpsParams(current.g + 1, 0, 0);
      return Position<int>(nX, nY, nextJpsParams, newPath);
    }

    // 현재 위치를 방문 처리
    visited[nX][nY] = true;

    // 계속해서 현재 방향으로 점프
    Position<int>::AStar nextJpsParams(current.g + 1, 0, 0);
    Position<int> next = jump(
        Position<int>(nX, nY, nextJpsParams, current.path), direction, end);
    if (next.x != -1)
      next.path.push_back({nX, nY});
    return next;
  }
};

#endif