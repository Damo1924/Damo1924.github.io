---
title: "k번째 원소 구하기"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` kth element

## $k$th Element Problems

이번 포스팅에서는 $k$번째 원소를 구하는 다양한 문제들에 대해 다루어 볼 것이다.

자주 만날 수 있는 $k$번째 원소 문제는 크게 세 가지로 나눌 수 있다.

- **[PROBLEM 1]** 길이가 $n$인 수열의 $k$($1 \leq k \leq n$)번째 원소 구하기
- **[PROBLEM 2]** 길이가 $n$인 수열에서, 길이가 $m$($1 \leq m \leq n$)인 연속부분수열들의 $k$($1 \leq k \leq m$)번째 원소 구하기
- **[PROBLEM 3]** 길이가 $n$인 수열에서, 임의의 구간 $\[l, r\]$($1 \leq l \leq r \leq n$)의 $k$($1 \leq k \leq r - l + 1$)번째 원소 구하기

각 문제들을 어떤 알고리즘을 이용해서 해결할 수 있는지 정리해보았다.

<br/>

## [PROBLEM 1]

길이가 $n$인 수열 $a_1, a_2, \dots, a_n$이 주어진다.

수열 $a$를 오름차순으로 정렬했을 때, 앞에서부터 $k$번째에 있는 수를 구하여라.

> [백준 11004. K번째 수](https://www.acmicpc.net/problem/11004)

### [SOLUTION] Sorting

주어진 수열을 오름차순으로 정렬한 후에 $k$번째 원소를 출력하면 된다.

**Time complexity**: $O(n \log n)$

<br/>

## [PROBLEM 2]

길이가 $n$인 수열 $a_1, a_2, \dots, a_n$이 주어진다.

정수 $m, k$($1 \leq m \leq n$, $1 \leq k \leq m$)가 주어질 때, 다음을 구하여라.

- 길이가 $m$인 모든 연속부분수열의 $k$번째 원소

> [백준 9426. 중앙값 측정](https://www.acmicpc.net/problem/9426)

<br/>

## [PROBLEM 3]

> [백준 7469. K번째 수](https://www.acmicpc.net/problem/7469)
