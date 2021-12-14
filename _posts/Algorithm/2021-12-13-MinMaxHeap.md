---
title: "Min-Max Heap"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:    
  - Algorithm
use_math: true
comments: true

---

`Tags`  Min-Max Heap, Double-ended priority queue, 이중 우선순위 큐

## 1. Min-Max Heap

Min-max heap은 최댓값과 최솟값을 각각 상수 시간에 얻을 수 있고, 로그 시간에 삭제가 가능한 Max heap와 Min heap의 장점을 동시에 가진 완전 이진 트리이다.

이는 **이중 우선순위 큐(Double-ended priority queue)**를 구현하는데 굉장히 유용한 자료구조로, 원소 삽입과 삭제를 로그 시간에 할 수 있다는 특징을 가지고 있다.

Min-max heap은 다음을 만족하는 트리 구조를 가진다.

1. 짝수 레벨에 위치한 노드는 해당 노드를 루트로 하는 서브트리에 속한 모든 노드보다 작다.
2. 홀수 레벨에 위치한 노드는 해당 노드를 루트로 하는 서브트리에 속한 모든 노드보다 크다.

이때 루트 노드의 레벨은 0이며, 짝수 레벨을 min level, 홀수 레벨은 max level이라고 부른다.

<center><img src="https://user-images.githubusercontent.com/88201512/145772828-9abdbc31-3fce-4683-8b1a-03a48741544a.jpg" width="60%" height="60%"></center>

<center>(출처: Reference [1])</center>

<br/>

위 조건으로 인해 다음과 같은 특징들이 얻어진다.

- Min-max heap의 최솟값은 루트 노드이다.
- Min-max heap의 최댓값은 루트 노드의 두 자식 노드 중 더 큰 값이다.

이와 반대로 최댓값이 루트 노드에 저장되고, 최솟값이 루트 노드의 자식 노드 중 하나인 자료구조를 Max-min heap이라고 한다.

<br/>

## 2. Implementation of Min-Max Heap

Min-max heap은 Min heap과 Max heap과 같은 원리로 삽입, 삭제가 이루어진다.

단지 Min heap과 Max heap은 모든 레벨에 있는 노드에 대해 대소관계를 비교했지만, Min-max heap은 min level이나 max level에 있는 노드만 비교하는 것 뿐이다.

다음은 구현 과정에 사용할 헤더 파일, 상수, 변수, 함수들이다.

```cpp
#include <iostream>
#include <cmath>
using namespace std;
const int INF = 2147483647;

int MMH[1000000], L;

void swap(int& a, int& b)
{
    int tmp = b;
    b = a;
    a = tmp;
}
```

- `<cmath>`: 인덱스를 통해 해당 노드의 레벨을 구하기 위해 `floor()`와 `log2()` 함수를 사용하였다.
- `INF`: 32-비트 정수로 표현할 수 있는 최대값
- `MMH[]`: Min-max-heap을 저장할 배열, **루트 노드의 인덱스는 1이다**.
- `L`: Min-max-heap의 길이 (= Min-max-heap의 마지막 원소의 인덱스)

---

### 2-1. Push Down Algorithm (Trickle Down Algorithm)

최댓값 또는 최솟값을 삭제한 후, 남은 트리를 min-max heap 구조로 만들기 위해 필요한 `pushDown()` 함수를 구현해보자.

이 함수는 무작위 배열을 min-max heap으로 바꾸는 `heapify()` 함수에서도 사용된다.

Push Down이라는 이름에서 알 수 있듯이, 인덱스 `idx`를 인자로 받아 해당 노드를 자식/손자 노드들과 비교하면서 대소 관계를 만족하도록 하는 알고리즘이다.

Push Down 함수는 다음과 같다.

```cpp
void pushDown(int idx)
{
    int h = floor(log2(idx));
    if (h % 2) pushDown_max(idx); // idx: max level
    else pushDown_min(idx); // idx: min level
}
```

> 앞으로 `h = floor(log2(idx))`를 자주 사용할 것으므로 기억해두자.
> 
> Min-max heap은 완전 이진 트리이기 때문에 위와 같이 노드의 레벨을 구할 수 있다.

