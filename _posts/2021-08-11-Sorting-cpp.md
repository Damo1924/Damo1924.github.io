---
title: "Sorting Algorithms with C++"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

# 0. What is Sorting?
정렬(sorting)은 computer science에서 가장 많이 연구된 알고리즘 중 하나로, 값(value)의 대소 관계에 따라 데이터 집합을 일정한 순서로 바꾸는 것을 말한다. 적절한 정렬 알고리즘을 이용한다면, 더 효과적이고 효율적인 코드를 작성할 수 있다. 대표적으로 다음과 같은 문제들에서 정렬 알고리즘을 사용할 수 있다.
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


<br/>
# 1. Bubble sort
> **이웃한 두 원소의 대소 관계를 비교하여 필요에 따라 교환을 반복하는 알고리즘**으로, 단순 교환 정렬이라고도 부른다.

## 1-1. Bubble sort algorithm
길이가 n인 리스트를 오름차순으로 정렬하려고 한다.  
**-** k가 1부터 시작해서 n-1까지 변할 때, k번째 원소와 k+1번째 원소를 비교해서 k번째 원소가 더 크면 두 원소를 교환하는 과정을 거치게 되면 가장 큰 원소가 맨 뒤에 위치하게 된다. 이러한 일련의 과정을 pass라고 하자.  
**-** 첫 번째 pass의 수행으로 가장 큰 원소가 맨 뒤에 위치하게 되었으므로, 나머지 n-1개의 원소들에 대해 pass를 수행하면 두 번째로 큰 원소가 정렬된다.  
**-** 즉, pass를 총 n-1번 수행하면 길이가 n인 리스트가 완벽하게 정렬된다.  
**-** 이렇게 원소들이 하나씩 정렬되는 것이 마치 액체 속의 공기 방울이 올라오는 것과 비슷해서 버블 정렬이라는 이름이 붙여졌다.

## 1-2. Bubble sort implementation
```cpp
#include <iostream>
#include <vector>
using namespace std;

void Bubblesort_1(int* arr, int len)
{
    for (int i = 1; i < len; i++){
        for (int j = 0; j < len - i; j++){
            if (vec[j] > vec[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main()
{
    vector<int> vec = {3, 5, 1, 6, 2, 9};
    Bubblesort(vec.data(), vec.size());
    for(int i = 0; i < vec.size(); i++) cout << vec[i] << " ";
}
```
```
1 2 3 5 6 9
```
: 첫 번째 for문은 pass의 수행 횟수를, 두 번째 for문은 실질적인 pass를 의미한다.

이미 정렬된 부분에 대해서는 비교/교환 과정을 수행할 필요가 없다. 즉, **교환 횟수가 0인 pass가 있다면 남은 부분이 완전히 정렬되었다는 의미**이다. 이를 구현하기 위해서 각 pass에서 일어난 교환의 횟수를 뜻하는 변수인 `exchange`를 도입하였다.
```cpp
void Bubblesort_2(int* arr, int len)
{
    for (int i = 1; i < len; i++){
        int exchange = 0;
        for (int j = 0; j < len - i; j++){
            if (vec[j] > vec[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                exchange++;
            }
        }
        if (exchange == 0) break;
    }
}
```


만약 pass에서 비교/교환 작업을 수행하다가 **어느 순간부터 교환을 하지 않는다면, 그 원소보다 뒤쪽에 있는 원소들은 이미 정렬을 마쳤다**고 할 수 있다. 그러므로 이미 정렬된 부분을 건너뛸 수 있도록 `last_exchange`에 마지막 교환 위치를 저장하였다.
```cpp
void Bubblesort_3(int* arr, int len)
{
    int i = n-1, last_exchange = n-1;
    while (i > 0){
        for (int j = 0; j < i; j++){
            if (vec[j] > vec[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                last_exchange = j;
            }
        }
        if (last_exchange == i) break;
        else i = last_exchange;
    }
}
```

## 1-3. Bubble sort time complexity
> Average-case: $O(n^2)$, Worst-case: $O(n^2)$

길이 n인 배열을 정렬하고자 할 때, k번째 pass에서 n-k번의 비교 연산을 하므로 bubble sort의 총 비교 연산 횟수는 다음과 같다.

> $1 + 2 + \cdots + (n - 1) = \frac{n \times (n-1)}{2}$

Big O Notation의 성질에 의해 계수와 일차항은 무시할 수 있으므로 시작복잡도는 $O(n^2)$임을 알 수 있다.


<br/>
# 2. Insertion sort
> 주목한 원소를 **알맞은 위치로 삽입**하여 정렬하는 알고리즘이다.

