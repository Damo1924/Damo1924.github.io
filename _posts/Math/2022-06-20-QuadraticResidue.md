---
title: "Properties of Quadratic Residue Modulo Prime Numbers"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Math
use_math: true
comments: true

---

`Tags` NumberTheory, Legendre symbol, Law of quadratic reciprocity, Lagrange's theorem, Euler's criterion

이번 포스팅에서는 소수의 제곱 잉여들이 가지는 성질들에 대해서 공부해볼 것이다.

먼저 제곱 잉여가 무엇이고, 소수의 제곱 잉여에 관한 함수인 르장드르 기호에 대해 공부하고,

소수의 제곱 잉여의 성질들을 증명해본 후, 이를 르장드르 기호로 표현하는 것까지의 과정을 정리하였다.

<br/>

## 1. Definitions

### 1-1. Quadratic Residue

두 정수 $q, n$에 대하여

\begin{aligned}
x^2 \equiv q \pmod{n}
\end{aligned}

을 만족하는 정수 $x$가 존재하면 **$q$가 $n$의 제곱 잉여(quadratic residue)**라고 한다.

반대로 그러한 정수 $x$가 존재하지 않는다면 **$q$가 $n$의 제곱 비잉여(quadratic non-residue)**라고 한다.

---

### 1-2. Legendre Symbol

**르장드르 기호(Legendre symbol)**은 홀수인 소수 $p$와 정수 $a$에 대하여 다음과 같이 정의된 함수이다.

\begin{aligned}
\left( \frac{a}{p} \right) = \begin{cases}
1 & \mbox{if }a\mbox{ is a quadratic residue modulo }p\mbox{ and }a \not\equiv 0 \pmod{p}, \\\\  
-1 & \mbox{if }a\mbox{ is a quadratic non-residue modulo }p, \\\\  
0 & \mbox{if }a \equiv 0 \pmod{p}.
\end{cases}
\end{aligned}

<br/>

## 2. Lagrange's Theorem in Number Theory

