---
title: "폴라드 로 알고리즘 (Pollard's rho algorithm)"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` Pollard's rho, 소인수분해, Cycle detection

## 1. Cycle Detection

유한한 집합 $S$에 대하여 정의된 함수 $f : S \to S$ 를 초기값 $x_0 \in S$에 반복적으로 적용하면 아래와 같은 수열을 얻을 수 있다.

\begin{aligned}
x_0, x_1 = f(x_0), x_2 = f(x_1), \dots, x_i = f(x_{i-1}), \dots
\end{aligned}

모든 $i$에 대하여 $x_i \in S$ 이므로 위 수열에는 두 번 이상 등장하는 값이 존재함을 알 수 있다.

즉, $x_i = x_j$ 을 만족하는 서로 다른 두 인덱스 $i, j$($i < j$)가 반드시 존재한다.

이후 수열은 $x_i$부터 $x_{j-1}$까지의 값이 반복적으로 나타나므로, 주기성을 띄게 된다.

함수 $f$와 초기값 $x_0$가 주어졌을 때, 이러한 $i, j$를 찾는 문제를 **cycle detection** 또는 **cycle finding**이라고 부른다.

---

### 1-1. Floyd's algorithm (Tortoise and hare algorithm)

플로이드의 알고리즘은 **두 개의 포인터를 서로 다른 속도로 움직임**으로서 사이클을 찾는 알고리즘이다.

이솝우화 "토끼와 거북이"의 이름을 따서 tortoise and hare algorithm이라고 부르기도 한다.

원리는 매우 간단하다.

사이클의 시작 인덱스를 $\mu$, 사이클의 길이를 $\lambda$라고 하면,

임의의 정수 $i \geq \mu$, $k \geq 0$ 에 대하여 $x_i = x_{i + k \lambda}$ 가 성립한다.

이로부터 $k \lambda \geq \mu$ 를 만족하는 $k$에 대하여 $i = k \lambda$ 일 필요충분조건은 $x_i = x_{2i}$ 임을 증명할 수 있다.

따라서 두 포인터의 위치를 각각 $j, 2j$로 두고 값을 비교하면 사이클의 길이의 배수인 주기 $\nu = k \lambda$ 를 발견할 수 있다.

발견한 주기로부터 $\mu$를 찾을 수 있고, 사이클의 시작 인덱스로부터 $\lambda$도 구할 수 있게 된다.

알고리즘의 시간복잡도는 $O(\mu + \lambda)$ 이다.

---

### 1-2. Brent's algorithm

브랜트의 알고리즘은 $\lambda$와 $\mu$보다 큰 $2$의 거듭제곱 중 가장 작은 것을 구함으로써 사이클을 찾는 알고리즘이다.

음이 아닌 정수 $i = 0, 1, 2, \dots$ 에 대하여 $x_{2^{i-1}\}$와 $x_j$($2^{i-1} < j < 2^i$)를 비교한다.

이는 플로이드의 알고리즘에 비해 $\lambda$를 직접 구할 수 있을 뿐만 아니라, 각 단계마다 함수 $f$를 적용하는 연산을 한 번만 수행한다는 장점이 있다.

시간복잡도는 $O(\mu + \lambda)$ 로 플로이드 알고리즘과 동일하다.

> 실제 속도는 평균적으로 브랜트 알고리즘이 플로이드 알고리즘보다 36% 정도 더 빠르다고 한다.

<br/>

## 2. Pollard's rho algorithm

폴라드 로 알고리즘은 
