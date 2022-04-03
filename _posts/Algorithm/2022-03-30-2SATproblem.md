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

## 3. Converting to 2-SAT Problems

2-SAT 문제 자체는 SCC를 구하는 알고리즘을 알고 있다면 쉽게 해결할 수 있다.

실제 문제를 풀 때 중요한 점은 주어진 문제를 2-SAT 문제의 형태로 모델링하는 것이다.

굳이 어떤 조작을 하지 않아도 되는 문제들도 있지만, 주어진 논리식을 CNF로 변형해서 풀어야하는 문제들도 있다.

모든 명제 논리식은 CNF로 변환할 수 있기 때문에 생각보다 다양한 문제들을 2-SAT 문제로 변형할 수 있다.

예로 아래와 같은 것들을 들 수 있다.

- $x \iff (x \lor x)$
- $x = y \iff (x \lor \lnot y) \land (\lnot x \lor y)$
- $x \neq y \iff (x \lor y) \land (\lnot x \lor \lnot y)$

이 외에도 분배법칙(distributive law)이나 드 모르간의 법칙(De Morgan's law) 등을 이용하면 어렵지 않게 CNF의 형태로 바꾸어줄 수 있다.

조금 더 어려운 문제들에는 $n$**개의 변수들 중 최대 1개만 참일 수 있는 조건**이 등장하기도 한다.

> 조건: $n$개의 변수 $x_1, x_2, \dots, x_n$ 중 최대 1개의 변수만 참이다.

$n$이 작은 경우에는 다음과 같이 처리할 수 있다.

> **모든 $i, j$($i < j$)에 대해 $(\lnot x_i \lor \lnot x_j)$**에 해당하는 간선을 추가한다.

$O(n^2)$개의 간선을 추가하게 되는데, 만약 $n$이 매우 커진다면 주어진 제한 시간 내에 통과하지 못할 수도 있다.

물론 [BOJ 2519. 막대기](https://damo1924.github.io/algorithm/2SATproblem/#boj-2519-%EB%A7%89%EB%8C%80%EA%B8%B0)처럼 $n$이 작다면 위와 같이 처리해도 충분하다.

하지만 $n$이 큰 값을 가질 수 있는 [BOJ. 19703. 실험]()과 같은 문제에서는 좋은 방법이라고 할 수 없다.

이러한 경우에는 아래 방법을 사용하면 된다.

> 기존 그래프에 새로운 정점 $y_1, y_2, \dots, y_{n-1}$, $z_1, z_2, \dots, z_{n-1}$을 추가한다.
> 
> 모든 $i$($1 \leq i \leq n$)에 대해 다음 간선들을 추가해준다.
> 
> - $x_i \to y_i$, $x_i \to z_i$
> - $y_i \to y_{i+1}$, $z_{i + 1} \to z_i$ ($i < n$)
> - $y_i \to \lnot x_{i+1}$, $z_{i+1} \to \lnot x_i$ ($i < n$)

이렇게 가상의 정점들을 추가하여 연결하면, $O(n)$개의 간선만 추가해도 $O(n^2)$개의 간선을 추가한 효과를 얻을 수 있다.

<br/>

## 4. Related Problems

### [BOJ] 3648. 아이돌

[BOJ 3648. 아이돌 문제 링크](https://www.acmicpc.net/problem/3648)

심사위원의 두 투표 중 적어도 하나가 반영되어하므로 2-SAT 문제임을 알 수 있다.

이때 $1$번 참가자가 반드시 통과되도록 해야하므로 $x_1$과 $\lnot x_1$의 위상정렬 순서를 추가적으로 비교해주면 된다.

---

### [BOJ] 1154. 팀 편성

[BOJ 1154. 팀 편성 문제 링크](https://www.acmicpc.net/problem/1154)

$n$명의 학생들을 두 팀으로 나누는데, 각 팀에 속한 학생들끼리는 모두 아는 사이여야한다.

서로 아는 사이인 두 학생의 번호가 주어질 때, 조건을 만족하도록 그룹을 나누는 문제이다.

서로 친구인 경우에는 서로 다른 팀에 속해도 상관이 없지만, 친구가 아니라면 반드시 다른 팀에 속해야한다는 점을 이용하자.

$a, b$가 서로 알지 못한다면, 다음과 같은 논리식을 세울 수 있다.

\begin{aligned}
(a \land \lnot b) \lor (\lnot a \land b)
\end{aligned}

분배법칙을 이용해서 정리하면, 2-CNF으로 만들 수 있다.

\begin{aligned}
(a \lor b) \land (\lnot a \lor \lnot b)
\end{aligned}

> 사실 이 문제는 서로 알지 못하는 두 학생을 잇는 간선을 갖는 그래프를 단순히 DFS로 탐색함으로써 풀 수 있다.

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

### [BOJ] 1739. 도로 정비하기

[BOJ 1739. 도로 정비하기 문제 링크](https://www.acmicpc.net/problem/1739)

가로 도로 $n$개, 세로 도로 $m$개가 있는 도시에서 $k$개의 버스가 운행하고 있다.

각 버스는 정해진 출발 지점으로부터 도착 지점까지 최대 두 개의 도로를 따라 최단 경로로 이동한다.

교통사고를 줄이기 위해 각 가로 도로들과 세로 도로들의 통행 방향을 한 방향으로 고정하려고 한다.

모든 버스가 위 조건을 만족하면서 운행할 수 있도록 도로들의 방향을 정할 수 있는지 구하는 문제이다.

$(a, b)$에서 $(c, d)$로 운행하는 버스를 생각해보자.

1. $a = c$, $b \neq d$ : 가로 도로 $a$의 방향이 정해진다.
2. $a \neq c$, $b = d$ : 세로 도로 $b$의 방향이 정해진다.
3. $a \neq c$, $b \neq d$ : $(a, d)$의 방향이 정해지거나, $(b, c)$의 방향이 정해진다.
4. $a = c$, $b = d$ : 도로의 방향에 영향이 없다.

각 경우를 2-CNF로 표현하면 다음과 같다.

1. $a \lor a$
2. $b \lor b$
3. $(a \lor b) \land (a \lor c) \land (d \lor b) \land (d \lor c)$

세 번째 경우는 $(a \land d) \lor (b \land c)$를 분배법칙을 통해 전개하여 얻을 수 있다.

따라서 변수가 $n + m$개인 2-SAT 문제를 풀면 된다.

---

### [BOJ] 16853. 필름

[BOJ 16853. 필름 문제 링크](https://www.acmicpc.net/problem/16853)

입력이 더욱 복잡해진 문제.

---

### [BOJ] 2519. 막대기**

[BOJ 2519. 막대기 문제 링크](https://www.acmicpc.net/problem/2519)

한 사람 당 세 개의 막대기를 바닥에 던졌졌다.

**각 사람이 자신의 막대 중 최대 한 개를 제거**해서 겹치는 막대가 없게 만들려고 한다.

먼저 겹치는 두 막대 중 적어도 하나는 제거해야한다.

따라서 겹치는 두 막대 $a, b$에 대해 $a \lor b$를 추가해준다.

그런데 각 사람이 던진 세 막대 중 최대 하나만 제거할 수 있다.

반대로 생각하면 **세 막대 중 적어도 두 막대를 남겨야한다.**

따라서 한 사람이 던진 세 막대 $a, b, c$에 대해 다음을 추가해준다.

\begin{aligned}
(\lnot a \lor \lnot b) \land (\lnot b \lor \lnot c) \land (\lnot c \lor \lnot a)
\end{aligned}

> 두 선분이 겹치는지 확인하기 위해 CCW를 이용한다.

---

### [BOJ] 19703. 실험**

[BOJ 19703. 실험 문제 링크](https://www.acmicpc.net/problem/19703)

$n$명의 유저를 $m$개의 그룹으로 나눈 후, 다음 조건을 만족하도록 베타 테스터를 선정하려고 한다.

- 하나의 그룹에서 최대 한 명의 베타 테스터만 뽑을 수 있다.
- 서로 반대되는 성향의 두 유저 중 적어도 한 명은 뽑아야한다.

이 문제의 경우 한 그룹에 $10^5$명의 사람이 속할 수 있기 때문에 $O(n)$ 방법으로 첫 번째 조건을 처리해야한다.

<br/>

## References

[1] [WIKIPEDIA, 'Conjunctive normal form'](https://en.m.wikipedia.org/wiki/Conjunctive_normal_form)  
[2] [Samsung Software Membership, leejseo, '2-SAT 및 그의 응용'](https://www.secmem.org/blog/2021/09/01/2sat-app/)


