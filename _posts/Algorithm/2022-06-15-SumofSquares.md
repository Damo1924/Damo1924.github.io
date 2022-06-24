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

두 가우스 정수 $z, w$에 대하여 $z$를 $w$로 나누는 과정은 다음과 같다.

> 1) $\frac{z}{w} = x + yi$ 에 가장 가까운 가우스 정수 $a + bi$를 구한다. 아래를 만족하는 $a, b$를 구해주면 된다.
> 
> \begin{aligned}
> \left\vert x - a \right\vert \leq \frac{1}{2},\, \left\vert y - b \right\vert \leq \frac{1}{2}
> \end{aligned}
> 
> 2) $z - w(a + bi)$ 는 $\left( (x - a) + (y - b)i \right) \times b$ 이므로, 노름을 구해주면,
> 
> \begin{aligned}
> N \left(z - w(a + bi) \right) = \left( (x-a)^2 + (y-b)^2 \right) N(b) \leq \frac{1}{2} N(b) < N(b)
> \end{aligned}
> 
> 가 되어 나머지의 정의를 만족한다.
> 
> 3) 따라서 몫은 $a + bi$, 나머지는 $z - w(a + bi)$ 로 구할 수 있다.

---

### 3-5. Euclidean Algorithm

나머지가 작아지도록 나눗셈을 정의하였으므로, [유클리드 호제법](https://damo1924.github.io/algorithm/EuclideanAlgorithm/)을 그대로 적용할 수 있다.

- 가우스 정수 $z, w$에 대하여 $z$를 $w$로 나눈 나머지를 $r$이라 하면, $\gcd(z, w) = \gcd(w, r)$ 이다.

---

### 3-6. Finding Two Squares which Sum to Prime

$p$의 약수 $a + bi$를 구하기 위해 $a + bi$를 약수로 갖는 또다른 가우스 정수 $q$를 찾아 $\gcd(p, q) = a + bi$ 가 되도록 하려고 한다.

$\gcd(p, q) = p$ 이면 안되기 때문에 $q$는 다음 조건을 만족해야한다.

- $N(q)$ 가 $p^2$ 보다 작은 $p$의 배수

이를 만족하는 $q$는 $x^2 \equiv -1 \pmod{p}$ 인 정수 $x$를 찾아 $q = x + i$ 로 구할 수 있다.

$N(q) = x^2 + 1 \equiv 0 \pmod{p}$ 이고, $0 < x < q$ 인 $x$를 찾으면 $N(q) < p^2$ 를 만족한다.

이때 [Euler's criterion](https://damo1924.github.io/math/LegendreJacobiSymbol/#3-eulers-criterion)에 의해 $1 \leq a \leq p - 1$ 인 정수 $a$ 중

\begin{aligned}
a^{(p-1)/2} \equiv -1 \pmod{p}
\end{aligned}

을 만족하는 $a$는 $\frac{p-1}{2}$ 개이므로 $\frac{1}{2}$ 의 확률로 위 합동식을 만족하는 $a$를 찾을 수 있다.

그러한 $a$를 찾았다면 $x = a^{(p-1)/4}$ 이다.

<br/>

## 4. Implementation

[BOJ 17646. 제곱수의 합 2(More Huge)](https://www.acmicpc.net/problem/17646) 소스코드:

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <map>
using namespace std;
typedef long long ll;

vector<ll> factors; // result of factorization

// Fast factorization using Miller-Rabin & Pollard rho algorithm
ll modpow(ll x, ll y, ll mod) {
    ll ret = 1;
    while (y) {
        if (y % 2) ret = (__int128)ret * x % mod;
        x = (__int128)x * x % mod;
        y /= 2;
    }
    return ret;
}
bool miller_rabin(ll n, ll a, ll d, ll s) {
    ll x = modpow(a, d, n);
    if (x == 1) return 0;
    for (int r = 0; r < s; r++) {
        if (x == n - 1) return 0;
        x = (__int128)x * x % n;
    }
    return 1;
}
bool isPrime(ll n) {
    if (n == 1) return 0;
    ll d = n - 1, s = 0;
    while (d % 2 == 0) s++, d /= 2;
    for (ll a : { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 }) {
        if (n % a == 0) return n == a;
        if (miller_rabin(n, a, d, s)) return 0;
    }
    return 1;
}
ll gcd(ll x, ll y) {
    while (y) {
        ll t = x % y;
        x = y;
        y = t;
    }
    return x;
}
ll pollard_rho(ll n) {
    ll x = 2, y = 2, g = 1, c = 1;
    auto f = [&](ll x) { return ((__int128)x * x % n + c) % n; };
    while (g == 1) {
        x = f(x), y = f(f(y));
        g = gcd(x > y ? x - y : y - x, n);
        if (g == n) {
            x = y = rand() % (n - 2);
            c = rand() % 10 + 1;
            g = 1;
        }
    }
    return g;
}
void factorize(ll n) {
    if (isPrime(n)) factors.push_back(n);
    else {
        ll g = (n % 2 ? pollard_rho(n) : 2);
        factorize(g);
        factorize(n / g);
    }
}

// calculate two squares that sum to some integer N using Gaussian integers
__int128 rem(__int128 x, __int128 y) { // remainder which is -y/2 < r < y/2
    __int128 r = x % y;
    if (r < 0) r += y;
    if (2 * r > y) r -= y;
    return r;
}
pair<ll, ll> gaussian_rem(ll a, ll b, ll c, ll d) { // calculating remainder of gaussian integers
    __int128 Re = (__int128)a * c + (__int128)b * d;
    __int128 Im = (__int128)c * b - (__int128)a * d;
    __int128 N = (__int128)c * c + (__int128)d * d;
    __int128 x = (Re - rem(Re, N)) / N;
    __int128 y = (Im - rem(Im, N)) / N;
    return { a - c * x + d * y, b - c * y - d * x };
};
pair<ll, ll> gaussian_gcd(ll a, ll b, ll c, ll d) { // GCD of gaussian integers
    while (c != 0 || d != 0) {
        pair<ll, ll> r = gaussian_rem(a, b, c, d);
        a = c, b = d;
        c = r.first, d = r.second;
    }
    return { a, b };
}
ll quadratic_residue(ll p) { // return any quadratic residue of prime p
    for (int x = 2; ; x++) {
        ll a = modpow(x, p / 4, p);
        if ((__int128)a * a % p == p - 1) return a;
    }
}
pair<ll, ll> two_square_sum_prime(ll p) { // get a, b which is a^2 + b^2 = p for prime p
    if (p == 2) return { 1, 1 };
    return gaussian_gcd(p, 0, quadratic_residue(p), 1);
}
pair<ll, ll> two_square_sum(ll n) { // get a, b which is a^2 + b^2 = n
    factorize(n);
    map<ll, ll> m;
    for (ll i : factors) m[i]++;
    for (auto i : m) if (i.first % 4 == 3 && i.second % 2) return { -1, -1 };

    ll a = 1, b = 0, k = 1;
    for (auto i : m) {
        k *= modpow(i.first, i.second / 2, 1e18);
        if (i.second % 2) {
            pair<ll, ll> tmp = two_square_sum_prime(i.first);
            ll c = a * tmp.first + b * tmp.second;
            ll d = a * tmp.second - b * tmp.first;
            a = c, b = d;
        }
    }
    if (a < 0) a *= -1;
    if (b < 0) b *= -1;
    return { k * a, k * b };
}

vector<ll> solve(ll N) {
    ll k = 1;
    while (N % 4 == 0) k *= 2, N /= 4;

    vector<ll> ans;

    ll N2 = sqrt(N);
    if (N2 * N2 == N) { // 1 square
        ans.push_back(k * N2);
        return ans;
    }

    if (N % 8 == 7) {
        N--;
        ans.push_back(k);
    }
    else {
        pair<ll, ll> res = two_square_sum(N);
        if (res.first != -1) { // 2 square
            ans.push_back(k * res.first);
            ans.push_back(k * res.second);
            return ans;
        }
    }

    for (ll c = 1; ; c++) { // find c which N - c^2 can be represented by sum of two squares
        ll n = N - c * c;
        factors.clear();
        pair<ll, ll> res = two_square_sum(n);
        if (res.first != -1) {
            ans.push_back(k * c);
            ans.push_back(k * res.first);
            ans.push_back(k * res.second);
            return ans;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    ll N; cin >> N;
    vector<ll> ans = solve(N);
    sort(ans.begin(), ans.end());
    cout << ans.size() << "\n";
    for (ll i : ans) cout << i << " ";
}
```

<br/>

## References

[1] [SECMEM, ho94949, '제곱수의 합'](http://www.secmem.org/blog/2019/10/18/sum-of-squares/)  
[2] [WIKIPEDIA, 'Landau-Ramanujan constant'](https://en.m.wikipedia.org/wiki/Landau%E2%80%93Ramanujan_constant)  
[3] [WIKIPEDIA, 'Gaussian integer'](https://en.m.wikipedia.org/wiki/Gaussian_integer)  


