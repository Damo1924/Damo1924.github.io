---
title: "Z algorithm"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:    
  - Algorithm
use_math: true
comments: true

---

`Tags` 문자열 알고리즘, Z array, 문자열 검색

## 1. Z array

문자열 $S$에 대하여 Z 배열의 원소 $Z\[i\]$ 은 다음과 같이 정의된다.

- $Z\[i\]$ : $S\[i:\]$의 접두사(prefix)이면서 $S$의 접두사인 부분문자열들 중 길이가 가장 긴 것의 길이

이때 $S\[i:\]$는 $S\[i\]$에서 시작하는 $S$의 부분문자열을 의미한다.

<br/>

## 2. Z algorithm

Z 알고리즘은 Z 배열을 구하는 알고리즘이다.

문자열 $S$의 길이가 $N$이라고 하면, Z 알고리즘은 $O(N)$의 시간복잡도를 갖는다.

---

### 2-1. IDEA

단순히 생각했을 때, $Z\[i\]$를 구하기 위해서는,

- $S\[0\]$과 $S\[i\]$를 비교
- $S\[1\]$과 $S\[i + 1\]$를 비교
- $\vdots$
- $S\[k\]$과 $S\[k + 1\]$를 비교
- $\vdots$

위와 같은 과정을 두 문자가 같지 않을 때까지 반복해주면 된다.

이렇게 Z 배열을 구하면 $O(N^2)$이 걸리게 되는데, 

