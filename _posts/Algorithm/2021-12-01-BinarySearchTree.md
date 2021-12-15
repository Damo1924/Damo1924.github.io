---
title: "이진 검색 트리 (Binary Search Tree)"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:    
  - Algorithm
use_math: true
comments: true

---

`Tags` BST, Preorder, Inorder, Postorder, set, map

## 1. 이진 검색 트리(Binary Search Tree)란?

모든 노드가 다음 조건을 만족하는 이진 트리를 이진 검색 트리라고 한다.

1. 노드의 왼쪽 서브트리에 있는 노드들의 값은 자신보다 작아야 한다.
2. 노드의 오른쪽 서브트리에 있는 노드들의 값은 자신보다 커야 한다.

위 조건에 의해 이진 검색 트리에는 값이 동일한 노드는 존재하지 않는다.

이진 검색 트리는 다음과 같은 특징들을 갖고 있다.

- 중위 순회(inorder, LNR)를 통해 노드들의 값을 오름차순으로 얻을 수 있다.
- 이진 탐색(binary search)과 비슷한 방식으로 아주 빠르게 값을 검색할 수 있다.
- 노드를 비교적 쉽게 삽입할 수 있다.
- 구조가 단순하다.

이러한 특징들로 인해 이진 검색 트리는 다양한 알고리즘에 이용되는데, 이를 C++의 class와 pointer를 이용해서 직접 구현해보자.

<br/>

## 2. C++로 이진 검색 트리 구현하기

### 2-1. 노드(node) 구현하기

먼저 이진 검색 트리를 구성하는 각 노드는 해당 노드의 값(value), 왼쪽 자식 노드(leftChild), 오른쪽 자식 노드(rightChild)에 대한 정보를 담고 있어야 한다.

```cpp
class Node {
public:
    int value; // 값
    Node* leftChild = NULL; // 왼쪽 자식 노드
    Node* rightChild = NULL; // 오른쪽 자식 노드
    
    Node(int _value, Node* _leftChild, Node* _rightChild) // 생성자
        : value(_value), leftChild(_leftChild), rightChild(_rightChild) { }
};
```

---

### 2-2. 노드 탐색(search)

이진 검색 트리의 가장 큰 장점 중 하나는 평균적으로 $O(\log n)$에 특정 값을 가진 노드를 검색하는 것이 가능하다는 점이다.

찾으려는 값이 어떤 노드의 값보다 크면 해당 노드의 오른쪽 서브트리에 대해 탐색을 이어나가면 되고, 반대로 찾으려는 값이 어떤 노드의 값보다 작으면 해당 노드의 왼쪽 서브트리에 대해 탐색을 하면 된다.

그러다 찾으려는 값을 가진 노드를 찾으면 해당 노드를 반환하고, 리프 노드까지 탐색했음에도 찾으려는 값을 가진 노드가 없으면 `NULL`을 반환하는 함수를 구현하였다.

```cpp
Node* searchNode (Node* root, int v)
{
    if (root == NULL) return NULL;
    
    if (root->value == v) return root;
    else if (root->value > v) return searchNode(root.leftChild, v);
    else return searchNode(root.rightChild, v);
}
```

---

### 2-3. 노드 삽입(insert)

이진 검색 트리에 새로운 노드를 삽입하기 위해서는 해당 노드가 삽입되었을 때도 이진 검색 트리의 조건을 만족하도록 올바른 위치에 노드를 삽입해야 한다.

새로운 노드를 삽입할 위치를 찾는 과정은 다음과 같다.

1. 현재 서브트리의 루트 노드와 삽입할 노드의 값을 비교한다.
2. 삽입할 노드의 값이 더 클 때, 루트 노드가 오른쪽 자식 노드가 없으면 그 자리에 노드를 삽입한다. 루트 노드가 오른쪽 자식 노드가 있으면 오른쪽 자식 노드를 루트로 하는 서브트리에 대해 1번부터 과정을 반복한다.
3. 삽입할 노드의 값이 더 작을 때, 루트 노드가 왼쪽 자식 노드가 없으면 그 자리에 노드를 삽입한다. 왼쪽 자식 노드가 있으면, 왼쪽 자식 노드를 루트로 하느 서브트리에 대해 1번부터 과정을 반복한다.

새로운 원소를 삽입하는 함수 `insertNode`를 구현해보았다.

