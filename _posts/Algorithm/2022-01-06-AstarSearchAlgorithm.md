---
title: "A* search algorithm"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` 최단 경로 문제, 휴리스틱 알고리즘, Heuristic

## 1. Introduction to A* search algorithm

A* 알고리즘은 주어진 출발 지점에서 목표 지점까지 가는 최단 경로를 찾아내는 그래프 탐색 알고리즘이다.

**A* 알고리즘은 각 정점** $n$**에 대해 해당 꼭짓점을 통과하는 최상의 경로를 추정한 휴리스틱 추정값** $h(n)$을 이용한다.

휴리스틱 추정값을 기반으로 각 정점에 대한 평가 함수를 구하고, 우선순위 큐를 이용해 평가 함수로 구한 값의 순서대로 정점을 방문하면서 최단 경로를 찾는 알고리즘이다.

우선순위 큐를 이용하여 최단 경로를 구하는 알고리즘이라는 점에서 다익스트라 알고리즘과 비슷하다.

다만,다익스트라는 출발 지점으로부터 다른 모든 정점까지의 최단 거리를 구하는 알고리즘이지만, A* 알고리즘은 도착 지점까지 정해져 있다.

A* 알고리즘은 출발 지점으로부터 도착 지점까지의 최단 경로를 찾기 위해 각 정점마다 다음과 같은 평가 함수 $f(n)$를 정의한다.

\begin{aligned}
f(n) = g(n) + h(n)
\end{aligned}

- $g(n)$: 출발 정점으로부터 정점 $v$까지의 경로 가중치
- $h(n)$: 정점 $v$로부터 목표 정점까지의 **추정 경로 가중치**

A* 알고리즘은 $h(n)$를 어떻게 구하느냐에 따라서 얼마나 빨리 최단 경로를 찾을 수 있는지가 달라지게 된다.

가장 대표적인 휴리스틱 함수로는 **맨해튼 거리 함수**와 **유클리드 거리 함수**가 있다.

---

A* 알고리즘은 두 저장소, **열린 목록(Open List)**와 **닫힌 목록(Close List)**를 사용한다.

열린 목록에는 탐색 중인 정점들이, 닫힌 목록에는 탐색을 마친 정점들이 들어가게 된다.

알고리즘은 다음과 같다.

1. 아래 과정을 $n$이 목표 정점일 때까지 반복한다.
2. 열린 목록에 있는 정점들 중 평가 함수 $f(n)$이 가장 작은 정점 $n$을 선택한다.
3. 해당 정점에서 이동할 수 있는 정점 $v$에 대해,  
  3-1. $v$가 닫힌 목록에 있으면 이동할 수 있는 다음 정점을 탐색  
  3-2. 정점 $n$을 거쳐 $v$로 오는 경로의 길이를 구해 얻은 $f'$이 기존 평가함수보다 더 작으면 평가함수를 갱신한다.
4. 정점 $n$에 대한 탐색을 마쳤으므로 닫힌 목록에 추가한다.

<br/>

## 2. How to choose a good Heuristic function

### 2-1. Properties about A* Algorithm

A* 알고리즘은 어떤 휴리스틱 함수를 사용하느냐에 따라 다음과 같은 성질들을 갖는다.

노드 $n$에서 목표 지점까지의 최단 거리를 $d(n)$, 추정치를 $h(n)$이라고 하자.

출발 지점에서 노드 $n$까지의 거리는 $g(n)$이다.

- 모든 $n$에 대해 $h(n) = 0$: 다익스트라 알고리즘(Dijkstra's algortihm)이 된다.
- 모든 $n$에 대해 $h(n) \leq d(n)$: 알고리즘을 통해 최단 경로를 찾을 수 있음이 보장된다. 이때 $h(n)$이 작을수록 더 많은 노드를 탐색하게 되어 시간이 더 오래 걸린다.
- $h(n) = d(n)$: 알고리즘은 최단 경로를 따라서만 탐색하기 때문에 매우 빠르게 찾게 된다.
- 어떤 $n$에 대해 $h(n) > d(n)$: 알고리즘을 통해 최단 경로를 찾을 수 있다는 사실이 보장되지 않는다. 그러나 더 빠르게 동작할 수는 있다.
- $h(n)$이 $g(n)$에 비해 매우 큰 경우: $h(n)$의 영향만을 받게 되므로 Greedy Best-First Search가 된다.

---

### 2-2. Trade-off between Speed & Accuracy

앞서 언급했던 성질들에서 알 수 있듯이, 어떤 휴리스틱 함수를 사용하느냐에 따라 A* 알고리즘은 최단 경로를 반환하지 않을 수도 있다.

하지만, 그렇다고 해당 알고리즘이 쓸모가 없는 것은 아니다.

예를 들어 우리가 어떤 게임을 개발하고 있다고 하자.

캐릭터를 한 곳에서 다른 곳으로 이동시키는 명령이 입력되었을 때, 캐릭터가 어떤 경로를 따라서 이동해야하는지를 구하는 알고리즘을 만들어야한다.

가장 좋은 경로는 당연히 최단 경로겠지만, 맵이 매우 복잡하여 최단 경로를 구하는데는 시간이 많이 소요된다고 한다.

이때 개발 중인 게임에서는 굳이 엄밀한 **최단 경로**로 이동할 필요가 없어서, 경로를 찾는데 필요한 연산 시간을 줄이기 위해 **최단 경로에 가까운 적당한 경로**를 찾아 이동하기로 하였다.

맵은 이동하는데 1만큼의 시간이 걸리는 **평지**와 이동하는데 3만큼의 시간이 걸리는 **산**으로 이루어져있다.

맵 상의 어떤 연결된 두 지점 사이를 이동하는데 걸리는 **추정 시간**을 1이라고 하면, A* 알고리즘은 산 지형을 통한 경로를 탐색하기 전에 산 주위를 평지를 통해 돌아갈 수 있는지 탐색하게 된다.

최대 세 번까지 평지를 통해 이동하면서 산을 통해 가는 것보다 빠른 경로가 있는지 찾게 된다.

만약 위 추정 시간을 1.5로 바꾸면, 평지로 최대 두 번만 이동한 뒤 탐색을 중단하므로 더 빠르게 결과를 얻을 수 있게 된다.

탐색하는 경우의 수를 줄이는 또다른 방법은 산을 통해 이동하는 시간을 2로 줄여서 입력하는 것이다.

그럼 추정 시간을 1.5로 늘린 것처럼 평지로 최대 두 번만 이동한 뒤 탐색을 중단하게 된다.

두 방법 모두 **좀 더 빠르게 경로를 찾기 위해 최적의 경로를 포기**하였음을 알 수 있다.

이처럼 우리는 상황에 맞게 정확성을 포기하더라도 더 빠른 속도를 선택할 수도 있다.

---

### 2-3. Well-known Heuristic Functions

좌표평면에서 최단 경로를 찾는 문제들에 대해 사용하는 대표적인 휴리스틱 함수들은 다음과 같다.

- 4방향으로 이동 가능할 때: Manhattan distance($L_1$)
- 8방향으로 이동 가능할 때: Chebyshev distance($L_{\infty}$)
- 모든 방향으로 이동 가능할 때: Euclidean distance($L_2$)

이때 $L_p$는 다음과 같다.

\begin{aligned}
\left( \sum_{i=1}^n \left\vert x_i - y_i \right\vert^p \right)^{1/p}
\end{aligned}

---

### 2-4. Multiple Goals

목표 지점이 여러 개이면, 다음과 같은 전략을 사용할 수 있다.

만약 여러 개의 목표 지점 중 하나의 지점까지의 경로를 찾고 싶다면, 각 목표 지점에 대한 휴리스틱 함수의 최솟값을 $h(n)$으로 사용하면 된다.

또는 목표 지점들과 비용이 0인 간선들로 연결된 새로운 노드를 추가하는 방법도 있다.

만약 모든 목표 지점들까지의 경로를 찾고 싶다면, 차라리 다익스트라 알고리즘을 사용하는 것도 좋은 방법이다.

---

### 2-5. Tie-Breaking

어떤 입력은 **여러 개의 동일한 길이의 경로들**이 존재한다.

이 경우, A* 알고리즘은 같은 $f(n)$ 값을 가지는 여러 개의 경로를 모두 탐색할 수도 있다.

이로부터 발생하는 시간 낭비를 줄이기 위한 방법을 **Tie-breaking**이라고 부른다.

가장 간단한 방법은 평가함수 $f$에 영향을 주는 $g$ 또는 $h$의 값을 조절하는 것이다.

$h$ 값을 적절히 조절하여 목표 지점에 빠르게 도달하도록 해보자.

만약 $h$ 값에 1보다 작은 숫자를 곱해 크기를 작게 만든다면, 오히려 목표 지점에 가까워질수록 $f$의 값이 커지게 된다.

그러므로 어떤 양수 $p$에 대해 $h$ 값을 다음과 같이 조절해야한다.

\begin{aligned}
h'(n) = h(n) \times (1 + p)
\end{aligned}

이때 $p$는 다음을 만족하는 상수이다.

\begin{aligned}
p < (minimum cost of taking one step) / (expected maximum path length)
\end{aligned}

이렇게 휴리스틱 함수의 값을 적절히 늘려주면, 목표 지점에 가까운 곳부터 탐색을 하게 되어 탐색 속도를 늘릴 수 있다.

이 외에도 좌표마다 휴리스틱 함수값에 특정 랜덤 숫자를 더해준다거나, 시작 지점과 목표 지점을 잇는 선분에 가까운 경로를 선호하도록 만드는 방법 등이 존재한다.

<br/>

## 3. Implementation

이번에는 직접 A* 알고리즘을 이용해서 문제를 풀어보도록 하자.

A* 알고리즘을 소개할 때 가장 대표적으로 다루는 문제인 **8-puzzle** 문제를 풀어보자.

### [백준] 1525. 퍼즐

[백준 1525. 퍼즐 문제 링크](https://www.acmicpc.net/problem/1525)

3 x 3 크기의 표에 1부터 8까지의 숫자가 채워져 있다.

표에는 하나의 빈칸이 존재해서 빈칸과 인접한 숫자를 빈칸으로 움직일 수 있다.

초기 상태가 입력으로 주어졌을 때, 정리된 상태를 만들기 위한 최소 이동 횟수를 구하는 문제이다.

이제 '정리된 상태'란 왼쪽 위부터 순서대로 1부터 8이 채워진 상태를 의미한다.(오른쪽 아래 칸은 빈칸)

**[Solution]**

다음과 같은 휴리스틱 함수를 정의하자.

> $h_1(n)$ = 정리된 상태에 해당하는 위치에 있지 않은 숫자의 개수(빈칸 포함)

상태 공간 트리에서 각 노드에 해당하는 클래스 `State`를 만들어서 필요한 변수와 함수를 정의하여 A* 알고리즘을 구현하였다.

```cpp
#include <iostream>
#include <queue>
#include <unordered_set>
using namespace std;

