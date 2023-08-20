# Algo-and-DS

用C++來練習基本的演算法與資料結構

| Sort Algo | Bubble | Insertion | Selection | Counting | Merge  | Quick  | Heap |
|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|
| 平均時間  | O(n^2)  | O(n^2)  | O(n^2)  | O(n+m)  | O(nlogn)  | O(nlogn)  | O(nlogn) |
| 最差時間  | O(n^2)  | O(n^2)  | O(n^2)  | O(n+m)  | O(nlogn)  | O(n^2)  | O(nlogn) |
| 額外空間  | O(1)    | O(1)    | O(1)    | O(n+m)  | O(n)      | O(1)  | O(1)     |

通常情況下，因CPU cache，quick sort會比merge sort表現較佳，但quick sort有機會面臨最差情況(如快排序好的或選到不好的pivot)，此時最好切換成insertion sort。

(1) Stable sorting
- Bubble sort : O(n^2)
- Insertion sort : O(n^2)
- Counting sort : O(n+k)
- Merge sort : O(nlogn)

(2) Unstable sorting
- Selection sort : O(n^2)
- Quick sort : O(nlogn)

| DS | Singly linked list | Doubly linked list | Stack | Queue | Hash map  | Skip list |
|:--:|:--:|:--:|:--:|:--:|:--:|:--:|
| 查找  | O(n)  | O(n)  | O(n)  | O(n)  | O(1)  | O(logn)  | 
| 插入  | O(1)  | O(1)  | O(1)  | O(1)  | O(1)  | O(logn)  | 
| 刪除  | O(n)    | O(n)    | O(1)    | O(1)  | O(1)      | O(logn)  | 

stack跟queue只有在刪除第一個(或最後一個)元素時才能達到O(1)，而Hash map受限於Array與Collision的問題，表現可能會達到O(n)，而Skip list若沒有做好平衡，也可能會變成O(n)

(3) List
- Singly linked list
- Doubly linked list
- Stack
- Queue
- Hash Map
- Skip List ~TODO
  
(4) Heap
- Max heap ~TODO
- Min heap ~TODO
- Priority queue ~TODO
- Heap sort : O(nlogn) ~TODO

(5) Tree
- Binary search tree
- AVL tree
- RB tree
- Splay tree ~TODO
- B tree ~TODO
- B+ tree ~TODO
- Radix tree ~TODO
- Maple tree ~TODO

(6) Graph ~TODO

