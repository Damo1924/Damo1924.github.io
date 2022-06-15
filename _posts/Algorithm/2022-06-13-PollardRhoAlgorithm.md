---
title: "Cycle Detection & Pollard's rho algorithm"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` 폴라드 로, 소인수분해, factorization, Birthday paradox

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

```cpp
pair<int, int> floyd(x_0) { // for given f, x_0
    int x = f(x_0), y = f(f(x_0));
    while (x != y) x = f(x), y = f(y);
    
    // get mu
    int m = 0;
    x = x_0;
    while (x != y) {
        x = f(x), y = f(y);
        m++;
    }
    
    // get lambda
    int l = 1;
    y = f(x);
    while (x != y) {
        y = f(y);
        l++;
    }
    
    return { l, m };
}
```

---

### 1-2. Brent's algorithm

브랜트의 알고리즘은 $\lambda$와 $\mu$보다 큰 $2$의 거듭제곱 중 가장 작은 것을 구함으로써 사이클을 찾는 알고리즘이다.

음이 아닌 정수 $i = 0, 1, 2, \dots$ 에 대하여 $x_{2^{i-1}\}$와 $x_j$($2^{i-1} < j < 2^i$)를 비교한다.

이는 플로이드의 알고리즘에 비해 $\lambda$를 직접 구할 수 있을 뿐만 아니라, 각 단계마다 함수 $f$를 적용하는 연산을 한 번만 수행한다는 장점이 있다.

시간복잡도는 $O(\mu + \lambda)$ 로 플로이드 알고리즘과 동일하다.

> 실제 속도는 평균적으로 브랜트 알고리즘이 플로이드 알고리즘보다 36% 정도 더 빠르다고 한다.

```cpp
pair<int, int> brent(x_0) { // for given f, x_0
    // get lambda
    int p = 1, l = 1; // p = 2^i, l = j - p
    int x = x_0, y = f(x_0);
    while (x != y) { // x == y -> l = lambda
        if (i == j) {
            x = y;
            p *= 2;
            l = 0;
        }
        y = f(y);
        l++;
    }
    
    // get mu
    x = x_0, y = x_0;
    for (int i = 0; i < l; i++) y = f(y);
    int m = 0;
    while (x != y) {
        x = f(x), y = f(y);
        m++;
    }
    
    return { l, m };
}
```

<br/>

## 2. Pollard's rho algorithm

### 2-1. Algorithm

**폴라드 로 알고리즘**은 함수 $f(x)$와 초기값 $x_0$에 대한 **cycle finding을 이용해서 인수를 찾는 확률적 알고리즘**이다.

> 수열을 방향그래프로 나타냈을 때의 형태가 $\rho$ 와 비슷해서 'rho' 라는 이름이 붙게 되었다.

> 폴라드 로 알고리즘은 다음을 **보장하지 않음**에 주의해야한다.
> 
> - 항상 인수를 발견
> - 발견한 인수가 소수

인수분해를 하고자 하는 정수 $n = pq$과 $n$의 자명하지 않은 인수 $p$($p \leq \sqrt{n}$)를 생각하자.

임의의 정수 $c$, 함수 $f(x) = x^2 + c \pmod{n}$ 와 초기값 $x_0$ 로부터 만들 수 있는 수열

\begin{aligned}
x_0, x_1 = f(x_0), x_2 = f(x_1), \dots, x_k = f(x_{k-1}), \dots
\end{aligned}

과 $y_i = x_i \pmod{p}$($i \geq 0$) 로 정의되는 수열은 모두 사이클을 갖는다.

$y_i = y_j$ 인 서로 다른 두 인덱스 $i, j$에 대하여 $p \mid x_i - x_j$ 이고, $p \mid n$ 이므로 다음이 성립한다.

\begin{aligned}
p \mid \gcd(x_i - x_j, n)
\end{aligned}

즉, 수열 $x$에서 $\gcd(x_j - x_i, n) \neq 1$ 인 $i, j$를 찾으면 $n$은 $p = \gcd(x_j - x_i, n)$ 라는 인수를 갖는다고 할 수 있다.

---

### 2-2. Time Complexity (Birthday Paradox)

$n$의 어떤 인수 $p$에 대하여 $y_i = y_j$ 인 두 인덱스 $i, j$($1 \leq i < j \leq k$)가 존재하는 **범위 $k$의 기댓값**은 어느 정도일까?

이는 **생일 역설(birthday paradox)**과 비슷한 방법으로 대략 $\sqrt{p}$ 임을 알 수 있다.

> **Birthday Paradox**: $n$명의 사람 중 생일이 같은 사람이 존재할 확률에 대한 문제이다.
> 
> 생일로 가능한 경우의 수가 $365$개이므로 단순히 생각하면 생일이 같은 사람이 존재하기 위해서는 많은 사람이 필요할 것 같지만,
> 
> $30$명 중 생일이 같은 사람이 존재할 확률은 $60$%보다 크고, $60$명 중 생일이 같은 사람이 존재할 확률은 $99$%보다 크다.

$y_1, y_2, \dots, y_k$ 중 겹치는 것이 없을 확률을 $P$라고 하면,

\begin{aligned}
P &= \left( 1 - \frac{1}{p} \right) \left( 1 - \frac{2}{p} \right) \dots \left( 1 - \frac{k - 1}{p} \right) \\\\  
&\leq e^{-1/p} \cdot e^{-2/p} \dots e^{-(k-1)/p} \\\\  
&= e^{- \frac{k(k-1)}{2p}\} \\\\  
&\sim e^{-k^2 / (2p)}
\end{aligned}

이다. 위 식에 $k = \sqrt{p}$ 를 대입하면, $k$개의 수들 중 겹치는 것이 없을 확률은 대략 $e^{-1/2} \leq 2/3$ 임을 알 수 있다.

따라서 겹치는 수가 존재할 확률이 어느 정도 있다고 할 수 있다.

이때 $p \leq \sqrt{n}$ 이므로 $k = \sqrt[4]{n}$ 이다.

그런데 $1 \leq i < j \leq k$ 에 있는 순서쌍 $(i, j)$의 개수는 ${k \choose 2} \sim \frac{1}{2} \sqrt{n}$ 이므로 **모든 수로 직접 나누어보는 브루트포스 방법과 차이가 없다**는 것을 알 수 있다.

이를 해결하기 위한 방법이 바로 **함수 $f(x) = x^2 + c \pmod{n}$와 초기값 $x_0$로 얻어지는 수열의 사이클을 찾는 것**이다.

> 엄밀히 증명된 것은 아니지만, 대부분의 초기값 $x_0$에 대하여 $x_i \equiv x_j \pmod{p}$인 인덱스 $i < j < C \sqrt{p}$ ($C$는 작은 상수) 가 존재한다는 것이 경험적으로(empirically) 확인되었다.

따라서 **cycle finding algorithm**을 이용하면 위의 "경험적 사실"에 의해 $C \sqrt{p} \leq C \sqrt[4]{n}$ 번 정도를 탐색하면 원하는 순서쌍을 찾을 수 있다.

만약 사이클을 찾는 탐색 횟수가 너무 길어진다면, 포기하고 $c$ 또는 $x_0$의 값을 바꾸어서 찾으면 된다.

---

### 2-3. Implementation (Factorization)

$\gcd(x_i - x_j, n)$의 값이 $1$이 아닐 때까지 플로이드 알고리즘을 통해 사이클을 찾아주도록 구현하였다.

만약 $\gcd(x_i - x_j, n) = n$ 이면 $c$와 $x_0$를 다른 랜덤한 값으로 바꾼 후 사이클을 찾아주었다.

폴라드 로 알고리즘을 사용할 때에는 반드시 **해당 수가 합성수인지 확인**해야하기 때문에 [밀러-라빈 소수판별법](https://damo1924.github.io/algorithm/MillerRabinPrimalityTest/)을 이용하였다.

또한, 폴라드 로 알고리즘이 반환하는 인수는 소인수라는 보장이 없기 때문에 재귀적으로 적용해서 소인수분해를 할 수 있다.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
using namespace std;
typedef unsigned long long ll;

ll modpow(ll x, ll y, ll mod) {
    ll ret = 1;
    while (y) {
        if (y % 2) ret = (__int128) ret * x % mod;
        x = (__int128) x * x % mod;
        y /= 2;
    }
    return ret;
}

bool miller_rabin(ll n, ll a, ll d, ll s) {
    ll x = modpow(a, d, n);
    if (x == 1) return 0;
    for (int r = 0; r < s; r++) {
        if (x == n - 1) return 0;
        x = (__int128) x * x % n;
    }
    return 1;
}

bool isPrime(ll n) { // 밀러-라빈
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
    auto f = [&](ll x) { return ((__int128) x * x % n + c) % n; };
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

vector<ll> factors;
void factorize(ll n) { // 소인수분해
    if (isPrime(n)) factors.push_back(n);
    else {
        ll g = (n % 2 ? pollard_rho(n) : 2); // 2^k 을 인수로 갖는 경우를 처리해주기 위함
        factorize(g);
        factorize(n / g);
    }
}
```

