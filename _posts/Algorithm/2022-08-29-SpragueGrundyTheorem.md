---
title: "Nim Game & Sprague Grundy Theorem"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:    
  - Algorithm
use_math: true
comments: true

---

`Tags` Game Theory, 게임 이론, 스프라그-그런디 정리, 

## 1. Perfect-Information Impartial Games

스프라그-그런디 정리에서는 perfect-information impartial two-player game에 대해 다룬다.

- **Two-player game**: 두 명이 번갈아가며 플레이한다.
- **Impartial game**: 한 사람이 먼저 플레이한다는 점이 두 플레이어의 유일한 차이이다.
- **Perfect information**: 모든 플레이어가 게임에 대한 모든 정보를 알고 있다.

추가적으로, 각 게임들은 아래 조건을 만족한다.

- **Ending condition**: 모든 게임은 반드시 종료된다.
- **Normal play condition**: 자신의 차례에 할 수 있는 행동이 없는 사람이 패배한다.

<br/>

## 2. Nim Game

Nim 게임이란 아래와 같은 게임이다.

- 여러 개의 돌로 이루어진 돌 무더기가 여러 개 주어진다.
- 두 플레이어가 번갈아가며 하나의 돌 무더기에서 원하는만큼의 돌을 가져간다. (반드시 하나 이상의 돌을 가져가야한다.)
- 더 이상 돌을 가져갈 수 없는 플레이러가 패배하게 된다.

Nim 게임은 perfect-information impartial two-player game임을 알 수 있다.

두 플레이어가 서로 최적으로 게임을 진행할 때, Nim 게임은 초기 상태에 의해 승자가 결정된다.

**돌 무더기에 있는 돌의 개수들에 대하여 모두 XOR 연산을 한 값**을 $x$라고 할 때,

- $x = 0$ 이면 처음으로 돌을 가져가는 플레이어가 패배
- $x \neq 0$ 이면 처음으로 돌을 가져가는 플레이어가 승리

하게 된다. 승리하기 위한 핵심은 **자기 차례에 $x = 0$ 이도록 돌을 가져가는 것**이다.

$x = 0$ 인 상태에서는 돌을 얼만큼 가져가던 $x \neq 0$ 으로 변하고,

$x \neq 0$ 인 상태에서는 $x = 0$ 이 되도록 돌을 가져가는 방법이 반드시 존재하기 때문에 위 승리 조건이 성립한다.

즉, 한 플레이어는 항상 $x \neq 0$ 인 상태에서 돌을 가져가고, 다른 한 플레이어는 항상 $x = 0$ 인 상태에서 돌을 가져가게 된다.

결국 돌이 하나도 남지 않게 되면 $x = 0$ 이므로 해당하는 플레이어가 무조건 패배하게 되는 것이다.

<br/>

## 3. Sprague Grundy Theorem

스프라그-그런디 정리는 **Two-player impartial game을 Nim game으로 치환할 수 있다**고 말한다.

Two-player impartial game의 임의의 상태 $v$에 대하여, $v_i$($i \in \{ 1, 2, \dots, k \}$, $k \geq 0$)을 $v$에서 도달할 수 있는 상태라고 정의하자.

상태 $v$의 게임이 $x$개의 돌로 이루어진 하나의 돌 무더기가 있는 Nim game으로 치환될 수 있는데,

이러한 $x$를 상태 $v$에 대한 **Grundy value** 또는 **Nim-value**라고 한다. 또한,

\begin{aligned}
x = mex \{ x_1, x_2, \dots, x_k \}
\end{aligned}

가 성립한다. 이때 $x_i$는 상태 $v_i$의 Grundy value이다.

> $mex(S)$는 집합 $S$에 속하지 않은 음이 아닌 정수들 중 가장 작은 것을 의미한다. (minimum excludant)

> 상태 $v$의 Grundy value가 $x$라는 것은, 모든 $0 \leq i < x$에 대하여 $v$에서 도달할 수 있는 상태들 중 Grundy value가 $i$인 상태가 존재한다는 뜻이다.

<br/>

## 4. Application

이제 위 정리를 이용해서 문제를 풀어보자.

상태 $v$의 Grundy value가 $x$라고 할 때, Nim game의 승리 조건에 의해 $x = 0$ 이면 현재 플레이어가 패배하고, $x \neq 0$ 이면 현재 플레이어가 승리한다.

즉, 게임의 초기 상태가 주어졌을 때, 누가 승리하는지 구하기 위해서는 초기 상태의 Grundy value를 구하면 된다.

Grundy value는 앞서 정의했던 것처럼 재귀적으로 구할 수 있다.

---

### [BOJ] 13034. 다각형 게임

[BOJ 13034. 다각형 게임 문제 링크](https://www.acmicpc.net/problem/13034)

꼭짓점들이 시계 방향으로 $1$부터 $N$까지 번호가 매겨진 볼록 $N$각형이 있다.

두 플레이어는 자신의 차례에 두 꼭짓점을 선택한 후, 연결하는 선분을 긋는다.

이때, 선분이 이미 그려진 선분과 교차하지 않아야한다. (선분의 끝 점이 만나는 것도 교차하는 것이다.)

더 이상 선분을 그릴 수 없는 사람이 패배한다.

두 플레이어가 최적의 방법으로 게임할 때, 누가 이기는지 구하는 문제이다.





<br/>

## References

[1] [Algorithms for Competitive Programming, 'Sprague-Grundy theorem. Nim'](https://cp-algorithms.com/game_theory/sprague-grundy-nim.html)  
