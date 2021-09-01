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

## 1-1. Hashing의 필요성
대학에서 학생들의 학번을 이용해서 학생들의 정보를 저장하는 시스템을 만들고 싶어한다. 이 시스템은 학번-정보를 삽입하거나 삭제하는 작업과 학번을 검색하여 해당 학생의 정보를 얻는 작업을 효율적으로 수행할 수 있어야한다.

우리는 다음과 같은 자료구조를 생각해볼 수 있다.

**1.** Array of student_id & information  
**2.** Linked List of student_id & information  
**3.** Balanced binary search tree with student_id as keys  
**4.** Direct access table with student_id as index of array

1, 2번은 선형 검색을 해야하기 때문에 전체 데이터의 크기가 커질수록 매우 비효율적이다. 배열을 정렬된 상태로 유지하면 이진 검색(binary search)를 이용해서 $O(\log n)$의 시간복잡도로 검색이 가능하지만, 삽입과 삭제를 할 때 정렬된 상태를 유지하기 위한 비용이 들기 때문에 좋다고 볼 수 없다.

3번의 경우에는 검색, 삽입, 삭제를 모두 $O(\log n)$로 수행할 수 있기 때문에 1, 2번에 비해 더 나은 선택지라고 할 수 있다.

마지막 4번은 굉장히 극단적인 방법이라고 할 수 있는데, 각 작업을 $O(1)$로 수행할 수 있다는 점에서 매우 뛰어나지만 학번의 자릿수가 많아질수록 필요한 배열의 크기가 매우 커진다는 문제가 있다. 학번이 $n$ 자리이면 table이 $O(m \times 10^{n})$의 공간을 필요로 하게 된다. 이때 $m$은 학생의 정보를 가리키는 포인터의 크기이다. 이러한 이유로 direct access table을 항상 사용할 수는 없기 때문에 등장한 것이 바로 **Hashing**이다.

## 1-2. Hash function & hash table
> *Hashing is an improvement over Direct Access Table. The idea is to use **hash function** that converts a given key to a smaller number and uses the small number as index in a table called **hash table**.*

**1. Hash function**: Hash table의 인덱스로 사용하기에 너무 큰 값이나 인덱스로 사용할 수 없는 문자열 등을 작은 정수로 바꾸어줌으로써 인덱스로 사용할 수 있도록 만들어주는 함수이다.

좋은 hash function은 다음과 같은 조건을 만족해야한다.

- 계산이 복잡하지 않아야한다.(efficiently computable)
- Key가 균일하게 분포하도록 해야한다.(should uniformly distribute the keys)