## 2-1. Insertion sort algorithm
길이가 n인 리스트를 오름차순으로 정렬하려 한다.
**-** 두 번째 원소를 첫 번째 원소와 비교 `>` 두 번째 원소가 더 작으면 첫 번째 원소 앞에 삽입 `>` 두 번째 원소까지 정렬  
**-** 세 번째 원소를 두 번째 원소와 비교 `>` 세 번째 원소가 더 작으면 첫 번째 원소와 비교 `>` 세 번째 원소를 알맞은 위치에 삽입 `>` 세 번째 원소까지 정렬  
**-** 즉, k번째 원소를 k번째 원소의 앞부분(첫 번째 원소 ~ k-1번째 원소)의 알맞은 위치에 삽입하는 과정을 k가 2일 때부터 n까지 반복한다.  
**-** k번째 원소에 주목하고 있으면 그 앞부분은 이미 앞선 과정으로 정렬된 상태이기 때문에 더 작은 원소를 만날 때까지 비교해 나가면 된다.  
**-** 만약 더 작은 원소를 찾았으면 그 원소 앞에 k번째 원소를 삽입하고, 찾지 못했다면 맨 앞에 삽입한다.

## 2-2. Insertion sort implementation
```cpp
void Insertionsort(int* arr, int len)
{
    for (int i = 0; i < len; i++){
        int j = i, temp = arr[i];
        while (j > 0 && arr[j-1] > temp){
            array[j] = array[j-1];
            j--;
        }
        array[j] = temp;
    }
}
```
: `i`는 주목한 원소의 인덱스, `j`는 주목한 원소와 비교할 원소의 인덱스이다. `j`를 줄여가면서 더 작은 원소를 만날 때까지 비교/교환 작업을 하면 자연스럽게 알맞은 위치에 들어가게 된다는 것을 알 수 있다.

## 2-3.Insertion sort time complexity
> Average-case: $O(n^2)$, Worst-case: $O(n^2)$

**-** Insertion sort는 비록 bubble sort와 동일한 시간 복잡도를 가지는 알고리즘이지만, 실제로 걸리는 시간을 비교해보면 bubble sort에 비해 평균적으로 빠르다. 이는 실질적인 비교/교환 연산의 수가 더 적기 때문이다.  
**-** Merge sort, quicksort와 같은 매우 강력한 정렬 알고리즘들이 있지만, **크기가 작은 리스트를 정렬하는데 걸리는 시간을 측정해보면 insertion sort가 더 빠르다**는 것을 알 수 있다. 특히 quicksort를 사용하는 경우, 어느 정도 작은 크기의 리스트에 대해서는 insertion sort를 이용하기도 한다. Python의 내장 정렬 함수 `sorted()`와 `.sort()`의 정렬 알고리즘인 Timsort은 전체 배열을 작은 부분으로 나누어서 각 부분들을 insertion sort로 정렬한 뒤 합치는 방식을 사용한다.  
**-** 물론 입력 크기의 제곱에 비례하는 시간복잡도를 가지고 있기 때문에 크기가 큰 입력에 대해서는 비효율적이다.

## 2-4. Binary insertion sort
주목한 원소를 삽입할 위치를 찾기 위해 선형 검색(linear search) 대신 이진 검색(binary search)를 사용한 정렬 방법이다.

<details>
<summary> 이진 검색이란? </summary>
<div markdown = "1">

이진 검색은 정렬된 배열에서 선형 검색보다 빠르게 원하는 값을 검색할 수 있는 알고리즘이다. 검색하려는 범위를 계속 절반으로 줄여나가면서 검색하는 방식이기 때문에 $O(\log n)$의 시간복잡도를 가진다.  

검색 과정은 다음과 같다.  
**-** 검색 범위 `pl` ~ `pr`의 중앙값의 인덱스 `pc`는 `pc = (pl + pr) / 2`로 구한다.
**-** 구한 인덱스를 이용해서 중앙값과 검색하려는 값을 비교한다.
- 검색하려는 값과 중앙값이 같으면 검색 종료
- 검색하려는 값이 더 크면 `pl = pc+1`
- 검색하려는 값이 더 작다면 `pr = pc-1`
**-** 위 과정을 반복하면서 검색 범위를 계속 줄여나간다.
**-** 만약 `pl`이 'pr`보다 커지면 더 이상 검색할 범위가 없으므로 검색하려는 원소가 존재하지 않는다는 의미이다.

</div>
</details>

```cpp
void Binary_insertionsort(int* arr, int len)
{
    for (int i = 0; i < len; i++){
        int key = arr[i], pl = 0, pr = i-1, pc;
        while(true){
            int pc = (pl + pr) / 2;
            if (arr[pc] == key) break;
            else if (arr[pc] < key) pl = pc + 1;
            else pr = pc - 1;
            if (pl > pr) break;
        }
        int pd = (pl <= pr) ? pc+1 : pr+1;
        for (int j = i; j > pd; j--) arr[j] = arr[j-1];
        arr[pd] = key;
    }
}
```















