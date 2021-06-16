#ifndef LIST_H
#define LIST_H

#include "structs.h"

void addChr(List **start, List **end, List **line, List **row, List **col, Stack **bottomUndo, Stack **bottomRedo, char c, int i, int ok);
void delOneChr(List **start, List **end, List **row, List **col);
List *delSeq(List **start, List **end, List **row, List **col, Stack **bottom, int j);
void addSeq(List **start, List **end, List **placeStart, List **placeEnd, List **startSeq, List **endSeq);
void addByKey(List **start, List **end, List **col, char c);

#endif