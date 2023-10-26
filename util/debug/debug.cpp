#include "debug.h"

#include <cstdio>

FILE* destination = NULL;

int isDebugging() { return destination != NULL; }

void startDebugging() {
  if (destination != NULL) {
    return;
  }
  destination = fopen("debug.txt", "w");
};

void debug(const char* message) {
  if (destination == NULL) {
    return;
  }

  fprintf(destination, "%s\n", message);
  fflush(destination);
}

void debug(const char* identifier, int i) {
  if (destination == NULL) {
    return;
  }

  fprintf(destination, "%s: %d\n", identifier, i);
  fflush(destination);
}

void stopDebugging() {
  if (destination == NULL) {
    return;
  }

  fclose(destination);
  destination = NULL;
}