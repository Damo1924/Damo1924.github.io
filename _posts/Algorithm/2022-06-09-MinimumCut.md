---
title: "최소 컷 문제 (Minimum Cut Problem)"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` Max-flow min-cut theorem

## 1. Minimum Cut Problem

그래프 $G = (V, E)$에 대하여, **cut** $C = (S, T)$는 $V$를 두 부분집합 $S$, $T$로 나눈 분할이다.

이때 $u \in S$, $v \in T$를 만족하는 간선 $(u, v)$들의 집합을 **cut-set**이라 부른다.

두 정점 $s, t \in V$에 대하여 **s-t cut**은 $s \in S$, $t \in T$를 만족하는 cut이다.

> 방향그래프(directed graph)에 대하여, s-t cut의 cut-set은 소스(source)가 속하는 부분집합의 정점에서 싱크(sink)가 속하는 부분집합의 정점으로 향하는 간선으로만 이루어져 있다.

**Weight of cut**은 아래와 같이 정의된다.

- 가중치가 없는 경우(Unweighted graph): cut-set의 크기
- 가중치가 있는 경우(Weighted graph): cut-set에 포함된 간선들의 가중치의 합

**최소 컷(minimum cut)**이란 weight이 최소인 cut을 의미한다.

최소 컷을 구하는 문제는 소스와 싱크의 유무에 따라서 나눌 수 있다.

1. 소스와 싱크가 주어진 경우
2. 소스와 싱크가 주어지지 않은 경우: **Global minimum cut problem**

1번은 **최대 유량 최소 컷 정리**에 따라서 소스에서 싱크로의 최대 유량을 구함으로써 해결할 수 있다.

무향 그래프에서 2번 문제는 **스토어-바그너 알고리즘**을 이용해서 해결할 수 있다.

이번 포스팅에서는 위 두 가지 문제를 해결하는 방법들에 대해서 다룰 것이다.

> 마찬가지로 최대 컷(maximum cut)도 정의할 수 있는데, 임의의 그래프의 최대 컷을 구하는 문제는 NP-complete이다.

<br/>

## 2. Minimum Cut Problem with Terminal Nodes

### 2-1. Max-Flow Min-Cut Theorem

다음과 같은 네트워크를 생각하자.

- 방향그래프(directed graph) $G = (V, E)$
- 소스(source) $s \in V$, 싱크(sink) $t \in V$
- 간선 $(u, v) \in E$의 최대 용량(capacity) $c_{uv}$, 간선에 흐르는 유량(flow) $f_{uv}$

$s$에서 $t$로의 유량은 다음과 같이 정의된다.

\begin{aligned}
\left\vert f \right\vert = \sum_{v:(s,v) \in E} f_{sv} = \sum_{v:(v,t) \in E} f_{vt}
\end{aligned}

$s \in S$, $t \in T$를 만족하는 s-t cut $C = (S, T)$의 cut-set을 $X_C$라 하면 s-t cut의 capacity는 다음과 같이 정의된다.

\begin{aligned}
c(S, T) = \sum_{(u, v) \in X_C} c_{uv}
\end{aligned}

이때 최대 유량 최소 컷 정리(max-flow min-cut theorem)는 다음과 같다.

> 방향그래프와 소스, 싱크가 주어졌을 때, 최대 유량은 최소 컷의 용량과 같다.
> 
> 즉, $\left\vert f \right\vert$의 최댓값과 $c(S, T)$의 최솟값이 같다.

따라서 소스와 싱크가 정해진 최소 컷 문제는 소스에서 싱크로 흐를 수 있는 최대 유량을 구함으로써 해결할 수 있다.

---

### 2-2. Proof of Max-Flow Min-Cut Theorem

포드-풀커슨 알고리즘(Ford-Fulkerson algorithm)으로 구한 그래프에 흐르는 유량 $f$를 생각하자.

알고리즘에서 최종 유량을 흘려보낸 후 얻을 수 있는 **residual graph** $G_f$에 대하여 정점들의 두 부분집합을 정의하자.

- $A$ : $G_f$에서 $s$로부터 도달 가능한 정점들의 집합
- $A^C$ : $V - A$

정점들의 임의의 부분집합 $A$에 대하여

\begin{aligned}
f = f_{out}(A) - f_{in}(A)
\end{aligned}

이고, s-t cut $C = (A, A^C)$에 대하여

\begin{aligned}
c(A, A^C) = \sum_{(u, v) \in X_C} c_{uv}
\end{aligned}

이다. 따라서 $f = c(A, A^C)$가 성립하기 위해서는 아래 두 조건을 만족해야한다.

- $A$의 정점에서 $A^C$의 정점으로 향하는 모든 간선에는 해당 간선의 최대 용량만큼 유량이 흘러야한다. (**fully saturated**)
- $A^C$의 정점에서 $A$의 정점으로 향하는 모든 간선에는 유량이 흐르지 않아야한다. (**zero flow**)

먼저, $x \in A$, $y \in A^C$인 간선 $(x, y)$ 중 포화되지 않은 것이 존재한다고 가정하자.

$f_{xy} < c_{xy}$ 이므로 $G_f$에서 $s$에서 $y$까지의 경로가 존재하게 되고, 이는 모순이다.

따라서 $A$의 정점에서 $A^C$의 정점으로 향하는 모든 간선은 포화되어 있다.

다음으로 $x \in A$, $y \in A^C$인 간선 $(y, x)$ 중 유량이 흐르는 간선이 존재한다고 가정하자.

$f_{yx} > 0$ 이므로 $G_f$에는 유량이 흐를 수 있는 $x$에서 $y$로의 역방향 간선이 존재한다.

즉, $G_f$에서 $s$에서 $y$까지의 경로가 존재하게 되고, 마찬가지로 모순이 발생한다.

따라서 $A^C$의 정점에서 $A$의 정점으로 향하는 모든 간선에는 유량이 흐르지 않는다.

두 조건이 성립한다는 것을 증명했으므로, $f = c(A, A^C)$가 성립함을 알 수 있다.

이때 $f$는 포드-풀커슨 알고리즘으로 구한 값이므로 **최대 유량**이다.

---

### [BOJ] 

<br/>

## 3. Global Minimum Cut Problem




## References

[1] [WIKIPEDIA, 'Max-flow min-cut theorem'](https://en.m.wikipedia.org/wiki/Max-flow_min-cut_theorem)  
[2] 
