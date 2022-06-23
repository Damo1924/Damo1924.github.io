---
title: "자연수를 제곱수들의 합으로 표현하는 방법"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` NumberTheory, 17633, 17646, Gaussian intergers, Euclidean algorithm

이 포스팅은 아래 문제들을 풀기 위해 필요한 내용에 대해 다루고 있다.

- [BOJ 17633. 제곱수의 합(More Huge)](https://www.acmicpc.net/problem/17633)
- [BOJ 17646. 제곱수의 합 2(More Huge)](https://www.acmicpc.net/problem/17646)

<br/>

## 1. How many squares are needed to represent given integer $N$?

이번 포스팅의 주제는 제목 그대로 **주어진 자연수를 제곱수들의 합으로 표현**하는 것이다.

일단 $1$이 제곱수이기 때문에 제곱수들의 개수에 제한을 두지 않는다면, 어떤 자연수라도 제곱수들의 합으로 나타낼 수 있음은 자명하다.

이처럼 가장 많은 개수의 제곱수들의 합으로 표현하는 방법은 너무 뻔하기 때문에, 자연스럽게 다음과 같은 궁금증이 생기게 된다.

- 주어진 자연수를 제곱수들의 합으로 표현하기 위해 필요한 **제곱수의 개수의 최솟값**은 얼마일까?

만약 주어진 자연수가 제곱수라면, 하나의 제곱수로 표현하는 것이 가능하다.

다음으로는 $13 = 3^2 + 2^2$ 이나 $29 = 5^2 + 2^2$ 처럼 두 개의 제곱수의 합으로 표현할 수 있는 자연수도 있다.

또, $14 = 3^2 + 2^2 + 1^2$ 은 세 개, $7 = 2^2 + 1^2 + 1^2 + 1^2$ 은 네 개나 필요하다.

그렇다면 적어도 다섯 개의 제곱수가 필요한 자연수도 있을까? 아래 정리를 보자.

> **Theorem 1.1.** (Lagrange's four-square theorem)
> 
> 모든 자연수는 **네 정수의 제곱의 합**으로 나타낼 수 있다.
> 
> 즉, 임의의 자연수 $n$에 대하여 $n = a_1^2 + a_2^2 + a_3^2 + a_4^2$ 을 만족하는 네 정수 $a_1, a_2, a_3, a_4$ 가 존재한다.
> 
> [Lagrange's four-square theorem의 증명](https://damo1924.github.io/math/FourSquareTheorem/)

따라서 어떤 자연수를 제곱수들의 합으로 표현하기 위한 제곱수의 개수의 최솟값으로 가능한 수는 $1, 2, 3, 4$ 뿐임을 알 수 있다.

아래 정리는 좀 더 상세한 조건을 서술하고 있다.

> **Theorem 1.2.** (Legendre's three-square theorem)
> 
> 자연수 $n$이 **세 정수의 제곱의 합**으로 나타낼 수 있기 위한 필요충분조건은
> 
> $n$이 $4^a(8b + 7)$ 의 꼴이 아니라는 것이다.($a, b$는 음이 아닌 정수)
> 
> [Legendre's three-square theorem의 증명](https://damo1924.github.io/math/ThreeSquareTheorem/)

이를 통해 $4^a(8b + 7)$ 꼴의 자연수의 제곱수의 개수의 최솟값은 $4$라는 것을 알 수 있다.

마지막으로, 아래 정리를 이용하면 모든 자연수에 대하여 완벽히 최솟값을 구할 수 있게 된다.

> **Theorem 1.3.** (Fermat's theorem on sums of two squares)
> 
> 홀수인 소수 $p$가 두 정수의 제곱의 합으로 나타낼 수 있기 위한 필요충분조건은 $p \equiv 1 \pmod{4}$ 이다.
> 
> [Fermat's theorem on sums of two squares의 증명](https://damo1924.github.io/math/SumofTwoSquares/)

> **Corollary of Theorem 1.3.** (Sum of two squares theorem)
> 
> $1$보다 큰 정수가 두 정수의 제곱의 합으로 나타낼 수 있기 위한 필요충분조건은 정수를 소인수분해했을 때 $p^k$를 포함하지 않는 것이다.
> 
> 이때 $p$는 $4$로 나눈 나머지가 $3$인 소수이고, $k$는 홀수이다.

 따라서 임의의 자연수 $N$에 대하여, 다음과 같은 과정을 통해 $N$을 제곱수의 합으로 표현하기 위한 제곱수의 개수의 최솟값을 구할 수 있다.
 
 1. $N$이 $4^a(8b + 7)$ 꼴의 자연수인지 확인 $\to$ 맞다면 최소 네 제곱수의 합으로 표현 가능하다.
 2. $N$을 소인수분해 했을 때, $4$로 나눈 나머지가 $3$인 소수가 홀수 개만큼 있는지 확인 $\to$ 있다면 $N$은 최소 세 제곱수의 합으로 표현 가능하다.
 3. $N$이 제곱수인지 확인 $\to$ 제곱수이면 한 개, 아니면 두 개의 제곱수의 합으로 표현 가능하다.

$N$의 소인수분해는 [폴라드 로 알고리즘(Pollard's rho algorithm](https://damo1924.github.io/algorithm/PollardRhoAlgorithm/)을 이용하면 $O(\sqrt[4]{n})$ 로 수행할 수 있다.

<br/>

## 2. How to find the squares which sum to a given integer $N$

임의의 자연수 $N$을 제곱수의 합으로 표현하기 위한 제곱수의 개수의 최솟값 $m$을 구했으므로, 직접 $N$을 $m$개의 제곱수들의 합으로 표현해보자.

먼저 $m = 1$ 이면 $N = \left( \sqrt{N} \right)^2$ 으로 바로 구할 수 있다.

$m = 4$ 이면 $N = 4^a(8b + 7) = (2^a)^2 + 4^a(8b + 6)$ 이고 $4^a(8b + 6)$은 세 제곱수의 합으로 표현이 가능하므로,

$m = 3$ 인 경우에 대하여 세 제곱수의 합으로 표현하는 방법을 구할 수 있으면 $m = 4$ 인 경우도 쉽게 구할 수 있다.

$m = 3$ 이면 $N' = N - c^2$ 이 두 제곱수의 합으로 표현할 수 있는 적당한 $c$를 찾으면 된다.

이러한 $c$를 찾기 위해 $c = 1$ 부터 $1$씩 증가시키면, 아래 정리에 의해 평균적으로 $O(\sqrt{\ln N})$ 내에 찾을 수 있음이 보장된다.

> **Theorem 2.1.** (Landau)
> 
> 어떤 양의 실수 $b$와 충분히 큰 $x$에 대해, $x$ 이하의 양의 정수 중 두 제곱수의 합으로 나타내어지는 것의 개수는 점근적으로 $\frac{bx}{\sqrt{\ln x}\}$ 이다.

이때 $b$를 [란다우-라마누잔 상수(Landau-Ramanujan constant)](https://en.m.wikipedia.org/wiki/Landau%E2%80%93Ramanujan_constant)라 부르고, 이 값은 $0.76422 \ldots$ 이다.

즉, $c = 1$ 부터 $1$씩 증가시키며 찾아도 충분히 빠른 시간 내에 찾을 수 있다.

지금까지 $m = 4$ 인 경우는 $m = 3$ 으로, $m = 3$ 인 경우는 $m = 2$ 인 경우로 바꿀 수 있다는 것을 알 수 있었다.

따라서 $m = 2$ 인 자연수 $N$을 두 제곱수의 합으로 표현하는 방법만 안다면, 나머지 케이스들도 어렵지 않게 구할 수 있다.

또한, Fermat's theorem on sums of two squares (Theorem 1.3)을 증명하는 과정에서 사용한 보조정리

> **Lemma 2.2.** 두 정수의 제곱의 합으로 표현되는 두 수의 곱은 두 정수의 제곱의 합으로 표현이 가능하다.
> 
> \begin{aligned}
> (a_1^2 + a_2^2)(b_1^2 + b_2^2) = (a_1b_1 + a_2b_2)^2 + (a_1b_2 - a_2b_1)^2
> \end{aligned}

를 이용하면, $N$의 소인수들을 두 제곱수의 합으로 표현하면 $N$을 두 제곱수의 합으로 표현할 수 있게 된다.

따라서 임의의 자연수 $N$을 $m$개의 제곱수들의 합으로 표현하는 문제는

- **$p \equiv 1 \pmod{4}$ 인 소수 $p$를 두 제곱수의 합으로 표현하는 문제**

가 된다. $p \equiv 3 \pmod{4}$ 인 소수는 두 제곱수의 합으로 표현할 수 없기 때문이다.

<br/>

## 3. Finding Two Squares which Sum to Prime using Gaussian Integer

### 3-1. Gaussian Integer

**가우스 정수(gaussian integer)**란 실수부와 허수부가 모두 정수인 복소수를 의미한다.

가우스 정수들의 집합 $\mathbb{Z}\[i\]$ 은

\begin{aligned}
\mathbb{Z}\[i\] = \\{ a + bi \mid a, b \in \mathbb{Z} \\}
\end{aligned}

와 같이 쓸 수 있고, 복소수의 덧셈과 곱셈에 의해 닫혀 있다.

또한 덧셈의 항등원이 $0$이고, 곱셈의 항등원이 $1$이라는 점, 그리고 나눗셈에 대하여 닫혀있지 않다는 점 등 **가우스 정수는 일반적인 정수와 비슷한 성질**을 가진다.

따라서 우리는 정수에서 소수를 정의했듯이 가우스 정수에서도 가우스 소수(Gaussian prime)을 정의할 수 있다.

---

### 3-2. Definition of Gaussian Prime

일반적으로 "소수"라 함은 자연수 범위에서 다음과 같이 정의된다.

- $1$보다 큰 자연수 중 $1$과 자기 자신만을 약수로 가지는 수

수학자들은 소수라는 개념을 자연수에 제한하지 않고 더 큰 범위로 확장하였다.

> 덧셈과 곱셈이 정의된 대수적 구조를 [환(ring)](https://en.m.wikipedia.org/wiki/Ring_(mathematics))이라고 부르는데, 이 중 곱셈의 교환법칙이 성립하는 것을 [가환환(commutative ring)](https://en.m.wikipedia.org/wiki/Commutative_ring)이라고 부른다.
> 
> 가환환에서 곱셈에 대한 역원을 가지는 원소들을 [가역원(unit)](https://en.m.wikipedia.org/wiki/Unit_(ring_theory))이라 한다.
> 
> 환 $R$의 원소 $u$에 대하여
> 
> \begin{aligned}
> uv = vu = 1
> \end{aligned}
> 
> 을 만족하는 $v \in R$ 이 존재하면, $u$를 $R$의 가역원이라고 한다.
> 
> 이때 $1$은 곱셈에 대한 항등원을 의미한다.
> 
> $0$이 아닌 원소 $u \in R$ 가 **가역원이 아닌 두 원소의 곱**으로 나타내어지지 않는다면 $u$를 [기약수(irreducible number)](https://www.scienceall.com/%EA%B8%B0%EC%95%BDirreducible-%E6%97%A3%E7%B4%84/)라고 정의하였다.
> 
> 이때 $0$은 덧셈에 대한 항등원을 의미한다.

정수에서 소수(정확히 말하면 기약수)는 다음과 같이 정의된다.

- $0$이나 $1, -1$이 아닌 정수 $n$를 두 정수의 곱 $n = ab$으로 나타내었을 때, $a, b$ 중 하나가 반드시 가역원인 수

다시 말해, $0$이나 $1, -1$이 아닌 정수 $n$ 중 $1, -1$ 과 $n, -n$ 만으로 나누어 떨어지는 수를 의마한다.

이때 $0$은 정수의 덧셈에 대한 항등원이고, $1$과 $-1$은 정수의 가역원이다.

이를 가우스 정수에 대해서도 똑같이 적용해주면, 가우스 소수를 정의할 수 있게 된다.

가우스 정수의 덧셈에 대한 항등원은 $0$이고, 가역원은 $\pm 1, \pm i$ 이다. 따라서

- $0$이나 $\pm 1, \pm i$ 가 아닌 가우스 정수 $z$를 두 가우스 정수의 곱 $z = w_1w_2$로 나타내었을 때, $w_1, w_2$ 중 하나가 반드시 가역원인 수

와 같이 가우스 소수를 정의할 수 있다.

---

### 3-3. Relation between Gaussian Primes & Finding Two Squares which Sum to Prime

그런데 왜 갑자기 가우스 정수와 가우스 소수라는 개념을 정의했을까?

그 이유는 아래의 가우스 정수 $z = a + bi$ 가 가우스 소수가 되기 위한 필요충분조건으로부터 알 수 있다.

- $a, b$ 중 하나가 $0$이고 다른 하나의 절댓값이 $4n + 3$ 꼴의 소수이거나,
- $a, b$ 가 둘 다 $0$이 아니면서 $a^2 + b^2$ 이 $4n + 1$ 꼴의 소수

만약 어떤 소수 $p$를 두 제곱수의 합 $a^2 + b^2 = p$ 로 나타낼 수 있다면, $p$는 가우스 소수가 아니다. 이는

\begin{aligned}
p = (a + bi)(a - bi)
\end{aligned}

가우스 정수의 범위에서 위와 같이 소인수분해가 가능하기 때문이다.

따라서 두 제곱수의 합으로 나타내어야하는 소수를 **가우스 정수의 범위에서 소인수분해**를 하면 원하는 두 제곱수를 찾을 수 있음을 알 수 있다.

---

### 3-4. Euclidean Division on Gaussian Integers

가우스 정수에서 소인수분해를 하기 위해서는 나눗셈을 했을 때의 **몫과 나머지**를 정의해야한다.

자연수의 나눗셈을 할 때 가장 중요한 것 중 하나는 **나머지의 크기가 나누는 수보다 작아야한다**는 것임을 떠올린다면, 아래와 같이 나눗셈을 정의할 수 있다.

- 가우스 정수 $z, w$에 대하여 $z$를 $w$로 나눈 몫을 $q$, 나머지를 $r$이라고 했을 때, $z = wq + r$ 이고, $N(r) < N(w)$ 이다.

이때 $N(a + bi)$는 가우스 정수 $a + bi$ 의 **노름(norm)**이라고 부르며,

\begin{aligned}
N(a + bi) = (a + bi)(a - bi) = a^2 + b^2
\end{aligned}

으로 정의된다, 이는 실수부와 허수부를 각각 제곱해서 더해준 것과 같다.






<br/>

## References

[1] [SECMEM, ho94949, '제곱수의 합'](http://www.secmem.org/blog/2019/10/18/sum-of-squares/)  
[2] [WIKIPEDIA, 'Landau-Ramanujan constant'](https://en.m.wikipedia.org/wiki/Landau%E2%80%93Ramanujan_constant)  
[3] [WIKIPEDIA, 'Gaussian integer'](https://en.m.wikipedia.org/wiki/Gaussian_integer)  
[4] 


