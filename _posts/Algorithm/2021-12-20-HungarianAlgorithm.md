---
title: "할당 문제(Assignment problem)과 헝가리안 알고리즘(Hungarian algorithm)"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` Assignment Problem, MCMF, SPFA

이번 포스팅의 주제인 헝가리안 알고리즘은 커녕 SPFA와 MCMF에 대해서도 알지 못했던 내가 어떻게 헝가리안 알고리즘에 대해 공부할 생각을 하게 되었는지부터 이야기를 해야할 것 같다.

비트마스크 기법을 적용한 DP를 공부하면서 [백준 1131. 할 일 정하기 1](https://www.acmicpc.net/problem/1311) 문제를 풀었는데, 유난히 빠르게 푼 분들의 코드를 보니 헝가리안 알고리즘이라는 것을 사용하고 있었다.

이 문제를 처음에 보았을 때도 이분 매칭 문제랑 비슷하다는 생각을 했었는데, 실제로 그러한 알고리즘이 있다는 것을 알게 되니 빨리 공부하고 싶었다.

그런데 조금 찾아본 결과, 헝가리안 알고리즘은 MCMF보다 빠르게 할당 문제를 풀 수 있는 방법이라고 해서 먼저 [MCMF](https://damo1924.github.io/algorithm/MCMF/)에 대해서 공부하려했고, 그러다보니 [SPFA](https://damo1924.github.io/algorithm/SPFA/)에 대해서도 공부하게 된 것이다.

그렇게 먼 길을 돌아 대망의 헝가리안 알고리즘에 이르렀다.

지금부터 **할당 문제**가 무엇이고, 할당 문제를 해결하는 **헝가리안 알고리즘**에 대해 알아본 후 직접 문제를 풀어볼 것이다.

## 1. Assignment Problem

할당 문제(assignmnet problem)은 다음과 같은 문제를 말한다.

> N명의 직원과 M개의 작업이 있다.
> 
> 모든 직원은 M개의 작업을 전부 수행할 수 있는데, 각 직원마다 각 작업을 하는데 필요한 비용이 다르다.
> 
> 모든 직원이 최대 하나의 작업을 할 수 있을 때, 최대한 많은 작업을 할 수 있도록 만들고 싶어한다.
> 
> 이때 전체 비용이 최소가 되도록 직원에게 작업을 할당하는 방법을 구하여라.

이때 직원의 수가 더 많다면 각 직원이 작업을 하는데 필요한 비용이 0인 작업을 (N-M)개 더 추가하고, 작업의 수가 더 많다면 모든 작업을 비용 0으로 수행할 수 있는 직원 (M-N)명을 추가하자.

<img src="https://user-images.githubusercontent.com/88201512/146673091-19b467b3-8842-4fdc-9040-ccf55278a803.jpg" width="70%" height="70%">

이렇게 직원의 수와 일의 수를 동일하게 만들 수 있으므로, 위 문제는 다음과 같이 일반화가 가능하다.

> 직원의 집합을 $I$, 작업의 집합을 $J$라고 하자. ($\left\vert I \right\vert = \left\vert J \right\vert$)
> 
> 어떤 직원 $i \in I$가 작업 $j \in J$를 처리할 때 필요한 비용을 $c(i, j)$라고 한다.
> 
> $I$**에서** $J$**로 가는 일대일 대응(bijection)** $f: I \to J$ 중 필요한 비용의 합이 가장 작은 것을 구하여라.

즉, $\sum_{i \in I} c(i, f(i))$가 최소가 되는 $f$를 구하는 문제가 된다.

앞서 본 그림과 같이 이분 그래프(bipartite graph)로 생각하면, 모든 직원이 모든 작업을 할 수 있으므로 **완전 이분 그래프(complete bipartite graph**가 된다.

이때 직원의 수와 작업의 수가 동일하므로 우리는 **완전 이분 그래프에서 비용의 합이 최소가 되는 Perfect Matching을 찾는 문제**라고 할 수 있다.

<br/>

## 2. Solving with MCMF

앞서 이야기했듯이, 할당 문제는 MCMF 문제로 바꾸어서 해결할 수 있다.

먼저 직원 N명, 작업 N개로 이루어진 완전 이분 그래프를 그린다.

그 다음 모든 직원들과 연결된 소스 정점과 모든 작업들과 연결된 싱크 정점을 추가한다.

이렇게 만들어진 그래프의 간선에 조건에 맞게 흐를 수 있는 유량과 비용을 정해주면 된다.

<center><img src="https://user-images.githubusercontent.com/88201512/146697253-ea2c238f-0b80-4ddf-8fca-522ae6c3a7ac.jpg" width="70%" height="70%"></center>

다음 링크에서는 할당 문제인 [백준 11408. 열혈강호 5](https://damo1924.github.io/algorithm/MCMF/#2-%EB%B0%B1%EC%A4%80-11408-%EC%97%B4%ED%98%88%EA%B0%95%ED%98%B8-5)를 MCMF 알고리즘으로 해결하는 과정을 확인할 수 있다.

MCMF 알고리즘의 시간복잡도는 $O(fVE)$이며, 앞서 그린 그래프는 다음을 만족한다.

- 최대 유량 $f = N$
- 정점의 수 $V = 2N + 2$
- 간선의 수 $E = (V - 2)^2 + 2N$

Big-O notation의 성질을 이용하면 할당 문제에 대한 MCMF 알고리즘의 시간복잡도는 $O(N^4)$가 된다.

<br/>

## 3. Hungarian Algorithm

이제 헝가리안 알고리즘이 어떤 과정을 통해 이루어지는지 알아보자.

3명의 직원 $i_1$, $i_2$, $i_3$와 3개의 작업 $j_1$, $j_2$, $j_3$이 있고, 직원들이 작업을 할 때 필요한 비용이 다음과 같은 행렬로 주어졌다고 하자.

<center><img src="https://user-images.githubusercontent.com/88201512/146701464-7db59f47-cbd5-4aa2-b1ab-3c15c79fa8f7.jpg" width="70%" height="70%"></center>

직원 $i_1$이 어떤 일을 할당받던 반드시 3만큼의 비용은 발생하게 되므로, 다음과 같이 행렬을 변형해도 된다.

<center><img src="https://user-images.githubusercontent.com/88201512/146701467-a64d4ee7-54d8-443b-b669-3f15695574b3.jpg" width="70%" height="70%"></center>

마찬가지로 다른 두 명의 직원에 대해서도 같은 방식으로 적용해주면 다음과 같은 행렬을 얻을 수 있다.

<center><img src="https://user-images.githubusercontent.com/88201512/146701468-5096d6f6-f3fb-46f7-9057-29a9165ccd08.jpg" width="70%" height="70%"></center>

이제 각 작업에 대해서도 반드시 발생하는 비용을 따로 빼주면 다음과 같아진다.

<center><img src="https://user-images.githubusercontent.com/88201512/146701677-3fcb1c2d-8853-4870-86df-0fcd015ec9b4.jpg" width="70%" height="70%"></center>

최종적으로 얻어진 위 행렬은 **모든 원소의 값이 0보다 크거나 같다**는 특징을 가지고 있다.

그러므로 **0의 값을 가지는 직원-작업 쌍들을 선택**하면 비용의 합이 가장 작아지게 된다.

그런데 위 행렬에서는 0의 값을 가지는 쌍만으로는 전부 매칭하는 것이 불가능하다.

이때 등장하는 것이 바로 **Konig's Theorem**이다.

> 이분 그래프의 Minimum Vertex Cover의 크기와 Maximum Matching의 크기는 동일하다.
> 
> 자세한 내용은 [이 포스트](https://damo1924.github.io/algorithm/BipartiteMatching/#konigs-theorem)를 참고.

우리는 0의 값을 가지는 직원-작업 쌍만으로 매칭을 구성하고 싶으므로 그러한 직원과 작업 노드를 잇는 간선만 존재하는 이분 그래프를 그리면 다음과 같다.

<center><img src="https://user-images.githubusercontent.com/88201512/146701677-3fcb1c2d-8853-4870-86df-0fcd015ec9b4.jpg" width="70%" height="70%"></center>

위 그래프는 표시된 것처럼 크기가 2인 Minimum Vertex Cover를 갖는다는 것을 알 수 있고, 이는 0의 값을 가지는 쌍만으로 perfect matching을 하는 것은 불가능함을 의미한다.

이제 우리가 해야 하는 일은 행렬을 값을 적당히 조절해서 **행렬의 모든 원소의 값이 0 이상이면서 0의 값을 가지는 직원-작업 쌍만으로 perfect matching이 가능하도록 만들어주는 것**이다.

<center><img src="https://user-images.githubusercontent.com/88201512/146701581-0c62996a-adb7-46f8-b4e9-c9e38ec3be8d.jpg" width="70%" height="70%"></center>

이 행렬에서 $i_3$와 $j_1$에 연결된 칸들을 제외한 나머지 칸들의 값 중 가장 작은 값을 구해서 나머지 두 행에서 빼주자.

<center><img src="https://user-images.githubusercontent.com/88201512/146701584-4cda1c31-4604-48e3-93bc-696ff107dcae.jpg" width="70%" height="70%"></center>

이렇게 변형하면 0의 값을 가지는 새로운 직원-작업 쌍이 생기게 된다.

다만, 문제는 **음수의 값을 가지는 칸이 존재**한다는 것이다.

이를 해결해주기 위해 양수 값이 아니라 음수 값을 해당 열에서 빼주면 음수였던 칸들을 다시 0 이상으로 만들 수 있다.

<center><img src="https://user-images.githubusercontent.com/88201512/146701585-638911f7-edd9-41c3-9ffe-257727b81aee.jpg" width="70%" height="70%"></center>

자, 이제 우리는 아래와 같이 0의 값을 가지는 쌍으로 perfect matching이 가능한 행렬을 얻게 되었다.

<center><img src="https://user-images.githubusercontent.com/88201512/146701586-6dc1e567-cb7d-47b5-8d60-f8bb28cbac7a.jpg" width="70%" height="70%"></center>

그렇다면 모든 일을 처리하는데 필요한 **최소 비용은 반드시 필요한 비용들의 합**이 된다.

### Algorithm

1. 

## References

[1] [WIKIPEDIA, 'Assignment problem'](https://en.m.wikipedia.org/wiki/Assignment_problem)  
[2] [WIKIPEDIA, 'Hungarian algorithm'](https://en.m.wikipedia.org/wiki/Hungarian_algorithm)  
[3] [Gazelle and Computer Science, '할당 문제 & 헝가리안 알고리즘 (Assignment Problem & Hungarian Algorithm)'](https://gazelle-and-cs.tistory.com/29)  