`h`는 `idx`의 레벨을 의미하고, 만약 노드가 max level에 있으면 `pushDown_max()`를 실행하고, 노드가 min level에 있으면 `pushDown_min()`을 실행하면 된다.

앞서 간략히 소개했듯이, min-max heap의 핵심은 max level 또는 min level에 따라 서로 다른 연산을 적용해주는 것이다.

먼저 입력으로 min level에 있는 노드의 인덱스를 받는 `pushDown_min()` 함수를 구현해보자.

1. 입력으로 받은 노드의 자식 노드와 손자 노드(최대 6개)들의 최솟값을 구한다.
2. 위에서 구한 최솟값이 자식 노드인지, 손자 노드인지에 따라 경우를 나눈다.

이때 입력으로 받은 노드의 인덱스를 `idx`, 최솟값에 해당하는 노드의 인덱스를 `m_idx`라고 하자.

> **2-1.** `m_idx` = `idx`의 손자 노드
> 
> `m_idx`와 `idx` 둘 다 min level의 노드이므로, 둘 중 더 작은 값이 `idx` 위치에 가야한다.
> 
> 만약 위 대소관계를 이미 만족한다면, min-max heap의 조건을 만족하게 된다.
> 
> 위 대소관계를 만족하지 않아 `swap()`을 해준 경우를 살펴보자.
> 
> 이제 원래 `idx`에 있던 값이 `m_idx`에 있게 되므로, `m_idx`와 `m_idx`의 부모 노드의 크기를 비교해야한다.
> 
> `m_idx`가 min level이기 때문에 `m_idx`의 값이 더 작아야한다.
> 
> 적절한 `swap()`을 해주었다면, 이제 위 과정을 `m_idx`에 대해 반복함으로써 min-max heap의 형태로 만든다.

> **2-2.** `m_idx` = `idx`의 자식 노드
> 
> `m_idx`가 `idx`의 자식 노드이면, `m_idx`는 자식 노드가 없다는 것을 의미한다.
> 
> 그러므로 `m_idx`와 `idx`의 크기를 비교해서 더 큰 값이 `m_idx`에 오게 해주면 끝난다.

함수 코드는 다음과 같다.

```cpp
void pushDown_min(int idx)
{
    int child[6]; // idx의 자식 노드, 손자 노드의 인덱스를 저장
    for (int i = 0; i < 2; i++) child[i] = 2 * idx + i;
    for (int i = 2; i < 6; i++) child[i] = 4 * idx + i - 2;
    
    int m = INF, m_idx = -1; // idx의 자식, 손자 노드 중 최솟값을 찾는다.
    for (int i = 0; i < 6; i++)
    {
        if (child[i] > L) break;
        
        if (m >= MMH[child[i]])
        {
            m = MMH[child[i]];
            m_idx = child[i];
        }
    }

    if (m_idx == -1) return; // idx가 자식 노드가 없는 경우

    if (m_idx >= 4 * idx) // 앞서 구한 최솟값이 손자 노드인 경우
    {
        if (MMH[m_idx] < MMH[idx])
        {
            swap(MMH[m_idx], MMH[idx]);
            if (MMH[m_idx] > MMH[m_idx / 2])
                swap(MMH[m_idx], MMH[m_idx / 2]);
            pushDown_min(m_idx);
        }
    }
    else if (MMH[m_idx] < MMH[idx]) // 앞서 구한 최솟값이 자식 노드인 경우
        swap(MMH[m_idx], MMH[idx]);
}
```

`pushDown_max()` 함수는 위와 정확히 부등호 방향만 바꾸어주면 된다.

