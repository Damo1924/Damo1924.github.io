---
title: "자연수를 제곱수의 합으로 나타내기"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` 정수론, 17633, 17646, 

이 포스팅은 아래 문제들을 풀기 위해 필요한 정수론 지식들을 다루고 있다.

- [BOJ 17633. 제곱수의 합(More Huge)](https://www.acmicpc.net/problem/17633)
- [BOJ 17646. 제곱수의 합 2(More Huge)](https://www.acmicpc.net/problem/17646)

<br/>

## 1. Lagrange's Four-Square Theorem

> **[Thm]** Lagrange's four-square theorem
> 
> 모든 자연수는 네 정수의 제곱의 합으로 나타낼 수 있다.
> 
> 즉, 임의의 자연수 $n$에 대하여 $n = a_1^2 + a_2^2 + a_3^2 + a_4^2$ 을 만족하는 네 정수 $a_1, a_2, a_3, a_4$ 가 존재한다.

이를 증명하기 위해서는 아래의 세 보조정리가 필요하다.

---

> **Lemma 1.** (Euler's four-square identity)
> 
> 네 정수의 제곱의 합으로 표현되는 두 정수의 곱은 네 정수의 제곱의 합으로 표현할 수 있다.

**Proof.** $a_i$, $b_i$가 정수일 때, $a = a_1, b$
