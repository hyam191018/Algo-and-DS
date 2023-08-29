# DataStructures and Algorithms

用C++來練習基本的資料結構與演算法

(1) Stable sorting
- Bubble sort
- Insertion sort
- Counting sort
- Merge sort (Top-down)

(2) Unstable sorting
- Selection sort
- Quick sort

(3) Linked List
- Singly linked list
- Doubly linked list
- Stack
- Queue
- Hash Map
- Skip List
  
(4) Heap
- Max heap
- Min heap
- Heap sort (in sort.h)

(5) Tree
- Binary search tree
- AVL tree
- Splay tree
- Red Black tree

(6) TODO
- Radix tree
- Maple tree

## 補充

| Sort Algo | Bubble | Insertion | Selection | Counting | Merge  | Quick  | Heap |
|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|
| 平均時間  | O(n^2)  | O(n^2)  | O(n^2)  | O(n+m)  | O(nlogn)  | O(nlogn)  | O(nlogn) |
| 最差時間  | O(n^2)  | O(n^2)  | O(n^2)  | O(n+m)  | O(nlogn)  | O(n^2)  | O(nlogn) |
| 額外空間  | O(1)    | O(1)    | O(1)    | O(n+m)  | O(n)      | O(1)  | O(1)     |

通常情況下，因為CPU cache的性質，quick sort會比merge sort表現較佳，但quick sort有機會面臨最差情況(如快排序好的或選到不好的pivot)，此時最好切換成insertion sort。

---

| DS | Singly linked list | Doubly linked list | Stack | Queue | Hash map  | Skip list |
|:--:|:--:|:--:|:--:|:--:|:--:|:--:|
| 查找  | O(n)  | O(n)  | O(n)  | O(n)  | O(1)  | O(logn)  | 
| 插入  | O(1)  | O(1)  | O(1)  | O(1)  | O(1)  | O(logn)  | 
| 刪除  | O(n)    | O(n)    | O(1)    | O(1)  | O(1)      | O(logn)  | 

stack跟queue只有在刪除第一個(或最後一個)元素時才能達到O(1)，而Hash map受限於Array與Collision的問題，表現可能會達到O(n)，而Skip list若沒有做好平衡，也可能會變成O(n)

---

| DS | Bineary search tree | AVL tree | Red black tree | Splay tree |
|:--:|:--:|:--:|:--:|:--:|
| 查找  | O(logn)  | O(logn)  | O(logn)  | O(logn)  |
| 插入  | O(logn)  | O(logn)  | O(logn)  | O(logn)  |
| 刪除  | O(logn)  | O(logn)  | O(logn)  | O(logn)  |
| 最差  | O(n)  | O(logn)  | O(logn)  | O(n)  |

BST跟Splay tree在某些情況可能會變成Linked list，導致存取效率變成O(n)，其他普遍都是趨近O(logn)，BST是二元搜尋法最基本的實現，而AVL tree、RB tree與Splay tree都有各自的優點:

AVL tree保證了平衡性(左右子樹最多相差1)，理論上會有最佳的search速度(相當接近完全二元樹)，但在insert與remove時，需額外花時間做平衡，包含計算每個node的高度，和藉由rotation達成AVL tree的條件。

RB tree犧牲了一點平衡性(最長路徑最多為最短路徑的兩倍)，雖然在search上沒辦法勝過AVL tree，但能有效提升insert與remove的速度(因為不是每個操作都要平衡)。

Splay tree最大的優點就是越常存取的node會越靠近root，非常適合用作cache/GC。

實現上的難易度: BST < Splay tree < AVL tree << RB tree

---

執行app/SpeedTest，會執行10萬次的隨機insert/search/remove:

在insert的測試中: 

1. Binear search tree: 32 ms
2. Red black tree: 34 ms
3. Splay tree: 162 ms
4. Skip list: 216 ms
5. Linked list: 3887 ms
6. AVL tree: 38312 ms

在search的測試中: 

1. AVL tree: 21 ms
2. Binear search tree: 23 ms
3. Red black tree: 26 ms
4. Splay tree: 148 ms
5. Skip list: 241 ms
6. Linked list: 5076 ms

在remove的測試中: 

1. Binear search tree: 23 ms
2. Red black tree: 26 ms
3. Splay tree: 64 ms
4. Skip list: 3659 ms
5. Linked list: 2714 ms
6. AVL tree: 14266 ms
