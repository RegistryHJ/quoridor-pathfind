#ifndef POSITION_HPP
#define POSITION_HPP

#include <array>
#include <utility>
#include <vector>

template <typename T> struct Position {
  int x, y;                              // 현재 위치 x, y 좌표
  std::vector<std::pair<int, int>> path; // 이동 경로를 저장하기 위한 벡터

  // 알고리즘별 멤버 변수
  int distance = 0;              // 시작 위치로부터의 거리 (BFS)
  T g = 0;                       // 현재까지의 비용 (A*, D* Lite)
  T h = 0;                       // 목표 비용 (A*)
  T f = 0;                       // 예상 총 비용 (A*)
  T rhs = 0;                     // 우측 비용 (D* Lite)
  std::array<T, 2> key = {0, 0}; // D* Lite 알고리즘에서 사용하는 키

  struct BFS {
    int distance = 0;
    explicit BFS(int distance) : distance(distance) {}
  };

  struct DFS {
    explicit DFS() {}
  };

  struct AStar {
    int g = 0;
    int h = 0;
    int f = 0;
    explicit AStar(int g, int h, int f) : g(g), h(h), f(f) {}
  };

  struct DStarLite {
    double g = 0;
    double rhs = 0;
    std::array<double, 2> key = {0, 0};
    explicit DStarLite(double g, double rhs, std::array<double, 2> key)
        : g(g), rhs(rhs), key(key) {}
  };

  // 기본 생성자
  Position() = default;

  // 기본 위치 생성자
  Position(int x, int y) : x(x), y(y) {}

  // 생성자 (BFS)
  Position(int x, int y, BFS bfs,
           const std::vector<std::pair<int, int>> &path = {})
      : x(x), y(y), distance(bfs.distance), path(path) {}

  // 생성자 (DFS)
  Position(int x, int y, DFS dfs,
           const std::vector<std::pair<int, int>> &path = {})
      : x(x), y(y), path(path) {}

  // 생성자 (A* 계열)
  Position(int x, int y, AStar astar,
           const std::vector<std::pair<int, int>> &path = {})
      : x(x), y(y), g(astar.g), h(astar.h), f(astar.f), path(path) {}

  // 생성자 (D* Lite)
  Position(int x, int y, DStarLite dstar)
      : x(x), y(y), g(dstar.g), rhs(dstar.rhs), key(dstar.key) {}

  // 연산자 함수 (A* 계열)
  bool operator<(const Position &other) const {
    return f > other.f; // 최소 힙을 위해 비교 연산자 정의
  }

  // 연산자 함수 (D* Lite)
  bool operator>(const Position &other) const {
    if (key[0] == other.key[0])
      return key[1] > other.key[1];
    return key[0] > other.key[0];
  }
};

#endif