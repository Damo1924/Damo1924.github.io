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

이번에 다룰 두 자료구조는 원소를 정렬하지 않는 set과 map이라고 할 수 있다. 이 자료구조가 가지는 장점은 원소를 삽입(insert), 삭제(erase), 검색(find)하는 작업이 모두 $O(1)$로 수행된다는 것이다. 기존 Set과 Map은 각 작업에 $O(\log n)$의 시간복잡도를 가졌는데, 어떻게 상수 시간에 삽입, 삭제, 검색이 가능한 것인지 이해하기 위해서는 **Hash**에 대해 알아야한다.

## 1-1. Hash

