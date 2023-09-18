#include "queue.h"

#include <stdlib.h>

int createQueue(struct Queue *queue) {
  queue->head = NULL;
  queue->tail = NULL;
  queue->size = 0;

  return 0;
}

int enqueue(struct Queue *queue, void *data) {
  struct QueueNode *node = malloc(sizeof(struct QueueNode));
  node->data = data;
  node->next = NULL;

  if (queue->size == 0) {
    queue->head = node;
    queue->tail = node;
  } else {
    queue->tail->next = node;
    queue->tail = node;
  }

  queue->size++;

  return 0;
}

int dequeue(struct Queue *queue, void **data) {
  if (queue->size == 0) {
    return 1;
  }

  *data = queue->head->data;

  struct QueueNode *node = queue->head;
  queue->head = queue->head->next;
  free(node);

  queue->size--;

  return 0;
}

int destroyQueue(struct Queue *queue) {
  while (queue->size > 0) {
    struct QueueNode *node = queue->head;
    queue->head = queue->head->next;
    free(node);

    queue->size--;
  }

  return 0;
}