#ifndef OPERATIONS_H
#define OPERATIONS_H
#include "structs.h"

int identifier(char *str);
void undo(List **start, List **end, Stack **bottomUndo, Stack **bottomRedo, char *str, List **row, List **col, int *EMPTY);
void redo(List **start, List **end, Stack **bottomUndo, Stack **bottomRedo, char *str, List **row, List **col, int *EMPTY);
void save(List **start, List **end, Stack **bottomUndo, Stack **bottomRedo, char *str, List **row, List **col, int *EMPTY);
void quit(List **start, List **end, Stack **bottomUndo, Stack **bottomRedo, char *str, List **row, List **col, int *EMPTY);
void backspace(List **start, List **end, Stack **bottomUndo, Stack **bottomRedo, char *str, List **row, List **col, int *EMPTY);
void del_line(List **start, List **end, Stack **bottomUndo, Stack **bottomRedo, char *str, List **row, List **col, int *EMPTY);
void goto_line(List **start, List **end, Stack **bottomUndo, Stack **bottomRedo, char *str, List **row, List **col, int *EMPTY);
void goto_chr(List **start, List **end, Stack **bottomUndo, Stack **bottomRedo, char *str, List **row, List **col, int *EMPTY);
void del_chr(List **start, List **end, Stack **bottomUndo, Stack **bottomRedo, char *str, List **row, List **col, int *EMPTY);
void rep_word(List **start, List **end, Stack **bottomUndo, Stack **bottomRedo, char *str, List **row, List **col, int *EMPTY);
void rep_all(List **start, List **end, Stack **bottomUndo, Stack **bottomRedo, char *str, List **row, List **col, int *EMPTY);
void del_word(List **start, List **end, Stack **bottomUndo, Stack **bottomRedo, char *str, List **row, List **col, int *found);
void del_all(List **start, List **end, Stack **bottomUndo, Stack **bottomRedo, char *str, List **row, List **col, int *EMPTY);

#endif