class State {
public:
    int board[9]; // 보드판(1 ~ 9)
    int f, g, h; // 평가함수 f, 현재까지 이동 횟수 g, 휴리스틱 함수 h
    int z; // 빈칸의 인덱스
    
    // 생성자 정의
    State(int _board[9], int _f, int _g, int _h, int _z) {
        for (int i = 0; i < 9; i++) board[i] = _board[i];
        f = _f; g = _g; h = _h; z = _z;
    }
    
    // 빈칸 z와 인접한 숫자 i를 교환하는 함수
    void change(int i) {
        int tmp = board[z];
        board[z] = board[i];
        board[i] = tmp;
        z = i;
    }
    
    // f, g, h 계산
    void cal() {
        int cnt = 0;
        for (int i = 0; i < 9; i++)
            if (board[i] != i + 1) cnt++;
        h = cnt; // h: 제자리에 있지 않은 숫자의 개수
        g++;
        f = g + h;
    }
    
    // 닫힌 목록(Closed list)에 있는지 확인하기 위해 보드판의 상태를 정수로 변환
    int hash() {
        int res = 0;
        for (int i = 0; i < 9; i++) res = res * 10 + board[i];
        return res;
    }
};

class compare { // 평가함수 f가 작은 것이 우선순위가 높도록.
public:
    bool operator() (State& i, State& j) {
        if (i.f == j.f) return i.h > j.h; // f의 값이 동일하면 h가 작은 것이 우선순위가 높도록.
        return i.f > j.f;
    }
};

