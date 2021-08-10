---
title: "Sorting Algorithms with C++"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Cpp
---

# 0. What is Sorting?
정렬(sorting)은 값(value)의 대소 관계에 따라 데이터 집합을 일정한 순서로 바꾸는 것을 말한다. 정렬은 computer science에서 가장 많이 연구된 알고리즘 중 하나이다. 적절한 정렬 알고리즘을 이용한다면, 더 효과적이고 효율적인 코드를 작성할 수 있다. 대표적으로 다음과 같은 문제들에서 정렬 알고리즘을 사용할 수 있다.
- **검색(searching)**: 정렬된 리스트에서 원소를 검색하는 것이 훨씬 더 빠르다.
- **선택(selection)**: 어떤 데이터를 대표하는 값을 선택할 때, 정렬된 데이터에서 찾는 것이 더 쉽다. 예를 들어 **kth-largest value**나 **median value**를 구하려고 한다면 값이 오름차순이나 내림차순으로 정렬되어 있는 것이 훨씬 빠르다.
- **분포(distribution)**: 리스트의 원소들에 대한 도수 분포를 분석하고자 할 때 사용할 수 있다. 예를 들어 리스트가 정렬되어 있다면 최빈값을 찾는 일은 매우 간단해진다.

정렬들을 다음과 같은 기준으로 분류할 수 있다.
- **오름차순(ascending order)**: 값이 작은 것부터 늘어놓는 것
- **내림차순(descending order)**: 값이 큰 것부터 늘어놓는 것
- **내부 정렬(internal sorting)**: 하나의 배열에서 작업할 수 있는 정렬
- **외부 정렬(external sorting)**: 두 개 이상의 배열이 필요한 정렬
- **안정적인 알고리즘(stable algorithm)**: 값이 같은 원소의 순서가 정렬 후에도 유지되는 알고리즘

이제 다양한 정렬 알고리즘들에 대해 하나씩 알아보도록 하자.
