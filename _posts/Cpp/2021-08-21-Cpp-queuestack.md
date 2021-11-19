---
title: "[C++] Queue & Stack"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Cpp
use_math: true

---

# 1. What is Queue?
> Queues are a type of container adaptors which operate in a **first in first out (FIFO)** type of arrangement.

## 1-1. 큐의 특징
큐는 선입선출, 즉 **먼저 삽입(push)된 데이터가 먼저 삭제(pop)**되는 방식의 자료구조이다.

C++에서 큐는 container adaptors로 구현되는데, 이는 다른 컨테이너를 underlying container로 사용하는 클래스라는 의미이다. 큐는 맨 끝에서 삽입이 일어나고, 맨 앞에서 삭제가 일어나기 때문에 다음 멤버 함수들을 가진 컨테이너들을 underlying container로 사용할 수 있다.
- `empty()`, `size()`, `front()`, `back()`, `push_back()`, `pop_front()`

예를 들어 벡터는 맨 앞에서 원소를 삭제하는 `pop_front()` 멤버 함수가 없기 때문에 사용하지 못한다. 위 조건을 만족하는 컨테이너에는 **덱(deque)과 리스트(list)**가 있다. 만약 큐를 선언할 때 따로 컨테이너를 지정하지 않는다면 기본값인 덱에 기반하여 큐를 생성한다.

## 1-2. 큐 선언하기
큐는 `<queue>` 헤더 파일에 정의되어 있으며, `queue<datatype> var_name;`의 형태로 선언할 수 있다. Underlying container로 리스트를 사용하고 싶다면, `queue<datatype, list<datatype>> var_name;`과 같이 선언하면 된다.
```cpp
#include <queue>
#include <list>
using namespace std;
int main()
{
    queue<int> qu_deque;
    queue<int, list<int>> qu_list;
}
```


<br/>
# 2. Member functions of Queue
## 2-1. (constructor)
생성자를 이용해서 선언과 동시에 초기화를 할 수 있다.
```cpp
#include <iostream>
#include <queue>
#include <deque>
#include <list>
using namespace std;

int main()
{
    deque<int> dq (5, 100);
    queue<int> qu_dq (dq);
    
    list<int> li (5, 100);
    queue<int, list<int>> qu_li (li);
}
```
: 이처럼 큐는 deque이나 list를 통해서만 생성자를 이용한 초기화가 가능하다.

## 2-2. Modifiers: push(), pop()
**1) push()**: 큐의 맨 끝에 원소를 삽입  
**2) pop()**: 큐의 첫 번째 원소를 삭제

## 2-3. Capacity: empty(), size()
**1) empty()**: 큐가 비어있으면 true, 아니면 false를 반환  
**2) size()**: 큐에 있는 원소의 개수를 반환
```cpp
#include <iostream>
#include <queue>
using namespace std;

int main()
{
    queue<int> qu;
    for (int i = 1; i <= 5; i++) qu.push(i);
    if (!qu.empty()) cout << qu.size() << endl;
}
```
```
5
```

## 2-4. Element Access: front(), back()
**1) front()**: 큐의 첫 번째 원소의 참조형을 반환  
**2) back()**: 큐의 마지막 원소의 참조형을 반환
```cpp
#include <iostream>
#include <queue>
using namespace std;

int main()
{
    queue<int> qu;
    for (int i = 1; i <= 5; i++) qu.push(i);
    while (!qu.empty()) {
        cout << qu.front() << " ";
        qu.pop();
    }
}
```
```
1 2 3 4 5
```


<br/>
# 3. What is Stack?
> Stacks are a type of container adaptor, specifically designed to operate in a **last in first out (LIFO)**, where elements are inserted and extracted only from one end of the container.

## 3-1. 스텍의 특징
스텍는 후입선출, 즉 **마지막에 삽입(push)된 데이터가 먼저 삭제(pop)**되는 방식의 자료구조이다.

C++에서 스텍은 큐와 마찬가지로 다른 컨테이너를 underlying container로 사용하는 클래스이다. 스텍은 맨 끝에서만 삽입과 삭제가 일어나기 때문에 다음 멤버 함수들을 가진 컨테이너들을 underlying container로 사용할 수 있다.
- `empty()`, `size()`, `back()`, `push_back()`, `pop_back()`

위 조건을 만족하는 컨테이너에는 **벡터(vector)와 덱(deque), 그리고 리스트(list)**가 있다. 만약 큐를 선언할 때 따로 컨테이너를 지정하지 않는다면 기본값인 덱에 기반하여 큐를 생성한다.

## 3-2. 스텍 선언하기
스텍는 `<stack>` 헤더 파일에 정의되어 있으며, `stack<datatype> var_name;`의 형태로 선언할 수 있다. Underlying container로 벡터를 사용하려면 `stack<datatype, vector<datatype>> var_name;`, 리스트를 사용하려면 `stack<datatype, list<datatype>> var_name;`과 같이 선언하면 된다.
```cpp
#include <stack>
#include <vector>
#include <list>
using namespace std;
int main()
{
    stack<int> st_deque;
    stack<int, vector<int>> st_vector;
    stack<int, list<int>> st_list;
}
```


<br/>
# 4. Member functions of Stack
## 4-1. (constructor)
생성자를 이용해서 선언과 동시에 초기화를 할 수 있다.
```cpp
#include <iostream>
#include <deque>
#include <vector>
#include <list>
using namespace std;

int main()
{
    deque<int> dq (5, 100);
    stack<int> st_dq (dq);
    
    vector<int> vec (5, 100);
    stack<int, vector<int>> st_vec (vec);
    
    list<int> li (5, 100);
    stack<int, list<int>> st_li (li);
}
```
: 이처럼 벡터, 덱, 리스트를 통해서만 생성자를 이용한 초기화가 가능하다.

## 4-2. Modifiers: push(), pop()
**1) push()**: 스텍의 맨 끝에 원소를 삽입  
**2) pop()**: 스텍의 마지막 원소를 삭제

## 4-3. Capacity: empty(), size()
**1) empty()**: 스텍이 비어있으면 true, 아니면 false를 반환  
**2) size()**: 스텍에 있는 원소의 개수를 반환

## 4-4. Element Access: back()
**1) back()**: 스텍의 마지막 원소의 참조형을 반환


<br/>
# References
[1] [cplusplus, 'queue'](https://www.cplusplus.com/reference/queue/queue/)  
[2] [Geeksforgeeks, 'Queue in Standard Template Library(STL)'](https://www.geeksforgeeks.org/queue-cpp-stl/)  
[3] [cplusplus, 'stack'](https://www.cplusplus.com/reference/stack/stack/)  
[4] [Geeksforgeeks, 'Stack in C++ STL'](https://www.geeksforgeeks.org/stack-in-cpp-stl/)
