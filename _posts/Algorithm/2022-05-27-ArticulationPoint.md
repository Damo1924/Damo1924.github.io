---
title: "단절점과 단절선(Articulation Point & Bridge)"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:    
  - Algorithm
use_math: true
comments: true

---

`Tags` DFS

## 1. Articulation Point

하나의 연결 요소(connected component)로 이루어진 그래프에서 제거했을 때 그래프가 두 개 또는 그 이상의 연결 요소로 나누어지는 정점을 **단절점(articulation point)**라고 부른다.

단절점은 다음과 같은 성질을 가지고 있다.

- 단절점에 인접한 정점들은 단절점을 통해서만 연결된다.

만약 단절점을 지나지 않는 우회로가 존재한다면, 단절점을 제거해도 연결 요소의 개수가 그대로임을 알 수 있다.

이를 이용해서 그래프의 단절점들을 구하기 위해 그래프에 대한 DFS tree를 그리면, 다음과 같이 단절점을 구할 수 있다.

- 어떤 정점 $v$가 단절점이 아니기 위해서는 DFS tree에서 $v$의 자손인 정점들이 $v$를 지나지 않고 $v$ 이전에 방문한 정점에 갈 수 있어야한다.

즉, **정점 $v$의 자식들 중 $v$를 거치지 않으면서 $v$ 이전에 방문한 정점으로 갈 수 없는 정점이 존재한다면 $v$는 단절점**이다.

단, DFS tree의 루트 노드는 따로 처리해준다.

- 루트 노드는 자식 노드가 $2$개 이상이면 단절점이다.

이는 루트 노드의 각 자식 노드를 루트로 하는 서브트리에 속하는 정점들은 루트 노드를 통해서만 연결될 수 있기 때문이다.

DFS를 한 번 수행하므로 시간복잡도는 $O(V + E)$ 이다.

---

### [BOJ] 11266. 단절점

[BOJ 11266. 단절점 문제 링크](https://www.acmicpc.net/problem/11266)

```cpp
#include <iostream>
#include <vector>
using namespace std;

vector<int> g[10001];
int ord[10001], k; // ord[i] : 방문 순서
int par[10001]; // par[i] : 부모 노드
bool chk[10001]; // chk[i] : 단절점이면 true

int dfs(int u)
{
    ord[u] = ++k;
    int ret = k, chd = 0; // 방문 순서의 최솟값, 자식 노드 수
    for (int v : g[u])
    {
        if (v == par[u]) continue;
        
        if (!ord[v])
        {
            par[v] = u;
            chd++;
            int tmp = dfs(v);
            if (par[u] && tmp >= ord[u]) chk[u] = 1;
            ret = min(ret, tmp);
        }
        else ret = min(ret, ord[v]);
    }
    if (!par[u] && chd > 1) chk[u] = 1; // 루트 노드의 경우, 자식 노드가 2개 이상이면 단절점
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int V, E; cin >> V >> E;
    while (E--)
    {
        int a, b; cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    
    for (int i = 1; i <= V; i++) if (!ord[i]) dfs(i);
    
    vector<int> ans;
    for (int i = 1; i <= V; i++) if (chk[i]) ans.push_back(i);
    cout << ans.size() << "\n";
    for (int i : ans) cout << i << " ";
}
```

<br/>

## 2. Articulation Bridge

하나의 연결 요소(connected component)로 이루어진 그래프에서 제거했을 때 그래프가 두 개 또는 그 이상의 연결 요소로 나누어지는 간선을 **단절선(articulation bridge)**라고 부른다.

단절선은 단절점과 마찬가지로 DFS tree를 이용해서 구할 수 있다.

- 정점 $v$와 $v$의 자식 노드를 잇는 간선이 단절선이기 위해서는 해당 간선을 지나지 않으면서 해당 자식 노드에서 $v$ 이전에 방문한 정점에 갈 수 있어야한다.

시간복잡도는 마찬가지로 $O(V + E)$이다.

---

### [BOJ] 11400. 단절선

[BOJ 11400. 단절선 문제 링크](https://www.acmicpc.net/problem/11400)

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> g[100001];
int ord[100001], k; // ord[i] : 방문 순서
int par[100001]; // par[i] : 부모 노드
vector<pair<int, int>> ans;

int dfs(int u)
{
    ord[u] = ++k;
    int ret = k; // 방문 순서의 최솟값
    for (int v : g[u])
    {
        if (v == par[u]) continue;
        
        if (!ord[v])
        {
            par[v] = u;
            int tmp = dfs(v);
            if (tmp > ord[u]) ans.push_back({ min(u, v), max(u, v) });
            ret = min(ret, tmp);
        }
        else ret = min(ret, ord[v]);
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int V, E; cin >> V >> E;
    while (E--)
    {
        int a, b; cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    
    for (int i = 1; i <= V; i++) if (!ord[i]) dfs(i);
    
    sort(ans.begin(), ans.end());
    cout << ans.size() << "\n";
    for (int i = 0; i < ans.size(); i++) cout << ans[i].first << " " << ans[i].second << "\n";
}
```

