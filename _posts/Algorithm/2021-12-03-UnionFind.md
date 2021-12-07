---
title: "유니온 파인드 (Union - Find)"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:    
  - Algorithm
use_math: true
comments: true

---

## 1. Union-Find Algorithm

유니온 파인드 알고리즘은 그래프 알고리즘의 일종으로, **두 노드가 같은 그래프에 속하는지 판별하는 알고리즘**이다.

노드를 합치는 **Union** 연산과 노드가 속한 트리의 루트 노드를 찾는 **Find** 연산으로 이루어진다.

노드를 트리 구조로 합치기 때문에 트리 구조로 이루어진 자료구조라고 할 수 있으며, **서로소 집합** 또는 **상호 베타적 집합(Disjoint-Set)**으로 불리기도 한다.

예를 들어 1, 2, 3, 4 노드를 하나로 묶고 싶다면 다음과 같이 배열을 이용해 연결해준다.

> `parent[2] = 1`, `parent[3] = 2`, `parent[4] = 3`

이 상황에서 어떤 두 노드가 연결되어 있는지 알고 싶다면 **두 노드가 속한 트리 구조의 루트 노드가 같은지 비교**하면 된다.

루트 노드가 같으면 연결되어 있는 것이고, 같지 않다면 연결되어 있지 않은 것을 의미한다.

그런데 위 방법처럼 연결하면 `1-2-3-4`와 같이 높이가 큰 트리 구조가 만들어지게 된다.

루트 노드를 찾는데 레벨에 비례하는 시간이 걸리기 때문에 위와 같은 트리 구조는 비효율적이다.

이를 해결하기 위해 노드를 연결하는 Union 연산을 할 때는 **연결하고자 하는 두 노드의 루트 노드들을 서로 연결**해준다.

<br/>

## 2. Union-Find Implementation

C++를 통해 유니온 파인드를 구현해보자.

이때 `parent[i]`는 노드 i의 부모 노드를 저장하는 배열을 의미한다.

위 배열의 초기 상태는 자기 자신을 가리키도록 `parent[i] = i`와 같이 설정해준다.

### 2-1. 루트 노드 찾는 함수: find

어떤 노드를 입력받아 해당 노드가 속한 트리의 루트 노드를 찾아 반환하는 함수를 구현해보자.

```cpp
int find (int x)
{
    if (parent[x] == x) return x; // 루트 노드를 발견하면 반환
    return find(parent[x]); // 루트 노드가 아니면 부모 노드를 재귀적으로 탐색
}
```

### 2-2. 노드를 합치는 함수: union

두 노드를 연결하는 함수를 구현해보자.

```cpp
void union (int x, int y)
{
    x = find(x);
    y = find(y);
    if (x == y) return;
    parent[y] = x;
}
```

두 노드를 연결하는 방법은 각 노드가 속한 트리의 루트 노드를 찾아 루트 노드를 연결해주는 것이다.

### 2-3. 두 노드가 연결되어 있는지 판별하는 함수: isUnion

```cpp
bool isUnion (int x, int y)
{
    x = find(x);
    y = find(y);
    if (x == y) return true;
    return false;
}
```

<br/>

## 3. Weighted Union

앞서 구현한 `union` 함수를 이용하면 높이가 높은 트리가 높이가 낮은 트리 밑으로 들어갈 수 있다.

이로 인해 트리의 높이가 계속 커지면, `find`와 `union`의 실행시간이 증가하게 된다.

이를 해결하기 위한 방법 중 하나는 항상 높이가 더 낮은 트리를 높이가 더 큰 트리 밑에 집어넣는 것이다.

이 방법을 **Weighted Union**이라고 부르며, 다음과 같은 배열을 사용한다.

> `rank[i]` = 노드 i를 루트로 하는 서브트리의 높이

하나의 노드로 이루어진 트리의 `rank` 값은 0이 된다.

```cpp
void union (int x, int y)
{
    x = find(x);
    y = find(y);
    if (rank[x] > rank[y]) parent[y] = x;
    else parent[x] = y;
    if (rank[x] == rank[y]) rank[y]++;
}
```

