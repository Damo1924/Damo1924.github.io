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

> 꼭 위의 규칙으로 정렬할 필요는 없으며, 문제를 풀기에 편한 쪽으로 순서를 정해주면 된다.

---

### Implementation

쿼리를 저장하는 방법에 따라서 구현 방법이 달라진다.

만약 모든 쿼리를 하나의 배열에 저장하여 처리하려고 한다면

```cpp
int n, sq; // sq = (int)sqrt(n) + 1;
struct query {
    int l, r, i;
    bool operator<(const query& q) const {
        int x = r / s, y = q.r / s;
        if (x == y) return l < q.l;
        return x < y;
    }
};
```

와 같이 구현한 후, 전체 쿼리들을 정렬해준다.

만약 구간의 오른쪽 끝이 같은 블록에 속한 쿼리들끼리 묶어서 저장하려고 한다면

```cpp
struct query {
    int l, r, i;
    bool operator<(const query& q) const { return l < q.l; }
};
```

와 같이 구현한 후, 같은 블록에 속한 쿼리들끼리 정렬하고 처리해준다.

각 방법으로 직접 문제를 풀어보았는데, 두 번째 방법이 좀 더 다양한 문제에 적용하기 편했다.

<br/>

## 3. Related Problems

Mo's algorithm은 코드가 정형화된 알고리즘보다는 **오프라인 쿼리를 빠르게 처리할 수 있는 방법**에 가깝기 때문에 원리를 이해하고 문제에 맞게 구현하여야한다.

---

### [BOJ] 13547. 수열과 쿼리 5 (서로 다른 수의 개수)

[BOJ 13547. 수열과 쿼리 5 문제 링크](https://www.acmicpc.net/problem/13547)

주어진 구간에 있는 **서로 다른 수의 개수**를 구하는 쿼리를 처리하는 문제이다.

$1 \leq a_i \leq 10^6$ 이므로 $1$부터 $10^6$까지의 정수가 해당 구간에서 각각 몇 번 등장하는지 저장하는 배열을 만들고,

구간의 양 끝 포인터를 움직여가면서 위 배열을 업데이트해주면 된다.

만약 새로운 수가 추가되었다면 서로 다른 수의 개수에 $1$을 더해주고, 하나밖에 없는 수가 제거되었다면 서로 다른 수의 개수에서 $1$을 빼준다.

아래는 앞서 설명한 두 번째 방법으로 구현한 코드이다.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
using namespace std;
typedef long long ll;

struct query {
    int l, r, i;
    bool operator<(const query& q) const { return r < q.r; } // 구간의 오른쪽 끝이 증가하는 순서로 정렬
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n; cin >> n;
    int sq = (int)sqrt(n) + 1;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    int m; cin >> m;
    vector<vector<query>> q(n / sq + 1);
    for (int i = 0; i < m; i++) {
        int l, r, ans = 0; cin >> l >> r;
        l--, r--;
        q[l / sq].push_back({ l, r, i }); // 구간의 왼쪽 끝이 속하는 블록이 동일한 것들끼리 묶는다.
    }
    
    vector<int> ans(m);
    int lb = 0; // 블록의 왼쪽 끝 인덱스 (lower bound)
    for (auto &p : q) {
        sort(p.begin(), p.end());
        vector<int> cnt(1000001, 0);
        int r = lb - 1, l = lb, x = 0;
        for (auto &[s, e, i] : p) {
            while (r < e) {
                r++;
                if (cnt[a[r]]++ == 0) x++; // 새로운 수가 추가되는 경우
            }
            while (l < s) {
                if (--cnt[a[l]] == 0) x--; // 하나 남은 수가 제거되는 경우
                l++;
            }
            while (l > s) {
                l--;
                if (cnt[a[l]]++ == 0) x++; // 새로운 수가 추가되는 경우
            }
            ans[i] = x;
        }
        lb += sq;
    }
    for (auto i : ans) cout << i << "\n";
}
```

아래는 첫 번째 방법으로 구현한 코드인데, 앞으로는 좀 더 직관적인 두 번째 방법을 사용할 것이다.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
using namespace std;
typedef long long ll;

int n, s;
struct query {
    int l, r, i;
    bool operator<(const query& q) const {
        int x = r / s, y = q.r / s;
        if (x == y) return l < q.l;
        return x < y;
    }
} q[100000];

int a[100001], cnt[1000001], ans[100000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n; cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int m; cin >> m;
    for (int i = 0; i < m; i++) {
        int l, r; cin >> l >> r;
        q[i] = { l, r, i };
    }
    s = (int)sqrt(n) + 1;
    sort(q, q + m);
    
    int l = 1, r = 0, c = 0;
    auto add = [&](int i) { if (cnt[a[i]]++ == 0) c++; };
    auto minus = [&](int i) { if (--cnt[a[i]] == 0) c--; };
    for (int i = 0; i < m; i++) {
        while (q[i].l < l) add(--l);
        while (q[i].l > l) minus(l++);
        while (q[i].r < r) minus(r--);
        while (q[i].r > r) add(++r);
        ans[q[i].i] = c;
    }
    for (int i = 0; i < m; i++) cout << ans[i] << "\n";
}
```

---

### [BOJ] 14897. 서로 다른 수와 쿼리 1

[BOJ 14897. 서로 다른 수와 쿼리 1 문제 링크](https://www.acmicpc.net/problem/14897)

마찬가지로 주어진 구간에 있는 **서로 다른 수의 개수**를 구하는 쿼리를 처리하는 문제인데,

입력의 범위가 $1 \leq a_i \leq 10^9$ 으로 늘어났기 때문에 좌표압축을 해주어야한다.

---

### [BOJ] 13548. 수열과 쿼리 6

[BOJ 13548. 수열과 쿼리 6 문제 링크](https://www.acmicpc.net/problem/13548)

주어진 구간에 있는 수들 중 **가장 많이 등장하는 수가 몇 번이나 등장했는지** 구하는 문제이다.

서로 다른 수의 개수를 구하는 문제에서 정수 $i$가 몇 번 등장하는지 저장하는 배열을 사용하였다면,

거기에 더해 **$j$번 등장하는 정수가 몇 개**인지 저장하는 배열을 추가로 사용한다.

첫 번째 배열을 업데이트함과 동시에 두 번째 배열도 업데이트해줌으로써 앞선 문제들과 동일한 시간복잡도로 해결할 수 있다.

---




<br/>

## References

[1] [Algorithms for Competitive Programming, 'Sqrt Decomposition'](https://cp-algorithms.com/data_structures/sqrt_decomposition.html)  
[2] [secmem.org, djm03178, 'Mo's Algorithm'](https://www.secmem.org/blog/2019/02/09/mo%27s-algorithm/#fn:1)  
