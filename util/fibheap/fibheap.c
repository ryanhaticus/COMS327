/*
  The files, `fibheap.c` and `fibheap.h`, were adapted on 09/18/2023 from
  https://www.programiz.com/dsa/fibonacci-heap.
*/

#include "fibheap.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct FibHeap *createFibHeap() {
  struct FibHeap *H;
  H = (struct FibHeap *)malloc(sizeof(struct FibHeap));
  H->n = 0;
  H->min = NULL;
  H->phi = 0;
  H->degree = 0;
  return H;
}

void destroyHeap(struct FibHeap *H) {
  struct FibHeapNode *x = H->min;
  struct FibHeapNode *y;
  if (x != NULL) {
    do {
      y = x;
      x = x->right_sibling;
      deleteNode(H, y->key);
    } while (x != H->min);
  }

  free(H);
}

// Printing the heap
void printHeap(struct FibHeapNode *n) {
  struct FibHeapNode *x;
  for (x = n;; x = x->right_sibling) {
    if (x->child == NULL) {
      printf("node with no child (%d) \n", x->key);
    } else {
      printf("FibHeapNode(%d) with child (%d)\n", x->key, x->child->key);
      printHeap(x->child);
    }
    if (x->right_sibling == n) {
      break;
    }
  }
}

// Inserting nodes
void insert(struct FibHeap *H, struct FibHeapNode *new, int val) {
  new = (struct FibHeapNode *)malloc(sizeof(struct FibHeapNode));
  new->key = val;
  new->degree = 0;
  new->mark = 0;
  new->parent = NULL;
  new->child = NULL;
  new->visited = 0;
  new->left_sibling = new;
  new->right_sibling = new;
  if (H->min == NULL) {
    H->min = new;
  } else {
    H->min->left_sibling->right_sibling = new;
    new->right_sibling = H->min;
    new->left_sibling = H->min->left_sibling;
    H->min->left_sibling = new;
    if (new->key < H->min->key) {
      H->min = new;
    }
  }
  (H->n)++;
}

// Find min node
struct FibHeapNode *findMinNode(struct FibHeap *H) {
  if (H == NULL) {
    printf(" \n Fibonacci heap not yet created \n");
    return NULL;
  } else
    return H->min;
}

// Union operation
struct FibHeap *unionHeap(struct FibHeap *H1, struct FibHeap *H2) {
  struct FibHeap *Hnew;
  Hnew = createFibHeap();
  Hnew->min = H1->min;

  struct FibHeapNode *temp1, *temp2;
  temp1 = Hnew->min->right_sibling;
  temp2 = H2->min->left_sibling;

  Hnew->min->right_sibling->left_sibling = H2->min->left_sibling;
  Hnew->min->right_sibling = H2->min;
  H2->min->left_sibling = Hnew->min;
  temp2->right_sibling = temp1;

  if ((H1->min == NULL) || (H2->min != NULL && H2->min->key < H1->min->key))
    Hnew->min = H2->min;
  Hnew->n = H1->n + H2->n;
  return Hnew;
}

// Calculate the degree
int cal_degree(int n) {
  int count = 0;
  while (n > 0) {
    n = n / 2;
    count++;
  }
  return count;
}

// Consolidate function
void consolidate(struct FibHeap *H) {
  int degree, i, d;
  degree = cal_degree(H->n);
  struct FibHeapNode *A[degree], *x, *y;
  for (i = 0; i <= degree; i++) {
    A[i] = NULL;
  }
  x = H->min;
  do {
    d = x->degree;
    while (A[d] != NULL) {
      y = A[d];
      if (x->key > y->key) {
        struct FibHeapNode *exchange_help;
        exchange_help = x;
        x = y;
        y = exchange_help;
      }
      if (y == H->min) H->min = x;
      fibHeapLink(H, y, x);
      if (y->right_sibling == x) H->min = x;
      A[d] = NULL;
      d++;
    }
    A[d] = x;
    x = x->right_sibling;
  } while (x != H->min);

  H->min = NULL;
  for (i = 0; i < degree; i++) {
    if (A[i] != NULL) {
      A[i]->left_sibling = A[i];
      A[i]->right_sibling = A[i];
      if (H->min == NULL) {
        H->min = A[i];
      } else {
        H->min->left_sibling->right_sibling = A[i];
        A[i]->right_sibling = H->min;
        A[i]->left_sibling = H->min->left_sibling;
        H->min->left_sibling = A[i];
        if (A[i]->key < H->min->key) {
          H->min = A[i];
        }
      }
      if (H->min == NULL) {
        H->min = A[i];
      } else if (A[i]->key < H->min->key) {
        H->min = A[i];
      }
    }
  }
}

// Linking
void fibHeapLink(struct FibHeap *H, struct FibHeapNode *y,
                 struct FibHeapNode *x) {
  y->right_sibling->left_sibling = y->left_sibling;
  y->left_sibling->right_sibling = y->right_sibling;

  if (x->right_sibling == x) H->min = x;

  y->left_sibling = y;
  y->right_sibling = y;
  y->parent = x;

  if (x->child == NULL) {
    x->child = y;
  }
  y->right_sibling = x->child;
  y->left_sibling = x->child->left_sibling;
  x->child->left_sibling->right_sibling = y;
  x->child->left_sibling = y;
  if ((y->key) < (x->child->key)) x->child = y;

  (x->degree)++;
}

