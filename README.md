# DataStructures and Algorithms

用C++來練習基本的資料結構與演算法

(1) Stable sorting
- Bubble sort : O(n^2)
- Insertion sort : O(n^2)
- Counting sort : O(n+k)
- Merge sort : O(nlogn)

註: 使用Top-down的方式

(2) Unstable sorting
- Selection sort : O(n^2)
- Quick sort : O(nlogn)

(3) List
- Singly linked list
- Doubly linked list
- Stack
- Queue
- Hash Map
- Skip List ~TODO
  
(4) Heap
- Max heap
- Min heap
- Heap sort : O(nlogn) 註: 在 sort.h
- Priority queue ~TODO

(5) Tree
- Binary search tree
- AVL tree

註: 為BST的進階版，每次insert和remove都要動態調整root，另外，對於要如何調整LL、LR、RR、RL最好用畫圖的方式判斷。

- RB tree

註: 因為root到leaf經過的黑色node數量相同且不能有紅色node相連，故最長路徑(紅黑交錯)不會超過最短路徑(全是黑)的兩倍。
另外程式的實現難度較高，insert時須考慮uncle node，remove時須考慮brother(sibling) node

- Splay tree ~TODO 註: 適合cache、garbage collection!
- B tree ~TODO
- B+ tree ~TODO
- Radix tree ~TODO
- Maple tree ~TODO

(6) Graph ~TODO

## 補充

| Sort Algo | Bubble | Insertion | Selection | Counting | Merge  | Quick  | Heap |
|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|
| 平均時間  | O(n^2)  | O(n^2)  | O(n^2)  | O(n+m)  | O(nlogn)  | O(nlogn)  | O(nlogn) |
| 最差時間  | O(n^2)  | O(n^2)  | O(n^2)  | O(n+m)  | O(nlogn)  | O(n^2)  | O(nlogn) |
| 額外空間  | O(1)    | O(1)    | O(1)    | O(n+m)  | O(n)      | O(1)  | O(1)     |

通常情況下，因CPU cache，quick sort會比merge sort表現較佳，但quick sort有機會面臨最差情況(如快排序好的或選到不好的pivot)，此時最好切換成insertion sort。

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

BST跟Splay tree在某些情況可能會變成Linked list，導致存取效率變成O(n)，其他普遍都是趨近O(logn)，BST是最基本的實現，而AVL tree、RB tree與Splay tree都有各自的優點:

AVL tree保證了平衡性(左右子樹最多相差1)，能最有效率的提升search速度，但在insert與remove時，需額外花時間做平衡。

RB tree犧牲了一點平衡性(左右子樹最多相差1倍)，雖然降低了search的速度，但提昇了insert與remove的速度，因為不會每次操作都要平衡。

Splay tree最大的優點就是越常存取的node會越靠近root，非常適合用作cache的設計。

在測試中(Linked list、BST、AVL Tree、RB Tree)，RB Tree的效率最好，再來是Linked list、BST，最後是AVL Tree。AVL Tree可能是設計問題，Top down的實作方式會導致每次rebalance時都要從root重新計算高度，花費太多時間了。
