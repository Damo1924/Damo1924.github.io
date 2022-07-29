---
title: "Sqrt Decomposition & Mo's Algorithm"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:    
  - Algorithm
use_math: true
comments: true

---

`Tags` 구간 쿼리

## 1. Sqrt Decomposition

**평방 분할(sqrt decomposition)**은 **전체 구간을 $\sqrt{n}$개의 같은 크기의 블록으로 나누어서 관리**함으로써 구간 쿼리를 $O(\sqrt{n})$에 처리할 수 있는 방법이다.

예를 들어 부분 수열의 합을 구하는 쿼리나, 최대/최소값을 구하는 쿼리 같은 것들을 빠르게 구할 수 있다.

> 물론 각 쿼리를 $O(\log n)$에 처리할 수 있는 **세그먼트 트리(segment tree)**보단 못하다.

좀 더 직관적인 이해를 위해 구간 합 쿼리를 평방 분할을 이용해서 처리해보자.

---

### 1-1. Element Update & Range Query Problem

길이가 $n$인 수열 $a_0, a_1, a_2, \dots, a_{n-1}$ 에 대하여 다음의 두 쿼리를 $O(\sqrt{n})$에 처리해야한다.

- 임의의 두 정수 $i, v$에 대하여 $a_i = v$ 로 업데이트하는 쿼리
- 임의의 두 정수 $l, r$($l < r$)가 주어졌을 때 구간 합 $a_l + a_{l+1} + \dots + a_r$ 의 값을 구하는 쿼리

$\sqrt{n}$가 정수가 아닐 수 있으므로 올림을 해주어서 각 블록의 크기 $s$를 정해주자.

\begin{aligned}
s = \lceil \sqrt{n} \rceil
\end{aligned}

이때 마지막 블록의 크기가 $s$보다 작을 수 있지만, 일단은 무시하자.

각 블록에 속한 원소들의 합을 $b_0, b_1, b_2, \dots, b_{s-1}$ 라고 하면,

\begin{aligned}
b_0 &= a_0 + a_1 + \dots + a_{s-1}, \\\\  
b_1 &= a_s + a_{s+1} + \dots + a_{2s-1}, \\\\  
& \vdots \\\\  
b_{s-1} &= a_{(s-1)s} + \dots + a_{n-1}.
\end{aligned}

이므로, 정수 $k$($0 \leq k < s$)에 대하여

\begin{aligned}
b_k = \sum_{i = ks}^{\min(n-1, (k+1)s - 1)} a_i
\end{aligned}

와 같이 쓸 수 있다. 모든 $b_k$들을 구하는데는 $O(n)$이 걸린다.

이제 구간 쿼리 $l, r$을 처리해보자.

구간 $\[l, r\]$은 크게 세 가지 부분으로 구분할 수 있다.

1. 블록의 일부만 구간에 속하는 원소들 (구간 왼쪽): $a_l, \dots, a_{xs - 1}$
2. 블록 전체가 구간에 속하는 원소들
3. 블록의 일부만 구간에 속하는 원소들 (구간 오른쪽): $a_{ys}, \dots, a_r$

이미 2번에 속하는 원소들의 합은 구해두었기 때문에 해당하는 $b_k$를 더해주기만 하면 된다.

2번에 해당하는 블록은 최대 $s$개이기 때문에 $O(s)$가 걸린다.

1번과 3번에 속하는 원소들은 최대 $2(s-1)$개이기 때문에 직접 더해주어도 $O(s)$이다.

따라서 임의의 구간에 대하여 구간 합을 구하는 쿼리를 $O(s) = O(\sqrt{n})$ 으로 처리할 수 있음을 알 수 있다.

만약 **데이터를 업데이트하는 쿼리**가 주어진다면 어떻게 할까?

블록의 구간의 합은 단순히 그 차이만큼 더해주면 되므로 $O(1)$에 처리할 수 있고,

> 만약 구간의 최대/최소값을 구하는 문제라면, 업데이트를 위해서는 해당 블록을 전부 탐색하면 되므로 $O(s)$가 걸린다.

쿼리의 개수를 $q$라고 하면 전체 시간복잡도는 $O(n + q \sqrt{n})$ 으로, 세그먼트 트리만큼은 아니지만 충분히 빠르다.

