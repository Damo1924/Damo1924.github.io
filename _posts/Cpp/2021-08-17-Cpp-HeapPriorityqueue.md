---
title: "[C++] Heap & Priority queue"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Cpp
use_math: true

---

# 1. Heap
## 1-1. 힙(heap)이란?
힙(heap)은 완전 이진 트리의 일종으로, **부모 노드와 자식 노드 간에 항상 일정한 대소관계가 성립**하는 자료구조이다. 부모와 자식 노드의 대소관계에 따라서 **최대힙**과 **최소힙**으로 나눈다.
- **최대 힙(max heap)**: 부모 노드가 자식 노드보다 크거나 같은 완전 이진 트리
- **최소 힙(min heap)**: 부모 노드가 자식 노드보다 작거나 같은 완전 이진 트리

또 형제 노드 간에 대소 관계가 정해져 있지 않아 **부분 순서 트리(partial ordered tree)**라고 부르기도 한다.

> 힙 구조는 Binary heap, Binomial heap, Fibonacci heap 등 다양하지만, 이번 포스트에서는 가장 기본적인 Binary heap에 대해서 다룰 것이다. 힙에 대해서 더 자세한 공부를 하고 싶다면 Reference \[1]을 참고하면 된다.

힙은 일반적으로 배열에 저장되는데, 배열을 H라고 했을 때 원소 `H[i]`에 대해 다음이 성립한다. 일반적으로 힙을 배열에 저장할 때는 인덱스 1부터 저장한다. 즉, 루트의 인덱스가 1이다.
- 부모 노드: `H[i/2]`
- 왼쪽 자식 노드: `H[2*i]`
- 오른쪽 자식 노드: `H[2*i + 1]`

이진 탐색 트리와는 달리 힙 트리에서는 중복된 값을 허용한다. 힙을 이용하면 주어진 데이터들의 **최댓값이나 최솟값을 찾기 쉽다**는 장점이 있다. 최대 힙에서는 루트(root)에 최댓값이, 최소 힙에서는 루트에 최솟값이 오기 때문에 최댓값과 최솟값을 찾기 용이하다. 이를 이용하면 빠른 정렬 알고리즘 중 하나인 **힙 정렬(heap sort)**과 유용한 자료구조인 **우선순위 큐(priority queue)**를 구현할 수 있다.

## 1-2. 힙 구조에 원소 추가/삭제하기
힙 구조에서 원소를 추가하고 삭제하는 방법에 대해서 알아보자.

먼저 원소를 추가하기 위해서는 추가하려는 원소를 힙의 가장 끝(배열의 맨 끝)에 삽입한 후 그 원소를 부모 노드와 비교/교환하는 과정을 통해 힙으로 만들어야 한다. 삽입한 원소를 부모 노드와 비교해서 대소관계를 만족할 때까지 교환한다. 아래는 힙에 원소를 추가하는 함수를 구현한 코드이다.
```cpp
#include <iostream>
#include <vector>
using namespace std;

void swap (int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heappush (vector<int> *vec, int k) {
    vec->push_back(k); // 배열의 맨 끝에 원소 삽입
    int n = vec->size() - 1;
    
    // 부모-자식 노드 간 대소관계가 성립할 때까지 교환
    while ((*vec)[n] > (*vec)[n/2]) {
        swap(vec->data() + n, vec->data() + n/2);
        n = n/2;
        
        if (n == 1) break; // 루트에 도달하면 중단
    }
}

int main()
{
    vector<int> heap = {0, 10, 5, 7, 1}; // 인덱스 1부터 저장
    heappush(&vec, 9);
    for(int i = 1; i < heap.size(); i++) cout << heap[i] << " ";
}
```
```
10 9 7 1 5
```

힙에서 원소를 삭제하는 것은 루트에 있는 원소를 삭제함을 의미한다. 루트(배열의 맨 앞)를 삭제하고 배열의 맨 끝에 위치한 원소를 루트로 옮긴다. 그 다음 해당 원소를 자식 노드와 비교해서 대소 관계가 성립할 때까지 교환하는 과정을 반복해서 다시 힙 구조로 만들어준다. 아래는 힙에 원소를 삭제하는 함수를 구현한 코드이다.
```cpp
#include <iostream>
#include <vector>
using namespace std;

void swap (int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heappop (vector<int> *vec) {
    int n = vec->size() - 1;
    
    // 루트와 맨 마지막 원소를 교환하고 루트였던 원소를 제거
    swap(vec->data(), vec->data() + n);
    vec->pop_back();
    
    // 아래 반복문에서 오류가 발생하는 케이스 처리
    if (n == 1 || n == 2) return;
    if (n == 3) {
        if ((*vec)[1] < (*vec)[2]) swap(vec->data() + 1, vec->data() + 2);
        return;
    }
    
    // 부모-자식 노드 간 대소관계가 성립할 때까지 교환
    int i = 1, m;
    while ((*vec)[i] < (*vec)[2*i] || (*vec)[i] < (*vec)[2*i+1]) {
        if ((*vec)[2*i] < (*vec)[2*i+1]) m = 2*i+1;
        else m = 2*i;
        swap(vec->data() + i, vec->data() + m);
        i = m;
        
        if (2*i >= n) break;
        else if (2*i == n-1) {
            if ((*vec)[i] < (*vec)[2*i]) swap(vec->data() + i, vec->data() + 2*i);
            break;
        }
    }
}

int main()
{
    vector<int> heap = {0, 10, 9, 7, 1, 5};
    heappop(&heap);
    for(int i = 1; i < heap.size(); i++) cout << heap[i] << " ";
}
```
```
9 5 7 1
```

