#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

struct PriorityQueueNode {
  void* data;
  int priority;
  struct PriorityQueueNode* next;
};

struct PriorityQueue {
  struct PriorityQueueNode* head;
  struct PriorityQueueNode* tail;
  int size;
};

int createPriorityQueue(struct PriorityQueue* queue);
int enqueueWithPriority(struct PriorityQueue* queue, void* data, int priority);
int dequeueWithPriority(struct PriorityQueue* queue, void** data);
int destroyPriorityQueue(struct PriorityQueue* queue);

#endif