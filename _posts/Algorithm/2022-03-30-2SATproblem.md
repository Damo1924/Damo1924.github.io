---
title: "2-SAT Problem"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` CNF, SCC, 

## 1. 2-SAT problem

2-SAT 문제란 **참 또는 거짓의 값을 가지는 $n$개의 변수 $x_1, x_2, \dots, x_n$으로 이루어진 2-CNF가 참이 되도록 $x_i$들에 적절한 값을 할당하는 문제이다.

> **CNF**: 논리곱 표준형(Conjunctive Normal Form)의 약자로, 절의 논리곱으로 나타낸 논리식이다. 이때 절은 변수 또는 변수들의 논리합이다.
> 
> **n-CNF**: 각 절이 n개의 변수의 논리합인 CNF을 의미하며, 2-CNF와 3-CNF가 주로 다루어진다.

CNF에서 등장할 수 있는 논리기호에는 **논리합($x \or y$)**, **논리곱($x \and y$)**, **부정($\lnot x$)**이 있다.

예를 들어, 두 변수 $x_1, x_2$로 이루어진 2-CNF $(x_1 \or x_2) \and (\lnot x_1 \or \lnot x_2)$를 생각해보자.

$x_1 = true$, $x_2 = false$로 값을 할당하면 위 식이 참이 되므로 2-SAT 문제의 해가 된다.

또, $x_1 = false$, $x_2 = true$도 위 식을 참으로 만든다.

반면 $(x_1 \or x_1) \and (\lnot x_1 \or \lnot x_1)$는 어떤 값을 할당해도 참으로 만들 수 없다.

이처럼 2-SAT 문제에는 해가 존재하지 않을 수도 있고, 해가 존재해도 유일하지 않을 수 있다.

<br/>

## 2. How to Solve 2-SAT problem

2-SAT 문제는 **강한연결요소(Strongly Connected Component)**을 통해 해결할 수 있다.

그러기 위해서는 주어진 2-CNF을 통해 적절한 그래프를 만들어야한다.

---

### 2-1. 

> **[Definition]** 두 명제 $P$와 $Q$가 모든 경우에 대해 진리값이 같을 때, "$P$는 $Q$와 **논리적 동치(logically equivalent)**이다"라고 하며, 다음과 같이 나타낸다.
> 
> \begin{aligned}
> P \equiv Q
> \end{aligned}