```cpp
void insertNode (Node* root, Node* node)
{
    if (node->value < root->value) // 서브트리의 루트보다 삽입하려는 노드의 값이 더 작을 때
    {
        if (root->leftChild == NULL) // 루트의 왼쪽 자식 노드가 없는 경우, 그 자리에 삽입
        {
            root->leftChild = node;
            return;
        }
        else // 루트의 왼쪽 자식 노드가 있으면, 재귀적으로 반복
        {
            insertNode(root->leftChild, node);
        }
    }
    else if (node->value > root->value) // 서브트리의 루트보다 삽입하려는 노드의 값이 더 클 때
    {
        if (root->rightChild == NULL) // 루트의 오른쪽 자식 노드가 없으면, 그 자리에 삽입
        {
            root->rightChild = node;
            return;
        }
        else // 루트의 오른쪽 자식 노드가 있으면, 재귀적으로 반복
        {
            insertNode(root->rightChild, node);
        }
    }
}
```

---

### 2-4. 노드 삭제(delete)

트리에서 노드를 삭제한다는 것의 의미는 연결되어있는 노드들 간의 연결을 끊는다는 것을 말한다.

이진 검색 트리에서 노드를 삭제하고 나면, 나머지 노드들이 이진 검색 트리를 이루도록 노드들을 잘 연결시켜주어야 한다.

이때 삭제할 노드의 자식 노드의 개수에 따라서 방법이 달라지게 된다.

주의할 점은 삭제할 노드의 부모 노드와 자식 노드를 연결시켜야하기 때문에 부모 노드에 대해서도 기억을 해두어야 한다는 것이다.

그럼 자식 노드의 개수가 0개, 1개, 2개일 때 각각에 대해 삭제 방법을 알아보자.

> **1. 삭제할 노드의 자식 노드의 개수 = 0개**
>
> 삭제할 노드가 리프 노드이면 그냥 부모 노드와의 연결을 끊으면 된다.
>
> **2. 삭제할 노드의 자식 노드의 개수 = 1개**
>
> 삭제할 노드의 자식 노드가 한 개이면 삭제할 노드의 위치에 자식 노드를 연결하면 된다.
> 
> **3. 삭제할 노드의 자식 노드의 개수 = 2개**
>
> 이전의 두 케이스는 간단하게 처리할 수 있었지만 자식 노드의 개수가 두 개이면 조금 복잡해진다.
>
> 삭제할 노드의 위치에 올 노드를 정해야하는데, 삭제될 노드의 왼쪽 서브트리보단 크고 오른쪽 서브트리보단 작은 값을 가진 노드여야한다.
>
> 이 조건을 만족하는 노드는 딱 두 개가 있다.
>
> - 삭제할 노드의 오른쪽 서브트리에서 가장 왼쪽에 있는 노드
> - 삭제할 노드의 왼쪽 서브트리에서 가장 오른쪽에 있는 노드
>
> 나는 왼쪽 서브트리의 가장 오른쪽에 있는 노드를 선택하는 쪽으로 코드를 작성하였다.

노드를 삭제하는 함수 `removeNode`를 구현하기 전에, 어떤 노드의 왼쪽 서브트리에서 가장 오르쪽에 있는 노드를 반환하는 함수 `searchMaxNode`를 구현하였다.

```cpp
Node* searchMaxNode (Node* node)
{
    if (node->right == NULL) return node; // 가장 오른쪽 노드이면 해당 노드를 반환
    else return searchMaxNode(node->right); // 오른쪽 자식 노드가 있으면 재귀적으로 탐색
}
```

다음은 노드를 삭제하는 함수의 코드이다.

```cpp
Node* removeNode (Node* root, Node* parent, int v)
{
    if (tree == NULL) return NULL;
    
    Node* removedNode = NULL; // 삭제된 노드를 반환하기 위함.
    
    // 삭제할 노드를 탐색
    if (root->value > v) removedNode = removeNode(root->left, root, v);
    else if (root->value < v) removedNode = removeNode(root->right, root, v);
    else // 찾았으면 노드를 삭제한다.
    {
        removedNode = root;
        
        // 자식 노드 = 0개
        if (root->leftChild == NULL && root->rightChild == NULL)
        {
            if (parent->leftChild == root) parent->leftChild = NULL;
            if (parent->rightChild == root) parent->rightChild = NULL;
        }
        
        // 자식 노드 = 1개
        else if (root->leftChild == NULL)
        {
            if (parent->leftChild == root) parent->leftChild = root->rightChild;
            else parent->rightChild = root->rightChild;
        }
        else if (root->rightChild == NULL)
        {
            if (parent->leftChild == root) parent->leftChild = root->leftChild;
            else parent->rightChild = root->leftChild;
        }
        
        // 자식 노드 = 2개
        else
        {
            Node* replaceNode = removeNode(root, NULL, searchMaxNode(root->left)->value); // 삭제할 노드 자리에 들어갈 노드를 찾고, 해당 노드를 삭제
            root->data = replaceNode->data; // 삭제할 노드의 값을 대체할 노드의 값으로 갱신한다.
        }
    }
    
    return removedNode;
}
```