(Hash function의 properties와 종류에 대해서 더 알고 싶다면 [WIKIPEDIA, 'Hash function'](https://en.wikipedia.org/wiki/Hash_function#Division_hashing)을 참고)

이러한 hash function을 통해 얻을 값을 **해시값(Hash value)**라고 부른다.

가장 간단한 hash function은 정수형 키 값을 적절한 수로 나누었을 때 나머지를 반환하는 함수이다. 계산이 매우 간단하고 key가 치우치지 않고 균일하게 분포시키는 것이 가능하므로 위 조건을 만족한다. 일반적으로 hash value가 겹치는 것을 막기 위해 소수로 나눈 나머지를 사용한다.

**2. Hash Table**: key에 대응되는 value가 저장된 곳의 포인터를 저장하는 배열을 의미한다. Hash table은 n개의 **bucket**으로 구성되고, 이 bucket은 s개의 **slot**으로 이루어져 있다. 하나의 슬롯(slot)에 하나의 원소가 저장되는데, 버킷(bucket)이 여러 개의 슬롯으로 이루어져 있는 이유는 **서로 다른 두 key가 hash function에 의해 동일한 hash value로 변환**될 수 있기 때문이다.

## 1-3. Hash collision
서로 다른 두 key가 동일한 hash value를 가지는 것을 해시 충돌(hash collision)이라고 한다.

앞에서 살펴본 direct access table은 버킷의 개수와 전체 key의 개수가 동일한 형태의 자료구조로, 당연히 해시 충돌이 발생하지 않는다. 하지만 실제로 사용하는 actual key들이 전체 개수에 비해 매우 적다면 많은 메모리를 낭비하게 된다. 그래서 일반적으로는 hash table의 크기가 실제 사용하는 key의 개수보다 적은 hash table을 사용하는데, 이때 **hash table의 한 bucket에 평균적으로 몇 개의 key가 할당되는지를 나타내는 지표**를 ***load factor***라고 부른다. Load factor가 1보다 크다면 hash collision이 발생하게 된다.

Hash collision은 hash value를 통해 정보에 접근하는 것을 방해하는 요소이기 때문에 이를 해결하기 위한 여러가지 방법들이 고안되었는데, 그 중 대표적인 것들을 살펴보도록 하겠다.

### 1-3-1. Chaining (Open hashing)
체인법(chaining)은 hash value가 같은 데이터를 체인과 같은 연결 리스트(linked list)로 연결하는 방법이다. 즉, 한 bucket 당 여러 개의 원소가 들어갈 수 있도록 함으로써 collision을 해결한다. 동일한 hash value를 같은 원소가 삽입되었다면, 기존에 컨테이너에 있던 원소가 새롭게 삽입된 원소를 가리키도록 구현한다.

Chaining을 이용했을 때 각 작업의 시간복잡도를 구해보자.

먼저 삽입의 경우,
1. Hash value를 구하기 - $O(1)$
2. 연결 리스트에 원소를 추가 - $O(1)$

의 과정을 통해 이루어지므로, 원소를 삽입할 때의 시간복잡도는 항상 $O(1)$이다.

검색은 조금 다르다. 만약 모든 원소들이 균일하게 분포해서 각 bucket에 k개씩 저장되어 있다고 가정하면,
1. Hash value를 구하기 - $O(1)$
2. 연결 리스트에서 원소를 검색 - $O(k)$

이므로 원소를 검색하는데 $O(1+k)$가 걸린다.

하지만, 최악의 경우에는 하나의 bucket에 모든 원소가 저장되어 있으므로 연결 리스트에서 원소를 검색하는데 $O(n)$이 필요하다. 즉, worst-case의 시간복잡도는 $O(n)$이 된다.

삭제는 결국 해당 key를 가지는 원소를 검색한 다음 연결 리스트에서 삭제가 이루어지는 것이기 때문에 검색과 마찬가지로 average-case는 $O(1+k)$, worst-case는 $O(n)$이다.

### 1-3-2. Open addressing (Closed hashing)
오픈 주소법(open addressing)은 hash collision이 발생했을 때 해당 원소를 저장할 빈 bucket을 찾아 저장하는 방법이다. 이 방법은 한 bucket 당 하나의 원소가 저장되므로 hash table의 크기가 사용되는 key의 개수보다 더 커야한다.

빈 bucket을 찾을 때 사용하는 함수는 자유롭게 정할 수 있는데, 예를 들어 key를 13으로 나눈 나머지를 hash value로 사용하는 자료구조가 있다고 하자. 충돌이 발생하면 key에 1을 더해(**Linear Probing**) 13으로 나눈 나머지를 hash value로 갖도록 정하였다. 이 컨테이너에 key가 1인 원소가 들어있는 상태에서 key가 14인 원소를 삽입할려면 hash value가 둘 다 1로 같기 때문에 hash collision이 발생한다. 미리 정해둔 함수을 이용해서 새로운 hash value를 구하면 `(14 + 1) % 13 = 2`이므로 해당하는 bucket에 저장하면 collision이 해결됨을 알 수 있다.

이처럼 비어있는 bucket을 찾을 때까지 계속 rehash해서 원소를 삽입할 수 있다. 검색도 비슷한 원리로 원하는 값을 찾거나 빈 슬롯을 만날 때까지 계속해서 rehash를 하면 된다.

특이한 부분은 바로 원소를 삭제하는 방법인데, **단순히 원소를 삭제하게 되면 삭제한 원소와 겹쳐 일부 원소들을 검색할 수 없게 된다.** 앞선 예시에서 key가 1, 14, 27인 원소를 순서대로 삽입하면 세 원소는 hash value가 각각 1, 2, 3가 된다. 이 상태에서 key가 14인 원소를 단순히 삭제해버리면 key가 27인 원소를 검색할 수 없게 된다. 그래서 오픈 주소법에서 원소를 삭제할 때는 반드시 **deleted**되었다는 표시를 해야한다. 이 **deleted** 표시가 된 슬롯에는 원소의 삽입은 가능하지만, 검색할 때는 해당 슬롯에서 멈추지 않고 검색을 이어나간다.

### 1-3-3. Chaining vs. Open addressing
다음은 hash collision을 해결하는 두 가지 방법의 차이점을 정리한 표이다.

|No.|Chaining|Open Addressing|
|:---:|:---:|:---:|
|1. Implementation|구현이 비교적 간단하다.|구현이 비교적 복잡하다.|
|2. Limited number of elements|원소 개수의 제한이 없다.|Hash table의 크기만큼의 원소만 허용된다.|
|3. Hash functions & load factors|비교적 영향을 덜 받는다.|영향이 커서 더 신경써야 한다.|
|4. Cache performance|연결 리스트에 저장되어있어 캐시 성능이 떨어진다.|Hash table에 직접 저장되어있어 캐시 성능이 뛰어나다.|
|5. Wastage of Space|메모리 낭비가 심하다.|메모리 낭비가 적다.|

<br/>
다음은 두 방법의 시간복잡도를 정리한 표이다.
- **m** = Number of slots in the hash table
- **n** = Number of keys to be inserted in the hash table
- **a** = Load factor = n / m ($a < 1$ when using open addressing)

라고 할 때, 시간복잡도는 다음과 같다.

|Task|Time complexity of Chaining|Time complexity of Open Addressing|
|:---:|:---:|:---:|
|Search|$O(1+a)$|$O(\frac{1}{1-a})$|
|Insert|$O(1)$|$O(\frac{1}{1-a})$|
|Delete|$O(1+a)$|$O(\frac{1}{1-a})$|


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

```cpp
cout << hashMap.find(14)->second << endl;
cout << hashMap.count(100) << endl;
```
```
Percy
0
```

모두 set과 map에도 존재하는 멤버함수로, unordered_set과 unordered_map은 중복 원소를 허용하지 않기 때문에 `count()`가 0 또는 1을 반환한다.

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

## 2-5. Capacity: empty(), size()
**1) empty()**: 컨테이너가 비어있으면 true, 아니면 false를 반환
**2) size()**: 컨테이너에 있는 원소의 개수를 반환
```cpp
hashMap = { {14, "Percy"}, {16, "Will"}, {13, "Harry"} };
if (!hashMap.empty())
    cout << hashMap.size() << endl;
```
```
3
```

