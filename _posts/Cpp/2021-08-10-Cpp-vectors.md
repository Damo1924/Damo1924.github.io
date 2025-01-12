---
title: "[C++] Vectors"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Cpp
---

# 1. What is a Vector?
> Vectors are same as dynamic arrays with the **ability to resize itself automatically when an element is inserted or deleted**, with their storage being handled automatically by the container.

## 1-1. 벡터 선언하기
 벡터는 크기가 변할 수 있는 배열이다. 선언할 때 크기가 고정되는 배열과는 다르게 벡터는 원소를 추가하거나 삭제함에 따라 크기가 달라진다.
C++에서 벡터를 사용하기 위해서는 표준 라이브러리에서 제공하는 `std::vector`를 사용하면 되며, 이는 `<vector>` 헤더파일에 정의되어 있다.
```cpp
#include <vector>
int main()
{
    std::vector<int> vec = {1, 3, 5, 6};
}
```
벡터는 `std::vector<datatype> vector_name`와 같이 선언할 수 있으며, `datatype`에는 벡터에 저장하려는 원소들의 자료형을 넣어주면 된다.

## 1-2. 벡터의 원소에 접근하기
원소에 접근하기 위해서는 배열처럼 `[ ]`을 이용하면 된다.
```cpp
cout << vec[2] << endl;
```
```
5
```
벡터는 배열을 이용해서 원소들을 저장하기 때문에 **각 원소에 대해 연속적인 저장 공간을 할당**한다.
```cpp
cout << &vec[0] << endl;
cout << &vec[1] << endl;
cout << &vec[2] << endl;
cout << &vec[3] << endl;
```
```
0xb400007de7405010
0xb400007de7405014
0xb400007de7405018
0xb400007de740501c
```
위 사실을 이용하면 배열에서 한 것처럼 **포인터 연산으로 각 원소에 접근이 가능**하다는 것을 알 수 있다.
```cpp
cout << "vec[2] = " << *(&vec[0] + 2) << endl;
```
```
vec[2] = 5
```
<br/>
**# 그렇다면 벡터는 배열을 이용해서 원소들을 저장함에도 원소를 추가하고 제거하는 것이 가능한 이유는 무엇일까?**<br/>
 벡터에 원소를 추가할 때마다 새로운 배열에 모든 원소를 옮기는 것(reallocate)은 시간적인 측면에서 매우 expensive한 방법이다. 그래서 vector container들은 원소의 추가로 인해 더 많은 저장공간이 필요할 것을 고려해서 벡터의 실제 크기보다 더 큰 용량(capacity)를 가진다. 그러다 할당된 용량 이상으로 원소가 추가되면 그 경우에만 새로운 배열로 reallocate하는 방식이다.

## 1-3. 벡터의 장단점
벡터는 다음과 같은 장단점을 가지고 있으므로, 상황에 맞게 알맞은 자료구조를 사용하면 된다.
- **벡터의 장점**<br/>
    1) 효율적으로 크기를 자유롭게 바꿀 수 있다. (dynamically sized)<br/>
    2) 벡터는 Deque, List 등과 같은 다른 dynamic sequence containers에 비해 원소에 접근하기가 매우 수월하며 효율적이다.<br/>
    3) 끝에서 원소를 추가하고 제거하는 작업이 다른 자료구조에 비해 상대적으로 더 효율적이다.<br/>
- **벡터의 단점**<br/>
    1) 같은 크기(원소 수가 동일한) 배열에 비해 더 많은 메모리를 사용한다.<br/>
    2) 중간에 원소를 추가하거나 제거하는 작업은 다른 자료구조에 비해 비효율적이다.<br/>


<br/>
# 2. Vector Initialization Methods
## 2-1. Using constructors
1) **Empty container constructor (default constructor)**: 비어 있는 벡터를 생성한다.
```cpp
vector<int> vec;
```

2) **Fill constructor**: 첫 번째 인자로 벡터의 크기를, 두 번째 인자로 원소의 값을 전달한다.
```cpp
vector<int> vec (5, -1);
```
크기가 5인 벡터가 만들어지고, 모든 원소가 -1로 초기화된다.
```cpp
vector<int> vec (5);
```
만약 모든 원소를 0으로 초기화하고 싶은 경우에는 첫 번째 인자만 입력해도 된다.

3) **Range constructor**: 인자로 두 개의 반복자(first, last)를 입력받아 \[first, last) 범위에 있는 원소들로 벡터를 초기화한다.
```cpp
vector<int> vec = {1, 2, 3, 4, 5};
vector<int> vec_range (vec.begin() + 1, vec.end() - 1);
```
이처럼 range constructor를 이용하면 **벡터 슬라이싱(slicing)**이 가능하다.

