---
title: "Associative containers in C++ - Map & Set"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Cpp
use_math: true

---
# 0. Associative containers
지금까지 공부한 벡터(vector), 리스트(list), 덱(deque)과 같은 자료구조들은 모두 sequence containers였다. Sequence container에서는 각 원소가 어느 위치에 있는지가 중요했다면, 연관 컨테이너(associative container)에서는 특정 데이터가 컨테이너 안에 존재하는지, 그리고 특정 key에 대응되는 데이터가 무엇인지가 중요하다. 특정 데이터의 존재 유무만을 판단하기 위해 사용하는 컨테이너에는 **Set과 Multiset**이 있고, key에 대응되는 value를 알고 싶을 때 사용하는 컨테이너에는 **Map과 Multimap**이 있다. 이번 포스트에서는 이 네 가지 자료구조에 대해서 알아보도록 하겠다.


<br/>
# 1. Map
> Maps are associative containers that store elements formed by a combination of a key value and a mapped value, following a specific order.

## 1-1. Map의 특징
- Map은 연관 컨테이너(associative container) 중 하나로, **key와 그에 해당하는 value**가 하나의 쌍으로 저장된다.
- Key와 value는 **pair**로 저장되며, 각각이 노드인 **균형 이진 트리** 구조이다. (참고: [red-black tree](https://damo1924.github.io/algorithm/RedBlackTree/))
  > Red-black tree로 구현되었기 때문에 원소의 삽입, 삭제, 탐색이 모두 $O(\log n)$의 시간복잡도를 가진다. 하지만 Big O notation에서 무시되는 상수 부분이 매우 크기 때문에 원소 삽입, 삭제의 실제 런타임을 측정해보면 시간복잡도에 비해 오래걸린다. 그렇기 때문에 삽입과 삭제가 자주 일어나는 경우에서는 다른 자료구조를 쓰는 것이 더 나은 방법이다.

- Key는 value에 접근하고 정렬하는데 사용되고, **중복이 불가능**하다. (`multimap`은 중복 key를 허용)
- Map에 key와 value를 삽입하면 **key를 기준으로 자동으로 정렬**된다.

## 1-2. Map 선언하기
Map은 `<map>` 헤더 파일에 정의되어 있으며, `map<T1, T2> var_name;`과 같이 선언한다. 이때 `T1`은 key의 자료형, `T2`는 연결되는 value의 자료형을 말한다. 만약 정렬 기준을 바꾸고 싶다면, 적절한 클래스를 정의해준 다음 인자로 전달한다.
```cpp
#include <map>

struct compare {
    bool operator() (int i, int j) { return (i > j); }
};

int main()
{
    map<int, char> var_name1; // 오름차순 정렬
    map<int, char, compare> var_name2; // 내림차순 정렬
}
```

## 1-3. Member functions of Map
### 1-3-1. Element Access: operator [], count()
**1) operator []**: Map에 존재하는 key이면 해당하는 value의 참조형을 반환, 존재하지 않는 key이면 새로운 원소를 삽입하고 그 원소의 value에 대한 참조형을 반환
```cpp
#include <iostream>
#include <map>
using namespace std;

int main()
{
    map<int, char> m;
    m[1] = 'A'; // 새로운 원소를 삽입
    m[2] = 'B';
    cout << "key: 1, value: " << m[1] << endl; // 이미 존재하는 원소의 value에 접근
    
    if (!m[3]) cout << "map size: " << m.size() << endl; // 새로운 원소의 value를 입력하지 않아도 원소가 삽입된다.
}
```
```
key: 1, value: A
map size: 3
```
: 존재하지 않는 key가 인자로 전달되면, mapped value를 입력하지 않아도 원소가 삽입되면서 컨테이너의 크기가 증가하게 된다.

**2) count(k)**: k를 key로 하는 원소의 개수를 반환, map의 경우 key는 유일하므로 1 아니면 0을 반환

### 1-3-2. Capacity: empty(), size()
**1) empty()**: Map이 비어있으면 true, 아니면 false를 반환  
**2) size()**: Map의 원소의 개수를 반환