아래는 [BOJ 2042. 구간 합 구하기](https://www.acmicpc.net/problem/2042)을 위 방법으로 해결한 코드이다.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
using namespace std;
typedef long long ll;

struct sqrt_decomposition {
    int n, s;
    vector<ll> a, b;
    sqrt_decomposition(int _n) {
        n = _n, s = (int)sqrt(n) + 1;
        a.resize(n);
        b.resize(s, 0);
    }
    void init() {
        for (int i = 0; i < n; i++) b[i / s] += a[i];
    }
    void upd(int i, ll val) {
        b[i / s] += val - a[i];
        a[i] = val;
    }
    ll query(int l, int r) {
        ll ret = 0;
        int L = l / s, R = r / s;
        if (L == R) for (int i = l; i <= r; i++) ret += a[i];
        else {
            for (int i = l; i < (L + 1) * s; i++) ret += a[i];
            for (int i = L + 1; i < R; i++) ret += b[i];
            for (int i = R * s; i <= r; i++) ret += a[i];
        }
        return ret;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n, m, k; cin >> n >> m >> k;
    sqrt_decomposition sd(n);
    for (int i = 0; i < n; i++) cin >> sd.a[i];
    sd.init();
    for (int i = 0; i < m + k; i++) {
        ll a, b, c; cin >> a >> b >> c;
        if (a == 1) sd.upd(b - 1, c);
        else cout << sd.query(b - 1, c - 1) << "\n";
    }
}
```

---

### 1-2. Update Range & Element Query Problem

이번에는 주어진 구간에 속하는 원소들에 특정 값을 더해주고, 특정 원소 하나의 값을 출력하는 문제를 평방 분할로 해결해보자.

구간 업데이트를 할 때 **양쪽 끝 블록에 속하는 원소들에는 직접 더해주고**, **블록이 구간 전체에 속한다면 해당 블록에 값을 더해준다**.

그렇다면 원소 $i$의 값은 `a[i] + b[i / s]` 로 구할 수 있다.

아래는 [BOJ 16975. 수열과 쿼리 21](https://www.acmicpc.net/problem/16975)을 평방 분할로 해결한 코드이다.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
using namespace std;
typedef long long ll;

struct sqrt_decomposition {
    int n, s;
    vector<ll> a, b;
    sqrt_decomposition(int _n) {
        n = _n, s = (int)sqrt(n) + 1;
        a.resize(n);
        b.resize(s, 0);
    }
    void upd(int l, int r, ll val) {
        int L = l / s, R = r / s;
        if (L == R) for (int i = l; i <= r; i++) a[i] += val;
        else {
            for (int i = l; i < (L + 1) * s; i++) a[i] += val;
            for (int i = L + 1; i < R; i++) b[i] += val;
            for (int i = R * s; i <= r; i++) a[i] += val;
        }
    }
    ll query(int i) {
        return a[i] + b[i / s];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n; cin >> n;
    sqrt_decomposition sd(n);
    for (int i = 0; i < n; i++) cin >> sd.a[i];
    int m; cin >> m;
    while (m--) {
        int t; cin >> t;
        if (t == 1) {
            int l, r, k; cin >> l >> r >> k;
            sd.upd(l - 1, r - 1, k);
        }
        else {
            int x; cin >> x;
            cout << sd.query(x - 1) << "\n";
        }
    }
}
```

---

이렇게 평방 분할을 이용하면 다양한 구간 쿼리를 비교적 빠르게 처리할 수 있다.

그럼에도 세그먼트 트리에 비해 메리트가 없어보이는 것이 사실이다.

하지만 평방 분할의 진가는 **Mo's algorithm**에서 드러난다.

<br/>

## 2. Mo's Algorithm

Mo's algorithm은 **해당 구간에 속하는 원소들을 모두 탐색해야 구간 쿼리를 처리할 수 있는 경우** 유용하게 사용할 수 있는 알고리즘이다.

대표적으로 [BOJ 13547. 수열과 쿼리 5](https://www.acmicpc.net/problem/13547)와 같은 문제가 있다.

길이가 $n$인 수열이 주어질 때, 구간 $\[l, r\]$에 있는 서로 다른 원소의 개수를 구해야하는데,

세그먼트 트리나 머지 소트 트리 등의 자료구조를 사용할려고 생각해보아도 결국 구간에 속하는 모든 원소들을 살펴보아야 한다는 결론을 내리게 된다.

모든 원소를 살펴보면 각 쿼리마다 $O(n)$이 걸리기 때문에 쿼리의 개수를 $q$라고 할 때 전체 시간복잡도가 $O(qn)$이다.

그런데 Mo's algorithm을 이용하면 $O((n + q) \sqrt{n})$ 으로 해결할 수 있다.

알고리즘의 핵심은 바로 **오프라인 쿼리 문제**라는 점을 이용해 **쿼리를 특정 순서로 정렬한 후 빠르게 해결**하는 것이다.

평면 분할에서 했던 것처럼 전체 구간을 $\sqrt{n}$개의 크기의 블록들로 나눈 후, 주어진 쿼리 $\[l_i, r_i\]$ 들을 아래 규칙으로 정렬하자.

1. 구간의 오른쪽 끝이 속한 블록이 증가하는 순서대로 정렬: $\lfloor \frac{r_i}{s} \rfloor < \lfloor \frac{r_j}{s} \rfloor$
2. 만약 두 구간의 오른쪽 끝이 동일한 블록에 속한다면, 왼쪽 끝이 증가하는 순서대로 정렬: $l_i < l_j$

이제 두 포인터 $l, r$을 움직여가면서 정렬한 순서대로 쿼리를 처리해줄 것이다.

구간의 오른쪽 끝을 나타내는 포인터 $r$가 쿼리마다 이동하는 횟수를

- 하나의 블록 내에서 $x$번 이동
- 다른 블록으로 이동하기 위해 $y$번 이동

으로 정의할 때, $O(x) = O(\sqrt{n})$ 이고 $O(\sum_{i=1}^q y_i) = O(n)$ 이므로 $r$이 움직이는 전체 횟수는

\begin{aligned}
O(n + q \sqrt{n})
\end{aligned}

이다. 구간의 왼쪽 끝을 나타내는 포인터 $l$은 $r$이 같은 블록 내에 있을 때 $O(n)$번 움직이게 된다.

즉, $l$이 움직이는 전체 횟수는

\begin{aligned}
O(n \sqrt{n})
\end{aligned}

이다. 따라서 Mo's algorithm을 이용하면 $O((n + q) \sqrt{n})$ 으로 문제를 해결할 수 있게 되는 것이다.

<br/>

## 3. Related Problems

### [BOJ] 13547. 수열과 쿼리 5

[BOJ 13547. 수열과 쿼리 5 문제 링크](https://www.acmicpc.net/problem/13547)

주어진 구간에 있는 서로 다른 수의 개수를 구하는 쿼리를 처리하는 문제이다.





<br/>

## References

[1] [Algorithms for Competitive Programming, 'Sqrt Decomposition'](https://cp-algorithms.com/data_structures/sqrt_decomposition.html)  
[2] [secmem.org, djm03178, 'Mo's Algorithm'](https://www.secmem.org/blog/2019/02/09/mo%27s-algorithm/#fn:1)  