> **Theorem 2.1.** (Lagrange's theorem)
> 
> 소수 $p$와 정수 계수를 가지는 다항식 $f(x) = a_n x^n + a_{n-1} x^{n-1} + \dots + a_0 \in \mathbb{Z}\[x\]$ ($a_n \not\equiv 0 \pmod{p}$)에 대하여,
> 
> $f(x) \equiv 0 \pmod{p}$ 는 최대 $\mathrm{deg} f(x) = n$ 개의 합동이 아닌 해(incongruent solution)를 갖는다.

**Proof.** 수학적 귀납법을 이용해서 증명할 수 있다.

$n = 1$ 일 때, $f(x) = a_1x + a_0 \equiv 0 \pmod{p}$ 로부터

\begin{aligned}
a_1 x \equiv -a_0 \pmod{p}
\end{aligned}

이다. $p$가 소수이고 $a_1 \not\equiv 0 \pmod{p}$ 이므로 $\gcd(a_1, p) = 1$ 이다. 따라서

\begin{aligned}
x \equiv -a_0a_1^{-1} \pmod{p}
\end{aligned}

인 해가 하나 존재하고, 이로부터 주어진 명제가 $n = 1$에 대해서 성립함을 알 수 있다.

$n = k - 1$ 일 때 주어진 명제가 성립한다고 가정하자.

$n = k$ 일 때 함수 $f(x) = a_k x^k + a_{k-1} x^{k-1} + \dots + a_0$ 에 대하여

$f(x) \equiv 0 \pmod{p}$ 가 합동이 아닌 $k + 1$ 개의 해 $x_0, x_1, \dots, x_k$ 를 갖는다고 가정하자.

\begin{aligned}
f(x) - f(x_0) = a_k (x^k - x_0^k) + a_{k-1} (x^{k-1} - x_0^{k-1}) + \dots + a_1 (x - x_0)
\end{aligned}

이므로 $f(x) - f(x_0) = (x - x_0) g(x)$ 인 $k-1$ 차 정수 계수 다항식 $g(x)$ 가 존재한다.

그런데 $f(x_0) \equiv 0 \pmod{p}$ 이므로 $f(x) \equiv (x - x_0) g(x) \pmod{p}$ 이다.

따라서 $x_1, x_2, \dots, x_k$ 는 $g(x) \equiv 0 \pmod{p}$ 의 합동이 아닌 해들이다.

이는 가정에 모순이므로 $n = k$ 일 때 주어진 명제가 성립함을 알 수 있다.

수학적 귀납법에 의해 증명이 완료된다.

<br/>

## 3. Euler's Criterion

> **Theorem 3.1.** (Euler criterion)
> 
> 홀수인 소수 $p$, $p$와 서로소인 정수 $a$에 대하여 다음이 성립한다.
> 
> \begin{aligned}
> a^{\frac{p-1}{2}\} \equiv \begin{cases}
> 1 \pmod{p} & \mbox{if }a\mbox{ is a quadratic residue modulo }p, \\\\  
> -1 \pmod{p} & \mbox{if }a\mbox{ is a quadratic non-residue modulo }p.
> \end{cases}
> \end{aligned}
> 
> 르장드르 기호를 이용하면 아래와 같이 표현할 수도 있다.
> 
> \begin{aligned}
> \left( \frac{a}{p} \right) \equiv a^{\frac{p-1}{2}\} \pmod{p}
> \end{aligned}

**Proof.** Lagrange's theorem에 의해 $x^2 \equiv a \pmod{p}$ 는 최대 $2$개의 서로 다른 해를 가질 수 있다.

즉, $0$부터 $p-1$까지의 정수를 제곱했을 때 $p$로 나눈 나머지가 동일한 수는 최대 두 개이다.

따라서 홀수인 소수 $p$는 $0$ 외에도 최소 $\frac{p-1}{2}$개의 서로 다른 제곱 잉여를 갖는다.

소수 $p$와 서로소인 정수 $a$에 대하여 페르마의 소정리(Fermat's little theorem)에 의해

\begin{aligned}
a^{p-1} \equiv 1 \pmod{p}
\end{aligned}

가 성립한다. 위 식은

\begin{aligned}
\left( a^{\frac{p-1}{2}\} - 1 \right) \left( a^{\frac{p-1}{2}\} + 1 \right) \equiv 0 \pmod{p}
\end{aligned}

로 변형할 수 있다. 이때 $p$가 소수이므로 위의 두 인자 중 하나는 $0$이어야한다.

Lagrange's theorem에 의해 $a^{\frac{p-1}{2}\} - 1 \equiv 0 \pmod{p}$ 을 만족하며 합동이 아닌 $a$는 최대 $\frac{p-1}{2}$ 개이다.

또, 만약 $a$가 $p$의 $0$이 아닌 제곱 잉여이면 $x^2 \equiv a \pmod{p}$ 인 정수 $x$가 존재하고,

\begin{aligned}
a^{\frac{p-1}{2}\} \equiv x^{p-1} \equiv 1 \pmod{p}
\end{aligned}

이다. 즉 $p$의 $0$이 아닌 제곱 잉여들은 $a^{\frac{p-1}{2}\} - 1 \equiv 0 \pmod{p}$ 을 만족한다.

앞에서 홀수인 소수 $p$는 $0$ 외에도 최소 $\frac{p-1}{2}$개의 서로 다른 제곱 잉여를 갖는다는 것을 증명했으므로,

$a^{\frac{p-1}{2}\} \equiv 1 \pmod{p}$ 을 만족하는 정수 $a$는 $p$의 제곱 잉여뿐이다.

그렇다면 $p$의 제곱 비잉여들은 모두 $a^{\frac{p-1}{2}\} \equiv -1 \pmod{p}$ 을 만족해야한다.

<br/>

## 4. Law of Quadratic Reciprocity

**이차 상호 법칙(law of quadratic reciprocity)**은 두 홀수인 소수가 서로에 대하여 제곱 잉여인지의 여부가 대칭적이라는 정리이다.

가우스가 처음으로 증명한 이후로 지금까지 200개 이상의 증명이 알려져 있는데, 대표적인 증명 방법 중 하나를 소개하고자 한다.

> **Lemma 4.1.** (Gauss's lemma)
> 
> 홀수인 소수 $p$, $p$와 서로소인 정수 $a$에 대하여
> 
> \begin{aligned}
> \left( \frac{a}{p} \right) = (-1)^n
> \end{aligned}
> 
> 이 성립한다. 이때 $n$은 정수
> 
> \begin{aligned}
> a,\,2a,\,3a,\dots,\frac{p-1}{2}a
> \end{aligned}
> 
> 들의 $p$로 나눈 나머지(least positive residues modulo $p$) 중 $\frac{p}{2}$ 보다 큰 것의 개수이다.

**Proof.** 주어진 $\frac{p-1}{2}$ 개의 정수들의 곱

\begin{aligned}
Z = a \cdot 2a \cdot 3a \cdot \dots \cdot \frac{p-1}{2}a
\end{aligned}

을 $p$로 나눈 나머지를 두 가지 서로 다른 방법으로 구함으로써 증명할 수 있다.

첫 번째로, $Z$는 간단히 다음과 같이 표현할 수 있다.

\begin{aligned}
Z = a^{(p-1)/2} \left( 1 \cdot 2 \cdot 3 \cdot \dots \cdot \frac{p-1}{2} \right)
\end{aligned}

두 번째 방법은 조금 복잡한데, $x$가 $1 \leq x \leq p - 1$ 인 정수(nonzero residue modulo $p$)일 때 $\left\vert x \right\vert$를 다음과 같이 정의하자.

\begin{aligned}
\left\vert x \right\vert = \begin{cases}
x & \mbox{if }1 \leq x < \frac{p}{2}, \\\\  
p - x & \mbox{if }\frac{p}{2} < x \leq p - 1.
\end{cases}
\end{aligned}

또, $1 \leq k \leq \frac{p-1}{2}$ 인 정수 $k$에 대하여 $ka$의 least positive residue modulo $p$를 $r(k)$라고 정의하자.

그렇다면 $n$의 정의에 의해 다음과 같이 쓸 수 있다.

\begin{aligned}
Z \equiv (-1)^n \left( \left\vert r(1) \right\vert \cdot \left\vert r(2) \right\vert \cdot \left\vert r(3) \right\vert \cdot \dots \cdot \left\vert r \left( \frac{p-1}{2} \right) \right\vert \right)
\end{aligned}

이제 $\left\vert r(k) \right\vert$ ($1 \leq k \leq \frac{p-1}{2}$) 중 겹치는 수가 없다는 것을 증명하자.

$\left\vert r(k_1) \right\vert \equiv \left\vert r(k_2) \right\vert \pmod{p}$ 을 만족하는 서로 다른 두 정수 $k_1, k_2$($1 \leq k_1, k_2 \leq (p-1)/ 2$)가 존재한다고 가정하자.

위에서 정의한 절댓값 기호의 정의에 따라 $r(k_1) \equiv \pm r(k_2) \pmod{p}$ 이고,

$r(k) \equiv ka \pmod{p}$ 이므로 $k_1 a \equiv \pm k_2 a \pmod{p}$ 를 얻을 수 있다.

$a$와 $p$가 서로소이므로 $r \equiv \pm s \pmod{p}$ 가 된다.

그런데 $r, s$는 $1$보다 크거나 같고 $\frac{p-1}{2}$보다 작거나 같은 정수이므로 $r = s$ 이다.

이는 $r, s$가 서로 다른 정수라는 가정에 모순이므로 $\left\vert r(k) \right\vert$ 들은 모두 서로 다르다.

이때 $1 \leq \left\vert r(k) \right\vert \leq \frac{p-1}{2}$ 이므로 $r(k)$들의 곱은 $1$부터 $\frac{p-1}{2}$까지의 정수들을 곱과 같다.

따라서 $Z$는 아래와 같이 표현할 수 있다.

\begin{aligned}
Z \equiv (-1)^n \left( 1 \cdot 2 \cdot 3 \cdot \dots \cdot \frac{p-1}{2} \right) \pmod{p}
\end{aligned}

첫 번째 방법과 두 번째 방법이 서로 합동이어야하므로

\begin{aligned}
a^{(p-1)/2} \equiv (-1)^n \pmod{p}
\end{aligned}

가 성립한다. 이때 Euler criterion에 의해 $a^{(p-1)/2} \equiv \left( \frac{a}{p} \right) \pmod{p}$ 이므로 증명이 완료된다.

---

> **Lemma 4.2.** (Eisenstein's lemma)
> 
> 홀수인 소수 $p$와 $q$에 대하여 다음이 성립한다.
> 
> \begin{aligned}
> \left( \frac{q}{p} \right) = (-1)^n
> \end{aligned}
> 
> 이때 $n$은 다음과 같이 정의된다.
> 
> \begin{aligned}
> n = \sum_{k=1}^{(p-1)/2} \left\lfloor \frac{kq}{p} \right\rfloor
> \end{aligned}

**Proof.** Gauss's lemma를 이용해서 증명할 것이다.



---

> **Theorem 4.1.** (Law of quadratic reciprocity)
> 
> $p$와 $q$를 서로 다른 홀수인 소수라고 할 때 다음이 성립한다.
> 
> \begin{aligned}
> \left( \frac{p}{q} \right) \left( \frac{q}{p} \right) = (-1)^{\frac{p-1}{2} \frac{q-1}{2}\}
> \end{aligned}

**Proof.** (Eisenstein's proof)



<br/>

## 5. Quadratic Residue Modulo Prime

먼저, 모든 정수는 $2$의 제곱 잉여이다.

홀수인 소수 $p$에 대하여 $0$부터 $p-1$까지의 정수 중 

<br/>

## References

[1] [WIKIPEDIA, 'Quadratic residue'](https://en.m.wikipedia.org/wiki/Quadratic_residue)  
[2] [WIKIPEDIA, 'Legendre symbol'](https://en.m.wikipedia.org/wiki/Legendre_symbol)  
[3] [WIKIPEDIA, 'Lagrange's theorem (number theory)'](https://en.m.wikipedia.org/wiki/Lagrange%27s_theorem_(number_theory))  
[4] [WIKIPEDIA, 'Euler's criterion'](https://en.m.wikipedia.org/wiki/Euler%27s_criterion)  
[5] [WIKIPEDIA, 'Proofs of quadratic reciprocity'](https://en.m.wikipedia.org/wiki/Proofs_of_quadratic_reciprocity)  
[6] 
