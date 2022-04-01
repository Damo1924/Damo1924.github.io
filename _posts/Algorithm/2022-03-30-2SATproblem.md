---
title: "2-SAT Problem"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` CNF, SCC, 

## 1. 2-SAT problem

2-SAT 문제란 **참 또는 거짓의 값을 가지는 $n$개의 변수 $x_1, x_2, \dots, x_n$으로 이루어진 2-CNF가 참이 되도록 $x_i$들에 적절한 값을 할당하는 문제**이다.

> **CNF**: 논리곱 표준형(Conjunctive Normal Form)의 약자로, 절의 논리곱으로 나타낸 논리식이다. 이때 절은 변수 또는 변수들의 논리합이다.
> 
> **n-CNF**: 각 절이 n개의 변수의 논리합인 CNF을 의미하며, 2-CNF와 3-CNF가 주로 다루어진다.

CNF에서 등장할 수 있는 논리기호에는 **논리합($x \lor y$)**, **논리곱($x \land y$)**, **부정($\lnot x$)**이 있다.

예를 들어, 두 변수 $x_1, x_2$로 이루어진 2-CNF $(x_1 \lor x_2) \land (\lnot x_1 \lor \lnot x_2)$를 생각해보자.

$x_1 = true$, $x_2 = false$로 값을 할당하면 위 식이 참이 되므로 2-SAT 문제의 해가 된다.

또, $x_1 = false$, $x_2 = true$도 위 식을 참으로 만든다.

반면 $(x_1 \lor x_1) \land (\lnot x_1 \lor \lnot x_1)$는 어떤 값을 할당해도 참으로 만들 수 없다.

이처럼 2-SAT 문제에는 해가 존재하지 않을 수도 있고, 해가 존재해도 유일하지 않을 수 있다.

<br/>

## 2. How to Solve 2-SAT problem

2-SAT 문제는 **강한연결요소(Strongly Connected Component)**을 통해 해결할 수 있다.

그러기 위해서는 주어진 2-CNF을 통해 적절한 그래프를 만들어야한다.

---

### 2-1. How to Convert CNF into Conditionals

수리논리학의 아주 기초적인 내용들에 대해 잠깐 공부해보자.

> [Definition] 두 명제 $P$와 $Q$가 모든 경우에 대해 진리값이 같을 때, "$P$는 $Q$와 **논리적 동치(logically equivalent)**이다"라고 하며, 다음과 같이 나타낸다.
> 
> \begin{aligned}
> P \equiv Q
> \end{aligned}

예를 들어 $\lnot p \lor q$는 $\lnot (p \land \lnot q)$와 논리적으로 동치라고 할 수 있다.

> [Definition] **조건문(conditional)**은 $p \to q$로 나타내고, "$p$이면 $q$이다"(if $p$ then $q$)로 읽으며 진리값은 다음과 같다.
> 
> |$p$|$q$|$p \to q$|
> |:---:|:---:|:---:|
> |T|T|T|
> |T|F|F|
> |F|T|T|
> |F|F|T|

조건문은 논리기호를 이용해서 표현이 가능하다.

> [Theorem] $p \to q \equiv \lnot p \lor q$

이는 진리표를 통해 간단히 증명이 가능하다.

---

### 2-2. Implication Graph & Solution to the problem

$p \lor q$는 $\lnot p \to q$, $\lnot q \to p$와 동치라는 사실을 이용해서 주어진 2-CNF로부터 그래프를 만들어보자.

> $x_1, \lnot x_1, x_2, \lnot x_2, \dots, x_n, \lnot x_n$을 정점으로 하고, 2-CNF의 각 절 $x_i \lor x_j$에 대해 $\lnot x_i \to x_j$와 $\lnot x_j \to x_i$을 간선으로 갖는 그래프
> 
> (이러한 그래프를 **implication graph**라고 부른다)

2-CNF가 참이기 위해서는 모든 간선이 참이어야하고, 따라서 $p = true$, $q = false$인 간선 $p \to q$가 존재하면 안된다.

이로부터 다음과 같은 사실을 알 수 있다.

> [Lemma] 그래프에 어떤 경로 $y_1 \to y_2 \to \dots \to y_l$가 존재한다면, 경로 위의 정점(변수)들은 다음과 같이 값을 가져야한다.
> 
> 어떤 정수 $k$($0 \leq k \leq l$)에 대해,
> 
> \begin{aligned}
> y_i =
> \begin{cases}
> false, & \mbox{if }1 \leq i \leq k \\\\  
> true, & \mbox{if }k < i \leq l
> \end{cases}
> \end{aligned}

이제 $x_i$와 $\lnot x_i$의 관계를 생각해보자.

- 경로 $x_i \to \lnot x_i$와 경로 $\lnot x_i \to x_i$가 모두 존재하는 경우
- 두 경로 중 하나만 존재하는 경우
- 두 경로 모두 존재하지 않는 경우

두 경로가 모두 존재한다면, Lemma에 의해 $x_i = \lnot x_i$이어야하므로 모순이다.

두 경로 중 하나만 존재한다면, Lemma에 의해 결론 부분에 오는 정점이 $true$가 된다.

어떤 정점이 결론 부분에 온다는 것은 SCC들을 위상정렬 했을 때, 해당 정점이 속한 SCC가 더 뒤에 있음을 의미한다.

따라서 다음과 같은 과정을 통해 2-SAT 문제를 풀 수 있다.

1. 2-CNF으로부터 implication graph를 구현한다.
2. 그래프를 SCC들로 분할한다.
3. $x_i$와 $\lnot x_i$가 같은 SCC에 속한다면, 해가 존재하지 않는다.
4. 위와 같은 경우가 없다면, 각 $x_i$, $\lnot x_i$ 사이의 위상 정렬 순서(topological order)를 비교함으로써 참/거짓을 할당해준다.

시간복잡도는 $O(V + E)$이다.

---

### 2-3. Implementation

[BOJ 11281. 2-SAT - 4 문제 링크](https://www.acmicpc.net/problem/11281)

위 문제는 2-SAT의 해가 존재하면 $1$과 해를 출력하고, 해가 존재하지 않으면 $-1$을 출력하는 문제이다.

SCC를 구하는 알고리즘 중 Tarjan's algorithm을 사용하였다.

위상정렬 순서를 저장하기 위해서 `ord[i]` 배열을 추가적으로 사용하였다.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;
const int N = 2e4 + 1;

int n, m;

int _not(int i) // i의 부정
{
    if (i > n) return i - n;
    return i + n;
}

vector<int> g[N]; // graph
int vis[N], v_k; // vis[i]: dfs(i)가 호출된 순서
int idx[N], i_k; // idx[i]: 정점 i가 속한 SCC의 인덱스
int ord[N], o_k; // ord[i]: 정점 i가 SCC에 속하게 된 순서 (topological order와 동일)
stack<int> st;

int dfs(int u) // Tarjan's algorithm
{
    vis[u] = ++v_k;
    st.push(u);
    
    int res = vis[u];
    for (int v : g[u])
    {
        if (!vis[v]) res = min(res, dfs(v));
        else if (!idx[v]) res = min(res, vis[v]);
    }
    
    if (res == vis[u])
    {
        i_k++;
        while (true)
        {
            int t = st.top();
            st.pop();
            idx[t] = i_k;
            ord[--o_k] = t;
            if (t == u) break;
        }
    }
    return res;
}

void solve2SAT()
{
    for (int i = 1; i <= n; i++)
        if (idx[i] == idx[i + n]) { cout << 0; return; }
    
    vector<bool> ans(2 * n + 1, 1);
    for (int i = 0; i < 2 * n; i++)
        if (ans[_not(ord[i])]) ans[ord[i]] = 0; // 위상정렬을 한 상태에서 먼저 등장하는 정점에 false를 할당
    
    cout << "1\n";
    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> n >> m;
    while (m--)
    {
        int i, j; cin >> i >> j;
        if (i < 0) i = n - i;
        if (j < 0) j = n - j;
        g[_not(i)].push_back(j);
        g[_not(j)].push_back(i);
    }
    
    o_k = 2 * n;
    for (int i = 1; i <= 2 * n; i++) if (!idx[i]) dfs(i);
    solve2SAT();
}
```

