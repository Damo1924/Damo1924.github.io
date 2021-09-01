---
title: "unordered_set/map in C++ (Hashmap)"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Cpp
use_math: true

---

# 1. unordered_set & unordered_map
> containers that store unique elements in no particular order.

이번에 다룰 두 자료구조는 원소를 정렬하지 않는 set과 map이라고 할 수 있다. 이 자료구조가 가지는 장점은 원소를 삽입(insert), 삭제(erase), 검색(find)하는 작업이 모두 $O(1)$로 수행된다는 것이다. 기존 Set과 Map은 각 작업에 $O(\log n)$의 시간복잡도를 가졌는데, 어떻게 상수 시간에 삽입, 삭제, 검색이 가능한 것인지 이해하기 위해서는 **Hashing**이 무엇인지에 대해 알아야한다.

## 1-1. Hashing
> Hashing is a technique or process of mapping keys, values into the hash table by using a hash function.

대학에서 학생들의 학번을 이용해서 학생들의 정보를 저장하는 시스템을 만들고 싶어한다. 이 시스템은 학번-정보를 삽입하거나 삭제하는 작업과 학번을 검색하여 해당 학생의 정보를 얻는 작업을 효율적으로 수행할 수 있어야한다. 우리는 다음과 같은 자료구조를 생각해볼 수 있다.

**1.** Array of student_id & information
**2.** Linked List of student_id & information
**3.** Balanced binary search tree with student_id as keys
**4.** Direct access table with student_id as index of array

1, 2번은 선형 검색을 해야하기 때문에 전체 데이터의 크기가 커질수록 매우 비효율적이다. 배열을 정렬된 상태로 유지하면 이진 검색(binary search)를 이용해서 $O(\log n)$의 시간복잡도로 검색이 가능하지만, 삽입과 삭제를 할 때 정렬된 상태를 유지하기 위한 비용이 들기 때문에 좋다고 볼 수 없다.

3번의 경우에는 검색, 삽입, 삭제를 모두 $O(\log n)$로 수행할 수 있기 때문에 1, 2번에 비해 더 나은 선택지라고 할 수 있다.

마지막 4번은 굉장히 극단적인 방법이라고 할 수 있는데, 각 작업을 $O(1)$로 수행할 수 있다는 점에서 매우 뛰어나지만 학번의 자릿수가 많아질수록 필요한 배열의 크기가 매우 커진다는 문제가 있다. 학번이 $n$ 자리이면 table이 $O(m \times 10^{n})$의 공간을 필요로 하게 된다. 이때 $m$은 학생의 정보를 가리키는 포인터의 크기이다. 이러한 이유로 direct access table을 항상 사용할 수는 없기 때문에 등장한 것이 바로 **Hashing**이다.

> Hashing is an improvement over Direct Access Table. The idea is to use **hash function** that converts a given key to a smaller number and uses the small number as index in a table called **hash table**.