## 1-3. 리스트를 힙 구조로 변환하기
임의의 리스트를 힙 구조로 바꾸는 방법에 대해서 알아보자.

가장 먼저 떠오르는 방법은 기존 리스트에서 원소를 차례대로 빈 리스트에 `heappush()`하는 것이다. 그러나 이 방법은 $O(n \log n)$의 시간복잡도를 갖는다.

위 방법 대신 Bottom-up으로 접근하면 $O(n)$의 시간복잡도를 갖는 함수를 구현할 수 있다. 가장 아래에 있는 작은 트리부터 시작해서 점차 힙 구조로 만들어 나가는 방법이다. 아래는 임의의 배열을 힙 구조로 바꾸는 함수를 구현한 코드이다.
```cpp
#include <iostream>
#include <vector>
using namespace std;

void swap (int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify (vector<int> *vec) {
    int n = vec->size() - 1;
    for (int i = n/2; i > 0; i--) { // 가장 마지막 부모 노드(i=n/2)부터 루트(i=1)까지
        int j = i, m;
        while (2*j <= n) { // 해당 부모 노드를 자식 노드와 대소관계가 성립하도록 비교/교환
            if (2*j == n && (*vec)[j] < (*vec)[n]) {
                swap(vec->data() + j, vec->data() + n);
                break;
            }
            
            if ((*vec)[2*j] < (*vec)[2*j+1]) m = 2*j + 1;
            else m = 2*j;
            if ((*vec)[j] < (*vec)[m]) swap(vec->data() + j, vec->data() + m);
            j = m;
        }
    }
}

int main()
{
    vector<int> heap = {0, 1, 5, 9, 10, 7};
    heappop(&heap);
    for(int i = 1; i < heap.size(); i++) cout << heap[i] << " ";
}
```
```
10 7 9 5 1
```

## 1-4. 힙 정렬(heap sort)
힙 구조에서 트리의 루트(배열의 첫 번째 원소)는 최댓값/최솟값이므로 주어진 배열을 `heapify()` 함수를 통해 힙 구조로 만들고, 루트를 새로운 배열에 추가하고 `heappop()` 함수를 통해 루트의 원소를 제거해나가는 과정을 반복하면 정렬이 가능하다. 아래는 1-2, 1-3에서 구현한 함수들을 이용해서 구현한 힙 정렬 코드이다.
```cpp
void heapsort (vector<int> *vec) {
    vector<int> temp = *vec;
    heapify(&temp);
    for (int i = 1; i < vec->size(); i++) {
        (*vec)[i] = temp[1]; // 루트를 정렬할 배열에 순서대로 저장
        heappop(&temp); // 저장한 루트는 제거
    }
}

int main()
{
    vector<int> heap = {0, 1, 5, 9, 10, 7};
    heapsort(&heap);
    for (int i = 1; i < heap.size(); i++) cout << heap[i] << " ";
}
```
```
10 9 7 5 1
```
반대로 오름차순 정렬을 구현하려면 최대 힙이 아닌 최소 힙에 대한 `heappop()`과 `heapify()` 함수들을 구현하면 된다.


<br/>
# 2. Priority Queue
## 2-1. 우선순위 큐(priority queue)란?
우선순위 큐는 우선순위에 따라 정렬된 큐를 말한다. 각 데이터들이 정해진 기준에 따라 우선 순위를 가지고 있고, 우선 순위가 가장 높은 데이터가 먼저 나가게 된다. 이를 다른 자료구조들과 비교해보면 다음과 같다.

|자료 구조|삭제되는 데이터|
|:---:|:---:|:---:|
|스택(Stack)|가장 최근에 들어온 데이터|
|큐(Queue)|가장 먼저 들어온 데이터|
|우선순위 큐(Priority Queue)|가장 우선순위가 높은 데이터|

우선순위 큐는 **배열(array), 연결 리스트(linked list), 힙(heap)**으로 구현이 가능한데, 어떤 것을 사용하느냐에 따라 시간복잡도가 달라지게 된다. 그 이유는 각 자료구조마다 원소를 삽입하고 삭제하는 작업의 시간복잡도가 다르기 때문이다.

