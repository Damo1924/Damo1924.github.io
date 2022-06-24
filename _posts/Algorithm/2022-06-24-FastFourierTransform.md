---
title: "Fast Fourier Transform Algorithm"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` Cooley-Tukey, 

<br/>

## 1. Introduction

두 다항식 $A(x), B(x)$가 각각

\begin{aligned}
A(x) = a_0 + a_1 x + a_2 x^2 + \dots + a_{n-1} x^{n-1} = \sum_{j=0}^{n-1} a_j x_j
\end{aligned}

\begin{aligned}
B(x) = b_0 + b_1 x + b_2 x^2 + \dots + b_{n-1} x^{n-1} = \sum_{j=0}^{n-1} b_j x_j
\end{aligned}

로 주어질 때, 두 다항식의 곱 $C(x) = A(x)B(x)$ 를

\begin{aligned}
C(x) = c_0 + c_1 x + c_2 x^2 + \dots + c_{2n-2} x^{2n-2} = \sum_{j=0}^{2n-2} c_j x_j
\end{aligned}

와 같이 쓸 수 있다. 이때 $c_i = a_0 b_i + a_1 b_{i-1} + \dots + a_i b_0$ 이다.

두 다항식을 전개하는 방법으로 $C(x)$를 구하면 $O(n^2)$ 의 시간복잡도로 구할 수 있다.

이번 포스팅에서 공부할 **고속 푸리에 변환(Fast Fourier Transform)**은 $O(n^2)$ 보다 빠르게 두 다항식의 곱을 계산하는 알고리즘이다.

<br/>

## 2. Basic Idea

### 2-1. Lagrange's Interpolation

고속 푸리에 변환 알고리즘의 핵심 아이디어는 **라그랑주 보간법(Lagrange's interpolation)**에 기반한다.

- $n$개의 점 $\left( x_k, f(x_k) \right)$ 을 지나는 $n-1$차 다항함수 $f(x)$는 유일하게 존재한다.

즉, 두 다항식의 곱 $C(x) = A(x)B(x)$ 을 표현하기 위해서는 $2n-1$개의 $x$값에 대한 함수값을 알아야한다.

서로 다른 $2n-1$개의 점 $x_0, x_1, \dots, x_{2n-2}$ 에 대하여

\begin{aligned}
C(x_k) = A(x_k)B(x_k)
\end{aligned}

이므로 $A(x_k)$와 $B(x_k)$의 값을 안다면 $C(x_k)$의 값을 계산할 수 있다.

---

### 2-2. Discrete Fourier Transform

다항식 $A(x) = a_0 + a_1 x + a_2 x^2 + \dots + a_{n-1} x^{n-1}$ 에 대하여,

복소수 $w \in \mathbb{C}$을 primitive $n$-th root of unity라고 할 때,

> **primitive $n$-th root of unity** $w$ : $w^n = 1$ 의 해
> 
> \begin{aligned}
> w = e^{\frac{2 \pi i}{n}\} = \cos \frac{2 \pi}{n} + i \cdot \sin \frac{2 \pi}{n}
> \end{aligned}

서로 다른 $n$개의 점 $w^0, w^1, w^2, \dots, w^{n-1}$ 에서의 함수값

\begin{aligned}
A(w^k) = \sum_{j=0}^{n-1} a_j (w^k)^j
\end{aligned}

들을 구할 수 있다. 이때 변환 $\mathbb{C} \to \mathbb{C}$ 

\begin{aligned}
(a_0, a_1, \dots, a_{n-1}) \mapsto \left( A(w^0), A(w^1), \dots, A(w^{n-1}) \right)
\end{aligned}

을 **이산 푸리에 변환(Discrete Fourier Transform, DFT)**라고 한다.

---

### 2-3. Inverse transform of DFT

반대로, DFT를 수행한 결과

\begin{aligned}
y_k = A(w^k) = \sum_{j = 0}^{n-1} a_j(w^k)^j
\end{aligned}

를 알고 있을 때, 역으로 $a_0, a_1, \dots, a_{n-1}$ 을 구하는 방법에 대하여 알아보자.

DFT는 아래와 같이 행렬로 표현할 수 있다.

\begin{aligned}
\begin{pmatrix} y_0 \\\\   y_1 \\\\   y_2 \\\\   \vdots \\\\   y_{n-1} \end{pmatrix} =
\begin{pmatrix} 1 & 1 & 1 & \dots & 1 \\\\   1 & w & w^2 & \dots & w^{n-1} \\\\   1 & w^2 & w^4 & \dots & w^{2(n-1)} \\\\   \vdots & \vdots & \vdots & \ddots & \vdots \\\\   1 & w^{n-1} & w^{2(n-1)} & \dots & w^{(n-1)(n-1)} \end{pmatrix}
\begin{pmatrix} a_0 \\\\   a_1 \\\\   a_2 \\\\   \vdots \\\\   a_{n-1} \end{pmatrix}
\end{aligned}

양변에 역행렬을 곱해주면,

\begin{aligned}
\begin{pmatrix} a_0 \\\\   a_1 \\\\   a_2 \\\\   \vdots \\\\   a_{n-1} \end{pmatrix} = \frac{1}{n}
\begin{pmatrix} 1 & 1 & 1 & \dots & 1 \\\\   1 & w^{-1} & w^{-2} & \dots & w^{-(n-1)} \\\\   1 & w^{-2} & w^{-4} & \dots & w^{-2(n-1)} \\\\   \vdots & \vdots & \vdots & \ddots & \vdots \\\\   1 & w^{-(n-1)} & w^{-2(n-1)} & \dots & w^{-(n-1)(n-1)} \end{pmatrix}
\begin{pmatrix} y_0 \\\\   y_1 \\\\   y_2 \\\\   \vdots \\\\   y_{n-1} \end{pmatrix}
\end{aligned}

을 얻을 수 있다. 즉, DFT의 역변환은 다음과 같다.

- $(y_0, y_1, \dots, y_{n-1})$ 을 $w^{-1}$ 에 대하여 DFT를 수행한 후, $n$으로 나누어주면 $(a_0, a_1, \dots, a_{n-1})$ 을 얻을 수 있다.

---

### 2-4. Idea

두 다항식의 곱은 다음과 같이 계산할 수 있다.

1. $A(x), B(x)$ 에 대해 DFT 수행
2. 위 결과를 이용하여 $C(w^0), C(w^1), \dots, C(w^{2n-2})$ 를 계산
3. 위 결과에 대해 역변환 DFT 수행

하지만 DFT를 그대로 계산하면 $O(n^2)$이기 때문에 이렇게 계산하는 것이 아무런 의미가 없다.

따라서 DFT를 빠르게 구할 수 있는 방법이 필요하다.

<br/>

## 3. Cooley-Tukey Algorithm

쿨리-튜키 알고리즘은 DFT를 구하기 위해 **분할 정복**을 이용하는 방법으로, 대표적인 FFT 알고리즘 중 하나이다.

---

### 3-1. Divide & Conquer

$n = 2^k$ 일 때, $n-1$차 다항식

\begin{aligned}
f(x) = a_{n-1}x^{n-1} + a_{n-2}x^{n-2} + \dots + a_2x^2 + a_1x + a_0
\end{aligned}

에 대하여, 두 다항식

\begin{aligned}
f_{even}(x) = a_{n-2} x^{(n-2)/2} + a_{n-4} x^{(n-4)/2} \dots + a_4 x^2 + a_2 x + a_0 = \sum_{i=0}^{(n-2)/2} a_{2i} x^i
\end{aligned}

\begin{aligned}
f_{odd}(x) = a_{n-1} x^{(n-2)/2} + a_{n-3}x^{(n-4)/2} + \dots + a_5 x^2 + a_3 x + a_1 = \sum_{i=0}^{(n-2)/2} a_{2i+1} x^i
\end{aligned}

을 정의하면, 다음이 성립한다.

\begin{aligned}
f(x) = f_{even} \left( x^2 \right) + x \cdot f_{odd} \left( x^2 \right)
\end{aligned}

어떤 복소수 $w$에 대하여,

\begin{aligned}
f(w) = f_{even} \left( w^2 \right) + w \cdot f_{odd} \left( w^2 \right)
\end{aligned}

\begin{aligned}
f(-w) = f_{even} \left( w^2 \right) - w \cdot f_{odd} \left( w^2 \right)
\end{aligned}

이므로, $f_{even} \left( w^2 \right)$ 과 $f_{odd} \left( w^2 \right)$ 의 값을 알고 있다면 $O(1)$로 $f(w)$ 와 $f(-w)$ 을 구할 수 있다.

---

### 3-2. Algorithm

이제 2절에서 다룬 DFT 아이디어와 위의 분할정복을 합쳐보자.

$n = 2^m$ 꼴일 때, Primitive $n$-th root of unity $w$, 모든 $0 \leq k < n$ 에 대하여 $f(w^k)$를 구해야하는데,

이는 $f_{even}(w^{2k})$과 $f_{odd}(w^{2k})$로부터 구할 수 있다.

이때 $w = e^{\frac{2 \pi i}{n}\}$ 이므로,

\begin{aligned}
w^{2k} = e^{\frac{4 \pi ki}{n}\} = e^{\frac{2 \pi ki}{n/2}\} = w_{n/2}^k
\end{aligned}

이다. 이때 $w_{n/2}$는 primitive $\frac{n}{2}$-th root of unity이다.

그런데 $f_{even}(x)$와 $f_{odd}(x)$는 모두 $\frac{n}{2}-1$ 차 다항식이므로,

**$f_{even}(w^{2k})$와 $f_{odd}(w^{2k})$는 각 다항식에 DFT를 수행해준 결과**임을 알 수 있다.

즉, 아래와 같이 정리할 수 있다.

- 짝수 $n$에 대하여 $n$차 다항식 $f(x)$에 DFT를 수행한 결과는 $f_{even}(x)$와 $f_{odd}(x)$에 DFT를 수행한 결과로부터 $O(n)$으로 구할 수 있다.

따라서 이를 분할정복으로 구현하면 총 $O(\log n)$ 개의 단계를 거치게 되고, 각 단계를 처리하는데 $O(n)$이므로 전체 시간복잡도는 $O(n \log n)$ 이 된다.

---

### 3-3. Implementation

C++ STL의 `<complex>`에서는 복소수 자료형이 정의되어 있어 덧셈, 뺄셈, 곱셈 등이 가능하다.

```cpp

```
