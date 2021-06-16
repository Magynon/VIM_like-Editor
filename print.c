#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "stack.h"
#include "print.h"

// prints stack last-first
void printStack(Stack *bottomUndo, Stack *bottomRedo)
{
    printf("CURRENT STACK: ");
    int ok = 0;
    Stack *tmp = bottomUndo;
    if (tmp == NULL)
    {
        printf("EMPTY");
    }
    while (tmp)
    {
        ok++;
        printf("\"%s\" ", tmp->x);
        tmp = tmp->asc;
    }
    printf("\n");

    printf("CURRENT UNDO STACK: ");
    ok = 0;
    tmp = bottomRedo;
    if (tmp == NULL)
    {
        printf("EMPTY\n");
    }
    while (tmp)
    {
        ok++;
        printf("\"%s\" ", tmp->x);
        tmp = tmp->asc;
    }
    printf("\n\n");
}

// prints list ascending
void printList(List *start)
{
    FILE *f = fopen("editor.out", "w");
    //fprintf(f, "\nCURRENT LIST: \n");
    List *tmp = start;
    char aux;

    while (tmp)
    {
        if (tmp != start)
        {
            if ((tmp->x == '\n' && tmp->desc->x == '\n') || tmp->x == 'p' || tmp->x == 'P')
            {
                ;
            }
            else
            {
                if (isalpha(tmp->x) || tmp->x == '\n')
                {
                    fprintf(f, "%c", tmp->x);
                }
            }
        }
        else
        {
            if (isalpha(tmp->x) || tmp->x == '\n')
            {
                fprintf(f, "%c", tmp->x);
            }
        }
        aux = tmp->x;
        tmp = tmp->asc;
    }
    if (aux != '\n')
    {
        fprintf(f, "\n");
    }

    fclose(f);
}

void printCurrentRow(List *row, List *col)
{
    FILE *f = fopen("editor.out", "a");
    fprintf(f, "CURRENT ROW: ");
    List *tmp = row;
    while (tmp->x != '\n')
    {
        fprintf(f, "%c", tmp->x);
        tmp = tmp->asc;
    }
    fprintf(f, "\n");
    fprintf(f, "CURRENT CHAR: \"%c\"\n", col->x);
    fclose(f);
}

void printSeq(List *startSeq, List *endSeq)
{
    List *tmp = startSeq;
    printf("SEQUENCE MODIFIED: \"");
    // printf("first letter: \"%c\"", startSeq->x);
    // printf("last letter: \"%c\"", endSeq->x);
    while (tmp != endSeq->asc)
    {
        printf("%c", tmp->x);
        tmp = tmp->asc;
    }
    printf("\"\n");
}

void delOut()
{
    FILE *f = fopen("editor.out", "w");
    //fprintf(f, "\0");
    fclose(f);
}