<br/>

## 3. Related Problems

2-SAT 문제 자체는 SCC를 구하는 알고리즘을 알고 있다면 쉽게 해결할 수 있다.

실제 문제를 풀 때 중요한 점은 주어진 문제를 2-SAT 문제의 형태로 모델링하는 것이다.

굳이 어떤 조작을 하지 않아도 되는 문제들도 있지만, 주어진 논리식을 CNF로 변형해서 풀어야하는 어려운 문제들도 있다.

> 모든 명제 논리식은 CNF로 변환할 수 있다.

Ex)

- $x \iff (x \lor x)$
- $x = y \iff (x \lor \lnot y) \land (\lnot x \lor y)$
- $x \neq y \iff (x \lor y) \land (\lnot x \lor \lnot y)$

---

### [BOJ] 3648. 아이돌

[BOJ 3648. 아이돌 문제 링크](https://www.acmicpc.net/problem/3648)

심사위원의 두 투표 중 적어도 하나가 반영되어하므로 2-SAT 문제임을 알 수 있다.

이때 $1$번 참가자가 반드시 통과되도록 해야하므로 $x_1$과 $\lnot x_1$의 위상정렬 순서를 추가적으로 비교해주면 된다.

---

### [BOJ] 16367. TV Show Game

[BOJ 16367. TV Show Game 문제 링크](https://www.acmicpc.net/problem/16367)

빨간색 또는 파란색 빛을 내는 $k$개의 램프가 있고, TV Show의 참가자들은 그 중 세 개의 램프를 골라 색깔을 맞추는 게임을 한다.

세 개 중 두 개 이상을 맞추면 상품을 받게 되는데, 모든 사람이 상품을 받을 수 있도록 램프들의 색을 정할 수 있는지 구하는 문제이다.

세 변수 $x, y, z$ 중 둘 이상이 참일 때만 참인 2-CNF를 찾으면 된다.

\begin{aligned}
(x \lor y) \land (y \lor z) \land (z \lor x)
\end{aligned}

---

### [BOJ] 

<br/>

## References

[1] [WIKIPEDIA, 'Conjunctive normal form'](https://en.m.wikipedia.org/wiki/Conjunctive_normal_form)

[2] [Samsung Software Membership, leejseo, '2-SAT 및 그의 응용'](https://www.secmem.org/blog/2021/09/01/2sat-app/)


