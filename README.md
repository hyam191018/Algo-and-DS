# DataStructures and Algorithms

用C++來練習基本的資料結構與演算法

(1) Stable sorting
- Bubble sort : O(n^2)
- Insertion sort : O(n^2)
- Counting sort : O(n+k)
- Merge sort : O(nlogn) - Top-down

(2) Unstable sorting
- Selection sort : O(n^2)
- Quick sort : O(nlogn)

(3) List
- Singly linked list
- Doubly linked list
- Stack
- Queue
- Hash Map
  
(4) Heap
- Max heap
- Min heap
- Heap sort : O(nlogn) - in sort.h

(5) Tree
- Binary search tree
- AVL tree
- Splay tree
- RB tree

(6) TODO
- Skip List
- Priority queue
- B tree
- B+ tree
- Radix tree
- Maple tree
- Graph

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

| DS | Bineary search tree | AVL tree | Read-Black tree | Splay tree |
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
