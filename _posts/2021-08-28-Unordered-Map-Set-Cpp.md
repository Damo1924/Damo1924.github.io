---
title: "unordered_set/map in C++ (Hashmap)"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Cpp
use_math: true

---


<br/>
C++의 **unordered_set**과 **unordered_map**은 원소들이 정렬된 상태로 저장되어있지 않는 set과 map이다.

> *containers that store unique elements in no particular order.*

Python의 set과 dictionary과 같다고 볼 수 있다. 이들은 **Hashing**을 통해 구현한 자료구조로, 삽입(insert), 삭제(erase), 검색(find)하는 작업이 모두 $O(1)$로 수행된다는 장점이 있다.

어떻게 상수 시간에 삽입, 삭제, 검색이 가능한 것인지 이해하기 위해 Hashing에 대해서 알아보자.

# 1. Hashing
> *Hashing is a technique or process of mapping keys, values into the hash table by using a hash function.*

대학에서 학생들의 학번을 이용해서 학생들의 정보를 저장하는 시스템을 만들고 싶어한다. 이 시스템은 학번-정보를 삽입하거나 삭제하는 작업과 학번을 검색하여 해당 학생의 정보를 얻는 작업을 효율적으로 수행할 수 있어야한다.

우리는 다음과 같은 자료구조를 생각해볼 수 있다.

**1.** Array of student_id & information  
**2.** Linked List of student_id & information  
**3.** Balanced binary search tree with student_id as keys  
**4.** Direct access table with student_id as index of array

1, 2번은 선형 검색을 해야하기 때문에 전체 데이터의 크기가 커질수록 매우 비효율적이다. 배열을 정렬된 상태로 유지하면 이진 검색(binary search)를 이용해서 $O(\log n)$의 시간복잡도로 검색이 가능하지만, 삽입과 삭제를 할 때 정렬된 상태를 유지하기 위한 비용이 들기 때문에 좋다고 볼 수 없다.

3번의 경우에는 검색, 삽입, 삭제를 모두 $O(\log n)$로 수행할 수 있기 때문에 1, 2번에 비해 더 나은 선택지라고 할 수 있다.

마지막 4번은 굉장히 극단적인 방법이라고 할 수 있는데, 각 작업을 $O(1)$로 수행할 수 있다는 점에서 매우 뛰어나지만 학번의 자릿수가 많아질수록 필요한 배열의 크기가 매우 커진다는 문제가 있다. 학번이 $n$ 자리이면 table이 $O(m \times 10^{n})$의 공간을 필요로 하게 된다. 이때 $m$은 학생의 정보를 가리키는 포인터의 크기이다. 이러한 이유로 direct access table을 항상 사용할 수는 없기 때문에 등장한 것이 바로 **Hashing**이다.

Hashing은 hash function과 hash table로 이루어져있다.
> *Hashing is an improvement over Direct Access Table. The idea is to use **hash function** that converts a given key to a smaller number and uses the small number as index in a table called **hash table**.*

**1. Hash function**: Hash table의 인덱스로 사용하기에 너무 큰 값이나 인덱스로 사용할 수 없는 문자열 등을 작은 정수로 바꾸어줌으로써 인덱스로 사용할 수 있도록 만들어주는 함수이다.

좋은 hash function은 다음과 같은 조건을 만족해야한다.

- 계산이 복잡하지 않아야한다.(efficiently computable)
- Key가 균일하게 분포하도록 해야한다.(should uniformly distribute the keys)

또, hash function을 통해 얻을 값을 **해시값(Hash value)**라고 부른다.

**2. Hash Table**: key에 대응되는 value가 저장된 곳의 포인터를 저장하는 배열을 의미한다.

Bucket: 

<br/>
# 2. unordered_set, unordered_map
## 2-1. unordered_set, unordered_map 선언하기
각각 `<unordered_set>`과 `<unordered_map>` 헤더 파일에 정의되어 있으며, 다음과 같이 선언할 수 있다.
```cpp
#include <unordered_set>
#include <unordered_map>
#include <string>
using namespace std;
int main()
{
    unordered_set<int> hashSet;
    unordered_map<int, string> hashMap;
}
```

## 2-2. (constructor), operator =
생성자를 이용하면 선언과 동시에 초기화가 가능하다.
```cpp
unordered_set<string> hashSet1; // 비어있는 unordered_set 생성
unordered_set<string> hashSet2 ( {"red", "green", "blue"} ); // 초기화 리스트 이용해서 초기화
unordered_set<string> hashSet3 (hashSet2); // 다른 unordered_set 복사
unordered_set<string> hashSet4 (hashSet3.begin(), hashSet3.end()); // 반복자를 이용해서 초기화(range)
    
unordered_map<int, string> hashMap ( { {14, "Percy"}, {16, "Will"}, {13, "Harry"} } ); // unordered_map도 동일하게 초기화가 가능하다.
```

