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

[Quadratic form](https://en.m.wikipedia.org/wiki/Quadratic_form)이란 다음과 같이 정의되는 **모든 항의 차수가 $2$인 다항식**을 의미한다.

\begin{aligned}
q(x_1, \dots, x_n) = \sum_{i=1}^n \sum_{j=1}^n a_{ij} x_i x_j
\end{aligned}

Quadratic form들은

- 변수의 개수 $n$ ($n = 1$: unary, $n = 2$: binary, $n = 3$, ternary)
- 계수 $a_{ij} \in K$ 가 속하는 field $K$ ($K = \mathbb{C}$ or $\mathbb{R}$ or $\mathbb{Z}$ or $\mathbb{Z}\_p$)

에 따라서 구분한다.

$M_n(\mathbb{Z})$을 정수들로 이루어진 $n \times n$ 행렬들의 [환(ring)](https://en.m.wikipedia.org/wiki/Ring_(mathematics))이라고 할 때,

행렬 $A \in M_n(\mathbb{Z})$ 에 대응되는 quadratic form은

\begin{aligned}
F_A(x_1, \dots, x_n) = \sum_{i=1}^n \sum_{j=1}{n} a_{ij} x_i x_j = xAx^T
\end{aligned}

로 쓸 수 있고, 이때 $x$는 행벡터 $(x_1, \dots, x_n)$ 이다.

이때 대칭행렬 $A' = \frac{1}{2} (A + A^T)$ 은 $F_{A'} = F_A$ 를 만족하고, 각 quadratic form에 대응되는 대칭행렬은 유일하게 결정된다.

따라서 앞으로는 quadratic form $F_A$에 대응되는 행렬 $A$을 대칭행렬로 둘 것이다.

---

### 1-2. Equivalance of Quadratic Forms

$SL_n(\mathbb{Z})$을 행렬식이 $1$인 행렬 $U \in M_n(\mathbb{Z})$ 들로 이루어진 [특수선형군(special linear group)](https://en.m.wikipedia.org/wiki/Special_linear_group)이라고 할 때,

두 행렬 $A, B \in M_n(\mathbb{Z})$ 가 어떤 행렬 $U \in SL_n(\mathbb{Z})$ 에 대하여

\begin{aligned}
U^TAU = B
\end{aligned}

을 만족하면 **$A$ is equivalent to $B$** 라고 하고, $A$~$B$ 로 표기한다.

$\mathrm{det} U = 1$ 이므로 equivalent한 두 행렬 $A, B$는 $\mathrm{det} A = \mathrm{det} B$를 만족한다.

서로 equivalent한 두 대칭행렬 $A, B$에 대응되는 quadratic form $F_A, F_B$ 에 대하여 $F_A$~$F_B$ 라고 쓴다.

이때 어떤 $U \in SL_n(\mathbb{Z})$에 대하여 $U^TAU = B$라고 하면,

\begin{aligned}
F_B(x) = xBx^T = xU^TAUx^T = (Ux^T)^T A (Ux^T) = F_A(Ux^T)
\end{aligned}

를 얻을 수 있다.

이로부터 **$F_A$~$F_B$ 이면 $F_A$로 나타낼 수 있는 정수들과 $F_B$가 나타낼 수 있는 정수들이 일치한다는 것**을 알 수 있다.

---

### 1-3. Discriminant & Positive Definite

Quadratic form $F_A$가 모든 $x_1, \dots, x_n \in \mathbb{Z}$ (모두 $0$인 경우 제외)에 대하여 $F_A(x_1, \dots, x_n) > 0$을 만족하면 **positive definite**이라고 부른다.

**대칭행렬** $A$에 대하여 $F_A$의 판별식(discriminant)는 $d(F_A) = \mathrm{det} A$ 로 정의되므로,

$F_A$가 positive definite이기 위한 필요충분조건은 $\mathrm{det} A < 0$ 이라고 할 수 있다.

<br/>

## 2. Binary Quadratic Forms

> **Lemma 1.** 판별식의 값이 $d$인 모든 positive definite binary quadratic form은 equivalent form
> 
> \begin{aligned}
> F_A(x_1, x_2) = a_{11}x_1^2 + 2a_{12}x_1x_2 + a_{22}x_2^2
> \end{aligned}
> 
> 을 가진다. 이때 $a_{11}, a_{12}, a_{22} \in \mathbb{Z}$ 이고, $2 \left\vert a_{12} \right\vert \leq a_{11} \leq 2 \sqrt{d/3}$ 이다.

**Proof.** 임의의 대칭행렬 $B \in M_2(\mathbb{Z})$ 에 대응되는 positive definite quadratic form

\begin{aligned}
F_B(x_1, x_2) = b_{11}x_1^2 + 2b_{12}x_1x_2 + b_{22}x_2^2
\end{aligned}

에 대하여 $d(F_B) = \mathrm{det} B = d$ 라고 하자.

$F_B$로 나타낼 수 있는 양의 정수의 최솟값을 $a_{11}$, 대응되는 $x_1, x_2$의 값을 $r_1, r_2 \in \mathbb{Z}$라고 하면,


\begin{aligned}
F_B(r_1, r_2) = a_{11}
\end{aligned}

이다. 이때 $\mathrm{gcd} (r_1, r_2) = g$ 라고 하면,

\begin{aligned}
a_{11} \leq F_B(\frac{r_1}{r}, \frac{r_2}{r}) = \frac{F_B(r_1, r_2)}{r^2} = \frac{a_{11}\}{r^2} \leq a_11
\end{aligned}

이므로 $r = 1$ 임을 알 수 있다.

$r_1s_2 - r_2s_1 = 1$ 인 두 정수 $s_1, s_2$, 그리고 어떤 정수 $t$에 대하여

\begin{aligned}
U = \begin{pmatrix} r_1 & s_1 + r_1 t \\\\  r_2 & s_2 + r_2 t \end{pmatrix}
\end{aligned}

로 정의되는 행렬 $U$는 $\mathrm{det} U = 1$ 이므로 $U \in SL_2(\mathbb{Z})$ 이다.

$U$를 이용해서 아래와 같이 행렬 $A$를 정의하자.

\begin{aligned}
U^TBU = A := \begin{pmatrix} a_{11} & a_{12} \\\\  a_{12} & a_{22} \end{pmatrix}
\end{aligned}

- $a_{12} = b_{11}r_1s_1 + b_{12}(r_1s_2 + r_2s_1) + b_{22} r_2 s_2$
- $a_{22} = F_B(s_1 + r_1 t, s_2 + r_2 t)$

$r_1(s_2 + r_2 t) - r_2(s_1 + r_1 t)= 1$ 이므로 $s_1 + r_1 t, s_2 + r_2 t$ 는 둘 다 $0$ 일 수 없고, 따라서 $a_{11} \leq a_{22}$ 이다.

정수 $t$를 $\left\vert a_{12} \right\vert \leq a_{11} / 2$ 가 성립하도록 잡으면,

\begin{aligned}
\mathrm{det} A = a_{11} a_{22} - a_{12}^2 \geq a_{11}^2 - \left( \frac{a_{11}\}{2} \right)^2 = \frac{3}{4} a_{11}^2
\end{aligned}

이다. 이때 $A$~$B$ 로부터 $F_A$~$F_B$ 이고, $\mathrm{det} A = \mathrm{det} B = d$ 이다.

따라서 $d \geq \frac{3}{4} a_{11}^2$, $a_{11} \leq 2 \sqrt{d/3}$ 이다.

---

> **Theorem 1.** 판별식의 값이 $1$인 모든 positive definite binary quadratic form $F(x_1, x_2)$ 는 $x_1^2 + x_2^2$ 와 equivalent하다.

**Proof.** Lemma 1에 의해,

\begin{aligned}
a_{11}a_{22} - a_{12} = d(F) = 1, \,\, 2 \left\vert a_{12} \right\vert \leq a_{11} \leq 2 \sqrt{\frac{1}{3}\} < 2
\end{aligned}

과 $F(x_1, x_2)$~$a_{11}x_1^2 + 2a_{12}x_1x_2 + a_{22}x_2^2$ 을 만족하는 $a_{11}, a_{12}, a_{22}$ 가 존재한다.

$a_{11} > 0$ 이므로 $a_{11} = 1$, $a_{12} = 0$, $a_{22} = 1$ 이다.

따라서 $F$~$x_1^2 + x_2^2$ 이다.

<br/>

## 3. Ternary Quadratic Forms