### 1-3-3. Iterators: begin(), end(), find(), lower_bound(), upper_bound(), equal_range()
**1) begin()**: Map의 첫 번째 원소를 가리키는 반복자를 반환  
**2) end()**: Map의 마지막 원소의 다음 원소를 가리키는 반복자를 반환  
**3) find(k)**: k를 key로 갖는 원소가 존재하면 그 원소를 가리키는 반복자를 반환, 존재하지 않는다면 `end()`와 동일한 반복자를 반환
```cpp
#include <iostream>
#include <map>
using namespace std;

int main()
{
    map<int, char> m;
    m[1] = 'A';
    m[2] = 'B';
    m[3] = 'C';
    
    for (map<int, char>::iterator it = m.begin(); it != m.end(); it++)
        cout << "key: " << it->first << ", value: " << it->second << endl;
    
    cout << m.find(2)->second << endl;
}
```
```
key: 1, value: A
key: 2, value: B
key: 3, value: C
B
```
: Map을 전체 순회하기 위해서는 반복자를 사용해야하며, map의 원소들은 항상 정렬되어 있으므로 반복자로 전체를 순회하면 정렬된 순서대로 순회하게 된다. 또한, 반복자를 이용할 때는 포인터와 마찬가지로 `->` 연산자를 사용한다.

**4) lower_bound(k)**: k보다 나중에 나오는 key를 가진 원소 중 첫 번째 원소를 가리키는 반복자를 반환  
**5) upper_bound(k)**: k보다 먼저 나오는 key를 가진 원소 중 마지막 원소를 가리키는 반복자를 반환
```cpp
#include <iostream>
#include <map>
using namespace std;

int main()
{
    map<int, char> m;
    m.insert({ {1, 'A'}, {5, 'B'}, {11, 'C'}, {17, 'D'} });
    
    cout << m.lower_bound(3)->second << endl;
    cout << m.lower_bound(5)->second << endl;
    
    cout << m.upper_bound(10)->second << endl;
    cout << m.upper_bound(11)->second << endl;
}
```
```
B
B
C
D
```
: 위의 결과를 보면 k와 동일한 key를 가진 원소가 존재할 때 `lower_bound(k)`는 그 원소를 가리키는 반복자를 반환하지만, `upper_bound(k)`는 해당 원소 다음의 원소를 가리키는 반복자를 반환한다는 사실을 알 수 있다.

**6) equal_range(k)**: k를 key로 하는 원소들에 접근할 수 있도록 범위를 `pair<iterator, iterator>`로 반환한다. Map과 Set은 중복 원소를 허용하지 않기 때문에 `find(k)`를 사용하면 되지만, 중복 원소를 허용하는 Multimap과 multiset에서는 유용하게 사용할 수 있다.

### 1-3-4. Modifiers; insert(), erase()
**1) insert()**: Map에 원소 삽입
```cpp
#include <iostream>
#include <map>
using namespace std;

int main()
{
    map<int, char> m;
    m.insert(pair<int, char>(1, 'A')); // pair로 원소 하나 삽입
    m.insert(make_pair(1, 'A')); // 매번 자료형을 입력하기 번거롭다면 make_pair() 함수를 사용하자.
    m.insert({ {2, 'B'}, {3, 'C'} }); // initializer_list 이용해서 삽입
    
    map<int, char> n;
    n[4] = 'D';
    n[5] = 'C';
    m.insert(n.begin(), n.end()); // 다른 map의 원소들을 삽입
    
    for (map<int, char>::iterator it = m.begin(); it != m.end(); it++)
        cout << "key: " << it->first << ", value: " << it->second << endl;
}
```
```
key: 1, value: A
key: 2, value: B
key: 3, value: C
key: 4, value: D
key: 5, value: E
```
: Map은 중복 원소를 허용하지 않기 때문에 이미 존재하는 key를 가진 원소를 insert해도 삽입되지 않는다. 즉, **동일한 key를 가진 원소를 여러 번 삽입하면 가장 먼저 삽입한 원소만 삽입**된다.

**2) erase()**: Map의 원소 삭제
```cpp
#include <iostream>
#include <map>
using namespace std;

int main()
{
    map<int, char> m;
    m.insert({ {1, 'A'}, {2, 'B'}, {3, 'C'}, {4, 'D'}, {5, 'E'} });
    
    m.erase(m.end()); // 반복자가 가리키는 원소를 삭제
    
    m.erase(m.begin(), m.find(3)); // 반복자로 주어진 범위의 원소들을 삭제
    
    m.erase(3); // key가 3인 원소를 삭제
    
    for (map<int, char>::iterator it = m.begin(); it != m.end(); it++)
        cout << "key: " << it->first << ", value: " << it->second << endl;
}
```
```
key: 4, value: D
```

