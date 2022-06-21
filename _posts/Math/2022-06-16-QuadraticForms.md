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
F_A(x_1, \dots, x_n) = \sum_{i=1}^n \sum_{j=1}^n a_{ij} x_i x_j = xAx^T
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

을 만족하면 **$A$ is equivalent to $B$** 라고 하고, $A \sim B$ 로 표기한다.

$\mathrm{det} U = 1$ 이므로 equivalent한 두 행렬 $A, B$는 $\mathrm{det} A = \mathrm{det} B$를 만족한다.

서로 equivalent한 두 대칭행렬 $A, B$에 대응되는 quadratic form $F_A, F_B$ 에 대하여 $F_A \sim F_B$ 라고 쓴다.

이때 어떤 $U \in SL_n(\mathbb{Z})$에 대하여 $U^TAU = B$라고 하면,

\begin{aligned}
F_B(x) = xBx^T = xU^TAUx^T = (xU^T) A (xU^T)^T = F_A(xU^T)
\end{aligned}

를 얻을 수 있다.

이로부터 **$F_A \sim F_B$ 이면 $F_A$로 나타낼 수 있는 정수들과 $F_B$가 나타낼 수 있는 정수들이 일치한다는 것**을 알 수 있다.

---

### 1-3. Discriminant & Positive Definite

Quadratic form $F_A$가 모든 $x_1, \dots, x_n \in \mathbb{Z}$ (모두 $0$인 경우 제외)에 대하여 $F_A(x_1, \dots, x_n) > 0$을 만족하면 **positive definite**이라고 부른다.

**대칭행렬** $A$에 대하여 $F_A$의 판별식(discriminant)는 $d(F_A) = \mathrm{det} A$ 로 정의된다.