```cpp
void pushDown_max(int idx)
{
    int child[6]; // idx의 자식 노드, 손자 노드의 인덱스를 저장
    for (int i = 0; i < 2; i++) child[i] = 2 * idx + i;
    for (int i = 2; i < 6; i++) child[i] = 4 * idx + i - 2;
    
    int m = -INF - 1, m_idx = -1; // idx의 자식, 손자 노드 중 최솟값을 찾는다.
    for (int i = 0; i < 6; i++)
    {
        if (child[i] > L) break;
        
        if (m <= MMH[child[i]])
        {
            m = MMH[child[i]];
            m_idx = child[i];
        }
    }

    if (m_idx == -1) return; // idx가 자식 노드가 없는 경우

    if (m_idx >= 4 * idx) // 앞서 구한 최솟값이 손자 노드인 경우
    {
        if (MMH[m_idx] > MMH[idx])
        {
            swap(MMH[m_idx], MMH[idx]);
            if (MMH[m_idx] < MMH[m_idx / 2])
                swap(MMH[m_idx], MMH[m_idx / 2]);
            pushDown_max(m_idx);
        }
    }
    else if (MMH[m_idx] > MMH[idx]) // 앞서 구한 최솟값이 자식 노드인 경우
        swap(MMH[m_idx], MMH[idx]);
}
```

---

### 2-2. Build (Heapify)

Push Down을 이용하면 주어진 임의의 배열을 min-max heap으로 만드는 함수를 만들 수 있다.

이는 **Floyd's linear-time heap construction algorithm**에 의해 구현된다.

```cpp
void heapify()
{
    for (int i = L / 2; i >= 0; i--) pushDown(i);
}
```

---

### 2-3. Push Up Algorithm (Bubble Up Algorithm, Insertion)

Min-max heap에 원소를 삽입하는 것은 Push Up Algorithm에 의해 이루어진다.

Push Down과 반대로 입력된 노드와 부모 노드를 비교하면서 트리를 min-max heap의 구조로 만드는 알고리즘이다.

Push Up (= Insertion)은 다음과 같다.

1. Min-max heap을 저장하고 있는 배열의 맨 끝에 삽입하려는 원소를 추가한다.
2. 삽입된 원소와 부모 원소를 비교한 후, max level 노드들끼리 비교하는 `pushUp_max()`와 min level 노드들끼리 비교하는 `pushUp_min()` 중 적절한 것을 택한다.

이때 다음과 같이 생각할 수 있다.

- 삽입된 원소가 부모 원소보다 작으면 루트 노드까지의 경로에 있는 모든 max level 노드들보다 작다는 것을 의미하므로, min level 노드들만 고려하면 된다.
- 삽입된 원소가 부모 원소보다 크면 루트 노드까지의 경로에 있는 모든 min level 노드들보다 크다는 것을 의미하므로, max level 노드들만 고려하면 된다.

`pushUp()` 함수는 다음과 같이 구성된다.

```cpp
void pushUp(int n)
{
    L++;
    MMH[L] = n; // 맨 끝에 n을 삽입
    if (L == 1) return; // n이 루트 노드인 경우

    int h = floor(log2(L)); // n의 레벨
    if (h % 2) // max level
    {
        if (MMH[L] < MMH[L / 2]) // 부모 노드보다 작으면 min level 노드들끼리 비교
        {
            swap(MMH[L], MMH[L / 2]);
            pushUp_min(L / 2);
        }
        else pushUp_max(L); // 부모 노드보다 크면 max level 노드들끼리 비교
    }
    else // min level
    {
        if (MMH[L] > MMH[L / 2]) // 부모 노드보다 크면 max level 노드들끼리 비교
        {
            swap(MMH[L], MMH[L / 2]);
            pushUp_max(L / 2);
        }
        else pushUp_min(L); // 부모 노드보다 작으면 min level 노드들끼리 비교
    }
}
```

`pushUp_min()`과 `pushUp_max()`는 딱 입력된 노드의 조부모 노드와만 비교하면 된다.

min level은 루트 노드로 올라갈수록 값이 감소해야하고, max level은 루트 노드로 올라갈수록 값이 증가하는 성질을 만족하도록 하는 것이 목표이다.

그러므로 다음과 같이 구현할 수 있다.

