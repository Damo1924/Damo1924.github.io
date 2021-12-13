---
title: "Min-Max Heap"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:    
  - Algorithm
use_math: true
comments: true

---

`Tags`  Min-Max Heap, Double-ended priority queue, 이중 우선순위 큐

## 1. Min-Max Heap

Min-max heap은 최댓값과 최솟값을 각각 상수 시간에 얻을 수 있고, 로그 시간에 삭제가 가능한 Max heap와 Min heap의 장점을 동시에 가진 완전 이진 트리이다.

이는 **이중 우선순위 큐(Double-ended priority queue)**를 구현하는데 굉장히 유용한 자료구조로, 원소 삽입과 삭제를 로그 시간에 할 수 있다는 특징을 가지고 있다.

Min-max heap은 다음을 만족하는 트리 구조를 가진다.

1. 짝수 레벨에 위치한 노드는 해당 노드를 루트로 하는 서브트리에 속한 모든 노드보다 작다.
2. 홀수 레벨에 위치한 노드는 해당 노드를 루트로 하는 서브트리에 속한 모든 노드보다 크다.

이때 루트 노드의 레벨은 0이다.

<img src="https://user-images.githubusercontent.com/88201512/145772828-9abdbc31-3fce-4683-8b1a-03a48741544a.jpg" width="60%" height="60%">

(출처: [WIKIPEDIA, 'Min-max heap'](https://en.m.wikipedia.org/wiki/Min-max_heap))

위 조건으로 인해 다음과 같은 특징들이 얻어진다.

- Min-max heap의 최솟값은 루트 노드이다.
- Min-max heap의 최댓값은 루트 노드의 두 자식 노드 중 더 큰 값이다.

이와 반대로 최댓값이 루트 노드에 저장되고, 최솟값이 루트 노드의 자식 노드 중 하나인 자료구조를 Max-min heap이라고 한다.

<br/>

---

## 2. Implementation of Min-Max Heap

Min-max heap은 Min heap과 Max heap과 같은 원리로 삽입, 삭제가 이루어진다.

단지 Min heap과 Max heap은 모든 레벨에 대해 

## Reference

[1] [WIKIPEDIA, 'Min-max heap'](https://en.m.wikipedia.org/wiki/Min-max_heap)  