---

### 2-5. 순회 구현하기

전위 순회, 중위 순회, 후위 순회를 각각 구현해보자.

**1. 전위 순회 (preorder)**

```cpp
void preOrder (Node* root, vector<int>& vec)
{
    if (root == NULL) return;
    vec.push_back(root->value);
    preOrder(root->leftChild, vec);
    preOrder(root->rightChild, vec);
}
```

**2. 중위 순회 (inorder)**

```cpp
void inOrder (Node* root, vector<int>& vec)
{
    if (root == NULL) return;
    inOrder(root->leftChild, vec);
    vec.push_back(root->data);
    inOrder(root->rightChild, vec);
}
```

**3. 후위 순회 (postorder)**

```cpp
void postOrder (Node* root, vector<int>& vec)
{
    if (root == NULL) return;
    postOrder(root->leftChild, vec);
    postOrder(root->rightChild, vec);
    vec.push_back(root->data);
}
```

<br/>

## 3. STL 사용하기

안타깝게도 위에서 구현한 이진 검색 트리는 **트리의 편향**이 발생할 수 있다는 문제가 있어서 사용하지 못한다.

트리가 편향되었다는 것은 트리에 노드들이 불균형적으로 존재해서 트리의 높이가 커지는 것을 의미한다.

이상적인 경우에는 N개의 노드가 있으면 트리의 높이는 $\log N$ 정도이므로 어떤 값을 검색, 삽입, 삭제하는데 걸리는 시간복잡도가 $O(\log N)$이다.

그러나 트리가 편향되면 이 높이가 최대 N, 즉 단순 벡터와 같아지기 때문에 시간복잡도가 $O(N)$이 된다.

이 부분을 개선한 트리가 바로 **자가 균형 트리(Self Balancing Tree)**이다.

대표적인 자가 균형 트리로는 **AVL Tree**와 **Red-Black Tree**가 있는데, Red-Black Tree가 조금 더 뛰어난 성능을 보여주기 때문에 주로 사용된다.