int astar(State& input)
{
    // move[i]: 빈칸 i에 인접한 칸의 인덱스
    vector<int> move[9] = {{1, 3}, {0, 2, 4}, {1, 5}, {0, 4, 6}, {1, 3, 5, 7}, {2, 4, 8}, {3, 7}, {4, 6, 8}, {5, 7}};
    
    // 닫힌 목록
    unordered_set<int> Closedset;
    
    // 평가함수 f 순서대로 정렬한 우선순위 큐
    priority_queue<State, vector<State>, compare> pq;
    pq.push(input);
    while (!pq.empty())
    {
        State cur = pq.top();
        pq.pop();
        
        if (cur.h == 0) return cur.g; // 정리된 상태에 도달하면 종료
        
        if (Closedset.count(cur.hash())) continue; // 닫힌 목록에 포함되어 있으면 continue
        Closedset.insert(cur.hash());
        
        for (int i = 0; i < move[cur.z].size(); i++)
        {
            State next = cur;
            next.change(move[cur.z][i]); // 이동
            
            if (Closedset.count(next.hash())) continue;
            next.cal(); // 새롭게 얻은 State를 우선순위 큐에 삽입
            pq.push(next);
        }
    }
    return -1; // 정리된 상태를 만들 수 없으면 -1을 반환
}

int main()
{
    // INPUT: 0을 9로 바꾸어서 저장, 0의 인덱스를 idx에 저장
    int input[9], idx;
    for (int i = 0; i < 9; i++)
    {
        cin >> input[i];
        if (input[i] == 0)
        {
            input[i] = 9;
            idx = i;
        }
    }
    
    // 초기 상태 s
    State s(input, 0, -1, 0, idx); 
    s.cal();
    
    // A* algorithm
    cout << astar(s);
}
```

이번에는 다음과 같은 휴리스틱 함수를 이용해보자.

> $h_2(n)$ = 각 숫자를 정리된 상태에 해당하는 위치로 옮기기 위한 이동 횟수의 합

아래와 같이 `State.cal()`만 바꾸어주면 된다.

```cpp
void cal() {
    int cnt = 0;
    for (int i = 0; i < 9; i++)
    {
        int a = i / 3, b = i % 3;
        int x = (board[i] - 1) / 3, y = (board[i] - 1) % 3;
        cnt += abs(x - a) + abs(y - b);
    }
    h = cnt;
    g++;
    f = g + h;
}
```