// Extract min
struct FibHeapNode *extractMin(struct FibHeap *H) {
  if (H->min == NULL)
    printf("\n The heap is empty");
  else {
    struct FibHeapNode *temp = H->min;
    struct FibHeapNode *pntr;
    pntr = temp;
    struct FibHeapNode *x = NULL;
    if (temp->child != NULL) {
      x = temp->child;
      do {
        pntr = x->right_sibling;
        (H->min->left_sibling)->right_sibling = x;
        x->right_sibling = H->min;
        x->left_sibling = H->min->left_sibling;
        H->min->left_sibling = x;
        if (x->key < H->min->key) H->min = x;
        x->parent = NULL;
        x = pntr;
      } while (pntr != temp->child);
    }

    (temp->left_sibling)->right_sibling = temp->right_sibling;
    (temp->right_sibling)->left_sibling = temp->left_sibling;
    H->min = temp->right_sibling;

    if (temp == temp->right_sibling && temp->child == NULL)
      H->min = NULL;
    else {
      H->min = temp->right_sibling;
      consolidate(H);
    }
    H->n = H->n - 1;
    return temp;
  }
  return H->min;
}

void cut(struct FibHeap *H, struct FibHeapNode *node_to_be_decrease,
         struct FibHeapNode *parent_node) {
  if (node_to_be_decrease == node_to_be_decrease->right_sibling)
    parent_node->child = NULL;

  node_to_be_decrease->left_sibling->right_sibling =
      node_to_be_decrease->right_sibling;
  node_to_be_decrease->right_sibling->left_sibling =
      node_to_be_decrease->left_sibling;
  if (node_to_be_decrease == parent_node->child)
    parent_node->child = node_to_be_decrease->right_sibling;
  (parent_node->degree)--;

  node_to_be_decrease->left_sibling = node_to_be_decrease;
  node_to_be_decrease->right_sibling = node_to_be_decrease;
  H->min->left_sibling->right_sibling = node_to_be_decrease;
  node_to_be_decrease->right_sibling = H->min;
  node_to_be_decrease->left_sibling = H->min->left_sibling;
  H->min->left_sibling = node_to_be_decrease;

  node_to_be_decrease->parent = NULL;
  node_to_be_decrease->mark = 0;
}

void cascadingCut(struct FibHeap *H, struct FibHeapNode *parent_node) {
  struct FibHeapNode *aux;
  aux = parent_node->parent;
  if (aux != NULL) {
    if (parent_node->mark == 0) {
      parent_node->mark = 1;
    } else {
      cut(H, parent_node, aux);
      cascadingCut(H, aux);
    }
  }
}

void decreaseKey(struct FibHeap *H, struct FibHeapNode *node_to_be_decrease,
                 int new_key) {
  struct FibHeapNode *parent_node;
  if (H == NULL) {
    printf("\n FIbonacci heap not created ");
    return;
  }
  if (node_to_be_decrease == NULL) {
    printf("Node is not in the heap");
  }

  else {
    if (node_to_be_decrease->key < new_key) {
      printf("\n Invalid new key for decrease key operation \n ");
    } else {
      node_to_be_decrease->key = new_key;
      parent_node = node_to_be_decrease->parent;
      if ((parent_node != NULL) &&
          (node_to_be_decrease->key < parent_node->key)) {
        printf("\n cut called");
        cut(H, node_to_be_decrease, parent_node);
        printf("\n cascading cut called");
        cascadingCut(H, parent_node);
      }
      if (node_to_be_decrease->key < H->min->key) {
        H->min = node_to_be_decrease;
      }
    }
  }
}

void *findNode(struct FibHeap *H, struct FibHeapNode *n, int key, int new_key) {
  struct FibHeapNode *find_use = n;
  struct FibHeapNode *f = NULL;
  find_use->visited = 1;
  if (find_use->key == key) {
    find_use->visited = 0;
    f = find_use;
    decreaseKey(H, f, new_key);
  }
  if (find_use->child != NULL) {
    findNode(H, find_use->child, key, new_key);
  }
  if ((find_use->right_sibling->visited != 1)) {
    findNode(H, find_use->right_sibling, key, new_key);
  }

  find_use->visited = 0;

  return f;
}

struct FibHeap *insert_procedure() {
  struct FibHeap *temp;
  int no_of_nodes, ele, i;
  struct FibHeapNode *new_node = NULL;
  temp = (struct FibHeap *)malloc(sizeof(struct FibHeap));
  temp = NULL;
  if (temp == NULL) {
    temp = createFibHeap();
  }
  printf(" \n enter number of nodes to be insert = ");
  scanf("%d", &no_of_nodes);
  for (i = 1; i <= no_of_nodes; i++) {
    printf("\n node %d and its key value = ", i);
    scanf("%d", &ele);
    insert(temp, new_node, ele);
  }
  return temp;
}

void deleteNode(struct FibHeap *H, int dec_key) {
  struct FibHeapNode *p = NULL;
  if (H->min == NULL) {
    printf("\n The heap is empty");
    return;
  }

  p = findNode(H, H->min, dec_key, 0);

  if (p == NULL) {
    printf("\n The node is not present in the heap");
    return;
  }

  struct FibHeapNode *node = extractMin(H);
  free(node);
}