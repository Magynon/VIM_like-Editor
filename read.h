#ifndef READ_H
#define READ_H

#include "structs.h"
#include "list.h"

void commandEditor(List **start, List **end, Stack **bottomUndo, Stack **bottomRedo, char *str, List **row, List **col);
void insert(List **start, List **end, Stack **bottomUndo, Stack **bottomRedo, List **row, List **col, FILE *f);
void read(List **start, List **end, List **line, List **row, List **col, Stack **bottomUndo, Stack **bottomRedo);

#endif