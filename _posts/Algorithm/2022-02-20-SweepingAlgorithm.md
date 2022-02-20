---
title: "스위핑 알고리즘(Sweeping Algorithm)"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` 

## 1. Sweeping Algorithm

스위핑 알고리즘은 정렬된 순서대로 탐색을 해나가는 기법을 말한다.

사실 어떤 알고리즘이라고 부를만큼 복잡한 매커니즘이 있는 것은 아니지만, 특정 문제들에서 굉장히 강력한 모습을 보여준다.

다른 알고리즘들과 함께 이용되는 경우가 많기 때문에 스위핑 알고리즘을 이용해야겠다는 생각을 하기 쉽지 않다.

이번 포스팅에서는 스위핑 알고리즘을 이용하는 여러가지 문제들을 직접 풀어볼 것이다.

<br/>

## [백준] 2170. 선 긋기

[백준 2170. 선 긋기 문제 링크](https://www.acmicpc.net/problem/2170)

$x$축 위에 $N$개의 선을 그으려고 한다.

이때 그은 선의 총 길이를 구하는 문제이다.

**[SOLUTION] Sweeping algorithm**

스위핑 알고리즘을 설명하는데 있어 가장 대표적인 문제 중 하나이다.

선들을 시작 좌표를 기준으로 정렬한 뒤, 순서대로 탐색하면서 선들의 길이를 측정해준다.



```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int N; cin >> N;
    vector<pair<int, int> v(N);
    for (int i = 0; i < N; i++) cin >> v[i].first >> v[i].second;
    sort(v.begin(), v.end());

    ll ans = 0;
    int x = v[0].first, y = v[0].second;
    for (int i = 1; i < N; i++)
    {
        if (v[i].first <= y) y = max(y, v[i].second);
        else { ans += y - x; x = v[i].first; y = v[i].second; }
    }
    ans += y - x;
    cout << ans;
}
```

<br/>
