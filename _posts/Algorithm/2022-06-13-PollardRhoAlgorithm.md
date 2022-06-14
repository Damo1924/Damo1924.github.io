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

`Tags` 폴라드 로, 소인수분해

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

인수분해를 하고자 하는 정수 $n = pq$과 $n$의 자명하지 않은 인수 $p$를 생각하자.

임의의 정수 $c$, 함수 $f(x) = x^2 + c \pmod{n}$ 와 초기값 $x_0$ 로부터 만들 수 있는 수열

\begin{aligned}
x_0, x_1 = f(x_0), x_2 = f(x_1), \dots, x_k = f(x_{k-1}), \dots
\end{aligned}

과 $y_i = x_i \pmod{p}$($i \geq 0$) 로 정의되는 수열은 모두 사이클을 갖는다.

$y_i = y_j$ 인 서로 다른 두 인덱스 $i, j$에 대하여 $p \mid (x_j - x_i)$ 이고, $(x_j - x_i) \mid n$ 이다.

즉, 수열 $x$에서 $\gcd(x_j - x_i, n) \neq 1$ 인 $i, j$를 찾으면 $n$은 $p = \gcd(x_j - x_i, n)$ 라는 인수를 갖는다고 할 수 있다.

만약 $\gcd(x_j - x_i, n) = n$ 이면 $c$ 또는 $x_0$ 를 바꾸어가며 알고리즘을 수행해주면 된다.

---

### 2-2. Time Complexity (Birthday Paradox)

> **Birthday paradox**에 의하면, 무작위 수열에 $N$개의 숫자가 나타날 때 사이클이 나타나는 순간의 기댓값은 $O(\sqrt{N})$ 정도라고 한다.
> 
> $p$는 $n$의 인수이므로 $p \leq \sqrt{n}$ 이므로 수열 $y_i$에서 사이클이 나타나는 순간의 기댓값은 $O(\sqrt[4]{n})$ 이다.
> 
> 폴라드 로 알고리즘의 실제 수행시간도 이를 따른다고 알려져 있긴 하지만, 엄밀히 증명된 적은 없다.

---

### 2-3. Implementation (Factorization)

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



<br/>

## Referernces


