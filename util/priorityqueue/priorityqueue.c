#include "priorityqueue.h"

#include <stdlib.h>

int createPriorityQueue(struct PriorityQueue *queue) {
  queue->head = NULL;
  queue->tail = NULL;
  queue->size = 0;

  return 0;
}

int enqueueWithPriority(struct PriorityQueue *queue, void *data, int priority) {
  struct PriorityQueueNode *node = malloc(sizeof(struct PriorityQueueNode));
  node->data = data;
  node->next = NULL;
  node->priority = priority;

  if (queue->size == 0) {
    queue->head = node;
    queue->tail = node;
  } else {
    if (priority < queue->head->priority) {
      node->next = queue->head;
      queue->head = node;
    } else {
      struct PriorityQueueNode *current = queue->head;
      while (current->next != NULL && current->next->priority <= priority) {
        current = current->next;
      }
      node->next = current->next;
      current->next = node;
    }
  }

  queue->size++;

  return 0;
}

int dequeueWithPriority(struct PriorityQueue *queue, void **data) {
  if (queue->size == 0) {
    return 1;
  }

  *data = queue->head->data;

  struct PriorityQueueNode *node = queue->head;
  queue->head = queue->head->next;
  free(node);

  queue->size--;

  return 0;
}

int destroyPriorityQueue(struct PriorityQueue *queue) {
  while (queue->size > 0) {
    struct PriorityQueueNode *node = queue->head;
    queue->head = queue->head->next;
    free(node);

    queue->size--;
  }

  return 0;
}