## 2-6. Buckets: bucket_count(), bucket_size(), bucket()
> ***Bucket** is a slot in the container's internal hash table to which elements are assigned based on the hash value of their key.*

**1) bucket_count()**: 컨테이너에 있는 bucket의 개수를 반환  
**2) bucket_size(n)**: bucket n에 있는 원소의 개수를 반환  
**3) bucket(k)**: k를 key로 하는 원소가 들어 있는 bucket의 번호를 반환(Bucket은 배열처럼 0부터 번호를 붙인다.)
```cpp
hashMap = { {14, "Percy"}, {16, "Will"}, {13, "Harry"}, {15, "Annabeth"} }
cout << "버킷의 개수: " << hashMap.bucket_count() << endl;
cout << "-----\n각 원소가 들어있는 버킷의 번호" << endl;
for (unordered_map<int, string>::iterator it = hashMap.begin(); it != hashMap.end(); it++)
    cout << "(" << it->first << ", " << it->second << ") -> Bucket #" << hashMap.bucket(it->first) << endl;
```
```
버킷의 개수: 5
-----
각 원소가 들어있는 버킷의 번호
(15, Annabeth) -> Bucket #0
(13, Harry) -> Bucket #3
(16, Will) -> Bucket #1
(14, Percy) -> Bucket #4
```

