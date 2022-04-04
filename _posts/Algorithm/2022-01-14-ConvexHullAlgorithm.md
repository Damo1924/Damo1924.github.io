---
title: "Convex Hull Algorithm & Rotating Calipers"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` 그레이엄 스캔, Graham's Scan, CCW, 회전하는 캘리퍼스, 가장 먼 두 점, 1708 볼록 껍질, 10254. 고속도로

## 1. Convex Hull Algorithm

2차원 평면 위에 여러 개의 점들이 주어질 때, 아래와 같이 **모든 점을 포함하는 볼록 다각형**이 존재한다.

<center><img src="https://user-images.githubusercontent.com/88201512/149804273-ab477bbb-1ac6-4dc5-b6e3-24ca4c76f720.jpg" width="60%" height="60%"></center>

이와 같은 볼록 다각형을 **볼록 껍질(convex hull)**이라고 하며, 볼록 껍질을 구하는 알고리즘을 **볼록 껍질 알고리즘(Convex hull algorithm)**이라고 부른다.

볼록 껍질 알고리즘들의 시간복잡도는 주어진 점의 개수 $n$과 볼록 껍질을 이루는 점의 개수 $h$에 영향을 받는다.

이번 포스팅에서는 가장 대표적인 볼록 껍질 알고리즘인 **그레이엄 스캔(Graham's Scan)**에 대해 다루어 볼 것이다.

<br/>

## 2. Graham Scan

### 2-1. Algorithm

그레이엄 스캔은 평면 상에서 유한한 점들의 볼록 껍질을 찾는 방법으로, 점의 개수를 $n$이라 하면 시간복잡도는 $O(n \log n)$이다.

알고리즘은 다음과 같은 과정으로 이루어진다.

1. 반드시 볼록 껍질에 포함되는 점인 **y좌표가 가장 작은 점**을 기준점으로 선택한다. 만약 y좌표가 가장 작은 점이 여러 개라면, 그 중 x좌표가 가장 작은 것을 선택한다.
2. 선택한 점을 기준으로 점들을 **반시계 방향으로 정렬**한다.
3. 볼록 껍질을 구성하는 점들을 저장할 스택(stack)을 만들고, 첫 두 점을 스택에 삽입한다.
4. 정렬된 순서대로 각 점들을 차례대로 처리한다.
  - 스택의 마지막 두 점을 각각 A와 B, 그리고 이번에 처리할 점을 C라고 하자.
  - 점 A, B, C가 반시계 방향을 이루면 C를 스택에 삽입한다.
  - 점 A, B, C가 시계 방향을 이루면 B는 볼록 껍질에 포함되지 않으므로 B를 스택에서 제거하고 위 과정을 반복한다.
5. 마지막으로 기준점까지 탐색하였다면 알고리즘을 종료한다.

아래 그림은 그레이엄 스캔 과정을 보여준다.

<center><img src="https://user-images.githubusercontent.com/88201512/149806393-331fbfee-b908-4a6d-a5e6-1c8ef956075b.jpg"></center>

주황색 선분들은 현재 탐색하고 있는 점들(A, B, C)을 이은 선분들이고, 노란색 선분들은 스택에 포함된 점들을 이은 것들이다.

기준점을 선택하는데 $O(n)$, 점들을 정렬하는데 $O(n \log n)$, 점들을 차례대로 처리하는데 $O(n)$이므로 전체 알고리즘의 시간복잡도는 $O(n \log n)$이다.

만약 점들이 반시계 방향으로 정렬되어 있다면 $O(n)$의 시간복잡도로 볼록 껍질을 구할 수 있다.

---

### 2-2. Implementation

이제 그레이엄 스캔을 구현해서 볼록 껍질을 구해보자.

[백준 1708. 볼록 껍질 문제 링크](https://www.acmicpc.net/problem/1708)

2차원 평면 위 N개의 점이 주어졌을 때, 볼록 껍질을 이루는 점의 개수를 구하는 문제이다.

N은 3 이상 100,000 이하인 자연수이고, 각 점의 좌표는 절댓값이 40,000을 넘지 않는다.

또한, 모든 점이 같은 직선 상에 위치하는 경우는 입력으로 주어지지 않는다.

**[Solution]**

먼저, 점들을 탐색해서 기준점을 고른다.

이제 선택한 기준점을 중심으로 다른 점들을 반시계 방향으로 정렬해야한다.

점들을 반시계 방향으로 정렬하는 가장 쉬운 방법은 **벡터의 외적**을 이용하는 것이다.

> 기준점 Q와 어떤 두 점 A, B가 주어졌을 때, $\vec{QA} \times \vec{QB} > 0$이면 Q에 대해 A-B는 반시계 방향이다.

세 점이 이루는 방향을 판단하기 위해서는 **CCW(Counter Clock Wise)** 알고리즘을 이용하면 된다.

> CCW에 대한 자세한 내용은 [이 포스팅](https://damo1924.github.io/algorithm/CCW/)에서 다루고 있다.

전체 코드는 다음과 같다.

```cpp
#include <iostream>
#include <math.h>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p;
#define x first
#define y second