## 1-4. Map에서 특정 조건을 만족한는 원소를 삭제하기
map에 대해 알아보기 위해 자료들을 찾아보다가 한 질문글을 보게 되었는데 꽤 좋은 내용인 것 같아 추가하였다.
```cpp
#include <iostream>
#include <map>
using namespace std;

// 조건을 만족하는 원소를 삭제하는 generic function
template <typename Map, typename F>
void map_erase_if(Map& m, F pred) {
    typename Map::iterator it = m.begin();
    while ((it = find_if(it, m.end(), pred)) != m.end())
        m.erase(it++);
}

bool pred(pair<int, char> p) { return (p.first < 3); }

int main()
{
    map<int, char> m = { {1, 'A'}, {2, 'B'}, {5, 'K'}, {3, 'D'} };
    map<int, char>::iterator it;
    
    map_erase_if(m, pred);
    for (it = m.begin(); it != m.end(); it++)
        cout << "key: " << it->first << ", value: " << it->second << endl;
}
```
```
key: 3, value: D
key: 4, value: K
```


<br/>
# 2. Set
> Sets are containers that store unique elements following a specific order.

## 2-1. Set의 특징
- Set은 간단히 말해 map에서 key가 없는 자료구조인데, 이는 저장된 value가 key의 역할도 하기 때문이다.
- Set의 원소들의 값을 수정할 수 없다. (삽입하거나 삭제하는 것만 가능, the elements are always const)
- Set은 map과 마찬가지로 원소를 삽입함과 동시에 정렬된다.
  > `class`나 `struct`로 직접 정의한 클래스를 set의 원소로 사용하고 싶은 경우에는 반드시 클래스 내부에 `operator<`를 정의하거나 따로 함수 객체를 정의해서 선언할 때 전달해주어야 한다. 그렇지 않으면 비교 기준이 없기 때문에 에러가 발생한다.

- Red-black tree로 구현되어 원소를 검색하거나 삽입, 삭제하는 시간복잡도가 $O(\log n)$이다.

## 2-2. Set 선언하기
Set은 `<set>` 헤더 파일에 정의되어 있으며, `set<datatype> var_name`와 같이 선언한다. 원소들의 정렬 기준을 바꾸고 싶다면, 함수 객체를 정의하여 선언과 동시에 전달한다.
```cpp
#include <set>

struct compare {
    bool operator() (int i, int j) { return (i > j); }
};

int main()
{
    set<int> s1; // 원소들을 오름차순으로 정렬한 상태로 저장(default)
    set<int, compare> s2; // 원소들을 내림차순으로 정렬한 상태로 저장
}
```

## 2-3. Member functions of Set
Set은 map과 동일한 멤버 함수들을 갖고 있다. 딱 하나의 차이점이 있는데, 바로 set에는 `operator []`가 없다는 점이다. 생각해보면 set은 key가 없이 value가 key의 역할까지 하기 때문에 당연하게도 key를 통해 value에 접근하는 연산자는 필요가 없다.

## 2-4. 사용자 정의 자료형을 Set의 원소로 사용하기
직접 정의한 클래스를 set의 원소로 사용하는 방법에 대해서 알아보자.
```cpp
#include <iostream>
#include <set>
#include <string>
using namespace std;

class product {
    int price;
    string name;
public:
    product(int _price, string _name): price(_price), name(_name) {}
    
    friend void printInfo(set<product>::iterator it) { // private member에 접근할 수 있도록 friend
        cout << it->name << ": " << it->price << "Won" << endl;
    }
    
    bool operator< (const product& p) const { // product class의 정렬 기준: 가격순 -> 이름순
        if (price == p.price) return name < p.name;
        else return price < p.price;
    }
};

int main()
{
    set<product> P;
    P.insert(product(200, "candy"));
    P.insert(product(1000, "apple"));
    P.insert(product(3000, "juice"));
    P.insert(product(1000, "pen"));
    
    for (set<product>::iterator it = P.begin(); it != P.end(); it++) printInfo(it);
}
```
```
candy: 200Won
apple: 1000Won
pen: 1000Won
juice: 3000Won
```


