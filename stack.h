#ifndef STACK_H
#define STACK_H

#include "structs.h"

Stack *addComm(char *c);
void push(Stack **bottom, char *c);
void pop(Stack **bottom);
void undoPop(Stack **bottomUndo, Stack **bottomRedo);
void redoPop(Stack **bottomUndo, Stack **bottomRedo);

#endif