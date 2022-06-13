---
title: "밀러-라빈 소수판별법 (Miller-Rabin Primality Test)"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` Miller-Rabin, Fermat's little theorem, Carmichael numbers

## 1. Simple Method: Trial Division

어떤 정수 $n$이 소수인지 판별하는 가장 쉽고 간단한 방법은 약수가 될 수 있는 모든 수로 직접 나누어보는 것이다.

이는 $2$와 $3$부터 $\sqrt{n}$까지의 홀수로만 나누어보는 것으로 최적화가 가능하고, 시간복잡도는 $O(\sqrt{n})$ 이다.

```cpp
bool isPrime(ll n) {
    if (n % 2 == 0) return false;
    for (int i = 3; i * i <= n; i += 2) if (n % i == 0) return false;
    return true;
}
```

구현이 매우 간단하고 확실하게 소수를 판별할 수 있는 방법이라는 장점이 있지만,

항상 $O(\sqrt{n})$ 번 정도의 연산을 수행하기 때문에 $n$이 커지거나 여러 개의 수를 판별해야하는 경우 오래 걸린다는 단점이 있다.

<br/>

## 2. Probabilistic Tests

앞서 살펴본 소수판별법은 예측한 그대로 동작하는 **결정론적 알고리즘(deterministic algorithm)**이었다.

특정 입력에 대해서 항상 동일한 과정을 거쳐 동일한 결과를 반환하는 알고리즘으로, 마치 함수와 같이 동작한다.

반대로, **확률적 알고리즘(probabilistic algorithm)**은 랜덤성을 포함하는 알고리즘을 말한다.

알고리즘의 성능의 **평균적**으로 향상시키기 위해 난수를 이용하는데, 그렇기 때문에 **오류**가 발생할 수 있다.

만약 오류가 발생할 확률을 통제하여 매우 작게 만들 수 있다면, 오류를 감안하더라도 효율성의 측면에서 뛰어나기 때문에 유용하게 사용할 수 있다.

이번 포스팅에서 다루는 밀러-라빈 소수판별법을 포함한 많은 소수판별법들은 확률적 알고리즘이다.

<br/>

## 3. Miller-Rabin Primality Test

###  3-1. Algorithm

**밀러-라빈 소수 판별법**은 **페르마 소정리(Fermat's little theorem)**를 확장하여 얻어지는 확률적 알고리즘이다.

홀수인 소수 $n$은 어떤 양의 정수 $s$와 홀수 $d$에 대하여 아래와 같이 나타낼 수 있다.

\begin{aligned}
n - 1 = 2^s d
\end{aligned}

페르마 소정리에 의해 $a^{n-1} - 1 \equiv 0 \pmod {n}$ 이 성립하고, 좌변을 인수분해하면

\begin{aligned}
a^{n-1} - 1 &= a^{2^s d} - 1 \\\\  
&= (a^{2^{s-1} d} + 1)(a^{2^{s-1} d} - 1) \\\\  
&\vdots
&= (a^{2^{s-1} d} + 1)(a^{2^{s-2} d} + 1) \dots (a^d + 1)(a^d - 1)
\end{aligned}

를 얻을 수 있으므로, 인수들 중 적어도 하나는 소수 $x$의 배수여야 한다.

이를 이용해서 $n$이 소수인지 판별하려고 할 때, 어떤 정수 $a$에 대하여

- $a^d \not\equiv 1 \pmod {n}$
- $a^{2^r d} \not\equiv -1 \pmod {n}$ (for all $0 \leq r \leq s - 1$)

이 성립하면, **$a$는 $n$이 합성수라는 것에 대한 강한 증거(strong witness)**가 된다.

만약 위 두 식 중 하나라도 성립하지 않으면 $a$는 $n$이 합성수라는 것에 대한 **강한 거짓증거(strong liar)**가 되고, $n$은 **확률적 소수(probably prime)**라고 부른다.

이제 $n$보다 작은 양의 정수들 중 무작위로 $a$를 선택한 후, 위의 두 식을 만족하는지 확인하는 과정을 반복함으로써 소수인지 판별하면 된다.

검사를 수행한 $a$의 개수를 $k$라고 하면, 전체 시간복잡도는 $O(k \log ^3 n)$이다.

> $n$의 크기가 작을 경우에는 특정 $a$에 대해서만 검사해보아도 **확실하게 소수를 판별**할 수 있다. 예를 들어,
> 
> - $n < 4759123141$ 이면 $a = 2, 7, 61$ 에 대해서만 검사해보면 된다.
> - $n < 2^{64}$ 이면 $a = 2,3,5,7,11,13,17, 19, 23, 29, 31, 37$ 에 대해서만 검사해보면 된다.
> 
> 등이 알려져 있다.

> $a^{n-1} \equiv 1 \pmod {n}$ 을 만족하는 **합성수** $n$을 **카마이클 수(Carmichael numbers)**라고 부르는데,
> 
> 이로 인해 단순히 여러 정수 $a$에 대하여 페르마의 소정리을 만족하는지 확인함으로써 소수를 판별하는 방법은 사용하지 않는다.

---

### 3-2. Implementation

밀러-라빈 소수판별법을 $O(\log^3 n)$으로 구현한 코드이다.

```cpp
#include <iostream>
using namespace std;
typedef unsigned long long ll;

ll pow(ll x, ll y, ll m) { // x ^ y % m
    if (y == 1) return x % m;
    ll t = pow(x, y / 2, m);
    t = t * t % m;
    if (y % 2) return t * x % m;
    return t;
}

bool isComposite(ll n, ll a, ll d, ll s) {
    ll x = pow(a, d, n);
    if (x == 1 || x == n - 1) return false;
    for (int r = 1; r < s; r++) {
        x = x * x % n;
        if (x == n - 1) return false;
    }
    return true;
}

bool isPrime(ll n) { // Miller-Rabin
    if (n == 1) return false;
    ll d = n - 1, s = 0;
    while (d % 2 == 0) s++, d /= 2;
    for (int a : { 2, 7, 61 }) { // always correct for all unsigned int
        if (n == a) return true;
        if (isComposite(n, a, d, s)) return false;
    }
    return true;
}
```

---

### [BOJ] 5615. 아파트 임대

[BOJ 5615. 아파트 임대 문제 링크](https://www.acmicpc.net/problem/5615)

아파트의 면적은 두 양의 정수 $x, y$에 대하여 $2xy + x + y$로 나타낼 수 있다.

총 $N$($N \leq 10^5$)개의 수가 주어질 때 아파트 면적으로 불가능한 수의 개수를 구하는 문제이다.

> $2xy + x + y = \frac{1}{2} (2x + 1)(2y + 1) - \frac{1}{2}$ 이므로,
> 
> 주어진 수를 $A$라고 하면 $2A + 1$가 소수인 것을 찾으면 된다.
> 
> `long long`의 범위를 초과하기 때문데 `unsigned long long`을 이용해야한다.

<br/>

## References

[1] [WIKIPEDIA, 'Miller–Rabin primality test'](https://en.m.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test)  


