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
1. 입력으로 주어질 수 있는 범위만큼의 배열(count)을 만들고 각 입력(k)이 들어올 때마다 `count[k]++`
2. 위 배열을 앞에서부터 누적합을 한 배열(countSum) 생성 `countSum[i] = count[i] + countSum[i-1]`
3. 기존 배열을 순회하면서 각 숫자(k)를 알맞은 위치에 저장 `--countSum[k]`

각 과정이 배열을 한 번 순회하므로 시간복잡도는 $O(n + m)$가 된다. 이때 n은 배열의 길이, m은 배열의 최댓값이다.

```cpp
#include <iostream>
#include <cstring>
using namespace std;

int maxNum = 100, maxLen = 10000;

void countingSort (int *arr, int n) {
    int count[maxNum+1];
    memset(count, 0, sizeof(count));
    for (int i = 0; i < n; i++)
        count[*(arr+i)]++;
    
    int countSum[maxNum+1];
    countSum[0] = count[0];
    for (int i = 1; i < maxNum+1; i++)
        countSum[i] = count[i] + countSum[i-1];
    
    int sorted[n];
    for (int i = 0; i < n; i++)
        sorted[--countSum[*(arr+i)]] = *(arr+i);
    
    for (int i = 0; i < n; i++)
        *(arr+i) = sorted[i];
}

int main()
{
    int n, arr[maxLen];
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    
    countingSort(arr, n);
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
}
```


<br/>
# References
[1] [Geeksforgeeks, 'Counting sort'](https://www.geeksforgeeks.org/counting-sort/)  
