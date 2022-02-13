---
title: "Fenwick Tree (Binary Indexed Tree, BIT)"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` Segment tree, 

## 1. Fenwick Tree

> 펜윅 트리는 Binary indexed tree라는 이름으로 불리기도 하며, 줄여서 BIT라고 한다.

펜윅 트리는 **주어진 수열의 부분 수열들의 구간 합**을 빠르게 구하기 위해 고안된 자료구조이다.

> 부분 수열의 구간 합을 구하는 대표적인 방법은 **세그먼트 트리(segment tree)**를 이용하는 것이다.

---

### 1-1. Structure

길이가 $n$인 수열 $a_1, a_2, \dots, a_n$이 주어졌을 때,

정수 $i(1 \leq i \leq n)$에 대해 펜윅 트리의 노드 $i$에 저장된 값 $bit_i$는 다음과 같이 정의된다.

1. $i$가 홀수일 때: $bit_i = a_i$
2. $i$가 $2^k$의 배수이면서 $2^{k+1}$의 배수가 아닐 때: 

---

### 1-2. Implementation



<br/>

## References

[1] 
