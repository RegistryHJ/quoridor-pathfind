# Quoridor AI 에이전트의 <br /> 성능 향상을 위한 길찾기 알고리즘 비교 연구

2024 교육장비개발 및 아이디어 경진대회 교육장비개발 부문 동상 (한국실천공학교육학회) <br />
한국실천공학교육학회 2024 종합학술발표대회 논문집 교육장비개발 부문 논문 게재 (PP. 243~244) <br />

**[논문 보기](https://github.com/user-attachments/files/18301757/Quoridor.AI.pdf)** &nbsp;/&nbsp;
**[A1 발표용 포스터 보기](https://github.com/user-attachments/files/18301733/A1.PPT.pdf)**

<br />

## Abstract

본 연구는 Quoridor AI 에이전트 성능 향상을 위한 최적의 길찾기 알고리즘을 탐색하는 것을 목적으로 한다. Quoridor 게임의 복잡성과 AI 에이전트의 성능 향상 필요성을 고려할 때, 효율적인 길찾기 알고리즘의 선택이 중요하다. 본 연구에서는 BFS, DFS, A*, D* Lite, JPS와 같은 다양한 길찾기 알고리즘을 구현하고, 실험을 통해 성능을 비교 분석하였다. 분석 결과, D* Lite와 JPS 알고리즘이 Quoridor 게임 환경에서 가장 효율적인 성능을 보였으며, 계산 속도와 최적 경로 탐색 측면에서 우수한 결과를 나타냈다. 특히 최단 경로 탐색에서 두 알고리즘은 실행 시간과 이동 횟수 면에서 균형 잡힌 성능을 보여주었다. 본 연구는 Quoridor AI 에이전트에 D* Lite나 JPS 알고리즘을 적용함으로써 Quoridor 앱의 성능을 크게 향상시킬 수 있음을 보여주었으며, 이는 앱의 경쟁력 강화에 기여할 것으로 기대된다.

**Key Word** <br /> 강화학습(RL), 길찾기 알고리즘(PathFind Alg.), BFS, DFS, A*, D* Lite, Jump-Point-Search

## Experiment

실험에서 사용할 길찾기 알고리즘은 다음과 같다.

1. BFS (Breadth-First Search)
2. DFS (Depth-First Search)
3. A\*
4. D\* Lite
5. JPS (Jump-Point Search)

### 1. 실험 설계

실험은 가로형, 세로형, 대칭 1출구형, 대칭 다출구형, 복합형 각 2종의 맵에 Quoridor의 최대 벽 20개를 설치하여 구현한다. 각 알고리즘은 관련 논문과 도서를 바탕으로 Quoridor 규칙에 맞게 변형하여 구현한다. 구현된 맵에서 각 알고리즘을 10회 실행하여 평균 실행 시간과 이동 거리를 측정하고, 이를 바탕으로 알고리즘별 최종 평균값을 산출한다.

### 2. 실행 환경 구성

실행 환경은 다음과 같다.

<table border="1">
  <tr>
    <td rowspan="3">
      Apple M3<br>
      APL1201<br>
      SoC
    </td>
    <td>Apple Everest 3.60GHz 4-core<br>+ Apple Sawtooth 2.48GHz 4-core</td>
  </tr>
  <tr>
    <td>Apple G16G 1,380 MHz 10-core</td>
  </tr>
  <tr>
    <td>Intergrated 24GB LPDDR5-6400)</td>
  </tr>
  <tr>
    <td>OS</td>
    <td>macOS Sequoia 15.0.1</td>
  </tr>
  <tr>
    <td>C++</td>
    <td>Apple Clang 16.0.0</td>
  </tr>
</table>

### 3. 맵의 구성

다음은 실험에서 사용하는 맵 10종이다.

<table border="1" cellpadding="10">
  <tr>
    <th>가로형</th>
    <th>세로형</th>
    <th>대칭 1출구형</th>
    <th>대칭 다출구형</th>
    <th>복합형</th>
  </tr>
  <tr>
    <td><img src="https://github.com/user-attachments/assets/991a19c5-763c-45b7-9835-25140f744c14" alt="가로형 미로 1" width="100"></td>
    <td><img src="https://github.com/user-attachments/assets/72997a34-77f3-4156-9ccf-e31a41fc80a7" alt="세로형 미로 1" width="100"></td>
    <td><img src="https://github.com/user-attachments/assets/83e37786-0016-407b-8dc1-ab577deda5d7" alt="대칭 1출구형 미로 1" width="100"></td>
    <td><img src="https://github.com/user-attachments/assets/308a1b91-e3c8-4553-895a-02d265399078" alt="대칭 다출구형 미로 1" width="100"></td>
    <td><img src="https://github.com/user-attachments/assets/07f27283-d768-490b-93dc-3d97c54bb792" alt="복합형 미로 1" width="100"></td>
  </tr>
  <tr>
    <td><img src="https://github.com/user-attachments/assets/6b9646b5-705d-4c2e-a7aa-f05e9dea230f" alt="가로형 미로 2" width="100"></td>
    <td><img src="https://github.com/user-attachments/assets/25abfa25-a96e-470f-b59a-282aff5a7028" alt="세로형 미로 2" width="100"></td>
    <td><img src="https://github.com/user-attachments/assets/9d4ddf53-4a20-4250-8eba-2a19a3e7afae" alt="대칭 1출구형 미로 2" width="100"></td>
    <td><img src="https://github.com/user-attachments/assets/8e25d578-cfd2-465f-8251-c4544b343688" alt="대칭 다출구형 미로 2" width="100"></td>
    <td><img src="https://github.com/user-attachments/assets/2905e7c7-3981-44b0-ba7d-4aea8f83aace" alt="복합형 미로 2" width="100"></td>
  </tr>
</table>

### 4. 실험 결과

실험 결과는 아래와 같다.

**실행 시간(ms):**

<table border="1" cellpadding="5">
  <thead>
    <tr>
      <th>Map</th>
      <th>BFS</th>
      <th>DFS</th>
      <th>A*</th>
      <th>D* Lite</th>
      <th>JPS</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>01</td>
      <td>1.1734</td>
      <td>0.0570</td>
      <td>1.0477</td>
      <td>0.5516</td>
      <td>0.5626</td>
    </tr>
    <tr>
      <td>02</td>
      <td>1.4825</td>
      <td>0.0595</td>
      <td>1.3955</td>
      <td>0.5072</td>
      <td>0.9569</td>
    </tr>
    <tr>
      <td>03</td>
      <td>0.8713</td>
      <td>0.0682</td>
      <td>0.9481</td>
      <td>0.5700</td>
      <td>0.5922</td>
    </tr>
    <tr>
      <td>04</td>
      <td>0.9855</td>
      <td>0.0441</td>
      <td>0.9494</td>
      <td>0.5599</td>
      <td>0.5860</td>
    </tr>
    <tr>
      <td>05</td>
      <td>0.7602</td>
      <td>0.0350</td>
      <td>0.9964</td>
      <td>0.5583</td>
      <td>0.5195</td>
    </tr>
    <tr>
      <td>06</td>
      <td>0.9807</td>
      <td>0.0554</td>
      <td>0.8051</td>
      <td>0.5317</td>
      <td>0.5605</td>
    </tr>
    <tr>
      <td>07</td>
      <td>1.0483</td>
      <td>0.0401</td>
      <td>0.7628</td>
      <td>0.5430</td>
      <td>0.5409</td>
    </tr>
    <tr>
      <td>08</td>
      <td>1.0318</td>
      <td>0.0304</td>
      <td>1.0408</td>
      <td>0.5963</td>
      <td>0.6571</td>
    </tr>
    <tr>
      <td>09</td>
      <td>0.9192</td>
      <td>0.0532</td>
      <td>0.8358</td>
      <td>0.5460</td>
      <td>0.5947</td>
    </tr>
    <tr>
      <td>10</td>
      <td>1.6681</td>
      <td>0.0888</td>
      <td>1.5610</td>
      <td>0.5137</td>
      <td>0.8229</td>
    </tr>
  </tbody>
  <tfoot>
    <tr>
      <th>Avg.</th>
      <td>1.0921</td>
      <td>0.0532</td>
      <td>1.0342</td>
      <td>0.5478</td>
      <td>0.6393</td>
    </tr>
  </tfoot>
</table>

**이동 횟수(Steps):**

<table border="1" cellpadding="5">
  <thead>
    <tr>
      <th>Map</th>
      <th>BFS</th>
      <th>DFS</th>
      <th>A*</th>
      <th>D* Lite</th>
      <th>JPS</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>01</td>
      <td>44.0</td>
      <td>48.0</td>
      <td>44.0</td>
      <td>44.0</td>
      <td>44.0</td>
    </tr>
    <tr>
      <td>02</td>
      <td>41.0</td>
      <td>54.0</td>
      <td>41.0</td>
      <td>41.0</td>
      <td>41.0</td>
    </tr>
    <tr>
      <td>03</td>
      <td>38.0</td>
      <td>42.0</td>
      <td>38.0</td>
      <td>38.0</td>
      <td>38.0</td>
    </tr>
    <tr>
      <td>04</td>
      <td>23.0</td>
      <td>24.0</td>
      <td>23.0</td>
      <td>23.0</td>
      <td>23.0</td>
    </tr>
    <tr>
      <td>05</td>
      <td>24.0</td>
      <td>28.0</td>
      <td>24.0</td>
      <td>24.0</td>
      <td>24.0</td>
    </tr>
    <tr>
      <td>06</td>
      <td>25.0</td>
      <td>31.0</td>
      <td>25.0</td>
      <td>25.0</td>
      <td>25.0</td>
    </tr>
    <tr>
      <td>07</td>
      <td>25.0</td>
      <td>32.0</td>
      <td>25.0</td>
      <td>25.0</td>
      <td>25.0</td>
    </tr>
    <tr>
      <td>08</td>
      <td>24.0</td>
      <td>28.0</td>
      <td>24.0</td>
      <td>24.0</td>
      <td>24.0</td>
    </tr>
    <tr>
      <td>09</td>
      <td>25.0</td>
      <td>33.0</td>
      <td>25.0</td>
      <td>25.0</td>
      <td>25.0</td>
    </tr>
    <tr>
      <td>10</td>
      <td>44.0</td>
      <td>66.0</td>
      <td>44.0</td>
      <td>44.0</td>
      <td>44.0</td>
    </tr>
  </tbody>
  <tfoot>
    <tr>
      <th>Avg.</th>
      <td>31.3</td>
      <td>38.6</td>
      <td>31.3</td>
      <td>31.3</td>
      <td>31.3</td>
    </tr>
  </tfoot>
</table>

위 실험에서 구현된 길찾기 알고리즘들의 성능을 맵 종류별로 분석한 결과, DFS는 모든 맵 유형에서 가장 빠른 실행시간(평균 0.0532ms)을 보였으나, 이동횟수가 다른 알고리즘보다 약 23% 많은 38.6steps로 측정되었다. 특히 복합형 맵에서는 최대 66steps까지 증가하여 실제 게임에서 부적합한 것으로 판단되었다. 반면 D* Lite와 JPS는 모든 맵 유형에서 최적 이동횟수(31.3steps)를 유지하면서도 각각 0.5478ms, 0.6393ms의 준수한 실행시간을 보여 가장 균형 잡힌 성능을 나타냈다. 특히 대칭형 맵들에서 효과적이었으며, 게임에서 요구되는 빠른 응답과 최적 경로 제공을 모두 만족하였다. BFS와 A* 는 최적 이동횟수를 보이지만 가장 느린 실행시간(각각 1.0921ms, 1.0342ms)을 보여 D* Lite나 JPS로 대체 가능함을 확인하였다.
<br>
위의 결과를 기반으로, Quoridor AI의 성능을 플레이어의 선호도와 게임 상황에 맞춰 최적화할 수 있도록 알고리즘 선택 기능을 제공할 예정이다. 실행 시간과 이동 횟수의 균형이 중요한 일반적인 상황에서는 D* Lite를, 보다 빠른 응답이 필요한 경우에는 JPS를 선택할 수 있게 하여 사용자 경험을 향상시킬 계획이다.

## References

1. Thomas H. Cormen et el., "Introduction to Algorithms, 4th Edition" March 2022. p.554
2. Thomas H. Cormen et el., "Introduction to Algorithms, 4th Edition" March 2022. p.563
3. Peter E. Hart et el., "A Formal Basis for the Heuristic Determination of Minimum Cost Paths" IEEE July 1968.
4. Sven Koenig et el., "D\* Lite" AAAI July 2002.
5. Daniel Harabor et el., "Online Graph Pruning for Pathfinding on Grid Maps" AAAI August 2011.
6. Hidekatsu Furukawa, "알파제로를 분석하며 배우는 인공지능" Jpub June 2020.

## <br />

Copyright © 2024 KibleLab