만약 두 트리의 높이가 동일한 경우에는 합쳤을 때 트리의 높이가 1 증가하기 때문에 이를 구현해주어야 한다.

이렇게 구현하면, 높이 1인 트리를 만드는데는 최소 2개의 노드가, 높이 2인 트리를 만드는데는 최소 4개의 노드가 필요함을 알 수 있다.

높이가 H인 트리를 만들기 위해서는 적어도 높이가 (H-1)인 트리가 두 개 필요하므로 귀납법에 의해 **높이가 H인 트리는 적어도** $2^H$**개의 노드를 포함하고 있음**을 알 수 있다.

트리에 있는 노드의 개수를 N이라 할 때, $2^H \leq N$ 이므로 $H \leq \log N$ 이 성립한다.

이때 `find`와 `union` 함수의 시간복잡도는 트리의 높이에 비례하므로 $O(\log N)$가 된다.

<br/>

## 4. Path Compression

Weight Union이 노드를 연결하는 과정에서 최적화를 한다면, 탐색 과정에서 최적화를 하는 방법도 있다.

2-1의 `find` 함수에서 `parent[x]`의 값을 루트 노드로 바꾸어줌으로써 효율을 개선할 수 있다.

```cpp
int find (int x)
{
    if (parent[x] == x) return x; // 루트 노드를 발견하면 반환
    return parent[x] = find(parent[x]); // 루트 노드를 찾아 부모 노드를 루트 노드로 만들어준다.
}
```

<br/>

## 5. Weighted Union with Path Compression

앞서 소개한 두 가지 최적화 방법을 모두 적용한 경우, $n$개의 노드에 대해 Union-Find를 $m$번 수행했을 때 worst-case 시간 복잡도는 $O(m \log^* n)$이다.

이때 $\log^* n$은 $n$에 $\log$를 $k$번 적용할 때 1 이하가 된다는 의미이다.

이는 **inverse Ackermann function**이라고 불리는 함수에 의해 bounded되어 있는데, 우리가 일반적으로 다루는 모든 수에 대해 5보다 작다고 한다. (사실상 상수 시간)

다음은 각 알고리즘에 대한 `union`, `find` 함수의 시간복잡도를 표로 나타낸 것이다.

| algorithm | union | find |
|:---:|:---:|:---:|
| union | $O(H)$ | $O(H)$ |
| weighted union | $O(\log N)$ | $O(\log N)$ |
| weighted union with path compression | $O(1)$ | $O(1)$ |

<br/>

## 6. 관련 문제

### 6-1. [백준] 1717. 집합의 표현