int CCW(p A, p B, p C)
{
    ll V = (B.x - A.x) * (C.y - B.y) - (C.x - B.x) * (B.y - A.y);
    if (V > 0) return 1;
    if (V < 0) return -1;
    return 0;
}

void getConvexHull(vector<p> &v, vector<p> &hull)
{
    swap(v[0], *min_element(v.begin(), v.end())); // 기준점을 맨 앞으로 옮긴다.
    sort(v.begin() + 1, v.end(), [&](p A, p B){ // 나머지 점들을 기준점에 대해 반시계방향으로 정렬
        int res = CCW(v[0], A, B);
        if (res) return res > 0;
        return abs(A.x - v[0].x) + abs(A.y - v[0].y) < abs(B.x - v[0].x) + abs(B.y - v[0].y); // 단, 세 점이 일직선 상에 있으면 기준점과 가까울수록 앞에 오도록 정렬
    });
    for (auto P : v)
    {
        while (hull.size() > 1 && CCW(hull[hull.size() - 2], hull.back(), P) != 1) hull.pop_back();
        hull.push_back(P);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n; cin >> n;
    vector<p> points(n), hull;
    for (int i = 0; i < n; i++) cin >> points[i].x >> points[i].y;
    getConvexHull(points, hull);
    cout << hull.size();
}
```

<br/>

## 3. Rotating Calipers

회전하는 캘리퍼스 알고리즘은 **볼록 껍질의 최대 직경**을 구하는 **Two pointer** 알고리즘이다.

볼록 껍질의 최대 직경은 **볼록 껍질을 구성하는 가장 먼 두 점의 길이**로 정의한다.

이때 볼록 껍질은 좌표평면 상의 모든 점을 포함하는 볼록 다각형이므로, 다음이 성립한다.

> **볼록 껍질의 최대 직경 = 가장 먼 두 점 사이의 거리**

볼록 껍질을 이루는 점의 개수를 $h$라고 하면, 회전하는 캘리퍼스 알고리즘은 $O(h)$의 시간복잡도로 볼록 껍질의 최대 직경을 구할 수 있다.

그러므로 **그레이엄 스캔**과 **회전하는 캘리퍼스** 알고리즘을 이용하면, 좌표평면에 $n$개의 점이 주어졌을 때 가장 멀리 떨어진 두 점 사이의 거리를 $O(n\log n)$의 시간복잡도로 구할 수 있게 된다.

회전하는 캘리퍼스 알고리즘에 대해 공부해보고, 직접 구현까지 해보자.

---

### 3-1. Algorithm

캘리퍼스는 길이를 정밀하게 측정하는 도구로, 아래 그림과 같다.

<center><img src="https://user-images.githubusercontent.com/88201512/149702638-01d8c755-5341-425e-a5e4-c6952b5bb92c.jpg" width="60%" height="60%"></center>

알고리즘을 말로 설명하기 전에, 그림을 통해 이해해보자.

<center><img src="https://user-images.githubusercontent.com/88201512/149804403-521759c6-9e2d-43d5-baa9-25856eec0bb8.jpg"></center>

$Q_1$과 $Q_2$는 우리가 거리를 구해볼 두 점을, 두 개의 평행한 빨간색 직선은 캘리퍼스의 두 턱을 의미한다.

그렇다면 왜 이 알고리즘의 이름이 '회전하는 캘리퍼스'인지 바로 알 수 있을 것이다.

볼록 다각형의 주위로 캘리퍼스를 회전시키면서, 캘리퍼스와 맞닿은 두 점 사이의 거리를 구하기 때문이다.

정리해보면,

1. y좌표가 가장 작은 점과 가장 큰 점을 찾고, 캘리퍼스의 두 집게를 x축에 평행하게 둔다. 직경의 초기값은 찾은 두 점 사이의 거리이다.
2. 각 점을 포함하는 볼록 다각형의 선분과 캘리퍼스의 집게가 이루는 각도 중 작은 각도만큼 캘리퍼스를 회전시킨다.
3. 캘리퍼스를 회전시켰을 때 새롭게 캘리퍼스에 닿는 점과 반대편 캘리퍼스에 기존에 닿아 있던 점 사이의 거리를 구해 최댓값을 갱신한다.
4. 볼록 다각형의 모든 변을 탐색할 때까지 2~3번 과정을 반복한다.

**볼록 다각형의 모든 변을 한 번씩 캘리퍼스의 집게가 맞닿기 때문**에 $O(h)$의 시간복잡도를 가진다.($h$: 볼록 껍질을 이루는 점의 개수)

---

### 3-2. Implementation

회전하는 캘리퍼스 알고리즘을 이용해서 **가장 먼 두 점 사이의 거리**를 구하는 문제를 풀어보자.

[백준 10254. 고속도로 문제 링크](https://www.acmicpc.net/problem/10254)

N개의 도시의 위치가 $(x, y)$로 주어질 때, 가장 먼 두 도시를 구하려고 한다.

입력으로 T개의 테스트케이스가 주어진다.

각 테스트케이스는 도시의 개수 N과 각 도시의 좌표 $(x, y)$로 이루어져 있다.

($2 \leq N \leq 200000$, $-10^7 \leq x, y \leq 10^7$)

**[Solution]**

가장 먼 두 점을 구하기 위해서는

1. 그레이엄 스캔으로 볼록 껍질 구하기: $O(n \log n)$
2. 회전하는 캘리퍼스 알고리즘으로 가장 먼 두 점 찾기: $O(n)$

를 수행하면 되므로, 1번은 앞서 구현한 코드를 그대로 사용하였다.

회전하는 캘리퍼스 알고리즘 구현의 핵심은 **두 각도 중 작은 것을 어떻게 구하느냐**이다.

내적이나 외적을 이용해서 코사인이나 사인 값을 구하면 된다고 생각할 수도 있겠지만, 기하 알고리즘에서는 **실수 연산을 최대한 피해야 한다.**

입력되는 값의 범위가 작다면 괜찮겠지만, 일반적으로 **실수 비교를 하는 알고리즘은 얼마든지 반례를 찾을 수 있기 때문이다.**

그러므로 우리는 실수 연산을 하지 않고 캘리퍼스를 얼마나 회전시켜야 하는지 알아내야한다.

아래 그림을 보자.

<center><img src="https://user-images.githubusercontent.com/88201512/150057568-87f9c24c-5edb-4b26-958d-8c862f856039.jpg" width="60%" height="60%"></center>

위 그림과 같이 새로운 점들을 정의하면, 다음이 성립한다.

\begin{aligned}
\vec{Q_2 Q_1''} \times \vec{Q_2 Q_2''} = \left\vert \vec{Q_2 Q_1''} \right\vert \left\vert \vec{Q_2 Q_2''} \right\vert \sin{\theta_2 - \theta_1}
\end{aligned}

위 외적의 결과값이 양수이면 $\theta_2 > \theta_1$이고, 음수이면 $\theta_2 < \theta_1$임을 알 수 있다.

따라서 실수 연산을 이용하지 않고도 각도 비교가 가능하다.

전체 코드는 다음과 같다.

```cpp
#include <iostream>
#include <math.h>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p;
#define x first
#define y second

ll dist(p A, p B)
{
    return (A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y);
}

int CCW(p A, p B, p C)
{
    ll V = (B.x - A.x) * (C.y - B.y) - (C.x - B.x) * (B.y - A.y);
    if (V > 0) return 1;
    if (V < 0) return -1;
    return 0;
}

void getConvexHull(vector<p> &v, vector<p> &hull)
{
    swap(v[0], *min_element(v.begin(), v.end()));
    sort(v.begin() + 1, v.end(), [&](p A, p B){
        int res = CCW(v[0], A, B);
        if (res) return res > 0;
        return abs(A.x - v[0].x) + abs(A.y - v[0].y) < abs(B.x - v[0].x) + abs(B.y - v[0].y);
    });
    for (auto P : v)
    {
        while (hull.size() > 1 && CCW(hull[hull.size() - 2], hull.back(), P) != 1) hull.pop_back();
        hull.push_back(P);
    }
}

void rotatingCalipers(vector<p> &hull)
{
    int n = hull.size();
    int i = min_element(hull.begin(), hull.end()) - hull.begin();
    int j = max_element(hull.begin(), hull.end()) - hull.begin();
    
    int a = i, b = j;
    ll d = dist(hull[i], hull[j]);
    
    for (int k = 0; k < n; k++)
    {
        int ni = (i + 1) % n, nj = (j + 1) % n; // next i, next j
        ll CP = (hull[ni].x - hull[i].x) * (hull[j].y - hull[nj].y); // cross product
        CP -= (hull[ni].y - hull[i].y) * (hull[j].x - hull[nj].x);
        if (CP > 0) i = ni;
        else if (CP < 0) j = nj;
        else i = ni, j = nj;
        
        ll D = dist(hull[i], hull[j]);
        if (d < D) { d = D; a = i; b = j; }
    }
    cout << hull[a].x << " " << hull[a].y << " " << hull[b].x << " " << hull[b].y << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t; cin >> t;
    while (t--)
    {
        int n; cin >> n;
        vector<p> points(n), hull;
        for (int i = 0; i < n; i++) cin >> points[i].x >> points[i].y;
        getConvexHull(points, hull);
        rotatingCalipers(hull);
    }
}
```

<br/>

## 4. Related Problems

### [BOJ] 3679. 단순 다각형

[BOJ 3679. 단순 다각형 문제 링크](https://www.acmicpc.net/problem/3679)

좌표평면 위에 주어진 점들을 모두 이용해서 다각형을 만드는 문제이다.

기준점을 선택한 후, 반시계 방향으로 점들을 정렬하여 점들을 출력하면 된다.

주의할 점은 **기준점을 지나는 한 직선 위에 있는 점들**을 정렬할 때, 기준점과 가까운 순서대로 정렬하되 **다각형의 마지막 변에서는 기준점에서 먼 순서대로 정렬**해야한다는 것이다.

---

### [BOJ] 7420. 맹독 방벽

[BOJ 7420. 맹독 방벽 문제 링크](https://www.acmicpc.net/problem/7420)

모든 건물을 감싸는 맹독 방벽을 만들려고 할 때, 각 건물들로부터 최소 $L$만큼 떨어지게 만들려고 한다.

이때 방벽의 최소 길이를 구하는 문제이다.

**[HINT]** (방벽의 최소 길이) $=$ (Convex hull의 둘레) $+$ $2 \pi L$

---

### [BOJ] 3878. 점 분리

[BOJ 3878. 점 분리 문제 링크](https://www.acmicpc.net/problem/3878)

좌표평면 위의 검은 점들과 흰 점들을 한 직선으로 분리할 수 있는지 알아내는 문제이다.

**[HINT]** 두 convex hull이 겹치지 않도록 하는 조건은 무엇일까?

> 자세한 풀이는 [이 포스트](https://damo1924.github.io/ps/BAEKJOON-3878/)에서 다루고 있다.

---

### [BOJ] 13310. 먼 별**

[BOJ 13310. 먼 별 문제 링크](https://www.acmicpc.net/problem/13310)

별들의 위치가 매일 달라질 때, 가장 멀리 떨어진 두 별 사이의 거리가 최소인 날을 구하는 문제이다.

Rotating calipers 알고리즘을 통해 어떤 날의 가장 먼 두 별 사이의 거리를 알 수 있다.

**[HINT 1]** 어떤 두 별 사이의 거리는 시간에 대한 아래로 볼록한 함수이다.

**[HINT 2]** 가장 먼 두 별 사이의 거리는 시간에 대한 아래로 볼록한 함수이다.

> 자세한 풀이는 [이 포스트](https://damo1924.github.io/ps/BAEKJOON-13310/)에서 다루고 있다.

<br/>

## References

[1] [위키백과, '볼록 껍질 알고리즘'](https://ko.m.wikipedia.org/wiki/%EB%B3%BC%EB%A1%9D_%EA%BB%8D%EC%A7%88_%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98)  
[2] [위키백과, '그레이엄 스캔'](https://ko.m.wikipedia.org/wiki/%EA%B7%B8%EB%A0%88%EC%9D%B4%EC%97%84_%EC%8A%A4%EC%BA%94)  
[3] [WIKIPEDIA, 'Rotating calipers'](https://en.m.wikipedia.org/wiki/Rotating_calipers)  
[4] [ruz, '회전하는 캘리퍼스 rotating calipers'](https://aruz.tistory.com/entry/rotating-calipers)