(Red-Black Tree에 대한 자세한 내용은 [이 포스트](https://damo1924.github.io/algorithm/RedBlackTree/)에서 다루고 있다.)

이러한 자가 균형 트리는 트리의 편향성을 해소함으로써 검색, 삽입, 삭제의 시간복잡도를 $O(\log N)$으로 유지한다.

그러므로 우리는 PS를 할 때 이진 검색 트리를 직접 구현해서 사용하는 것이 아니라 내장된 자료구조를 이용하면 되는 것이다.

C++의 STL에는 `set`, `multiset`, `map`라는 이름으로 Red-Black Tree가 구현되어 있으며, 자세한 내용은 [이 포스트](https://damo1924.github.io/cpp/Cpp-map/)에서 다루고 있다.

<br/>

## 4. 관련 문제 풀어보기

마지막으로 이진 검색 트리를 이용해서 풀 수 있는 문제들을 풀어보면서 언제 BST를 사용하는지 익히자.

아래에 있는 문제들은 [BaaaaaaaaaaarkingDog](https://www.acmicpc.net/user/BaaaaaaaaaaarkingDog) 님이 만드신 백준 문제집 [0x16강 - 이진 검색 트리](https://www.acmicpc.net/workbook/view/9346)에 있는 문제들이다.

### [백준] 23326. 홍익 투어리스트

[백준 23326. 홍익 투어리스트 문제 링크](https://www.acmicpc.net/problem/23326)

BST를 이용하면 아주 쉽게 해결할 수 있는 문제이다.

`set`에 **명소인 구역의 번호**를 저장하면 새로운 명소를 추가, 기존의 명소를 삭제, 현재 위치부터 다음 명소까지의 거리를 구하는 작업 모두 로그 시간복잡도로 수행할 수 있게 된다.

<details>
<summary>소스 코드</summary>
<div markdown="1">

```cpp
#include <iostream>
#include <set>
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N, Q;
	cin >> N >> Q;

	set<int> s; // 명소인 구역의 번호를 저장
	int A;
	for (int i = 1; i <= N; i++)
	{
		cin >> A;
		if (A) s.insert(i);
	}

	int pos = 1; // 현재 도현이의 위치
	int a, b;
	while (Q--)
	{
		cin >> a;
		if (a == 1)
		{
			cin >> b;
			if (s.count(b)) s.erase(b);
			else s.insert(b);
		}
		else if (a == 2)
		{
			cin >> b;
			pos = (pos + b) % N;
			if (pos == 0) pos = N; // 0번째 구역이 아니라 N번째 구역으로 바꾸어주자.
		}
		else
		{
			if (s.empty())
			{
				cout << "-1\n";
				continue;
			}

			auto it = s.lower_bound(pos);
			if (it == s.end()) cout << *s.begin() + N - pos << "\n"; // 현재 위치에서 구역 N까지 명소가 없으면 가장 번호가 작은 명소가 가장 가까운 명소이다.
			else cout << *it - pos << "\n";
		}
	}
}
```
  
</div>
</details>

### [백준] 21939. 문제 추천 시스템 Version 1

[백준 21939. 문제 추천 시스템 Version 1 문제 링크](https://www.acmicpc.net/problem/21939)

각 문제마다 문제 번호와 난이도가 주어질 때, "추천 문제 리스트"에 문제를 추가, 삭제하는 명령과 "추천 문제 리스트"에서 가장 어려운(또는 쉬운) 문제를 출력하는 명령을 구현하는 문제이다.

마찬가지로 원소를 삽입, 삭제, 검색하는 작업을 로그 시간에 할 수 있는 이진 검색 트리를 이용하면 해결할 수 있다.

이 경우에는 `set`에 '난이도, 문제 번호'를 묶은 `pair<int, int>`를 저장함으로써 쉽게 가장 어려운/쉬운 문제를 찾을 수 있다.

> 이때 가장 어려운 문제는 `<iterator>` 헤더 파일에 있는 `prev()` 함수를 이용하여 출력해야한다.

<details>
<summary>소스 코드</summary>
<div markdown="1">

```cpp
#include <iostream>
#include <set>
#include <iterator>
using namespace std;
typedef pair<int, int> p;

set<p> LP; // 추천 문제 리스트를 set으로 구현: {난이도, 문제번호}를 저장

int L[100001]; // 리스트에서 문제를 삭제할 때 문제 번호만 주어지기 때문에 문제번호를 통해 난이도를 알 수 있도록 저장해둠.

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int N;
    cin >> N;
    
    int p, l;
    for (int i = 0; i < N; i++)
    {
        cin >> p >> l;
        L[p] = l;
        LP.insert({l, p});
    }
    
    int M;
    cin >> M;
    
    string s;
    int a, b;
    for (int i = 0; i < M; i++)
    {
        cin >> s >> a;
        if (s == "recommend")
        {
            if (a == 1) cout << (*prev(LP.end())).second << "\n";
            else cout << (*LP.begin()).second << "\n";
        }
        else if (s == "add")
        {
            cin >> b;
            LP.insert({b, a});
            L[a] = b;
        }
        else
        {
            LP.erase({L[a], a});
        }
    }
}
```

</div>
</details>

### [백준] 21944. 문제 추천 시스템 Version 2

[백준 21944. 문제 추천 시스템 Version 2 문제 링크](https://www.acmicpc.net/problem/21944)

앞선 Version 1을 조금 더 복잡하게 바꾸어 놓은 문제이다.

각 명령을 구현하기 위해 필요한 `set`을 적절히 선언하고, 명령의 세부적인 부분까지 잘 고려해야한다.

그렇게 어려운 문제는 아니니 꼭 한 번 직접 구현해보는 것을 추천한다.

<details>
<summary>소스 코드</summary>
<div markdown="1">

```cpp
#include <iostream>
#include <set>
#include <iterator>
using namespace std;
typedef pair<int, int> p;

// LPG: {난이도, 문제번호, 분류}, GLP: {분류, 난이도, 문제번호} 순서로 저장하는 이진 검색 트리
// LPG로 recommend2, recommend3을, GLP로 recommend를 구현할 것이다.
set<pair<p, int>> LPG, GLP;

// 리스트에서 문제를 삭제할 때 문제 번호를 통해 난이도와 분류를 알아야해서 각각을 저장할 배열을 사용
int L[100001], G[100001];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int N;
    cin >> N;
    
    int p, l, g;
    for (int i = 0; i < N; i++)
    {
        cin >> p >> l >> g;
        L[p] = l;
        G[p] = g;
        LPG.insert({ {l, p}, g });
        GLP.insert({ {g, l}, p });
    }
    
    int M;
    cin >> M;
    
    string s;
    int a, b, c;
    for (int i = 0; i < M; i++)
    {
        cin >> s >> a;
        if (s == "recommend")
        {
            cin >> b;
            if (b == 1) cout << (*prev(GLP.lower_bound({ {a, 101}, 0 }))).second << "\n";
            else cout << (*GLP.lower_bound({ {a, 0}, 0 })).second << "\n";
        }
        else if (s == "recommend2")
        {
            if (a == 1) cout << (*prev(LPG.end())).first.second << "\n";
            else cout << (*LPG.begin()).first.second << "\n";
        }
        else if (s == "recommend3")
        {
            cin >> b;
            auto it = LPG.lower_bound({ {b, 0}, 0 });
            if (a == 1)
            {
                if (it == LPG.end()) cout << "-1\n";
                else cout << (*LPG.lower_bound({ {b, 0}, 0 })).first.second << "\n";
            }
            else
            {
                if (it == LPG.begin()) cout << "-1\n";
                else cout << (*prev(LPG.lower_bound({ {b, 0}, 0 }))).first.second << "\n";
            }
        }
        else if (s == "add")
        {
            cin >> b >> c;
            LPG.insert({ {b, a}, c });
            GLP.insert({ {c, b}, a });
            L[a] = b;
            G[a] = c;
        }
        else
        {
            LPG.erase({ {L[a], a}, G[a] });
            GLP.erase({ {G[a], L[a]}, a });
        }
    }
}
```

</div>
</details>

### [백준] 19700. 수업

[백준 19700. 수업 문제 링크](https://www.acmicpc.net/problem/19700)

조건을 만족하면서 수강생들을 최대한 적은 그룹으로 나누는 문제이다.

앞의 세 문제는 단순히 각 명령들을 구현하는 문제였다면, 이 문제는 **학생들을 그룹에 배치하는 그리디한 방법**을 떠올려야 해결할 수 있다.

**Hint**

> 키가 큰 사람부터 그룹에 배치하면 키는 고려할 필요가 없어지고, 각 그룹에 몇 명의 사람이 있는지만 알면 된다.
> 
> 그러므로 **각 그룹에 몇 명의 사람이 있는지에 대한 이진 검색 트리**를 사용하면 된다.
>
> 그룹에 있는 사람의 수는 중복될 수 있으므로 `multiset`을 이용하자.

<details>
<summary>소스 코드</summary>
<div markdown="1">

```cpp
#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>
using namespace std;

pair<int, int> HK[500000]; // HK[i] = {h_i, k_i}

multiset<int> group; // 각 그룹에 있는 사람의 수를 저장하는 이진 검색 트리

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int N;
    cin >> N;
    for (int i = 0; i < N; i++) cin >> HK[i].first >> HK[i].second;
    
    sort(HK, HK + N); // 키에 대한 오름차순으로 정렬
    
    for (int i = N - 1; i >= 0; i--) // 키가 큰 사람부터 그룹에 배치한다.
    {
        auto it = group.lower_bound(HK[i].second);
        if (it == group.begin()) // 모든 그룹의 사람 수가 학생 i의 한계보다 많을 때는 새로운 그룹을 만든다.
        {
            group.insert(1);
            continue;
        }
        
        it = prev(it); // 학생 i의 한계보다 적은 수의 사람이 있는 그룹 중 가장 사람이 많은 그룹
        int k = *it + 1;
        group.erase(it); // set은 값 변경이 불가능하므로 기존 그룹에 있는 사람 수를 제거하고 1을 더한 값을 삽입한다.
        group.insert(k);
    }
    cout << group.size(); // 그룹의 최소 개수를 출력한다.
}
```

</div>
</details>

### [백준] 7662. 이중 우선순위 큐

자세한 풀이는 [이 포스트](https://damo1924.github.io/ps/BAEKJOON-7662/) 참고.

### [백준] 1202. 보석 도둑

자세한 풀이는 [이 포스트](https://damo1924.github.io/ps/BAEKJOON-1202/) 참고.

### [백준] 1539. 이진 검색 트리

자세한 풀이는 [이 포스트](https://damo1924.github.io/ps/BAEKJOON-1539/) 참고

