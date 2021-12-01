---
title: "이진 탐색 트리 (Binary Search Tree)"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:    
  - Algorithm
use_math: true
comments: true

---

## 1. 이진 탐색 트리(Binary Search Tree)란?

모든 노드가 다음 조건을 만족하는 이진 트리를 이진 탐색 트리라고 한다.

1. 노드의 왼쪽 서브트리에 있는 노드들의 값은 자신보다 작아야 한다.
2. 노드의 오른쪽 서브트리에 있는 노드들의 값은 자신보다 커야 한다.

위 조건에 의해 이진 검색 트리에는 값이 동일한 노드는 존재하지 않는다.

이진 검색 트리는 다음과 같은 특징들을 갖고 있다.

1. 중위 순회(inorder, LNR)를 통해 노드들의 값을 오름차순으로 얻을 수 있다.
2. 이진 탐색(binary search)과 비슷한 방식으로 아주 빠르게 값을 검색할 수 있다.
3. 노드를 비교적 쉽게 삽입할 수 있다.
4. 구조가 단순하다.

이러한 특징들로 인해 이진 탐색 트리는 다양한 알고리즘에 이용되는데, 이를 C+=의 class와 pointer를 이용해서 직접 구현해보자.

---

<br/>

## 2. C++로 이진 탐색 트리 구현하기

### 2-1. 노드(node) 구현하기

먼저 이진 탐색 트리를 구성하는 각 노드는 해당 노드의 값(value), 왼쪽 자식 노드(leftChild), 오른쪽 자식 노드(rightChild)에 대한 정보를 담고 있어야 한다.

```cpp
class Node {
public:
    int value; // 값
    Node* leftChild = NULL; // 왼쪽 자식 노드
    Node* rightChild = NULL; // 오른쪽 자식 노드
    
    Node(int _value, Node* _leftChild, Node* _rightChild) // 생성자
        : value(_value), leftChild(_leftChild), rightChild(_rightChild) { }
};
```

---

### 2-2. 노드 탐색(search)

이진 탐색 트리의 가장 큰 장점 중 하나는 평균적으로 $O(\log n)$에 특정 값을 가진 노드를 검색하는 것이 가능하다는 점이다.

찾으려는 값이 어떤 노드의 값보다 크면 해당 노드의 오른쪽 서브트리에 대해 탐색을 이어나가면 되고, 반대로 찾으려는 값이 어떤 노드의 값보다 작으면 해당 노드의 왼쪽 서브트리에 대해 탐색을 하면 된다.

그러다 찾으려는 값을 가진 노드를 찾으면 해당 노드를 반환하고, 리프 노드까지 탐색했음에도 찾으려는 값을 가진 노드가 없으면 `NULL`을 반환하는 함수를 구현하였다.

```cpp
Node* searchNode (Node* root, int v)
{
    if (root == NULL) return NULL;
    
    if (root->value == v) return root;
    else if (root->value > v) return searchNode(root.leftChild, v);
    else return searchNode(root.rightChild, v);
}
```

---

### 2-3. 노드 삽입(insert)

이진 탐색 트리에 새로운 노드를 삽입하기 위해서는 해당 노드가 삽입되었을 때도 이진 탐색 트리의 조건을 만족하도록 올바른 위치에 노드를 삽입해야 한다.

새로운 노드를 삽입할 위치를 찾는 과정은 다음과 같다.

1. 현재 서브트리의 루트 노드와 삽입할 노드의 값을 비교한다.
2. 삽입할 노드의 값이 더 클 때, 루트 노드가 오른쪽 자식 노드가 없으면 그 자리에 노드를 삽입한다. 루트 노드가 오른쪽 자식 노드가 있으면 오른쪽 자식 노드를 루트로 하는 서브트리에 대해 1번부터 과정을 반복한다.
3. 삽입할 노드의 값이 더 작을 때, 루트 노드가 왼쪽 자식 노드가 없으면 그 자리에 노드를 삽입한다. 왼쪽 자식 노드가 있으면, 왼쪽 자식 노드를 루트로 하느 서브트리에 대해 1번부터 과정을 반복한다.

새로운 원소를 삽입하는 함수 `insertNode`를 구현해보았다.

```cpp
void insertNode (Node* root, Node* node)
{
    if (node->value < root->value) // 서브트리의 루트보다 삽입하려는 노드의 값이 더 작을 때
    {
        if (root->leftChild == NULL) // 루트의 왼쪽 자식 노드가 없는 경우, 그 자리에 삽입
        {
            root->leftChild = node;
            return;
        }
        else // 루트의 왼쪽 자식 노드가 있으면, 재귀적으로 반복
        {
            insertNode(root->leftChild, node);
        }
    }
    else if (node->value > root->value) // 서브트리의 루트보다 삽입하려는 노드의 값이 더 클 때
    {
        if (root->rightChild == NULL) // 루트의 오른쪽 자식 노드가 없으면, 그 자리에 삽입
        {
            root->rightChild = node;
            return;
        }
        else // 루트의 오른쪽 자식 노드가 있으면, 재귀적으로 반복
        {
            insertNode(root->rightChild, node);
        }
    }
}
```

