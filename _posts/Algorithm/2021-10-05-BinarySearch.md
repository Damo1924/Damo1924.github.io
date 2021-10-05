---
title: "이분 탐색(Binary Search) 알고리즘"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

## 1. Binary Search Algorithm

이분 탐색 알고리즘은 정렬된 리스트에서 탐색 범위를 절반씩 줄여나가며 데이터를 탐색하는 알고리즘이다.

탐색할 범위(`start` ~ `end`)의 중앙(`(start + end) / 2`)값과 찾으려는 값을 비교해가며 탐색한다.

정렬되어 있는 데이터에서만 사용할 수 있다는 한계가 있지만, 탐색 범위를 매번 절반으로 줄이기 때문에 $O(\log N)$의 시간복잡도를 가진다는 장점이 있다.

매우 간단하면서도 강력한 알고리즘이기 때문에 다양한 문제에서 다양한 형태로 활용된므로 꼭 알아두자.

구현하는 방법으로는 재귀함수와 반복문이 있는데, 재귀함수 호출에 시간이 소요된다는 점으로 인해 PS에서는 일반적으로 반복문을 사용한다.

**[재귀함수로 구현한 이분 탐색 알고리즘]**

```cpp
int binarySearch (int start, int end, int x)
{
    if (start > end) return -1;
    
    int mid = (start + end) / 2;
    if (A[mid] < x) return binarySearch(start, mid - 1, x);
    else if (A[mid] > x) return binarySearch(mid + 1, end, x);
    else return mid;
}
```

**[반복문으로 구현한 이분 탐색 알고리즘]**

```cpp
int start = 0, end = N - 1, idx = -1;
while (start <= end)
{
    int mid = (start + end) / 2;
    if (A[mid] < x) start = mid + 1;
    else if (A[mid] > x) end = mid - 1;
    else
    {
        idx = mid;
        break;
    }
}
```

##
