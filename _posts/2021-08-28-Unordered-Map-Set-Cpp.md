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

Hashing에는 hash function과 hash table로 이루어져있다.
> *Hashing is an improvement over Direct Access Table. The idea is to use **hash function** that converts a given key to a smaller number and uses the small number as index in a table called **hash table**.*

**1. Hash function**: Hash table의 인덱스로 사용하기에 너무 큰 값이나 인덱스로 사용할 수 없는 문자열 등을 작은 정수로 바꾸어줌으로써 인덱스로 사용할 수 있도록 만들어주는 함수이다.

좋은 hash function은 다음과 같은 조건을 만족해야한다.

- 계산이 복잡하지 않아야한다.(efficiently computable)
- Key가 균일하게 분포하도록 해야한다.(should uniformly distribute the keys)

**2. Hash Table**: key에 대응되는 value가 저장된 곳의 포인터를 저장하는 배열을 의미한다.



# 2. unordered_set, unordered_map
## 2-1. unordered_set, unordered_map 선언하기
각각 `<unordered_set>`