---

### 2-4. 노드 삭제(delete)

트리에서 노드를 삭제한다는 것의 의미는 연결되어있는 노드들 간의 연결을 끊는다는 것을 말한다.

이진 탐색 트리에서 노드를 삭제하고 나면, 나머지 노드들이 이진 탐색 트리를 이루도록 노드들을 잘 연결시켜주어야 한다.

이때 삭제할 노드의 자식 노드의 개수에 따라서 방법이 달라지게 된다.

주의할 점은 삭제할 노드의 부모 노드와 자식 노드를 연결시켜야하기 때문에 부모 노드에 대해서도 기억을 해두어야 한다는 것이다.

그럼 자식 노드의 개수가 0개, 1개, 2개일 때 각각에 대해 삭제 방법을 알아보자.

> **1. 삭제할 노드의 자식 노드의 개수 = 0개**
>
> 삭제할 노드가 리프 노드이면 그냥 부모 노드와의 연결을 끊으면 된다.
>
> **2. 삭제할 노드의 자식 노드의 개수 = 1개**
>
> 삭제할 노드의 자식 노드가 한 개이면 삭제할 노드의 위치에 자식 노드를 연결하면 된다.
> 
> **3. 삭제할 노드의 자식 노드의 개수 = 2개**
>
> 이전의 두 케이스는 간단하게 처리할 수 있었지만 자식 노드의 개수가 두 개이면 조금 복잡해진다.
>
> 삭제할 노드의 위치에 올 노드를 정해야하는데, 삭제될 노드의 왼쪽 서브트리보단 크고 오른쪽 서브트리보단 작은 값을 가진 노드여야한다.
>
> 이 조건을 만족하는 노드는 딱 두 개가 있다.
>
> - 삭제할 노드의 오른쪽 서브트리에서 가장 왼쪽에 있는 노드
> - 삭제할 노드의 왼쪽 서브트리에서 가장 오른쪽에 있는 노드
>
> 나는 왼쪽 서브트리의 가장 오른쪽에 있는 노드를 선택하는 쪽으로 코드를 작성하였다.

노드를 삭제하는 함수 `removeNode`를 구현하기 전에, 어떤 노드의 왼쪽 서브트리에서 가장 오르쪽에 있는 노드를 반환하는 함수 `searchMaxNode`를 구현하였다.

```cpp
Node* searchMaxNode (Node* node)
{
    if (node->right == NULL) return node; // 가장 오른쪽 노드이면 해당 노드를 반환
    else return searchMaxNode(node->right); // 오른쪽 자식 노드가 있으면 재귀적으로 탐색
}
```

다음은 노드를 삭제하는 함수의 코드이다.

```cpp
Node* removeNode (Node* root, Node* parent, int v)
{
    if (tree == NULL) return NULL;
    
    Node* removedNode = NULL; // 삭제된 노드를 반환하기 위함.
    
    // 삭제할 노드를 탐색
    if (root->value > v) removedNode = removeNode(root->left, root, v);
    else if (root->value < v) removedNode = removeNode(root->right, root, v);
    else // 찾았으면 노드를 삭제한다.
    {
        removedNode = root;
        
        // 자식 노드 = 0개
        if (root->leftChild == NULL && root->rightChild == NULL)
        {
            if (parent->leftChild == root) parent->leftChild = NULL;
            if (parent->rightChild == root) parent->rightChild = NULL;
        }
        
        // 자식 노드 = 1개
        else if (root->leftChild == NULL)
        {
            if (parent->leftChild == root) parent->leftChild = root->rightChild;
            else parent->rightChild = root->rightChild;
        }
        else if (root->rightChild == NULL)
        {
            if (parent->leftChild == root) parent->leftChild = root->leftChild;
            else parent->rightChild = root->leftChild;
        }
        
        // 자식 노드 = 2개
        else
        {
            Node* replaceNode = removeNode(root, NULL, searchMaxNode(root->left)->value); // 삭제할 노드 자리에 들어갈 노드를 찾고, 해당 노드를 삭제
            root->data = replaceNode->data; // 삭제할 노드의 값을 대체할 노드의 값으로 갱신한다.
        }
    }
    
    return removedNode;
}
```

---

### 2-5. 순회 구현하기

전위 순회, 중위 순회, 후위 순회를 각각 구현해보자.

**1. 전위 순회 (preorder)**

```cpp
void preOrder (Node* root, vector<int>& vec)
{
    if (root == NULL) return;
    vec.push_back(root->value);
    preOrder(root->leftChild, vec);
    preOrder(root->rightChild, vec);
}
```

**2. 중위 순회 (inorder)**

```cpp
void inOrder (Node* root, vector<int>& vec)
{
    if (root == NULL) return;
    inOrder(root->leftChild, vec);
    vec.push_back(root->data);
    inOrder(root->rightChild, vec);
}
```

**3. 후위 순회 (postorder)**

```cpp
void postOrder (Node* root, vector<int>& vec)
{
    if (root == NULL) return;
    postOrder(root->leftChild, vec);
    postOrder(root->rightChild, vec);
    vec.push_back(root->data);
}
```


