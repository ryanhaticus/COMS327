#ifndef DEBUG_H
#define DEBUG_H

void startDebugging();
void debug(const char* message);
void debug(const char* identifier, int i);
void stopDebugging();
int isDebugging();

#endif