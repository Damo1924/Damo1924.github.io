---
title: "Convex Hull Algorithm & Rotating Calipers"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` 그레이엄 스캔, Graham's Scan, CCW, 회전하는 캘리퍼스, 가장 먼 두 점, 1708 볼록 껍질, 

## 1. Convex Hull Algorithm

2차원 평면 위에 여러 개의 점들이 주어질 때, 아래와 같이 **모든 점을 포함하는 볼록 다각형**이 존재한다.

<center><img src="https://user-images.githubusercontent.com/88201512/149804273-ab477bbb-1ac6-4dc5-b6e3-24ca4c76f720.jpg" width="60%" height="60%"></center>

이와 같은 볼록 다각형을 **볼록 껍질(convex hull)**이라고 하며, 볼록 껍질을 구하는 알고리즘을 **볼록 껍질 알고리즘(Convex hull algorithm)**이라고 부른다.

볼록 껍질 알고리즘들의 시간복잡도는 주어진 점의 개수 $n$과 볼록 껍질을 이루는 점의 개수 $h$에 영향을 받는다.

이번 포스팅에서는 가장 대표적인 볼록 껍질 알고리즘인 **그레이엄 스캔(Graham's Scan)**에 대해 다루어 볼 것이다.

<br/>

## 2. Graham Scan

### 2-1. Algorithm

그레이엄 스캔은 평면 상에서 유한한 점들의 볼록 껍질을 찾는 방법으로, 점의 개수를 $n$이라 하면 시간복잡도는 $O(n \log n)$이다.

알고리즘은 다음과 같은 과정으로 이루어진다.

1. 반드시 볼록 껍질에 포함되는 점인 **y좌표가 가장 작은 점**을 기준점으로 선택한다. 만약 y좌표가 가장 작은 점이 여러 개라면, 그 중 x좌표가 가장 작은 것을 선택한다.
2. 선택한 점을 기준으로 다른 점들을 반시계 방향으로 정렬한다.
3. 볼록 껍질을 구성하는 점들을 저장할 스택(stack)을 만들고, 첫 두 점을 스택에 삽입한다.
4. 정렬된 순서대로 각 점들을 차례대로 처리한다.
  4-1. 스택의 마지막 두 점을 각각 A와 B, 그리고 이번에 처리할 점을 C라고 하자.
  4-2. 점 A, B, C가 반시계 방향을 이루면 C를 스택에 삽입한다.
  4-3. 점 A, B, C가 시계 방향을 이루면 B는 볼록 껍질에 포함되지 않으므로 B를 스택에서 제거하고 4-1로 돌아간다.
5. 마지막으로 기준점까지 탐색하였다면 알고리즘을 종료한다.

아래 그림은 그레이엄 스캔 과정을 보여준다.

<center><img src="https://user-images.githubusercontent.com/88201512/149806393-331fbfee-b908-4a6d-a5e6-1c8ef956075b.jpg"></center>

기준점을 선택하는데 $O(n)$, 점들을 정렬하는데 $O(n \log n)$, 점들을 차례대로 처리하는데 $O(n)$이므로 전체 알고리즘의 시간복잡도는 $O(n \log n)$이다.

만약 점들이 반시계 방향으로 정렬되어 있다면 $O(n)$의 시간복잡도로 볼록 껍질을 구할 수 있다.

이때 세 점이 이루는 방향을 판단하기 위해서는 **CCW(Counter Clock Wise)** 알고리즘을 사용한다.

> CCW에 대한 자세한 내용은 [이 포스팅](https://damo1924.github.io/algorithm/CCW/)에서 다루고 있다.

---

### 2-2. Implementation

이제 그레이엄 스캔을 구현해서 볼록 껍질을 구해보자.

[백준 1708. 볼록 껍질 문제 링크](https://www.acmicpc.net/problem/1708)

2차원 평면 위 N개의 점이 주어졌을 때, 볼록 껍질을 이루는 점의 개수를 구하는 문제이다.

N은 3 이상 100,000 이하인 자연수이고, 각 점의 좌표는 절댓값이 40,000을 넘지 않는다.

또한, 모든 점이 같은 직선 상에 위치하는 경우는 입력으로 주어지지 않는다.

**[Solution]**

먼저, 점들을 탐색해서 기준점을 고른다.

이제 선택한 기준점을 중심으로 다른 점들을 반시계 방향으로 정렬해야한다.

점들을 반시계 방향으로 정렬하는 가장 쉬운 방법은 **벡터의 외적**을 이용하는 것이다.

> 기준점 Q와 어떤 두 점 A, B가 주어졌을 때, $\vec{QA} \times \vec{QB} > 0$이면 Q에 대해 A-B는 반시계 방향이다.

세 점이 이루는 방향을 판단하기 위해서는 CCW 알고리즘을 이용하면 된다.

전체 코드는 다음과 같다.

```cpp
#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;

struct point {
    long long x, y;
} P[100000];