|구현 방법|원소 삽입|원소 삭제|
|:---:|:---:|:---:|
|순서 없는 배열|$O(1)$|$O(n)$|
|순서 없는 연결 리스트|$O(1)$|$O(n)$|
|정렬된 배열|$O(n)$|$O(1)$|
|정렬된 연결 리스트|$O(n)$|$O(1)$|
|힙|$O(\log n)$|$O(\log n)$|

위 표를 통해 **힙을 사용하는 것이 가장 효율적**인 구현 방법이라는 것을 알 수 있다.

## 2-2. C++ STL Priority Queue
C++에서는 우선순위 큐를 일반 큐와 동일한 헤더 파일인 `<queue>`에서 제공하고 있다.

우선순위 큐는 기본적으로 다음과 같은 형태로 선언한다.
```cpp
priority_queue<T, container, compare> object_name;
```
- **T**: 저장할 데이터의 형태
- **container**: 우선순위 큐가 저장될 컨테이너로, `empty()`, `size()`, `front()`, `push_back()`, `pop_back()` 멤버 함수가 있어야 한다. 이를 만족하는 standard container class는 벡터(vector)와 덱(deque)이며, 기본 컨테이너는 벡터이다.
- **compare**: 해당 자료형(T)의 원소 두 개를 인자로 받아 true/false를 반환하는 클래스로, 데이터 간의 우선순위를 제공한다. 디폴트는 `less<T>`이다.

다음과 같이 Max Heap과 Min Heap을 만들 수 있다.
```cpp
#include <iostream>
#include <queue> // priority_queue
#include <functional> // less, greater
#include <vector> // vector
using namespace std;

int main()
{
    // Max Heap
    priority_queue<int, vector<int>, less<int>> pq; // priority_queue<int> pq; 와 동일
    
    // Min Heap
    priority_queue<int, vector<int>, greater<int>> pq;
```

직접 우선순위 구현을 위한 클래스를 만들 수도 있다. 다음은 Max heap을 구현하기 위한 클래스이다.
```cpp
class compare {
public:
    bool operator() (int i, int j) { return (i < j); }
};

int main()
{
    priority_queue<int, vector<int>, compare> pq;
}
```

이번에는 이름과 성적 데이터를 묶은 `Student` 클래스를 우선순위 큐에 넣어 성적순으로 우선순위를 부여해 보았다. 만약 성적이 같다면 이름이 사전순으로 앞에 오는 사람이 우선적으로 큐에서 삭제되도록 하였다.
```cpp
class Student {
public:
    string name;
    int score;
    Student (string _name, int _score): name(_name), score(_score) { }
};

class compare {
public:
    bool operator() (Student i, Student j) {
        if (i.score != j.score) return (i.score < j.score); // 성적이 다르면 성적순으로
        else return (i.name > j.name); // 성적이 같으면 이름순으로
    }
};

int main()
{
    priority_queue<Student, vector<Student>, compare> pq;
    
    pq.push(Student("Kim", 80));
    pq.push(Student("Park", 85));
    pq.push(Student("Lee", 95));
    pq.push(Student("Choi", 90));
    pq.push(Student("Han", 85));
    pq.push(Student("Kwon", 85));
    
    while (!pq.empty()) {
        cout << pq.top().name << ": " << pq.top().score() << endl;
        pq.pop();
    }
}
```
```
Lee: 95
Choi: 90
Han: 85
Kwon: 85
Park: 85
Kim: 80
```

## 2-3. Member functions of Priority Queue
**1) top()**: 우선순위 큐의 top element(힙 구조의 root)를 반환  
**2) push()**: 우선순위 큐에 새로운 원소를 삽입  
**3) pop()**: 우선순위 큐의 top element를 제거  
**4) (constructor)**: 배열의 범위를 입력받아 해당 범위의 원소들을 가진 우선순위 큐를 생성  
```cpp
int arr[] = {1, 6, 4, 3};
priority_queue<int> pq (arr, arr+4);

for (int i = 0; i < 4; i++) {
    cout << pq.top() << " ";
    pq.pop();
}
```
```
6 4 3 1
```

**5) empty()**: 우선순위 큐가 비어있으면 true, 아니면 false를 반환
**6) size()**: 우선순위 큐에 있는 원소의 개수를 반환
```cpp
priority_queue<int> pq;

pq.push(4);
pq.push(3);
pq.push(6);
pq.push(1);
cout << "size: " << pq.size() << endl;

while (!pq.empty()) {
    cout << pq.top() << " ";
    pq.pop();
}
```
```
size: 4
6 4 3 1
```


<br/>
# References
[1] [Geeksforgeeks, 'Heap Data Structure'](https://www.geeksforgeeks.org/heap-data-structure/)  
[2] [cplusplus, 'priority queue'](http://www.cplusplus.com/reference/queue/priority_queue/)  
[3] 자료구조와 함께 배우는 알고리즘 입문, Bohyoh Shibata 저, 이지스 
