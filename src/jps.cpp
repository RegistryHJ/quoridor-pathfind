#include <chrono>
#include <iostream>
#include <vector>

#include "../headers/algorithms/jps.hpp"
#include "../headers/maps/map_10.hpp"

using namespace std;
using namespace chrono;

int main() {
  // 시작 위치 'S'의 x, y 좌표를 -1로 초기화
  Position<int> start;
  start.x = -1;
  start.y = -1;

  // 끝 위치 'E'의 x, y 좌표를 -1로 초기화
  Position<int> end;
  end.x = -1;
  end.y = -1;

  // 맵을 순회하면서 'S'와 'E'를 찾음
  for (int i = 0; i < map.size(); ++i) {
    for (int j = 0; j < map[i].size(); ++j) {
      if (map[i][j] == 'S') {
        start.x = i;
        start.y = j;
        start.g = 0;
        start.path = { { i, j } }; // 시작 위치로 경로 초기화
      }
      if (map[i][j] == 'E') end = { i, j }; // 끝 위치 'E'를 찾음
    }
  }

  // 시작 위치 'S'와 끝 위치 'E'를 찾지 못한 경우
  if (start.x == -1 || end.x == -1) {
    cout << "Starting point 'S' or end 'E' not found." << endl;
    return 1;
  }

  // JPS 알고리즘을 사용하기 위해 JPS 객체 생성
  JPS jps(map);

  // 시작 시간 기록
  auto start_time = high_resolution_clock::now();

  // JPS 알고리즘을 사용하여 경로 찾기
  Position<int> result = jps.findPath(start, end);

  // 종료 시간 기록
  auto end_time = high_resolution_clock::now();

  // 경과 시간 계산
  duration<double, milli> elapsed_time = end_time - start_time;

  // 경로를 찾은 경우
  int step_count = 0;
  if (result.x != -1) {
    // 경로에 '*' 표시하고 실제 이동한 횟수 계산
    for (const auto &pos : result.path) {
      if (map[pos.first][pos.second] == '.') {
        map[pos.first][pos.second] = '*';
        step_count++;
      }
    }

    // 이동 횟수 출력
    cout << "Reached an 'E' in " << step_count << " steps." << endl;

    // 경로가 표시된 맵 출력
    for (const auto &row : map) {
      for (const auto &cell : row) { cout << cell; }
      cout << endl;
    }
  } else
    cout << "No path to the end found." << endl;

  // 경과 시간 출력
  cout << "Time taken: " << elapsed_time.count() << " ms" << endl;

  return 0;
}