<br/>

## 3. Related Problems

### [BOJ] 4149. 큰 수 소인수분해

[BOJ 4149. 큰 수 소인수분해 문제 링크](https://www.acmicpc.net/problem/4149)

$1$보다 크고 $2^{62}$보다 작은 정수가 주어질 때, 해당 수를 소인수분해한 결과를 출력하는 문제이다.

---

### [BOJ] 13926. gcd(n, k) = 1

[BOJ 13926. gcd(n, k) = 1 문제 링크](https://www.acmicpc.net/problem/13926)

자연수 $n$($1 \leq n \leq 10^{18}$)이 주어졌을 때, $\gcd(n, k)= 1$을 만족하는 자연수 $1 \leq k \leq n$ 의 개수를 구하는 문제이다.

> $n$을 소인수분해하여 서로 다른 소인수들을 구한다.
> 
> 포함 배제의 원리를 이용하면 $n$과 서로소가 아닌 $k$의 개수를 구할 수 있고, 이를 $n$에서 빼주면 원하는 값을 구할 수 있다.

<br/>

## Referernces

[1] [WIKIPEDIA, 'Pollard's rho algorithm'](https://en.m.wikipedia.org/wiki/Pollard%27s_rho_algorithm)  
[2] [MIT 18.310 lecture notes, Michel Goemans, 'Factoring'](https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&cad=rja&uact=8&ved=2ahUKEwj52dGZlqz4AhWVSWwGHfIYCtkQFnoECDUQAQ&url=https%3A%2F%2Fmath.mit.edu%2F~goemans%2F18310S15%2Ffactoring-notes.pdf&usg=AOvVaw0nAwtS-kP0M-01Ri_XO1dQ)
