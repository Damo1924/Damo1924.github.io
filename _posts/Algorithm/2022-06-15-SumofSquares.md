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

> **Theorem 1.** (Lagrange's four-square theorem)
> 
> 모든 자연수는 네 정수의 제곱의 합으로 나타낼 수 있다.
> 
> 즉, 임의의 자연수 $n$에 대하여 $n = a_1^2 + a_2^2 + a_3^2 + a_4^2$ 을 만족하는 네 정수 $a_1, a_2, a_3, a_4$ 가 존재한다.

이를 증명하기 위해서는 아래의 세 보조정리가 필요하다.

---

> **Lemma 1.** (Euler's four-square identity)
> 
> 네 정수의 제곱의 합으로 표현되는 두 정수의 곱은 네 정수의 제곱의 합으로 표현할 수 있다.

**Proof.** 정수 $a_i$, $b_i$에 대하여 다음이 성립한다.

\begin{aligned}
(a_1^2 + a_2^2 + a_3^2 + a_4^2) (b_1^2 + b_2^2 + b_3^2 + b_4^2) &= (a_1 b_1 + a_2 b_2 + a_3 b_3 + a_4 b_4)^2 \\\\  
&+ (a_1 b_2 - a_2 b_1 - a_3 b_4 + a_4 b_3)^2 \\\\  
&+ (a_1 b_3 + a_2 b_4 - a_3 b_1 - a_4 b_2)^2 \\\\  
&+ (a_1 b_4 - a_2 b_3 + a_3 b_2 - a_4 b_1)^2
\end{aligned}

---

> **Lemma 2.** 어떤 정수 $m$에 대하여 $2m$ 이 두 정수의 제곱의 합으로 나타낼 수 있으면, $m$도 두 정수의 제곱의 합으로 나타낼 수 있다.

**Proof.** $2m = a^2 + b^2$ 라고 하면, $a$와 $b$는 모두 짝수이거나 모두 홀수이다.

따라서 $m$은 아래와 같이 두 정수의 제곱의 합으로 나타낼 수 있다.

\begin{aligned}
m = \left( \frac{x-y}{2} \right)^2 + \left( \frac{x+y}{2} \right)^2
\end{aligned}

---

> **Lemma 3.** 모든 소수 $p$에 대하여 $p^2$보다 작은 $p$의 배수 중 네 정수의 제곱의 합으로 표현 가능한 것이 존재한다.

**Proof.** $p = 2$는 $2 = 1^2 + 1^2 + 0^2 + 0^2$ 이므로 성립한다.

홀수인 소수 $p$와 $p$보다 작은 자연수 $k$에 대하여 $a^2 + b^2 + 1 = kp$ 를 만족하는 정수 $a, b$ 가 존재함을 보이자.

$p = 2n + 1$ 라고 할 때, 다음과 같은 두 집합 $A, B$를 정의하자.

- $A := \\{ a^2 \\mid a = 0, 1, \dots, n \\}$
- $B := \\{ -b^2 - 1 \mid b= 0, 1, \dots, n \\}$

$x^2 \equiv y^2 \pmod{p}$ 인 서로 다른 두 정수 $x, y$($0 \leq x, y \leq n$)가 존재한다고 가정하자.

$(x-y)(x+y) \equiv 0 \pmod{p}$ 로부터 $p \mid x-y$ 또는 $p \mid x+y$ 임을 알 수 있다.

그런데 $x-y \leq x + y < 2n < p$ 이므로 모순이 발생한다.

따라서 집합 $A$의 어떤 두 원소도 법 $p$에 대한 합동(congruent modulo $p$)이 아니다.

같은 방법으로 집합 $B$의 어떤 두 원소도 법 $p$에 대한 합동(congruent modulo $p$)이 아님을 증명할 수 있다.

집합 $A$의 원소들은 모두 음이 아닌 정수이고, 집합 $B$의 원소들은 모두 음의 정수이므로 $A \cup B$ 에는 $2n + 2 = p + 1$ 개의 원소가 있다.

비둘기집 원리에 의해서 $A \cup B$ 에는 법 $p$에 대하여 합동인 두 원소가 존재한다.

즉, $a^2 \equiv -b^2 - 1 \pmod{p}$ 인 $a^2 \in A$, $-b^2-1 \in B$ 가 존재하므로 다음을 얻을 수 있다.

\begin{aligned}
a^2 + b^2 + 1 = kp
\end{aligned}

이때 $a^2 + b^2 + 1 \leq 2n^2 + 1 < p^2$ 이므로 $k < p$ 이다.

---

위 보조정리들을 이용해서 Lagrange's four-square theorem을 증명해보자.

**Proof of Theorem 1.** 먼저, Lemma 1에 의해 모든 소수 $p$가 네 정수의 제곱의 합으로 표현된다는 것만을 증명하면 된다.

$p = 2$ 는 자명하므로 $p$가 홀수라고 가정하자.

Lemma 3에 의해 $mp = a_1^2 + a_2^2 + a_3^2 + a_4^2$ 인 정수 $m$($0 < m < p$), $a_1, a_2, a_3, a_4$ 가 존재한다.

$m = 1$ 이면 소수 $p$가 네 정수의 제곱의 합으로 나타낼 수 있음을 의미하므로 증명이 끝난다.

$m > 1$ 인 경우에 대해서 $np$($1 \leq n < m$)가 네 정수의 제곱의 합으로 나타낼 수 있음을 보이면 된다.

$m$이 짝수이면 $a_1, a_2, a_3, a_4$를 홀짝성이 동일한 두 정수로 이루어진 두 그룹으로 나눌 수 있고, 이는 Lemma 2에 의해 $n = m / 2$ 라고 할 수 있다.

이제 $m$이 $1$보다 큰 홀수라고 가정하자.

$1 \leq i \leq 4$ 인 $i$에 대하여 정수 $b_i$를 다음과 같이 정의하자.

- $b_i \equiv a_i \pmod{m}$
- $b_i \in (-m/2, m/2)$

그렇다면

\begin{aligned}
b_1^2 + b_2^2 + b_3^2 + b_4^2 < 4 \cdot \frac{m^2}{4} = m^2
\end{aligned}

\begin{aligned}
b_1^2 + b_2^2 + b_3^2 + b_4^2 \equiv 0 \pmod{m}
\end{aligned}

이므로, 어떤 음이 아닌 정수 $n$에 대하여 $b_1^2 + b_2^2 + b_3^2 + b_4^2 = nm$ 라고 할 수 있다.

또한, $b_1^2 + b_2^2 + b_3^2 + b_4^2 < m^2$ 이므로 $n < m$ 이다.

만약 $n = 0$ 이면 $b_i = 0$ 이 되어 $a_i \equiv 0 \pmod{m}$ 인데,

$mp = a_1^2 + a_2^2 + a_3^2 + a_4^2 \equiv 0 \pmod{m^2}$ 이므로 $m \mid p$ 가 된다.

그런데 $p$가 소수이고 $m$은 $1$보다 크기 때문에 $m = p$ 일 수 밖에 없고, 이는 $m < p$ 라는 것에 모순이다.

따라서 $n$은 $0$보다 크고 $m$보다 작은 정수이다.

Lemma 1의 증명에서 사용한 식의 좌변은

\begin{aligned}
(a_1^2 + a_2^2 + a_3^2 + a_4^2)(b_1^2 + b_2^2 + b_3^2 + b_4^2) = mp \cdot nm = nm^2p
\end{aligned}

이고, 우변의 네 항은

\begin{aligned}
a_1 b_1 + a_2 b_2 + a_3 b_3 + a_4 b_4 \equiv b_1^2 + b_2^2 + b_3^2 + b_4^2 \equiv 0 \pmod{m}
\end{aligned}

\begin{aligned}
a_1 b_2 - a_2 b_1 - a_3 b_4 + a_4 b_3 = (a_1 b_2 - a_2 b_1) - (a_3 b_4 - a_4 b_3) \equiv 0 \pmod{m}
\end{aligned}

\begin{aligned}
a_1 b_3 + a_2 b_4 - a_3 b_1 - a_4 b_2 = (a_1 b_3 - a_3 b_1) + (a_2 b_4 - a_4 b_2) \equiv 0 \pmod{m}
\end{aligned}

\begin{aligned}
a_1 b_4 - a_2 b_3 + a_3 b_2 - a_4 b_1 = (a_1 b_4 - a_4 b_1) - (a_2 b_3 + a_3 b_2) \equiv 0 \pmod{m}
\end{aligned}

이므로 모두 $m$의 배수이다. 따라서 양변의 모든 항은 $m^2$으로 나누어 떨어진다.

실제로 양변을 $m^2$으로 나누면 $np$가 네 정수의 제곱의 합으로 나타내어짐을 알 수 있다.

이때 $0 < n < m$ 이므로 증명이 끝난다.

<br/>

## 2. Fermat's Theorem on Sums of Two Squares

> **Theorem 2-1.** (Fermat's theorem on sums of two squares)
> 
> 홀수인 소수 $p$가 두 정수의 제곱의 합으로 나타낼 수 있기 위한 필요충분조건은 $p \equiv 1 \pmod{4}$ 이다.

> **Theorem 2-2.** (Sum of two squares theorem)
> 
> $1$보다 큰 정수가 두 정수의 제곱의 합으로 나타낼 수 있기 위한 필요충분조건은 정수를 소인수분해했을 때 $p^k$를 포함하지 않는 것이다.
> 
> 이때 $p$는 $4$로 나눈 나머지가 $3$인 소수이고, $k$는 홀수이다.

Theorem 2-2는 Theorem 2-1로부터 간단히 증명할 수 있으므로 Theorem 2-1을 증명해보자.

---

> **Lemma 4.** 두 정수의 제곱의 합으로 표현되는 두 수의 곱은 두 정수의 제곱의 합으로 표현이 가능하다.

**Proof.** $(a_1^2 + a_2^2)(b_1^2 + b_2^2) = (a_1 b_1 + a_2 b_2)^2 + (a_1 b_2 - a_2 b_1)^2$ 이므로 증명된다.

---

> **Lemma 5.** 두 정수의 제곱의 합으로 표현되는 수가 두 정수의 제곱의 합으로 표현되는 소수로 나누어 떨어지면, 그 몫도 두 정수의 제곱의 합으로 표현이 가능하다.

**Proof.** $a = a_1^2 + a_2^2$ 가 소수 $p = p_1^2 + p_2^2$ 로 나누어 떨어진다고 하자. 그렇다면,

\begin{aligned}
(p_1 a_2 - a_1 p_2) (p_1 a_2 + a_1 p_2) &= p_1^2 a_2^2 - a_1^2 p_2^2 \\\\  
&= p_1^2 (a_1^2 + a_2^2) - a_1^2 (p_1^2 + p_2^2)
&= p_1^2 a - a_1^2 p \equiv 0 \pmod{p}
\end{aligned}

이므로, $p_1 a_2 - a_1 p_2$ 또는 $p_1 a_2 + a_1 p_2$ 중 적어도 하나는 $p$로 나누어 떨어진다.

일반성을 잃지 않고 $p_1 a_2 - a_1 p_2$ 가 $p$로 나누어 떨어진다고 할 수 있다. Lemma 1에 의해,

\begin{aligned}
ap = (a_1^2 + a_2^2)(p_1^2 + p_2^2) = (a_1 p_1 + a_2 p_2)^2 + (a_1 p_2 - a_2 p_1)^2
\end{aligned}

이므로 $(a_1 p_1 + a_2 p_2)^2$ 도 $p$로 나누어 떨어진다.

위 식의 양변을 $p^2$로 나누어주면,

\begin{aligned}
\frac{a}{p} = \left( \frac{a_1 p_1 + a_2 p_2}{p} \right)^2 + \left( \frac{a_1 p_2 - a_2 p_1}{p} \right)^2
\end{aligned}

이고 모든 항은 정수이므로 증명이 완료된다.

---

> **Lemma 6.** 서로소인 두 양의 정수 $a, b$에 대하여 $a^2 + b^2$의 모든 소인수는 두 정수의 제곱수의 합으로 표현할 수 있다.

**Proof.** $a^2 + b^2$ 이 소수이면 자명하므로 소수가 아니라고 하자.



<br/>

## 3. Legendre's Three-Square Theorem

> **Theorem 3.** (Legendre's three-square theorem)
> 
> 자연수 $n$이 세 정수의 제곱의 합으로 나타낼 수 있기 위한 필요충분조건은
> 
> $n$이 $4^a(8b + 7)$ 의 꼴이 아니라는 것이다.($a, b$는 음이 아닌 정수)

정수 $x$를 제곱했을 때 $8$로 나눈 나머지는 $0$ 또는 $1$ 또는 $4$뿐이라는 것을 이용하면 $n = 4^a(8b + 7)$ 꼴의 수를 세 제곱수의 합으로 표현하지 못한다는 것은 쉽게 증명할 수 있다.

<br/>

 




## References

[1] [WIKIPEDIA, 'Lagrange's four-square theorem'](https://en.m.wikipedia.org/wiki/Lagrange%27s_four-square_theorem)  
[2] [WIKIPEDIA, 'Legendre's three-square theorem'](https://en.m.wikipedia.org/wiki/Legendre%27s_three-square_theorem)  
[3] [WIKIPEDIA, 'Fermat's theorem on sums of two squares'](https://en.m.wikipedia.org/wiki/Fermat%27s_theorem_on_sums_of_two_squares)  
[4] 

