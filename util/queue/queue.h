#ifndef QUEUE_H
#define QUEUE_H

struct Node {
  void* data;
  struct Node* next;
};

struct Queue {
  struct Node* head;
  struct Node* tail;
  int size;
};

int createQueue(struct Queue* queue);
int enqueue(struct Queue* queue, void* data);
int dequeue(struct Queue* queue, void** data);
int destroyQueue(struct Queue* queue);

#endif