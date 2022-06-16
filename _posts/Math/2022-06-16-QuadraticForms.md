---
title: "Proof of Legendre's Three-Square Theorem using Quadratic Form"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Math
use_math: true
comments: true

---

`Tags` NumberTheory, 

## 1. Definitions

### 1-1. Quadratic Form

[Quadratic form]()이란 다음과 같이 정의되는 **모든 항의 차수가 $2$인 다항식**을 의미한다.

\begin{aligned}
q(x_1, \dots, x_n) = \sum_{i=1}^n \sum_{j=1}{n} a_{ij} x_i x_j
\end{aligned}

Quadratic form들은

- 변수의 개수 $n$ ($n = 1$: unary, $n = 2$: binary, $n = 3$, ternary)
- 계수 $a_{ij} \in K$ 가 속하는 field $K$ ($K = \mathbb{C}$, $\mathbb{R}$, $\mathbb{Z}$, $\mathbb{Z}\_p$)

에 따라서 구분한다.

$M_n(\mathbb{Z})$을 정수들로 이루어진 $n \times n$ 행렬들의 [환(ring)]()이라고 할 때,

행렬 $A \in M_n(\mathbb{Z})$ 에 대응되는 quadratic form은

\begin{aligned}
F_A(x_1, \dots, x_n) = \sum_{i=1}^n \sum_{j=1}{n} a_{ij} x_i x_j = xAx^T
\end{aligned}

로 쓸 수 있고, 이때 $x$는 행벡터 $(x_1, \dots, x_n)$ 이다.

---

### 1-2. Equivalance of Quadratic Forms

두 행렬 $A, B \in M_n(\mathbb{Z})$ 가 어떤 행렬 $U \in M_n(\mathbb{Z})$ 에 대하여

\begin{aligned}
U^TAU = B
\end{aligned}

을 만족하면 **$A$ is equivalent to $B$** 라고 하고, $A \~ B$ 로 표기한다.

행렬식의 성질에 의해 equivalent한 두 행렬 $A, B$는 $\mathrm{det} A = \mathrm{det} B$를 만족한다.

---

### 1-3. 

$SL_n(\mathbb{Z})$을 행렬식이 $1$인 행렬 $U \in M_n(\mathbb{Z})$ 들로 이루어진 [특수선형군(special linear group)]()이라고 할 때,

두 행렬 $A, B \in M_n(\mathbb{Z})$ 가 어떤 행렬 $U \in SL

\begin{aligned}
F_A(x_1, \dots, x_n) = \sum_{i=1}^n \sum_{j=1}{n} a_{ij} x_i x_j = xAx^T
\end{aligned}

로 쓸 수 있고, 이때 $x$는 행벡터 $(x_1, \dots, x_n)$ 이다.

두