```cpp
void pushUp_min(int idx)
{
    int grandparent = idx / 2 / 2; // 조부모 노드
    if (grandparent == 0) return;
    
    if (MMH[idx] < MMH[grandparent]) // min level인데 조부모 노드가 더 크면 교환하고 비교를 이어간다.
    {
        swap(MMH[idx], MMH[grandparent]);
        pushUp_min(grandparent);
    }
}

void pushUp_max(int idx)
{
    int grandparent = idx / 2 / 2;
    if (grandparent == 0) return;
    
    if (MMH[idx] > MMH[grandparent]) // max level인데 조부모 노드가 더 작으면 교환하고 비교를 이어간다.
    {
        swap(MMH[idx], MMH[grandparent]);
        pushUp_max(grandparent);
    }
}
```

---

### 2-4. Find Min, Find Max

Min-max heap에서 최솟값과 최댓값을 찾는 것은 매우 간단하다.

먼저 최솟값은 루트 노드, 즉 `MMH[1]`을 반환하면 된다.

최댓값도 어렵지 않게 구할 수 있는데, 루트 노드의 두 자식 노드들 중 더 큰 것이 최댓값이다.

다만, min-max heap의 길이가 짧아서 자식 노드가 없거나 하나만 있을 수 있으므로 이 경우들은 따로 처리해주었다.

```cpp
int findMin() { return MMH[1]; }

int findMax()
{
    if (L == 1) return MMH[1]; // 길이가 1이면 루트 노드가 최솟값임과 동시에 최댓값이다.
    if (L == 2) return MMH[2]; // 길이가 2이면 루트 노드의 자식 노드가 유일하므로 해당 노드를 반환한다.
    return (MMH[2] < MMH[3]) ? MMH[3] : MMH[2]; // 길이가 3 이상이면 두 자식 노드 중 더 큰 값을 반환한다.
}
```

---

### 2-5. Delete Min, Delete Max

마지막으로 최솟값과 최댓값을 삭제하는 함수를 구현해보자.

Min heap과 max heap처럼 원소를 삭제하는 과정은 다음과 같이 생각할 수 있다.

1. 삭제할려는 노드의 값과 가장 마지막 노드를 `swap()`한다.
2. 마지막 노드를 삭제한다.
3. 트리를 min-max heap이 되도록 조정한다.

이때 3번 과정에서 `pushDown()` 함수가 사용된다.

```cpp
void deleteMin()
{
    swap(MMH[1], MMH[L]);
    L--;
    pushDown(1);
}

void deleteMax()
{
    if (L < 3) L--; // 길이가 1 또는 2이면 최댓값은 트리의 마지막 노드이므로 단순히 L--만 해주면 된다.
    else // 길이가 3 이상이면 최댓값을 찾아 해당 노드를 삭제한다.
    {
        if (MMH[2] < MMH[3])
        {
            swap(MMH[3], MMH[L]);
            L--;
            if (L > 2) pushDown(3);
        }
        else
        {
            swap(MMH[2], MMH[L]);
            L--;
            pushDown(2);
        }
    }
}
```

혹시라도 이해가 어려운 부분이 있다면 Reference [1]의 링크를 참고하면 된다.

<br/>

## [백준] 7662. 이중 우선순위 큐

다양한 해법이 있는 문제이지만, min-max heap을 구현하여 해결하는 방법이 최적의 풀이이다.

위에서 구현한 함수들을 바탕으로 다음과 같이 입력과 출력을 구현하면 된다.

```cpp
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int T;
    cin >> T;
    while (T--)
    {
        L = 0;

        int k;
        cin >> k;
        while (k--)
        {
            char c;
            int n;
            cin >> c >> n;

            if (c == 'I') pushUp(n);
            else if (n == 1)
            {
                if (L == 0) continue;
                deleteMax();
            }
            else
            {
                if (L == 0) continue;
                deleteMin();
            }
        }

        if (L == 0) cout << "EMPTY\n";
        else cout << findMax() << " " << findMin() << "\n";
    }
}
```

다른 풀이가 궁금하다면 [이 포스트](https://damo1924.github.io/ps/BAEKJOON-7662/)를 참고하면 된다.

<br/>

## Reference

[1] [WIKIPEDIA, 'Min-max heap'](https://en.m.wikipedia.org/wiki/Min-max_heap)  











