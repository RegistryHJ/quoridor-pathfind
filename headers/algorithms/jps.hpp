#ifndef JPS_HPP
#define JPS_HPP

#include <queue>
#include <vector>

#include "common/grid_navigator.hpp"
#include "common/position.hpp"

class JPS : GridNavigator {
public:
  JPS(const std::vector<std::vector<char>> &inputMap) : GridNavigator(inputMap) {}

  Position<int> findPath(Position<int> start, Position<int> end) {
    std::priority_queue<Position<int>> openList;

    start.g = 0;
    start.f = heuristic(start.x, start.y, end.x, end.x);
    start.path.push_back({ start.x, start.y });

    openList.push(start);

    while (!openList.empty()) {
      Position<int> current = openList.top();
      openList.pop();

      if (visited[current.x][current.y]) { continue; }

      visited[current.x][current.y] = true;

      // 목표 위치에 도달했을 때
      if (current.x == end.x && current.y == end.x) { return current; }

      // 상/하/좌/우 방향으로 점프 시도 (대각선 제외)
      for (int i = 0; i < 4; ++i) {
        Position<int> next = jump(current, i);
        if (next.x != -1) {
          next.f = next.g + heuristic(next.x, next.y, end.x, end.x);
          next.path.push_back({ next.x, next.y });
          openList.push(next);
        }
      }
    }

    return { -1, -1, 0, 0, {} }; // 경로를 찾지 못한 경우
  }

private:
  // 강제 이웃 감지 함수 (X축 (대각선 제외))
  bool hasForcedNeighborInX(int nX, int nY, int currentY) const {
    return (nX > 0 && isValidMove(nX - 1, nY) && !isValidMove(nX - 1, currentY)) ||
           (nX < map.size() - 1 && isValidMove(nX + 1, nY) && !isValidMove(nX + 1, currentY));
  }

  // 강제 이웃 감지 함수 (Y축 (대각선 제외))
  bool hasForcedNeighborInY(int nX, int nY, int currentX) const {
    return (nY > 0 && isValidMove(nX, nY - 1) && !isValidMove(currentX, nY - 1)) ||
           (nY < map[0].size() - 1 && isValidMove(nX, nY + 1) && !isValidMove(currentX, nY + 1));
  }

  // 점프 함수
  Position<int> jump(Position<int> current, int direction) {
    int nX = current.x + dx[direction];
    int nY = current.y + dy[direction];

    // 이동 가능 여부 체크
    if (!isValidMove(nX, nY)) {
      return { -1, -1, 0, 0, {} }; // 유효하지 않은 이동
    }

    // 목표에 도달했을 경우
    if (map[nX][nY] == 'E') {
      Position<int> result = { nX, nY, current.g + 1, 0, current.path };
      result.path.push_back({ nX, nY });
      return result;
    }

    // 강제 이웃이 있는 경우 (X축)
    if ((direction == 2 || direction == 3) && hasForcedNeighborInX(nX, nY, current.y)) {
      Position<int> result = { nX, nY, current.g + 1, 0, current.path };
      result.path.push_back({ nX, nY });
      return result;
    }

    // 강제 이웃이 있는 경우 (Y축)
    if ((direction == 0 || direction == 1) && hasForcedNeighborInY(nX, nY, current.x)) {
      Position<int> result = { nX, nY, current.g + 1, 0, current.path };
      result.path.push_back({ nX, nY });
      return result;
    }

    // 현재 위치를 방문 처리
    visited[nX][nY] = true;

    // 계속해서 현재 방향으로 점프
    Position<int> next = jump({ nX, nY, current.g + 1, 0, current.path }, direction);
    if (next.x != -1) { next.path.push_back({ nX, nY }); }
    return next;
  }
};

#endif