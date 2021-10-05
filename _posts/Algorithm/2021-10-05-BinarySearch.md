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

### [관련 문제]

다음 문제는 이분 탐색을 응용해서 해결할 수 있는 대표적인 문제들 중 하나이다.

**[백준] 1300. K번째 수**

[백준 1300. K번째 수 문제 링크](https://www.acmicpc.net/problem/1300)

$10^5$보다 작거나 같은 자연수 N이 주어질 때, N x N 배열 A의 각 성분은 다음과 같이 주어진다.

`A[i][j] = i * j`

배열 A의 모든 성분들을 일차원 배열 B에 넣고 오름차순으로 정렬했을 때, `B[k]`의 값을 구하는 문제이다.

(단, 배열 A와 B의 인덱스는 1부터 시작하며, k는 $10^9$보다 작거나 같다.)

**[풀이]**

배열 B가 정렬되어 있으므로 $N^2$ 이하의 어떤 자연수 $n$에 대해 $n$이 몇 번째 원소인지는 다음과 같은 방법으로 찾을 수 있다.

```cpp
int idx = 0;
for (int i = 0; i < min(n, N); i++) idx += min(n / i, N);
```



이분 탐색으로 찾을 수 있다.

<br/>
## 2. Parametric Search



