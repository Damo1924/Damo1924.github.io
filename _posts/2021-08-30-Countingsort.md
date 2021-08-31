---
title: "Counting sort"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

# 1. What is Counting sort?
Counting sort는 작은 범위의 정수들을 $O(n)$의 시간복잡도로 정렬할 수 있는 알고리즘이다. 이름 그대로 각 숫자가 몇 번 등장했는지 세어준 정보를 배열에 저장하는 방식이다. 하지만 주어진 입력의 최댓값이 커질수록 그에 해당하는 크기의 배열을 필요로 하기 때문에 다른 정렬 방식에 비해 메모리 사용량이 더 크다.

예를 들어 1부터 100까지의 정수 10,000개를 정렬하는데는 다른 복잡한 정렬 알고리즘들보다 강력하면서 메모리 사용도 적으므로 최적의 정렬 알고리즘이라고 할 수 있다.

반대로 최대값이 커지면 커질수록 counting sort는 그닥 유용하지 않다. 극단적인 예시로 `9999, 1`이라는 두 정수를 정렬할 때, counting sort를 이용하면 길이가 10000인 배열을 만들어야 한다. 다른 정렬 알고리즘들이 8byte를 사용할 때 40000byte를 사용하게 된다. 심지어 고작 두 정수를 정렬하기 위해 길이가 10000인 배열을 한 번 순회해야 하기 때문에 시간적으로도 오히려 더 오래 걸리게 된다.

즉, counting sort는 주어지는 입력의 범위가 작고, 입력의 크기(길이)가 큰 경우에 사용할 수 있는 정렬 알고리즘이다.

# 2. C++로 counting sort 구현하기
Counting sort는 다음과 같이 구현한다.
1. 입력으로 주어질 수 있는 범위만큼의 배열을 만들고 각 입력이 들어올 때마다 count.
2. 위 배열을 앞에서부터 누적합을 한 배열 생성
3. 기존 배열을 뒤에서부터 순회하면서 각 숫자를 알맞은 위치에 저장(이때 2번에서 만든 배열의 값이 알맞은 위치 

```cpp
#include <iostream>
#include <

```


# References
[1] [Geeksforgeeks, 'Counting sort'](https://www.geeksforgeeks.org/counting-sort/)  
[2] 
