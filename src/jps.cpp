#include <chrono>
#include <iostream>
#include <vector>

#include "../headers/algorithms/jps.hpp"
#include "../headers/maps/map_15.hpp"

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

  // 각 'E' 위치에 대해 경로 찾기
  for (const auto end : ends) {
    vector<vector<char>> map_copy = map;

    // JPS 알고리즘을 사용하기 위해 JPS 객체 생성
    JPS jps(map_copy);

    // 시작 시간 기록
    auto start_time = high_resolution_clock::now();

    // 종료 시간 기록
    auto end_time = high_resolution_clock::now();

    // 경과 시간 계산
    duration<double, milli> elapsed_time = end_time - start_time;

    // JPS 알고리즘을 사용하여 경로 찾기
    Position<int> result = jps.find_path(start, end);

    // 경로를 찾은 경우
    int step_count = 0;
    if (result.x != -1) {
      // 경로에 '*' 표시하고 실제 이동한 횟수 계산
      for (const auto &pos : result.path) {
        if (map_copy[pos.first][pos.second] == '.') {
          map_copy[pos.first][pos.second] = '*';
          step_count++;
        }
      }

      // 이동 횟수 출력
      cout << "Reached an 'E' in " << step_count << " steps." << endl;

      // 경로가 표시된 맵 출력
      for (const auto &row : map_copy) {
        for (const auto &cell : row) cout << cell;
        cout << endl;
      }
    } else
      cout << "No path to the end found." << endl;

    // 경과 시간 출력
    cout << "Time taken: " << elapsed_time.count() << " ms" << endl;
  }
  return 0;
}