operator `=`를 이용해서 초기화를 할 수도 있다.
```cpp
hashSet1 = {"red", "green", "blue"};
hashSet2 = hashSet1;

hashMap = { {14, "Percy"}, {16, "Will"}, {13, "Harry"} };
```

## 2-3. Iterators: begin(), end()
**1) begin()**: 자료구조의 첫 번째 원소를 가리키는 반복자를 반환  
**2) end()**: 자료구조의 마지막 원소의 다음 원소를 가리키는 반복자를 반환
```cpp
for (unordered_map<int, string>::iterator it = hashMap.begin(); it != hashMap.end(); it++)
    cout << "Number: " << it->first << ", Name: " << it->second << endl;
```
```
Number: 13, Name: Harry
Number: 16, Name: Will
Number: 14, Name: Percy
```
기존 Map이나 Set의 경우, 원소들이 정렬되어 있었기 때문에 첫 번째 원소와 마지막 원소가 정해져 있었지만, 이 경우에는 어느 원소가 첫 번째로 올지 정해져 있지 않다. 그러므로 unordered_map이나 unordered_set에서 `begin()`과 `end()`는 자료구조 전체를 순회할 때만 의미를 가진다. 

## 2-3. Element lookup: find(), count(), eqaul_range()
**1) find(k)**: k를 key로 갖는 원소가 존재하면 해당 원소를 가리키는 반복자를 반환, 없으면 `end()`와 동일한 결과를 반환  
**2) count(k)**: k를 key로 갖는 원소의 개수를 반환  
**3) equal_range(k)**: k를 key로 갖는 원소의 범위를 `pair<iterator, iterator>` 형태로 반환

모두 set과 map에도 존재하는 멤버함수로, unordered_set과 unordered_map은 중복 원소를 허용하지 않기 때문에 `count()`가 0 또는 1을 반환한다.

```cpp
cout << hashMap.find(14)->second << endl;
cout << hashMap.count(100) << endl;
```
```
Percy
0
```

## 2-4. Modifiers: insert(), erase(), clear()
**1) insert()**: 새로운 원소를 삽입, 만약 동일한 key를 가진 원소가 존재하면 삽입하지 않는다.  
**2) erase()**: 반복자 또는 key를 전달받아 해당 원소를 삭제한다.  
**3) clear()**: 모든 원소들을 삭제
```cpp
hashMap = { {14, "Percy"}, {16, "Will"}, {13, "Harry"} };
hashMap.insert( {15, "Annabeth"} );

hashMap.erase( hashMap.begin() ); // 반복자로 원소 삭제 (삭제한 원소의 다음 원소를 가리키는 반복자를 반환)
hashMap.erase( 14 ); // key로 원소 삭제 (삭제된 원소의 개수 반환)
hashMap.erase( hashMap.begin(), hashMap.end() ); // 반복자로 범위에 해당하는 원소들 삭제, hashMap.clear()와 동일
```

`hashMap.erase(k)`는 k를 key로 가지는 원소를 삭제하는데, 만약 해당 원소가 없다면 0을 반환하므로 조건문에서 활용할 수 있다는 점을 기억해두자.

## 2-5. Buckets: bucket_count(), bucket_size(), bucket()
> Bucket is a slot in the container's internal hash table to which elements are assigned based on the hash value of their key.

**1) bucket_count()**: 컨테이너에 있는 bucket의 개수를 반환  
**2) bucket_size(n)**: bucket n에 있는 원소의 개수를 반환  
**3) bucket(k)**: k를 key로 하는 원소가 들어 있는 bucket의 번호를 반환(Bucket은 배열처럼 0부터 번호를 붙인다.)
```cpp
hashMap = { {14, "Percy"}, {16, "Will"}, {13, "Harry"}, {15, "Annabeth"} }
```


<br/>
# References
[1] [Geeksforgeeks, 'Hashing|Set1(Introduction)'](https://www.geeksforgeeks.org/hashing-set-1-introduction/)  
[2] [WIKIPEDIA, 'Hash function'](https://en.m.wikipedia.org/wiki/Hash_function)  
[3] [cplusplus, 'unordered_set'](https://www.cplusplus.com/reference/unordered_set/unordered_set/)  
