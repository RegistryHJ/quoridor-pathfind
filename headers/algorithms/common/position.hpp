#ifndef POSITION_HPP
#define POSITION_HPP

#include <utility>
#include <vector>

template <typename T> struct Position {
  int x, y;                              // 현재 위치 x, y 좌표
  T g = 0;                               // 현재까지의 비용
  T h = 0;                               // 목표 비용
  T f = 0;                               // 예상 총 비용 (g + h)
  T rhs = 0;                             // 우측 비용 (D* Lite)
  int distance = 0;                      // 시작 위치로부터의 거리 (BFS)
  std::vector<std::pair<int, int>> path; // 이동 경로를 저장하기 위한 벡터

  // 기본 생성자
  Position() = default;

  // 기본 위치 생성자
  Position(int x, int y) : x(x), y(y) {}

  // 생성자 (BFS)
  Position(int x, int y, int distance, const std::vector<std::pair<int, int>> &path)
      : x(x), y(y), distance(distance), path(path) {}

  // 생성자 (DFS)
  Position(int x, int y, const std::vector<std::pair<int, int>> &path) : x(x), y(y), path(path) {}

  // 생성자 (A*, JPS, JPS+, JPS B)
  Position(int x, int y, int g, int f, const std::vector<std::pair<int, int>> &path)
      : x(x), y(y), g(g), f(f), path(path) {}

  // // 생성자 (D* Lite)
  // Position(int x, int y, double g, double rhs) : x(x), y(y), g(g), rhs(rhs) {}

  // 연산자 함수 (A*, D* Lite, JPS, JPS+, JPS B)
  bool operator<(const Position &other) const {
    return f > other.f; // 최소 힙을 위해 비교 연산자 정의
  }
};

#endif