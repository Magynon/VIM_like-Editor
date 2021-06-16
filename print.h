#ifndef PRINT_H
#define PRINT_H

#include "structs.h"

void printStack(Stack *bottomUndo, Stack *bottomRedo);
void printList(List *start);
void printCurrentRow(List *row, List *col);
void printSeq(List *startSeq, List *endSeq);
void delOut();

#endif