4) **Copy constructor**: 인자로 다른 벡터를 입력받아 복사본을 생성한다.
```cpp
vector<int> vec = {1, 2, 3, 4, 5};
vector<int> vec_copy (vec);
```

## 2-2. Using \<algorithm\> fill
`<algorithm>` 헤더 파일에 정의되어 있는 함수로, 범위 내 원소들을 같은 값으로 채워준다. 첫 번째와 두 번째 인자는 범위를 정해주는 iterator, 마지막 인자는 원소들에 대입할 값을 의미한다.
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
    vector<int> vec (10); // 0 0 0 0 0 0 0 0 0 0
    fill(vec.begin()+2, vec.begin()+7, 1); // 0 0 1 1 1 1 1 0 0 0
}
```

## 2-3. 2차원 벡터 초기화하기
특정 값으로 채워진 원하는 크기의 2차원 벡터를 만들고 싶으면 다음과 같이 초기화하면 된다.
```cpp
vector<vector<int>> vec(6, vector<int>(5, 0)); // 길이가 6인 벡터를 vector<int>(5, 0)으로 채운다.
```
만약 비어있는 벡터를 원소로 하는 벡터를 만들고 싶다면 다음과 같이 두 번째 인자를 전달하지 않으면 된다.
```cpp
vector<vector<int>> vec(6);
vec[3].push_back(10);
cout << vec[3][0] << endl;
```
```
10
```
행과 열의 개수가 둘다 0인 완전히 비어있는 2차원 벡터는 단순히 선언만 해주면 된다.
```cpp
vector<vector<int>> vec;
vec.push_back(vector<int>());
vec[0].push_back(10);
cout << vec[0][0] << endl;
```
```
10
```

<br/>
# 3. Member functions of Vectors
## 3-1. Iterators: begin(), end()
**1) begin()**: 벡터의 첫 번째 원소를 가리키는 반복자(iterator)를 반환<br/>
**2) end()**: 벡터의 마지막 원소의 다음 원소(past-the-end element)를 가리키는 반복자(iterator)를 반환

past-the-end element는 마지막 원소 다음에 오는 **가상의 원소**로, 실제로 존재하지 않는 원소이기 때문에 역참조(dereference, \*)는 불가능하다. 표준 라이브러리의 함수들에서 사용되는 범위(range)가 closing iterator가 가리키는 원소를 포함하지 않기 때문에 `vec.begin()`과 `vec.end()`를 이용해서 문자열 전체를 포함하는 range를 만들 수 있다.
```cpp
vector<int> vec = {1, 3, 5, 6};
for(vector<int>::iterator it = vec.begin(); it != vec.end(); it++) cout << *it << " ";
```
```
1 3 5 6
```
: for문의 범위를 iterator를 이용해서 만들어서 벡터의 원소들을 공백으로 구분하여 출력해보았다. 반복자 `it`가 벡터의 가장 첫 번째 원소부터 마지막 원소까지 가리키게 된다.

## 3-2. Element Access: front(), back(), data()
**1) front()**: 벡터의 첫 번째 원소를 반환<br/>
**2) back()**: 벡터의 마지막 원소를 반환<br/>
**3) data()**: 벡터의 첫 번째 원소를 가리키는 포인터를 반환
```cpp
vector<int> vec = {1, 3, 5, 6};
cout << "First element = " << vec.front() << endl;
cout << "Last element = " << vec.back() << endl;

int *ptr = vec.data(); // pointing to the first element
*ptr = 100;
ptr++; // pointing to the second element
ptr[1] = 1000; // ptr[1] becomes the third element of vec
for(vector<int>::iterator it = vec.begin(); it != vec.end(); it++) cout << *it << " ";
```
```
First element = 1
Last element = 6
100 3 1000 6
```
: 위와 같이 벡터는 포인터 연산을 통해 원소에 접근하고 값을 수정하는 것이 가능하다.

## 3-3. Modifiers: push_back(), pop_back(), insert(), erase(), clear()
**1) push_back()**: 벡터의 끝에 원소 추가<br/>
**2) pop_back()**: 벡터의 마지막 원소 제거
```cpp
vector<int> vec = {1, 3, 5, 6};
vec.push_back(100);
cout << "Last element = " << vec.back() << endl;
vec.pop_back();
cout << "Last element = " << vec.back() << endl;
```
```
Last element = 100
Last element = 6
```

**3) insert()**: 원하는 위치에 새로운 원소들을 추가
```cpp
vector<int> vec = {1, 3, 5, 6};
vec.insert(vec.begin(), 100);
for(int i = 0; i < vec.size(); i++) cout << vec[i] << " ";
cout << endl;

