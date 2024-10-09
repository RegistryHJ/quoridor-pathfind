#include <chrono>
#include <iostream>
#include <limits> // std::numeric_limits 사용
#include <vector>

#include "../headers/algorithms/bfs.hpp"
#include "../headers/maps/map_15.hpp"

using namespace std;
using namespace chrono;

int main() {
  // 시작 위치 'S'의 x, y 좌표를 -1로, 거리를 0으로 초기화
  Position<int> start;
  start.x = -1;
  start.y = -1;
  start.distance = 0;

  // 끝 위치 'E'의 x, y 좌표를 -1로 초기화
  Position<int> end;
  end.x = -1;
  end.y = -1;

  // 여러 개의 끝 위치 'E'를 저장하는 벡터
  vector<Position<int>> ends;

  // 맵을 순회하면서 'S'와 'E'를 찾음
  for (int i = 0; i < map.size(); ++i) {
    for (int j = 0; j < map[i].size(); ++j) {
      if (map[i][j] == 'S') {
        start.x = i;
        start.y = j;
        start.g = 0;
        start.path = { { i, j } }; // 시작 위치로 경로 초기화
      }
      if (map[i][j] == 'E') ends.push_back({ i, j }); // 끝 위치 'E'를 찾음
    }
  }

  int min_steps = numeric_limits<int>::max(); // 가장 작은 경로의 이동 횟수
  vector<vector<char>> best_map_copy; // 가장 짧은 경로의 맵 복사본
  double best_time = 0.0; // 가장 짧은 경로의 시간

  // 각 'E' 위치에 대해 경로 찾기
  for (const auto &end : ends) {
    vector<vector<char>> map_copy = map;

    // BFS 알고리즘을 사용하기 위해 BFS 객체 생성
    BFS bfs(map_copy);

    // 시작 시간 기록
    auto start_time = high_resolution_clock::now();

    // BFS 알고리즘을 사용하여 경로 찾기
    Position<int> result = bfs.find_path(start);

    // 종료 시간 기록
    auto end_time = high_resolution_clock::now();

    // 경과 시간 계산
    duration<double, milli> elapsed_time = end_time - start_time;

    // 경로를 찾은 경우
    int step_count = 0;
    if (result.x != -1) {
      // 경로에 '*' 표시하고 실제 이동한 횟수 계산
      for (const auto &pos : result.path) {
        if (map_copy[pos.first][pos.second] == '.' || map_copy[pos.first][pos.second] == 'E') {
          map_copy[pos.first][pos.second] = '*';
          step_count++;
        }
      }

      // 가장 작은 step_count와 비교하여 업데이트
      if (step_count < min_steps) {
        min_steps = step_count;
        best_map_copy = map_copy; // 가장 짧은 경로의 맵 복사본 저장
        best_time = elapsed_time.count(); // 경과 시간 저장
      }
    }
  }

  // 가장 작은 step_count를 가진 경로 출력
  if (min_steps < numeric_limits<int>::max()) {
    cout << "Reached an 'E' in " << min_steps << " steps." << endl;

    // 경로가 표시된 맵 출력
    for (const auto &row : best_map_copy) {
      for (const auto &cell : row) cout << cell;
      cout << endl;
    }

    // 경과 시간 출력
    cout << "Time taken: " << best_time << " ms" << endl;
  } else {
    cout << "No path to the end found." << endl;
  }

  return 0;
}