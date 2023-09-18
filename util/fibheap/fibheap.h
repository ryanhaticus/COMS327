/*
  The files, `fibheap.c` and `fibheap.h`, were adapted on 09/18/2023 from
  https://www.programiz.com/dsa/fibonacci-heap.
*/

#ifndef FIBHEAP_H
#define FIBHEAP_H

struct FibHeapNode {
  int key;
  int degree;
  struct FibHeapNode *left_sibling;
  struct FibHeapNode *right_sibling;
  struct FibHeapNode *parent;
  struct FibHeapNode *child;
  int mark;
  int visited;
};

struct FibHeap {
  int n;
  struct FibHeapNode *min;
  int phi;
  int degree;
};

struct FibHeap *createFibHeap();
void insert(struct FibHeap *H, struct FibHeapNode *new, int val);
struct FibHeapNode *extractMin(struct FibHeap *H);
void consolidate(struct FibHeap *H);
void fibHeapLink(struct FibHeap *H, struct FibHeapNode *y,
                 struct FibHeapNode *x);
struct FibHeapNode *findMinNode(struct FibHeap *H);
void decreaseKey(struct FibHeap *H, struct FibHeapNode *node, int key);
void cut(struct FibHeap *H, struct FibHeapNode *node_to_be_decrease,
         struct FibHeapNode *parent_node);
void cascadingCut(struct FibHeap *H, struct FibHeapNode *parent_node);
void deleteNode(struct FibHeap *H, int dec_key);

#endif