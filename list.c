#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "print.h"

// adds full sequence to text in the placeStart
void addSeq(List **start, List **end, List **placeStart, List **placeEnd, List **startSeq, List **endSeq)
{
    (*startSeq)->desc = *placeStart;
    (*endSeq)->asc = *placeEnd;
    //printf("inceput: \"%c\"\n", (*endSeq)->x);
    if ((*placeStart) != NULL)
    {
        (*placeStart)->asc = *startSeq;
    }
    else
    {
        *start = *placeStart;
    }
    if ((*placeEnd) != NULL)
    {
        (*placeEnd)->desc = *endSeq;
    }
    else
    {
        *end = *placeEnd;
    }

    if ((*placeStart)->x == '\n')
    {
        (*startSeq)->new_line = 'y';
        (*startSeq)->l_up = (*endSeq)->l_up;
        (*startSeq)->l_down = (*endSeq)->l_down;
        if ((*placeEnd) != NULL)
        {
            (*endSeq)->new_line = 'n';
        }
    }
}

// adds character to text list
void addChr(List **start, List **end, List **line, List **row, List **col, Stack **bottomUndo, Stack **bottomRedo, char c, int i, int ok)
{
    List *garb = (List *)malloc(sizeof(List));
    List *new = (List *)malloc(sizeof(List));
    if (new == *end)
    {
        printf("wow");
    }
    new->x = c;

    if ((*bottomUndo)->asc != NULL)
    {
        if ((*bottomUndo)->asc->x[0] == 'g' && c != '\n')
        {

            new->asc = (*col)->asc;
            new->desc = *col;
            new->asc->desc = new;
            (*col)->asc = new;

            (*col) = new;
            //printList(*start);
            return;
        }
    }

    new->asc = NULL;
    new->desc = *end;
    if (*start == NULL)
    {
        *start = new;
        (*start)->l_down = NULL;
        (*start)->l_up = NULL;
        (*start)->new_line = 'y';
        *line = *start;
        *row = *start;
    }
    else
    {
        if (i == 0)
        {
            (*line)->l_up = new;
            new->l_down = *line;
            new->l_up = NULL;
            new->new_line = 'y';
            *line = new;
        }
        (*end)->asc = new;
    }
    if (ok == 1)
    {
        // save first ch address for undo
        (*bottomUndo)->start_seq[0] = new;
        (*bottomUndo)->old_col[0] = new->desc;
        (*bottomUndo)->old_row[0] = new->l_down;
    }
    (*bottomUndo)->end_seq[0] = new;
    *end = new;
}

// deletes one character
void delOneChr(List **start, List **end, List **row, List **col)
{
    List *tmp = *col;
    *col = tmp->asc;

    if (tmp->new_line == 'y')
    {
        *row = tmp->asc;
        if (tmp->asc != NULL)
        {
            tmp->asc->new_line = 'y';
            tmp->asc->l_up = tmp->l_up;
            tmp->asc->l_down = tmp->l_down;
        }
        if (tmp->l_down == NULL)
        {
            tmp->l_up->l_down = tmp->asc;
        }
        if (tmp->l_up == NULL)
        {
            tmp->l_down->l_up = tmp->asc;
        }
        if (tmp->l_down != NULL && tmp->l_up != NULL)
        {
            tmp->l_down->l_up = tmp->asc;
            tmp->l_up->l_down = tmp->asc;
        }
    }

    if (tmp->asc != NULL)
    {
        tmp->asc->desc = tmp->desc;
    }
    else
    {
        (*end) = tmp->desc;
    }
    if (tmp->desc != NULL)
    {
        tmp->desc->asc = tmp->asc;
    }
    else
    {
        (*start) = tmp->asc;
    }

    if (tmp->x == '\n')
    {
        *row = (*row)->l_down;
        if ((*row)->l_up->l_up != NULL)
        {
            (*row)->l_up->l_up->l_down = (*row);
        }
        (*row)->l_up->new_line = 'n';
        (*row)->l_up = (*row)->l_up->l_up;
    }

    // free(tmp);
}

List *delSeq(List **start, List **end, List **row, List **col, Stack **bottom, int j)
{
    List *tmp = *col;

    for (int i = 0; i < j; i++)
    {
        //printf("tmp: %c si %d si %d\n", tmp->x, i, j);
        tmp = tmp->asc;
    }
    if ((*bottom)->x[0] == 'b')
    {
        tmp = *col;
    }
    else
    {
        tmp = tmp->desc;
    }

    //printf("tmp: %c\n", tmp->x);
    if ((*col)->new_line == 'y')
    {
        tmp->asc->new_line = 'y';
    }

    if (*col != *start && *col != *end)
    {
        (*col)->desc->asc = tmp->asc;
        tmp->asc->desc = (*col)->desc;
        *col = (*col)->desc;
    }
    else
    {
        if (*col == *start)
        {
            tmp->asc->desc = NULL;
            *start = tmp->asc;
            *col = *start;
        }
        if (*col == *end)
        {
            tmp->desc->asc = NULL;
            *end = tmp->desc;
            *col = *end;
        }
    }

    return tmp;
}

// adds character by key
void addByKey(List **start, List **end, List **col, char c)
{
    List *new = (List *)malloc(sizeof(List));
    new->x = c;
    new->asc = *col;
    new->desc = (*col)->desc;
    if ((*col)->desc != NULL)
    {
        (*col)->desc->asc = new;
    }
    else
    {
        (*start) = new;
    }
    if ((*col) != NULL)
    {
        (*col)->desc = new;
    }
    else
    {
        (*end) = new;
    }
    if ((*col)->new_line == 'y' || new == *start)
    {
        (*col)->new_line = 'n';
        new->new_line = 'y';
        new->l_up = (*col)->l_up;
        new->l_down = (*col)->l_down;
    }
    *col = new;
}