## 2-7. Hash Policy: load_factor(), rehash(), reserve()
**1) load_factor()**: 컨테이너의 load factor를 float 형태로 반환한다.
> ***load factor** is the ratio between the number of elements in the container and the number of buckets.*
> 
> $load factor = size \div bucket count$

**2) rehash(n)**: 컨테이너의 최대 bucket의 개수를 n 또는 그 이상으로 설정한다.  
**3) reserve()**: 컨테이너의 bucket의 개수를 최소 n개의 원소들을 저장할 수 있는 적절한 개수로 설정
```cpp
unordered_set<int> hashSet;
hashSet.reserve(10); // 10개의 입력을 받아 저장할 것이므로 미리 10개의 원소를 저장할 수 있도록 설정

for(int i = 0; i < 10; i++) {
    int temp;
    cin >> temp;
    hashSet.insert(temp);
}

cout << "size = " << hashSet.size() << endl;
cout << "bucket_count = " << hashSet.bucket_count() << endl;
cout << "load_factor = " << hashSet.load_factor() << endl;
```
**input:**
```
1 2 3 4 5 6 7 8 9 1
```
**output:**
```
size = 9
bucket_count = 11
load_factor = 0.818182
```
컨테이너에 원소를 계속 추가해서 `load_factor`가 컨테이너의 `max_load_factor`를 넘어서려고 하면 자동적으로 rehash를 해서 최대 bucket의 개수를 늘린다. 이 과정에서 모든 원소들이 새로운 bucket에 재할당되는데, 이는 $O(n)$의 시간복잡도를 가지는 작업이므로 만약 컨테이너에 삽입될 원소의 최대 개수를 알고 있다면 `rehash()` 또는 `reserve()`를 통해 불필요한 rehash를 줄일 수 있다.

## 2-8. Observers: hash_function(), key_eq()
**1) hash function()**: hash function을 반환(**::hasher**)
```cpp
hashMap = { {"Percy", "Jackson"}, {"Will", "Treaty"}, {"Harry", "Potter"}, {"Annabeth", "Chase"} };
unordered_map<string, string>::hasher fn = hashMap.hash_function();
cout << "fn("Percy") = " << fn("Percy") << endl;
cout << "fn("Will") = " << fn("Will") << endl;
```
```
fn("Percy") = 14185119579773389234
fn("Will") = 10725321351515508676
```
이처럼 hash function은 문자열을 정수로 변환해서 저장한다.

**2) key_eq()**: key equality를 비교하는 객체를 반환
```cpp
unordered_set<string> hashSet;

bool case_insensitive = hashSet.key_eq()("checking", "CHECKING");

cout << "hashSet.key_eq() is ";
cout << (case_insensitive ? "case insensitive" : "case sensitive") << endl;
```
```
hashSet.key_eq() is case sensitive
```
문자열 key를 받았을 때 대문자와 소문자를 구분하는지 확인해본 결과, `case_insensitive`가 false를 반환하였으므로 대소문자를 구분한다는 사실을 알 수 있다.


<br/>
# References
[1] [Geeksforgeeks, 'Hashing data structure'](https://www.geeksforgeeks.org/hashing-data-structure/)  
[2] [WIKIPEDIA, 'Hash function'](https://en.m.wikipedia.org/wiki/Hash_function)  
[3] [cplusplus, 'unordered_set'](https://www.cplusplus.com/reference/unordered_set/unordered_set/)  
[4] [cplusplus, 'unordered_map'](https://www.cplusplus.com/reference/unordered_map/unordered_map/)  
