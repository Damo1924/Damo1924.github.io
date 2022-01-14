---
title: "Convex Hull Algorithm"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` 기하 알고리즘, 볼록 다각형, 그레이엄 스캔, Graham's Scan algorithm, CCW

## 1. Convex Hull Algorithm

2차원 평면 위에 여러 개의 점들이 주어질 때, 아래와 같이 **모든 점을 포함하는 볼록 다각형**이 존재한다.

<img src="" width="60%" height="60%">

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
  - 스택의 마지막 두 점을 각각 A와 B, 그리고 이번에 처리할 점을 C라고 하자.
  - 점 A, B, C가 반시계 방향을 이루면 C를 스택에 삽입한다.
  - 점 A, B, C가 시계 방향을 이루면 B는 볼록 껍질에 포함되지 않으므로 B를 스택에서 제거하고 C를 스택에 삽입한다.
5. 마지막으로 기준점까지 탐색하였다면 알고리즘을 종료한다.

기준점을 선택하는데 $O(n)$, 점들을 정렬하는데 $O(n \log n)$, 점들을 차례대로 처리하는데 $O(n)$이므로 전체 알고리즘의 시간복잡도는 $O(n \log n)$이다.

만약 점들이 반시계 방향으로 정렬되어 있다면 $O(n)$의 시간복잡도로 볼록 껍질을 구할 수 있다.

이때 세 점이 이루는 방향을 판단하기 위해서는 **CCW(Counter Clock Wise)** 알고리즘을 사용한다.

> CCW에 대한 자세한 내용은 [이 포스팅](https://damo1924.github.io/algorithm/CCW/)에서 다루고 있다.

---

### 2-2. Implementation

이제 그레이엄 스캔을 구현해서 볼록 껍질을 구해보자.





## References

[1] [위키백과, '볼록 껍질 알고리즘'](https://ko.m.wikipedia.org/wiki/%EB%B3%BC%EB%A1%9D_%EA%BB%8D%EC%A7%88_%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98)  
[2] [위키백과, '그레이엄 스캔'](https://ko.m.wikipedia.org/wiki/%EA%B7%B8%EB%A0%88%EC%9D%B4%EC%97%84_%EC%8A%A4%EC%BA%94)  