vec.insert(vec.begin() + 2, 3, 99);
for(int i = 0; i < vec.size(); i++) cout << vec[i] << " ";
```
```
100 1 3 5 6
100 1 99 99 99 3 5 6
```
: 첫 번째 인자에는 원소를 삽입하고자 하는 위치를 iterator로, 두 번째 인자에는 삽입하려는 원소를 자료형에 맞게 전달한다. 만약 동일한 원소를 여러 개 삽입하고 싶으면 삽입하려는 원소보다 앞에 반복 횟수를 입력한다.

**4) erase()**: 원하는 위치 또는 범위에 있는 원소를 제거
```cpp
vector<int> vec = {1, 3, 5, 7, 9, 10};
vec.erase(vec.begin());
for(int i = 0; i < vec.size(); i++) cout << vec[i] << " ";
vec.erase(vec.begin()+1, vec.end-1);
for(int i = 0; i < vec.size(); i++) cout << vec[i] << " ";
```
```
3 5 7 9 10
3 10
```
: 원하는 위치나 범위를 iterator를 이용해서 전달하면 해당 원소들은 벡터에서 제거된다. 이때 `end()`는 마지막 원소 다음 원소를 가리킨다는 사실에 주의하면서 범위를 설정한다.

> 벡터는 배열을 이용해서 저장하기 때문에 끝이 아닌 중간에서 원소를 추가하거나 제거하는 작업을 하기 위해서는 나머지 원소들의 위치를 전부 옮겨야한다. 그렇기 때문에 `insert()`와 `erase()`는 `O(n)`의 시간복잡도를 가지는 비효율적인 함수이며, 만약 이 함수들을 자주 사용해야하는 상황이라면 좀 더 효율적인 다른 자료구조를 사용하는 것이 좋다.

**5) clear()**: 벡터의 모든 원소들을 제거하여 크기가 0인 상태로 만드는 함수

## 3-4. Capacity: size(), capacity(), clear(), shrink_to_fit(), reserve()
**1) size()**: 원소의 개수를 반환<br/>
**2) capacity()**: 현재 할당된 메모리의 크기를 저장할 수 있는 원소의 개수로 반환<br/>
**3) empty()**: 벡터의 크기가 0이면 true, 아니면 false를 반환<br/>
**4) shrink_to_fit()**: 벡터의 capacity를 size로 줄인다.
```cpp
vector<int> vec = {1, 3, 5, 6};
cout << "Size = " << vec.size() << ", Capacity = " << vec.capacity() << endl;
vec.pop_back();
cout << "Size = " << vec.size() << ", Capacity = " << vec.capacity() << endl;
if (!vec.empty()) vec.shrink_to_fit();
cout << "Size = " << vec.size() << ", Capacity = " << vec.capacity() << endl;
```
```
Size = 4, Capacity = 4
Size = 3, Capacity = 4
Size = 3, Capacity = 3
```

**5) reserve()**: 벡터가 최소 n개의 원소를 저장할 수 있도록 capacity를 설정
```cpp
vector<int> vec;
vec.reserve(100);
```
: 벡터는 capacity가 부족할 때마다 동적 할당을 통해 capacity를 늘려 원소를 저장한다. 그렇기 때문에 입력의 개수를 알고 있다면 입력을 받을 벡터의 capacity를 미리 입력을 받을 수 있도록 설정하면 좀 더 효율적으로 벡터를 사용할 수 있다.

## 3-5. vector bool class
`vector<bool>` 클래스는 bool 값들을 원소로 같는 특수한 벡터 클래스로, 각 값들을 single bit에 저장해서 공간에 대한 최적화를 제공한다.
```cpp
vector<bool> vec = {true, false, false};
```


<br/>
# Reference
[1] [cplusplus, 'vector'](https://www.cplusplus.com/reference/vector/vector/)<br/>
[2] [Geeksforgeeks, 'vector in c++'](https://www.geeksforgeeks.org/vector-in-cpp-stl/)<br/>
[3] [cplusplus, 'vector bool'](https://www.cplusplus.com/reference/vector/vector-bool/)<br/>
[4] [cplusplus, 'fill'](https://www.cplusplus.com/reference/algorithm/fill/)