$F_A$가 항상 양수($x \neq \vec{0}$)이기 위한 필요충분조건은 행렬 $A$가 [정치행렬(positive definite matrix)](https://en.m.wikipedia.org/wiki/Definite_matrix)이어야하므로,

모든 $k = 1, \dots, n$에 대하여 $\mathrm{det} (a_{ij})\_{1 \leq i, j \leq k} > 0$ 을 만족해야한다.

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

이다. 이때 $\mathrm{gcd} (r_1, r_2) = r$ 라고 하면,

\begin{aligned}
a_{11} \leq F_B(\frac{r_1}{r}, \frac{r_2}{r}) = \frac{F_B(r_1, r_2)}{r^2} = \frac{a_{11}\}{r^2} \leq a_{11}
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

따라서 $2 \left\vert a_{12} \right\vert \leq a_{11} \leq 2 \sqrt{d/3}$ 이다.

---

> **Theorem 1.** 판별식의 값이 $1$인 모든 positive definite binary quadratic form $F(x_1, x_2)$ 는 $x_1^2 + x_2^2$ 와 equivalent하다.

**Proof.** Lemma 1에 의해,

\begin{aligned}
a_{11}a_{22} - a_{12} = d(F) = 1, \,\, 2 \left\vert a_{12} \right\vert \leq a_{11} \leq 2 \sqrt{\frac{1}{3}\} < 2
\end{aligned}

과 $F(x_1, x_2) \sim a_{11}x_1^2 + 2a_{12}x_1x_2 + a_{22}x_2^2$ 을 만족하는 $a_{11}, a_{12}, a_{22}$ 가 존재한다.

$a_{11} > 0$ 이므로 $a_{11} = 1$, $a_{12} = 0$, $a_{22} = 1$ 이다.

따라서 $F \sim x_1^2 + x_2^2$ 이다.

<br/>

## 3. Ternary Quadratic Forms

> **Lemma 2.** 판별식이 $d$인 대칭행렬 $A \in M_3(\mathbb{Z})$ 에 대하여 $A$에 대응되는 ternary quadratic form을 $F_A$라고 하자.
> 
> \begin{aligned}
> A' = \begin{pmatrix} a_{11}a_{22} - a_{12}^2 & a_{11}a_{23} - a_{12}a_{13} \\\\  a_{11}a_{23} - a_{12}a_{13} & a_{11}a_{33} - a_{13}^2 \end{pmatrix}
> \end{aligned}
> 
> 인 행렬 $A'$에 대응되는 binary quadratic form을 $G_{A'}$라고 하면 다음이 성립한다.
> 
> \begin{aligned}
> a_{11} F_A(x_1, x_2, x_3)= (a_{11}x_1 + a_{12}x_2 + a_{13}x_3)^2 + G_{A'}(x_2, x_3)
> \end{aligned}
> 
> \begin{aligned}
> d(G_{A'})= \mathrm{det} A' = a_{11} d
> \end{aligned}
> 
> 또한, $F_A$가 positive definite이면 $G_{A'}$도 positive definite이다.

**Proof.** 두 식은 직접 양 변을 전개함으로써 성립함을 확인할 수 있다.

$F_A$가 positive definite라고 하면, $a_{11} = F_A(1, 0, 0) > 0$ 이다.

어떤 $x_2, x_3 \in \mathbb{Z}$ 에 대하여 $G_{A'} (x_2, x_3) \leq 0$ 이고, $x_1 = -a_{12}x_2 - a_{13}x_3$ 라고 하면,

\begin{aligned}
a_{11} F_A(x_1, a_{11}x_2, a_{11}x_3) &= a_{11}^2 (x_1 + a_{12}x_2 + a_{13}x_3)^2 + G_{A'}(a_{11}x_2, a_{11}x_3) \\\\  
&= 0 + a_{11}^2 G_{A'}(x_2, x_3) \leq 0
\end{aligned}

이다. $a_{11} > 0$ 이므로 $F_A(x_1, a_{11}x_2, a_{11}x_3) \leq 0$ 이고, $F_A$가 positive definite이므로 $x_1= x_2 = x_3 = 0$ 이다.

따라서 $G_{A'}(x_2, x_3) \leq 0$를 만족하는 순서쌍 $(x_2, x_3)$는 $(0, 0)$뿐이고, 이는 $G_{A'}$가 positive definite임을 의미한다.

---

> **Lemma 3.** 판별식이 $d$인 각 positive definite ternary quadratic form은 equivalent form
> 
> \begin{aligned}
> F_A(x_1, x_2, x_3) = \sum_{i=1}^3 \sum_{j=1}^3 a_{ij} x_i x_j
> \end{aligned}
> 
> 를 가진다. 이때 $A$는 대칭행렬이고, 다음을 만족한다.
> 
> \begin{aligned}
> 2 \max(\left\vert a_{12} \right\vert, \left\vert a_{13} \right\vert) \leq a_{11} \leq \frac{4}{3} \sqrt[3]{d}
> \end{aligned}

**Proof.** 앞서 Lemma 1을 증명했던 것과 비슷한 방법으로 증명할 수 있다.

$\mathrm{det} C = d$인 대칭행렬 $C \in M_3(\mathbb{Z})$ 의 positive definite ternary quadratic form을 $F_C$라고 하자.

$F_C$가 나타낼 수 있는 가장 작은 양의 정수를 $a_{11}$, $F_C(u_{11}, u_{21}, u_{31}) = a_{11}$라고 하자.

세 정수 $u_{11}, u_{21}, u_{31}$ 의 최대공약수를 $u$라고 하면,

\begin{aligned}
a_{11} \leq F_C \left( \frac{u_{11}\}{u}, \frac{u_{21}\}{u}, \frac{u_{31}\}{u} \right) = \frac{a_{11}\}{u^2} \leq a_{11}
\end{aligned}

이므로, $u = 1$ 임을 알 수 있다.

$\gcd(u_{11}, u_{21}) = a$ 라고 하면, $u_{11}u_{22} - u_{21}u_{12} = a$ 을 만족하는 정수 $u_{12}, u_{22}$ 가 존재한다.

$\gcd(a, u_{31}) = u = 1$ 이므로 $a u_{33} - b u_{33}= 1$ 을 만족하는 정수 $u_{33}, b$ 가 존재한다.

다음과 같이 행렬 $U$를 정의하면,

\begin{aligned}
U = \begin{pmatrix} u_{11} & u_{12} & bu_{11} / a \\\\ u_{21} & u_{22} & bu_{21} / a \\\\  u_{31} & 0 & u_{33} \end{pmatrix}
\end{aligned}

$\mathrm{det} U = 1$ 가 되어 $U \in SL_3(\mathbb{Z})$ 가 된다.

행렬 $B$를 $B := U^T C U$ 라고 정의하면, $F_B \sim F_C$ 이고 $d(F_B) = d(F_C) = d$ 이다.

이때 $b_{11} = \sum_{j, k = 1}^3 = F_C(u_{11}, u_{21}, u_{31}) = a_{11}$ 이다.

Lemma 2에서 정의한 행렬 $B'$과 대응되는 binary quadratic form $G_{B'}$에 대하여,

\begin{aligned}
a_{11} F_B(x_1, x_2, x_3)= (b_{11}x_1 + b_{12}x_2 + b_{13}x_3)^2 + G_{B'}(x_2, x_3)
\end{aligned}

이고, $d(G_{B'})= a_{11} d$ 이다.

또한, $F_B$가 positive definite이므로 $G_{B'}$도 positive definite이다.

Lemma 1에 의해 $G_{B'}(x_2, x_3)$ 는 equivalent form

\begin{aligned}
G_{\hat{A}\}(x_2, x_3) = \hat{a}\_{11} x_2^2 + 2 \hat{a}\_{12}x_2x_3 + \hat{a}\_{22} x_3^2
\end{aligned}

을 갖고, 이때 행렬 $\hat{A} \in SL_2(\mathbb{Z})$ 의 성분들은 다음을 만족한다.

\begin{aligned}
2 \left\vert \hat{a}\_{12} \right\vert \leq \hat{a}\_{11} \leq 2 \sqrt{\frac{a_{11}d}{3}\}
\end{aligned}

$\hat{A} \sim B'$ 이므로 어떤 행렬 $\hat{V} \in SL_2(\mathbb{Z})$ 에 대하여 $\hat{A} = \hat{V}^T B' \hat{V}$ 이다.

어떤 정수 $r, s$ 에 대하여 행렬 $V \in SL_3(\mathbb{Z})$ 을

\begin{aligned}
V = \begin{pmatrix} 1 & r & s \\\\ 0 & \hat{v}\_{11} & \hat{v}\_{12} \\\\  0 & \hat{v}\_{21} & \hat{v}\_{22} \end{pmatrix}
\end{aligned}

로, 행렬 $A = V^T B V$ 로 정의하자.

어렵지 않게 $V^T B V$의 $(1, 1)$ 성분이 $b_{11}$ 인 것을 알 수 있고, 앞서 $b_{11} = a_{11}$ 이었다.

두 행벡터 $x = (x_1, x_2, x_3)$, $y = (y_1, y_2, y_3) = xV^T$ 에 대하여

\begin{aligned}
F_A (x_1, x_2, x_3) = F_B (y_1, y_2, y_3)
\end{aligned}

이고, $(y_2, y_3) = (x_2, x_3) \hat{V}$ 로부터

\begin{aligned}
G_{B'}(y_2, y_3) = G_{\hat{V}^T B' \hat{V}\} (x_2, x_3) = G_{\hat{A}\}(x_2, x_3)
\end{aligned}

이다. 또한, $A = V^T B V$ 에서

\begin{aligned}
\sum_{j=1}^3 a_{1j} x_j = \sum_{j=1}^3 \left( \sum_{i=1}^3 b_{1i} v_{ij} \right) x_j = \sum_{i=1}^3 b_{1i} \sum_{j=1}^3 b_{ij}x_j = \sum_{i=1}^3 b_{1i}y_i
\end{aligned}

를 얻을 수 있다. 그렇다면 Lemma 2에 의해,

\begin{aligned}
(a_{11} x_1 + a_{12} x_2 + a_{13} x_3)^2 + G_{A'}(x_2, x_3) &= a_{11} F_A (x_1, x_2, x_3) = b_{11} F_B (y_1, y_2, y_3) \\\\  
&= (b_{11}x_1 + b_{12}x_2 + b_{13}x_3)^2 + G_{B'}(x_2, x_3) \\\\  
&= (a_{11} x_1 + a_{12} x_2 + a_{13} x_3)^2 + G_{\hat{A}\}(x_2, x_3)
\end{aligned}

가 되고, $G_{A'}(x_2, x_3) = G_{\hat{A}\}(x_2, x_3)$ 를 얻는다.

어떤 quadratic form에 대응되는 대칭행렬은 유일하므로 $A' = \hat{A}$ 임을 알 수 있다.

이제 $r, s$를 $\left\vert a_{12} \right\vert \leq a_{11} / 2$ 와 $\left\vert a_{13} \right\vert \leq a_{11} / 2$ 이도록 선택하자.

$A = V^T B V = (UV)^T C (UV)$, $UV \in SL_3(\mathbb{Z})$ 이므로 $A \sim C$이고, $F_C$와 $F_A$가 나타낼 수 있는 정수는 동일하다.

즉, $F_A$가 나타낼 수 있는 양의 정수 중 최솟값도 $a_{11}$이므로,

\begin{aligned}
a_{22} = F_A(0, 1, 0) \geq a_{11}
\end{aligned}

이다. Lemma 2의 정의에 의해 다음이 성립한다.

\begin{aligned}
a_{11}^2 \leq a_{11}a_{22} = \hat{a}\_{11} + a_{12}^2 \leq 2 \sqrt{\frac{a_{11}d}{3}\} + \left( \frac{a_{11}\}{2} \right)^2
\end{aligned}

따라서 $a_{11} \leq \frac{4}{3} \sqrt[3]{d}$ 이다.

---

> **Theorem 2.** 판별식의 값이 $1$인 모든 positive definite ternary quadratic form $F(x_1, x_2, x_3)$ 는 $x_1^2 + x_2^2 + x_3^2$ 와 equivalent하다.

**Proof.** Lemma 3에 의해 $F$와 equivalent한 $F_A(x_1, x_2, x_3)$ 가 존재하고, 이때 대칭행렬 $A \in M_3(\mathbb{Z})$ 은

\begin{aligned}
2 \max(\left\vert a_{12} \right\vert, \left\vert a_{13} \right\vert) \leq a_{11} \leq \frac{4}{3}
\end{aligned}

을 만족한다. 각 성분은 모두 정수이므로 $a_{11}$은 $0$ 또는 $1$의 값을 가질 수 있는데, 어느 값이던 $a_{12} = a_{13} = 0$ 이다.

$\mathrm{det} A = 1 \neq 0$ 이므로 $a_{11} = 1$ 수밖에 없다.

$F_A$가 positive definite이므로,

\begin{aligned}
\mathrm{det} \begin{pmatrix} a_{11} & a_{12} \\\\  a_{21} & a_{22} \end{pmatrix} = a_{22} > 0
\end{aligned}

이다. 행렬 $A'$을

\begin{aligned}
A' = \begin{pmatrix} a_{22} & a_{23} \\\\  a_{23} & a_{33} \end{pmatrix}
\end{aligned}

라고 정의하면, $a_{22} > 0$ 이고, $\mathrm{det} A' = 1 > 0$ 가 된다.

따라서 $F_{A'}$는 판별식이 $1$인 positive definite binary quadratic form 이다.

Theorem 1에 의해 $F_{A'}$은 $x_1^2 + x_2^2$ 과 equivalent하므로, 어떤 행렬

\begin{aligned}
U' = \begin{pmatrix} u_{22} & u_{23} \\\\  u_{23} & u_{33} \end{pmatrix} \in SL_2(\mathbb{Z})
\end{aligned}

에 대하여 $(U')^T A' U' = I_2$ 이다. ($I_2$는 $2 \times 2$ 단위행렬)

행렬 $U$를

\begin{aligned}
U = \begin{pmatrix} 1 & 0 & 0 \\\\  0 & u_{22} & u_{23} \\\\  0 & u_{23} & u_{33} \end{pmatrix} \in SL_3(\mathbb{Z})
\end{aligned}

라고 정의하면, $U^T A U = I_3$ 가 되어 $A_3 \sim I_3$ 임을 알 수 있다.

따라서 $F(x_1, x_2, x_3) \sim F_A(x_1, x_2, x_3) \sim F_{I_3}(x_1, x_2, x_3) = x_1^2 + x_2^2 + x_3^2$ 이다.

<br/>

## 4. Legendre's Three-Square Theorem

> **Lemma 4.** $n > 1$, $d > 0$ 인 두 정수 $n, d$ 에 대하여 $-d$ 가 [quadratic residue](https://en.m.wikipedia.org/wiki/Quadratic_residue) modulo $dn - 1$ 이면,
> 
> $n = x^2 + y^2 + z^2$ 을 만족하는 $x, y, z \in \mathbb{Z}$ 가 존재한다.

**Proof.** 조건에 의해 $a_{12}^2 = a_{11} (dn-1) + d$ 인 정수 $a_{11}, a_{12}$ 가 존재한다.

$a_{22} = dn - 1$ 라고 하면, $a_{12}^2 + d = a_{11} a_{12}$ 가 된다.

$d > 0$ 이므로 $a_{11} > 0$, $a_{22} > 0$ 이다.

\begin{aligned}
A = \begin{pmatrix} a_{11} & a_{12} & 1 \\\\  a_{12} & a_{22} & 0 \\\\  1 & 0 & n \end{pmatrix}
\end{aligned}

라고 정의하면,

\begin{aligned}
\mathrm{det} A = 1 \times \mathrm{det} \begin{pmatrix} a_{12} & 1 \\\\  a_{22} & 0 \end{pmatrix} + n \times \mathrm{det} \begin{pmatrix} a_{11} & a_{12} \\\\  a_{12} & a_{22} \end{pmatrix} = -a_{22} + dn = 1
\end{aligned}

이다. 따라서 $F_A$는 판별식이 $1$인 positive definite ternary quadratic form이다.

Theorem 2에 의해 $F_A(x_1, x_2, x_3) \sim x_1^2 + x_2^2 + x_3^2$ 이다.

$n = F_A(0, 0, 1)$ 이므로 $n$은 $x_1^2 + x_2^2 + x_3^2$ 로도 나타낼 수 있다.

---

> **Theorem 3.** (Dirichlet's theorem on arithmetic progression)
> 
> 서로소인 두 양의 정수 $a, d$에 대하여 $a + nd$ 꼴의 소수들이 무한히 많다. ($n$은 양의 정수)

---

> **Theorem 4.** (Legendre's three-square theorem)
> 
> 자연수 $n$이 세 정수의 제곱의 합으로 나타낼 수 있기 위한 필요충분조건은
> 
> $n$이 $4^a(8b + 7)$ 의 꼴이 아니라는 것이다.($a, b$는 음이 아닌 정수)

**Proof of Theorem 3.**

($\to$) 정수를 제곱해서 얻을 수 있는 수들을 $8$로 나눈 나머지는,

- $(4n)^2 = 16n^2 \equiv 0 \pmod{8}$
- $(4n+1)^2 = 16n^2 + 8n + 1 \equiv 1 \pmod{8}$
- $(4n+2)^2 = 16n^2 + 16n + 4 \equiv 4 \pmod{8}$
- $(4n+3)^2 = 16n^2 + 24n + 9 \equiv 1 \pmod{8}$

이므로 $0, 1, 4$ 뿐이다.

따라서 $8$로 나눈 나머지가 $7$인 자연수는 세 정수의 제곱의 합으로 나타낼 수 없다.

또한, 세  $4^a(8b + 7)$($a > 0$) 꼴의 자연수들이 세 정수의 제곱의 합으로 나타낼 수 있다고 가정하자.

제곱수들을 $8$로 나눈 나머지를 생각해보았을 때 세 정수는 모두 짝수일 수밖에 없으므로 짝수인 정수 $x, y, z$에 대하여

\begin{aligned}
4^a(8b + 7) = x^2 + y^2 + z^2
\end{aligned}

라고 쓸 수 있다. 위 식의 양 변을 $4$로 나누면,

\begin{aligned}
4^{a-1}(8b + 7) = \left(\frac{x}{2} \right)^2 + \left(\frac{y}{2} \right)^2 + \left(\frac{z}{2} \right)^2
\end{aligned}

이므로 $4^{a-1}(8b + 7)$ 도 세 정수의 제곱의 합으로 나타낼 수 있음을 알 수 있다.

이를 반복해주면 $8b + 7$ 도 세 정수의 제곱의 합으로 나타낼 수 있게 되므로 모순이 발생한다.

따라서 $4^a(8b + 7)$ 꼴의 정수는 모두 세 정수의 합으로 표현할 수 없다.

---

($\gets$) $1 = 1^2 + 0^2 + 0^2$ 이므로 $n = 1$ 은 세 정수의 제곱의 합으로 나타낼 수 있다.

$4^a(8b + 7)$ 꼴이 아닌 정수 $n > 1$ 을 세 정수의 제곱의 합으로 나타낼 수 있음을 보이자.

- Case 1. $n \equiv 2 \pmod{4}$

$\gcd(4n, n - 1) = 1$ 이므로 Dirichlet's theorem에 의해 $p = 4nj + n - 1 = (4j + 1)n - 1$ 가 소수인 양의 정수 $j$가 존재한다.

정수 $d = 4j + 1$ 이라 하면 $p = dn - 1 \equiv 1 \pmod{4}$ 이므로,

\begin{aligned}
\left( \frac{-d}{p} \right) = \left( \frac{-1}{p} \right) \left( \frac{d}{p} \right) = \left( \frac{d}{p} \right)
\end{aligned}

- Case 2. $2 \nmid n$ and $n \not\equiv 7 \pmod{4}$



- Case 3. $4 \mid n$







