#ifndef ASTAR_HPP
#define ASTAR_HPP

#include <queue>
#include <vector>

#include "common/grid_navigator.hpp"
#include "common/position.hpp"

class AStar : public GridNavigator {
public:
  AStar(const std::vector<std::vector<char>> &map) : GridNavigator(map) {}

  Position<int> findPath(Position<int> start, Position<int> end) {
    std::priority_queue<Position<int>> openList;

    start.g = 0;
    start.f = heuristic(start.x, start.y, end.x, end.y);
    start.path.push_back({ start.x, start.y });

    openList.push(start);

    while (!openList.empty()) {
      Position<int> current = openList.top();
      openList.pop();

      // 이미 방문한 위치인 경우
      if (visited[current.x][current.y]) continue;

      // 방문한 위치로 표시
      visited[current.x][current.y] = true;

      // 목표 위치에 도달했을 때
      if (current.x == end.x && current.y == end.y) return current;

      // 네 방향 탐색
      for (int i = 0; i < 4; ++i) {
        int nX = current.x + dx[i];
        int nY = current.y + dy[i];

        // 이동 가능한 위치인지 확인
        if (isValidMove(nX, nY)) {
          Position<int> next;
          next.x = nX;
          next.y = nY;
          next.g = current.g + 1; // 비용 1로 설정 (맨해튼 거리)
          next.f = next.g + heuristic(nX, nY, end.x, end.y); // f = g + h
          next.path = current.path;                          // 이전 경로 복사
          next.path.push_back({ nX, nY });                   // 다음 위치 추가
          openList.push(next);                               // 다음 위치를 openList에 추가
        }
      }
    }

    return { -1, -1, 0, 0, {} }; // 경로를 찾지 못한 경우
  }
};

#endif