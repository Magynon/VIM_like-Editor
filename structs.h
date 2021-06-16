#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct List
{
    char x;
    char new_line;
    struct List *asc;
    struct List *desc;
    struct List *l_up;
    struct List *l_down;
} List;

typedef struct Stack
{
    char x[22];
    struct Stack *asc;
    List *start_seq[20];
    List *end_seq[20];
    int number_of_addresses;
    List *old_col[20];
    List *old_row[20];
} Stack;

#endif