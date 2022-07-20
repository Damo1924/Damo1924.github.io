---
title: "아호-코라식(Aho-Corasick) 알고리즘"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:    
  - Algorithm
use_math: true
comments: true

---

`Tags` 문자열 알고리즘, Multiple pattern matching, string search, failure fuction

## 1. Aho-Corasick algorithm

아호-코라식 알고리즘은 **텍스트에서 여러 개의 패턴을 효율적으로 탐색**하는 알고리즘이다.

텍스트에서 하나의 패턴을 탐색하는 것은 [KMP 알고리즘](https://damo1924.github.io/algorithm/KMPalgorithm/) 등에 의해 선형 시간에 가능하다는 사실을 알고 있다.

그런데 KMP 알고리즘을 이용하여 하나가 아니라 여러 개의 패턴을 탐색한다면, 시간복잡도가 패턴의 개수에 비례하게 된다.

텍스트의 길이를 $n$, 패턴의 개수를 $z$, 모든 패턴들의 길이의 합을 $m$이라고 하면 $O(m + zn)$ 이 된다.

이번 포스팅에서 살펴볼 아호-코라식 알고리즘은 이를 $O(m + n + k)$로 처리할 수 있게 해주기 때문에 **패턴과 텍스트의 길이에 대한 선형 시간**으로 탐색이 가능해진다.

이때 $k$는 텍스트 내에서 패턴이 발생하는 횟수이다.

탐색해야하는 패턴의 개수가 많아질수록 강력한 성능을 자랑하기 때문에 KMP 알고리즘과 더불어서 가장 유명한 문자열 검색 알고리즘들 중 하나이다.

---

### 1-1. Failure Link

우리는 KMP 알고리즘에서 실패 함수(failure function)라는 것을 이용해서 문자열 검색을 빠르게 수행할 수 있었다.

- 먼저 패턴의 실패 함수를 구하고,
- 텍스트를 탐색하면서 패턴과 다른 부분을 발견한다면, 실패 함수가 가리키는 위치로 돌아가 탐색을 이어나갔다.

아호-코라식은 이를 확장한 **failure link**라는 개념을 이용한다.

여러 개의 패턴을 동시에 검색할 것이기 때문에 **패턴들을 저장하고 있는 트라이(Trie) 자료구조**를 이용하는데,

트라이 위에서 텍스트를 탐색하다가 **더 이상 연결된 트라이가 없다면, 현재 위치한 트라이에 연결된 failure link를 타고 이동**하여 탐색을 이어나가게 된다.

트라이에서 각 노드의 failure link는 다음과 같이 정의된다.

- 루트가 아닌 각 노드 $u$에 대하여 $u$의 failure link는 아래 조건을 만족하는 노드 $v$($u \neq v$)로 향한다.
- **루트에서 $v$로 가는 경로가 루트에서 $u$로 가는 경로의 접미사(suffix)인 $v$ 중 루트부터의 경로가 가장 긴 것**

다소 뜬금없을 수 있지만, KMP 알고리즘의 실패 함수가 **접두사이면서 접미사인 부분문자열들 중 가장 긴 것의 길이**였다는 것을 떠올린다면 어렵지 않게 원리를 이해할 수 있다.

이러한 failure link가 있는 트라이 위에서 텍스트를 탐색한다면, 겹치는 부분이 최대가 되기 때문에 **항상 트라이에서 최대 깊이를 유지하면서 탐색**하게 된다.

---

### 1-2. Output Link

그런데 앞서 설명한 것처럼 탐색하게 되면, **다른 패턴의 부분문자열인 패턴**을 탐색하지 못할 수 있다.

즉, 루트에서 현재 노드까지의 경로에 해당하는 문자열의 접미사들 중 패턴이 존재할 때 이를 처리할 수 있기 추가적인 장치가 필요하다.

이를 처리하기 위해서 **output link**라는 개념을 이용한다.

현재 노드에서 failure function을 따라 이동한 노드가 패턴의 끝이라면, 현재 노드는 해당 패턴의 끝 노드와 output link로 연결시켜준다.

텍스트를 탐색하면서 현재 노드에 도달하게 되면, output link를 통해 루트에서 현재 노드까지의 경로에 해당하는 문자열의 접미사들 중 패턴이 존재한다는 것을 알 수 있게 되는 것이다.

---

### 1-3. Implementation: Trie with Links

이제 위의 두 링크를 포함한 트라이 자료구조를 구현해보자.

현재 노드를 $x$, $x$에서 문자 $c$로 라벨린된 간선으로 연결된 노드를 $y$라고 하자.

루트부터 $x$까지의 경로에 해당하는 문자열을 $S$라고 하면, 루트부터 $y$까지의 경로에 해당하는 문자열은 $Sc$이다.

$x$의 failure link $p$에 대하여, 루트부터 $p$까지의 경로에 해당하는 문자열을 $T$라고 하면 $T$는 $S$의 접두사이면서 접미사인 부분문자열 중 가장 긴 것이다.

만약 $p$에서 $c$로 라벨링된 간선으로 연결된 노드 $q$가 존재한다면,

$y$에 해당하는 문자열 $Sc$의 접두사이면서 접미사인 부분문자열 중 가장 긴 것이 $Tc$라는 사실로부터 $q$가 $y$의 failure link가 된다.

반대로 $p$에서 $c$로 라벨링된 간선으로 연결된 노드가 존재하지 않는다면, 그러한 노드가 존재할 때까지 $p$의 failure link를 타고 이동하면서 탐색해준다.

위 과정을 통해 트라이의 각 노드의 failure link를 구하기 위해서는 현재 노드보다 깊이가 작은 노드들의 failure link를 알고 있어야하므로 **BFS로 트라이를 탐색**하면서 구할 수 있다.

또한, 노드 $x$의 Output link는 $x$의 failure link $p$의 output link로부터 상수 시간에 구할 수 있다.

아래 코드는 텍스트에서 패턴들의 존재 여부를 구하는 아호-코라식 알고리즘이다.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <memory.h>
using namespace std;

const int mxN = 1e5 + 1, mxC = 26;
struct aho_corasick {
    int trie[mxN][mxC], piv = 0; // trie
    int fail[mxN]; // failure link
    int term[mxN]; // output link
    
    void init(vector<string> &v) { // multiple patterns
        memset(trie, 0, sizeof(trie));
        memset(fail, 0, sizeof(fail));
        memset(term, 0, sizeof(term));
        piv = 0;
        
        for (string &s : v) {
            int p = 0;
            for (int i = 0; i < s.size(); i++) {
                int j = s[i] - 'a';
                if (!trie[p][j]) trie[p][j] = ++piv;
                p = trie[p][j];
            }
            term[p] = 1;
        }
        
        queue<int> q;
        for (int i = 0; i < mxC; i++) if (trie[0][i]) q.push(trie[0][i]);
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (int i = 0; i < mxC; i++) if (trie[x][i]) {
                int p = fail[x];
                while (p && !trie[p][i]) p = fail[p];
                p = trie[p][i];
                fail[trie[x][i]] = p;
                if (term[p]) term[trie[x][i]] = 1;
                q.push(trie[x][i]);
            }
        }
    }
    
    bool query(string& s) {
        int p = 0;
        for (int i = 0; i < s.size(); i++) {
            int j = s[i] - 'a';
            while (p && !trie[p][j]) p = fail[p];
            p = trie[p][j];
            if (term[p]) return 1;
        }
        return 0;
    }
};
```

<br/>

## 2. Related Problems

### [BOJ] 9250. 문자열 집합 판별

[BOJ 9250. 문자열 집합 판별 문제 링크](https://www.acmicpc.net/problem/9250)

주어진 문자열에 패턴들의 존재 여부를 구하는 문제이다.

Output link를 통해 failure link를 타고 올라갔을 때 패턴의 끝에 해당하는 노드가 있는지만 전달하면 된다.

---

### [BOJ] 5735. Emoticons :-)

[BOJ 5735. Emoticons :-) 문제 링크](https://www.acmicpc.net/problem/5735)

주어진 문자열에서 이모티콘을 없애기 위해 특정 문자를 공백으로 대체하려고 한다.

공백을 포함하지 않는 이모티콘들이 주어지고, 문자열에 이모티콘이 없도록 만들기 위해 공백으로 바꾸어야하는 문자의 개수의 최솟값을 구하는 문제이다.

이는 찾은 이모티콘의 마지막 문자를 공백으로 대체해줌으로써 구할 수 있다.

즉, 문자열에서 이모티콘을 찾으면 트라이의 루트 노드로 돌아가서 탐색을 이어나가면 된다.

---

### [BOJ] 10256. 돌연변이

[BOJ 10256. 돌연변이 문제 링크](https://www.acmicpc.net/problem/10256)

주어진 문자열에 패턴들이 총 몇 번이나 나타나는지 구하는 문제이다.

이번에는 output link를 통해 failure link를 타고 올라갔을 때 패턴의 끝에 해당하는 노드의 개수를 전달해야한다.

텍스트를 탐색하면서 지나는 노드들의 output link에 저장된 값을 모두 더해줌으로써 답을 구할 수 있다.

---

### [BOJ] 2809. 아스키 거리

[BOJ 2809. 아스키 거리 문제 링크](https://www.acmicpc.net/problem/2809)

주어진 문자열에서 어떤 패턴에도 포함되지 않는 문자의 개수를 구하는 문제이다.

트라이의 각 노드에서 끝나는 패턴들 중 길이가 가장 긴 것의 길이를 기억해두고, 이후 문자열을 선형탐색하면서 어떤 패턴에도 속하지 않은 문자를 찾아주면 된다.

<br/>

## References

[1] [위키백과, '아호-코라식 알고리즘'](https://ko.m.wikipedia.org/wiki/%EC%95%84%ED%98%B8_%EC%BD%94%EB%9D%BC%EC%8B%9D_%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98)  
[2] [koosaga, 'Aho-Corasick Multiple Pattern Matching Algorithm'](https://koosaga.com/157)  