bool CCW(point& A, point& B, point& C) // CCW이면 true, 아니면 false를 반환하는 함수
{
    return (B.x - A.x) * (C.y - B.y) - (C.x - B.x) * (B.y - A.y) > 0;
}

point Q; // 기준점
bool compare(point& A, point& B) // 반시계 방향으로 정렬
{
    long long V = (A.x - Q.x) * (B.y - Q.y) - (A.y - Q.y) * (B.x - Q.x);
    if (V > 0) return true;
    if (V < 0) return false;
    return abs(A.x - Q.x) + abs(A.y - Q.y) < abs(B.x - Q.x) + abs(B.y - Q.y);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int N;
    cin >> N;
    
    // 1. 입력 & 기준점 찾기
    int idx = 0;
    for (int i = 0; i < N; i++)
    {
        cin >> P[i].x >> P[i].y;
        if (P[i].y < P[idx].y) idx = i;
        else if (P[i].y == P[idx].y && P[i].x < P[idx].x) idx = i;
    }
    Q = P[idx];
    
    // 2. 점들을 반시계 방향으로 정렬
    sort(P, P + N, compare);
    
    // 3. 점들을 차례대로 탐색하면서 볼록 껍질 구하기
    vector<point> vec = {P[0], P[1]};
    for (int i = 2; i < N; i++)
    {
        while (vec.size() > 1 && !CCW(vec[vec.size() - 2], vec[vec.size() - 1], P[i]))
            vec.pop_back();
        vec.push_back(P[i]);
    }
    if (!CCW(vec[vec.size() - 2], vec[vec.size() - 1], P[0])) vec.pop_back();
    cout << vec.size();
}
```

<br/>

## 3. Rotating Calipers

회전하는 캘리퍼스 알고리즘은 **볼록 껍질의 최대 직경**을 구하는 알고리즘이다.

볼록 껍질의 최대 직경은 **볼록 껍질을 구성하는 가장 먼 두 점의 길이**로 정의한다.

이때 볼록 껍질은 좌표평면 상의 모든 점을 포함하는 볼록 다각형이므로, 다음이 성립한다.

> **볼록 껍질의 최대 직경 = 가장 먼 두 점 사이의 거리**

볼록 껍질을 이루는 점의 개수를 $h$라고 하면, 회전하는 캘리퍼스 알고리즘은 $O(h)$의 시간복잡도로 볼록 껍질의 최대 직경을 구할 수 있다.

그러므로 **그레이엄 스캔**과 **회전하는 캘리퍼스** 알고리즘을 이용하면, 좌표평면에 $n$개의 점이 주어졌을 때 가장 멀리 떨어진 두 점 사이의 거리를 $O(n\log n)$의 시간복잡도로 구할 수 있게 된다.

회전하는 캘리퍼스 알고리즘에 대해 공부해보고, 직접 구현까지 해보자.

---

### 3-1. Algorithm

캘리퍼스는 길이를 정밀하게 측정하는 도구로, 아래 그림과 같다.

<center><img src="https://user-images.githubusercontent.com/88201512/149702638-01d8c755-5341-425e-a5e4-c6952b5bb92c.jpg" width="60%" height="60%"></center>

회전하는 캘리퍼스 알고리즘은 말 그대로 캘리퍼스를 볼록 껍질의 주위에서 회전시키며 최대 직경을 구한다.

알고리즘은 아래 그림과 같은 과정을 거쳐 진행된다.

<center><img src="https://user-images.githubusercontent.com/88201512/149804403-521759c6-9e2d-43d5-baa9-25856eec0bb8.jpg"></center>

간단히 정리해보면,

1. y좌표가 가장 작은 점과 가장 큰 점을 찾고, 캘리퍼스의 두 집게를 x축에 평행하게 둔다. 직경의 초기값은 찾은 두 점 사이의 거리이다.
2. 각 점을 포함하는 볼록 다각형의 선분과 캘리퍼스의 집게가 이루는 각도 중 작은 것 만큼 캘리퍼스를 회전시킨다.
3. 캘리퍼스를 회전시켰을 때 새롭게 캘리퍼스에 닿는 점과 반대편 캘리퍼스에 기존에 닿아 있던 점 사이의 거리를 구해 최댓값을 갱신한다.
4. 볼록 다각형의 모든 변을 탐색할 때까지 2~3번 과정을 반복한다.

즉, 볼록 다각형의 모든 변을 한 번씩 캘리퍼스의 집게가 맞닿기 때문에 $O(h)$의 시간복잡도를 가진다.($h$: 볼록 껍질을 이루는 점의 개수)

---

### 3-2. Implementation





<br/>

## References

[1] [위키백과, '볼록 껍질 알고리즘'](https://ko.m.wikipedia.org/wiki/%EB%B3%BC%EB%A1%9D_%EA%BB%8D%EC%A7%88_%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98)  
[2] [위키백과, '그레이엄 스캔'](https://ko.m.wikipedia.org/wiki/%EA%B7%B8%EB%A0%88%EC%9D%B4%EC%97%84_%EC%8A%A4%EC%BA%94)  






