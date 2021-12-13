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

이때 루트 노드의 레벨은 0이며, 짝수 레벨을 min level, 홀수 레벨은 max level이라고 부른다.

<center><img src="https://user-images.githubusercontent.com/88201512/145772828-9abdbc31-3fce-4683-8b1a-03a48741544a.jpg" width="60%" height="60%"></center>

(출처: [WIKIPEDIA, 'Min-max heap'](https://en.m.wikipedia.org/wiki/Min-max_heap))

위 조건으로 인해 다음과 같은 특징들이 얻어진다.

- Min-max heap의 최솟값은 루트 노드이다.
- Min-max heap의 최댓값은 루트 노드의 두 자식 노드 중 더 큰 값이다.

이와 반대로 최댓값이 루트 노드에 저장되고, 최솟값이 루트 노드의 자식 노드 중 하나인 자료구조를 Max-min heap이라고 한다.

<br/>

---

## 2. Implementation of Min-Max Heap

Min-max heap은 Min heap과 Max heap과 같은 원리로 삽입, 삭제가 이루어진다.

단지 Min heap과 Max heap은 모든 레벨에 있는 노드에 대해 대소관계를 비교했지만, Min-max heap은 min level이나 max level에 있는 노드만 비교하는 것 뿐이다.

### 2-1. Insertion

Min-max heap에 원소를 삽입하는 과정은 다음과 같다.

1. Min-max heap을 저장하고 있는 배열의 맨 끝에 삽입하려는 원소를 추가한다.
2. 삽입된 원소와 부모 원소를 비교한다.
  - 삽입된 원소가 부모 원소보다 작으면 루트 노드까지의 경로에 있는 모든 max level 노드들보다 작다는 것을 의미하므로, min level 노드들만 고려하면 된다.
  - 삽입된 원소가 부모 원소보다 크면 루트 노드까지의 경로에 있는 모든 min level 노드들보다 크다는 것을 의미하므로, max level 노드들만 고려하면 된다.
3. 삽입된 원소로부터 루트 노드까지의 경로에 있는 min level 노드들은 내림차순으로, max level 노드들은 오름차순으로 정렬되어야한다. 이를 만족할 때까지 삽입한 원소를 해당 level에 있는 부모 노드와 비교하여 교환해나가면 된다.

위 과정은 **Push Up algorithm**(또는 **Bubble-Up**)으로 구현할 수 있다.



### 2-2. Deletion

## Reference

[1] [WIKIPEDIA, 'Min-max heap'](https://en.m.wikipedia.org/wiki/Min-max_heap)  