<br/>
# 3. Multimap & Multiset
> Multimap = 중복 원소를 허용하는 map, Multiset = 중복 원소를 허용하는 set

Multimap과 multiset은 각각 `<map>`, `<set>` 헤더 파일에 정의되어 있으며, 중복 원소를 허용한다는 점을 제외하고는 map, set과 완전히 동일한 컨테이너이다. 그렇기 때문에 이번 절에서는 주요 차이점들에 대해서 다루어 볼 것이다.

## 3-1. 동일한 key를 가진 원소들에 접근하기
Multimap은 중복 원소를 허용하기 때문에 원소에 접근하는 방식이 map과는 조금 다르다. 기존에 사용하던 접근 방식들은 다음과 같은 문제가 있다.

- `operator []`를 사용할 수 없다. 동일한 key에 대응되는 여러 개의 데이터 중 어떤 것을 반환해야할지 알 수 없기 때문이다. 
- `find()`를 사용하면 대응되는 여러 개의 데이터 중 임의의 것을 반환한다. C++에서 어떤 것을 반환하라고 정해두지 않았기 때문이다.

그렇다면 특정 key에 대응되는 여러 개의 데이터들을 전부 알고 싶다면 어떤 방법을 써야할까?? 바로 `equal_range()`를 이용하는 방법밖에 없다. 이 함수는 전달한 값을 key로 갖는 원소들의 범위를 `pair<iterator, iterator>`의 형태로 반환하는 함수로써, 이를 이용해서 특정 key를 가지는 원소들에 접근할 수 있다.
```cpp
#include <iostream>
#include <map>
using namespace std;

typedef multimap<int, char>::iterator It; // 반복자를 자주 사용하므로 정의해두면 편하다.

int main()
{
    multimap<int, char> m = { {1, 'A'}, {5, 'D'}, {10, 'E'}, {1, 'K'} };
    
    for (It it = m.begin(); it != m.end(); it++) // Multimap 내의 모든 원소를 출력
        cout << "key: " << it->first << ", value: " << it->second << endl;
    cout << endl;
    
    pair<It, It> range = m.equal_range(1); // key가 1인 원소들의 범위를 가리키는 반복자를 pair로 반환
    cout << "Elements which has key = 1 : ";
    for (It it = range.first; it != range.second; it++) // key가 1인 원소들만 출력
        cout << it->second << " ";
    cout << "\n" << endl;
}
```
```
key: 1, value: A
key: 1, value: K
key: 5, value: D
key: 10, value: E

Elements which has key = 1 : A K
```

## 3-2. 동일한 key를 가진 원소들을 삭제하기
동일한 key를 가진 모든 원소들을 한 번에 삭제하고 싶다면 `erase(k)`를 사용하면 된다. 이는 k를 key로 갖는 원소 전부를 삭제해준다.
```cpp
#include <iostream>
#include <map>
using namespace std;

typedef multimap<int, char>::iterator It; // 반복자를 자주 사용하므로 정의해두면 편하다.

int main()
{
    multimap<int, char> m = { {1, 'A'}, {5, 'D'}, {10, 'E'}, {1, 'K'} };
    
    m.erase(1);
    for (It it = m.begin(); it != m.end(); it++)
        cout << "key: " << it->first << ", value: " << it->second << endl;
}
```
```
key: 5, value: D
key: 10, value: E
```


<br/>
# References
[1] [Geeksforgeeks, 'Map in C++ Standard Template Library(STL)'](https://www.geeksforgeeks.org/map-associative-containers-the-c-standard-template-library-stl/)  
[2] [cplusplus, 'map'](http://www.cplusplus.com/reference/map/map/)  
[3] [KLDP, 'STL map을 순환문 내에서 삭제시키기'](https://kldp.org/node/133371)  
[4] [cplusplus, 'set'](http://www.cplusplus.com/reference/set/set/)  
[5] [모두의 코드, '씹어먹는 C++ - <10-2. C++ STL - set, map, unorderd_set, unordered_map>`](https://modoocode.com/224#page-heading-2)  
[6] [cplusplus, 'multimap'](https://www.cplusplus.com/reference/map/multimap/)  
