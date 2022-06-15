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

> **Corollary of Lemma 5.** 두 정수의 제곱의 합으로 표현되는 수가 두 정수의 제곱의 합으로 표현할 수 없는 수로 나누어 떨어지면, 그 몫도 두 정수의 제곱의 합으로 표현할 수 없는 수로 나누어 떨어진다.

**Proof.** $a^2 + b^2$ 의 약수이면서 두 정수의 제곱의 합으로 표현할 수 없는 수를 $q$라고 하자.

$a^2 + b^2$ 을 $q$로 나눈 몫의 인수들이 모두 두 정수의 제곱의 합으로 표현된다고 가정하면,

$a^2 + b^2$ 을 몫의 인수들로 계속해서 나누어가다보면 $q$만 남게 되고, $q$도 두 정수의 제곱의 합으로 표현할 수 있게 된다.

이는 모순이므로 따름정리가 증명된다.

---

> **Lemma 6.** 서로소인 두 양의 정수 $a, b$에 대하여 $a^2 + b^2$의 모든 소인수는 두 정수의 제곱수의 합으로 표현할 수 있다.

**Proof.** $a^2 + b^2$ 이 소수이면 자명하므로 소수가 아니라고 하자.

$a^2 + b^2$ 의 인수를 $q$라 하고, $q$가 두 정수의 제곱의 합으로 표현된다는 것을 증명할 것이다.

$q = 2$ 이면 자명하므로 $q > 2$ 라고 하자.

$m, n$을 각각 $mq, nq$가 $a, b$에 가장 가깝도록 하는 음이 아닌 정수라고 하면,

그 차이 $c = a - mq$, $d= b - nq$ 는 절댓값이 $q / 2$ 보다 작은 정수가 된다.

$a, b$에 각 식을 대입해서 정리하면,

\begin{aligned}
a^2 + b^2 &= m^2 q^2 + 2mqc + c^2 + n^2 q^2 + 2nqd + d^2 \\\\  
&= (m^2 q + 2mc + n^2 q + 2nd)q + (c^2 + d^2)
\end{aligned}

을 얻을 수 있고, $c^2 + d^2$ 도 $q$로 나누어 떨어지다는 것을 알 수 있다.

$c, d$의 최대공약수를 $g$라고 하면 $a, b$가 서로소라는 조건으로부터 $g$와 $q$는 서로소이다.

세 정수 $e = c / g$, $f = d / g$, $s = r / g^2$ 이라 정의하면, $e^2 + f^2 = qs$ 가 된다.

이때 $e^2 + f^2 \leq c^2 + d^2 < (q/2)^2 + (q/2)^2 = q^2 / 2$ 임을 이용하면 $qs < q^2 / 2$, $s < q / 2$ 를 얻을 수 있다.

만약 $q$가 두 정수의 제곱의 합으로 표현할 수 없는 수이면, Lemma 5의 따름정리에 의해 $s$의 인수 중에도 두 정수의 제곱으로 표현할 수 없는 수가 존재해야한다.

그러한 인수를 $q_1$이라고 하면, $q_1 \leq s < q / 2 < q$ 이므로 $q_1 < q$ 이다.

서로소인 두 양의 정수 $a, b$와 $a^2 + b^2$의 인수 $q$에 대한 위의 과정을 서로소인 두 양의 정수 $e, f$와 인수 $q_1$에 대해서도 반복해주자.

이렇게 반복해서 얻은 두 정수의 제곱으로 표현할 수 없는 수로 이루어진 수열을 $q, q_1, q_2, \dots$ 라고 하면, 이 수열은 단조감소한다.

양의 정수로 이루어진 수열이 무한히 단조감소하는 것은 불가능하므로 모순이 발생한다.

따라서 $q$는 두 정수의 제곱의 합으로 표현되는 수가 되고, 증명이 완료된다.

---

**Proof of Theorem 2-1.** 소수 $p$를 $p = 4n + 1$라고 하자.

[페르마의 소정리](https://damo1924.github.io/algorithm/BinomialCoefficient/#3-fermats-little-theorem--eulers-theorem)에 의해 모든 정수 $1 \leq a \leq 4n$ 에 대하여 $a^{4n} \equiv 1 \pmod{p}$ 가 성립한다.

이웃한 수들끼리의 차이 $(a + 1)^{4n} - a^{4n}$($1 \leq a < 4n$) 는 모두 $p$로 나누어 떨어진다. 이는

\begin{aligned}
(a + 1)^{4n} - a^{4n} = \left( (a+1)^{2n} - a^{2n} \right) \left( (a+1)^{2n} + a^{2n} \right)
\end{aligned}

로 인수분해할 수 있고, $p$가 소수이므로 두 인수 중 적어도 하나는 $p$로 나누어 떨어져야한다.

모든 $1 \leq a < 4n$ 중 어느 하나라도 $(a+1)^{2n} + a^{2n}$ 가 $p$로 나누어 떨어진다면, Lemma 6에 의해 $p$는 두 정수의 제곱의 합으로 표현이 가능하다.

따라서 $(a+1)^{2n} - a^{2n}$ 가 $p$로 나누어 떨어지지 않은 $a$가 존재한다는 것을 보이면 증명이 완료된다.



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

