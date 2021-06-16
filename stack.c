#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

// initializes stack element
Stack *addComm(char *c)
{
    Stack *new = (Stack *)malloc(sizeof(Stack));
    c[strlen(c) - 1] = '\0';
    strcpy(new->x, c);
    return new;
}

// adds element to stack
void push(Stack **bottom, char *c)
{
    Stack *new = addComm(c);
    new->asc = *bottom;
    *bottom = new;
}

// pops command from stack
void pop(Stack **bottom)
{
    if (*bottom == NULL)
    {
        printf("The stack is empty!\n");
        return;
    }
    Stack *tmp = *bottom;
    *bottom = tmp->asc;
    free(tmp);
}

void undoPop(Stack **bottomUndo, Stack **bottomRedo)
{
    Stack *tmp = *bottomUndo;
    *bottomUndo = tmp->asc;
    tmp->asc = *bottomRedo;
    *bottomRedo = tmp;
}

void redoPop(Stack **bottomUndo, Stack **bottomRedo)
{
    Stack *tmp = *bottomRedo;
    *bottomRedo = tmp->asc;
    tmp->asc = *bottomUndo;
    *bottomUndo = tmp;
}