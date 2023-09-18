#ifndef QUEUE_H
#define QUEUE_H

struct QueueNode {
  void* data;
  struct QueueNode* next;
};

struct Queue {
  struct QueueNode* head;
  struct QueueNode* tail;
  int size;
};

int createQueue(struct Queue* queue);
int enqueue(struct Queue* queue, void* data);
int dequeue(struct Queue* queue, void** data);
int destroyQueue(struct Queue* queue);

#endif