[백준 1717. 집합의 표현 문제 링크](https://www.acmicpc.net/problem/1717)

0부터 n까지 (n + 1)개의 원소가 있을 때, 다음의 두 연산을 수행하려고 한다.

1. a와 b의 합집합 연산: a가 포함되어 있는 집합과 b가 포함되어 있는 집합을 합친다.
2. a와 b가 같은 집합에 포함되어 있는지를 확인하는 연산: 맞으면 YES, 아니면 NO를 출력한다.

초기에는 0부터 n까지의 원소들이 각각 다른 집합에 속해있다.

입력된 연산을 수행하는 프로그램을 작성하면 된다.

**[Solution]**

첫 번째 연산은 앞서 구현한 `union` 함수를 실행하면 되고, 두 번째 연산은 `isUnion` 함수를 실행하면 된다.

---

### 6-2. [백준] 4195. 친구 네트워크

[백준 4195. 친구 네트워크 문제 링크](https://www.acmicpc.net/problem/4195)

친구 관계인 두 사람의 이름이 주어질 때마다 두 사람의 친구 네트워크에는 몇 명이 있는지 출력하면 된다.

**[Solution]**

먼저, 문자열로 입력받은 이름들을 숫자에 대응시키기 위해 `unordered_map`을 사용한다.

이름들을 숫자에 대응시킨 후, Union-Find를 통해 친구 네트워크를 구현한다.

이 문제의 특징은 **각 친구 네트워크에 있는 사람의 수**를 구해야한다는 것이다.

이를 해결할 수 있는 방법은 크게 두 가지가 있다.

> 1) `parent` 외에 새로운 배열 `cnt`를 선언하여 사용하는 방법
> 
> **:** `parent[i] == i`가 참인 루트 노드 i에 대해서 `cnt[i]`는 해당 트리에 속한 노드의 개수를 저장한다.
> 
> `cnt` 배열의 초기 상태는 모두 1이고, `union` 함수에 `cnt` 관련 코드를 추가해주면 된다.
> 
> 2) `parent`에 두 가지 정보를 모두 저장하는 방법
> 
> **:** 위 방법에 대해 생각해보면, `cnt` 배열에서 의미있는 값은 루트 노드의 값 뿐이다.
> 
> 그러므로 루트 노드에 대해서는 `parent` 배열에 해당 트리에 속한 노드의 개수를 저장하고, 나머지 노드에 대해서는 해당 노드의 부모 노드를 그대로 저장하면 하나의 배열로 문제를 해결할 수 있다.
> 
> 하지만 저장된 값이 트리의 노드 개수인지, 부모 노드의 번호인지 알 수 없기 때문에 **트리의 노드 개수는 - 부호를 붙여서 저장**한다.
> 
> `parent[i]`의 초기 상태를 i가 아니라 -1로 설정하면 된다.
> 
> 이러면 `parent[i]`가 음수이면 노드 i는 루트 노드이고, `-parent[i]`는 해당 트리에 속한 노드의 개수가 된다.

나는 첫 번째 방법을 택해서 해결하였고, 소스 코드는 다음과 같다.

<details>
<summary>소스 코드</summary>
<div markdown="1">

```cpp
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

unordered_map<string, int> name; // 이름 -> 인덱스 변환

vector<int> parent, cnt; // 각각 부모노드의 번호, 트리에 있는 노드의 개수를 저장

int find(int x)
{
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}

void _union(int x, int y)
{
    x = find(x);
    y = find(y);
    if (x == y) return;
    parent[y] = x; // x가 루트 노드가 되도록 합쳤으니
    cnt[x] += cnt[y]; // cnt[x]에 cnt[y]를 더해준다.
}

bool isUnion(int x, int y)
{
    x = find(x);
    y = find(y);
    if (x == y) return true;
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int T;
    cin >> T;
    while (T--)
    {
        parent = {0};
        cnt = {0};
        name.clear();
        
        int F;
        cin >> F;
        
        int idx = 1;
        string A, B;
        while (F--)
        {
            cin >> A >> B;
            if (name[A] == 0) // 처음 입력된 이름인 경우, 이름과 인덱스를 매칭시켜준다.
            {
                name[A] = idx;
                parent.push_back(idx);
                cnt.push_back(1);
                idx++;
            }
            if (name[B] == 0)
            {
                name[B] = idx;
                parent.push_back(idx);
                cnt.push_back(1);
                idx++;
            }
            
            _union(name[A], name[B]); // 친구 관계 맺어준다.
            cout << cnt[find(name[A])] << "\n"; // 해당 친구 네트워크에 있는 사람들의 숫자를 출력
        }
    }
}
```

</div>
</details>

---

### 6-3. [백준] 2162. 선분 그룹

[백준 2162. 선분 그룹 문제 링크](https://www.acmicpc.net/problem/2162)

교차하는 선분들끼리 하나의 그룹으로 묶고, 각 그룹에 속한 선분의 개수를 구해야하는 문제이다.

선분끼리 만나는지 만나지 않는지 판별하는 것을 구현하는 것이 포인트이다.

자세한 풀이는 [이 포스트](https://damo1924.github.io/ps/BAEKJOON-2162/) 참고.

<br/>

## Reference

[1] [Robert Sedgewick, Kevin Wayne, Algorithms,  4th Edition, "Case Study: Union-Find"](https://algs4.cs.princeton.edu/15uf/)




