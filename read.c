#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operations.h"
#include "read.h"
#include "stack.h"
#include "print.h"
#include "list.h"

void undoEditor(List **start, List **end, Stack **bottomUndo, Stack **bottomRedo, List **row, List **col)
{
    int i;
    if (*bottomRedo == NULL)
    {
        printf("Stack empty!\n");
        return;
    }

    // works for anything except gl and gc
    if ((*bottomRedo)->x[0] == 'g')
    {
        *col = (*bottomRedo)->old_col[0];
        *row = (*bottomRedo)->old_row[0];
    }
    else
    {
        if ((*bottomRedo)->x[0] == 'i')
        {
            (*bottomRedo)->old_col[0]->asc = NULL;
        }
        for (i = 0; i <= (*bottomRedo)->number_of_addresses - 1; i++)
        {
            List *placeStart = (*bottomRedo)->old_col[i];
            List *placeEnd = (*bottomRedo)->old_row[i];

            List *startSeq = (*bottomRedo)->start_seq[i];
            List *endSeq = (*bottomRedo)->end_seq[i];

            //printf("ch: %c\n", placeStart->x);
            addSeq(start, end, &placeStart, &placeEnd, &startSeq, &endSeq);
        }
        //printList(*start);
        //printStack(*bottomUndo, *bottomRedo);
    }
}

void commandEditor(List **start, List **end, Stack **bottomUndo, Stack **bottomRedo, char *str, List **row, List **col)
{
    void (*functions[13])(List **, List **, Stack **, Stack **, char *, List **, List **, int *) =
        {undo, redo, save, quit, backspace, del_line, goto_line, goto_chr,
         del_chr, rep_word, rep_all, del_word, del_all};

    int function = identifier(str) - 1;
    int garbage = -1; // dummy value
    (*functions[function])(start, end, bottomUndo, bottomRedo, str, row, col, &garbage);
    if (function == 0)
    {
        undoEditor(start, end, bottomUndo, bottomRedo, row, col);
    }
}

void insert(List **start, List **end, Stack **bottomUndo, Stack **bottomRedo, List **row, List **col, FILE *f)
{
    char str[22];
    while (fgets(str, 22, f) != NULL)
    {
        if (str[0] == ':' && str[1] == ':')
        {
            return;
        }
        if (str[0] != '\n')
        {
            // if undo redo save or quit dont add to stack
            if ((str[0] == 'u' || str[0] == 'r' || str[0] == 's' || str[0] == 'q') && str[1] == '\n')
            {
                ;
            }
            else
            {
                push(bottomUndo, str);
            }
            // start editing text accordingly

            commandEditor(start, end, bottomUndo, bottomRedo, str, row, col);
        }
    }
}

void read(List **start, List **end, List **line, List **row, List **col, Stack **bottomUndo, Stack **bottomRedo)
{
    char str[50], input[3];
    int ok = 1, i;
    input[0] = 'i';
    input[1] = '\n';
    input[2] = '\0';
    FILE *f;
    f = fopen("editor.in", "r");
    if (f)
    {
        while (fgets(str, 30, f) != NULL)
        {
            // read line
            if (str[0] == ':' && str[1] == ':')
            {

                // INSERT MODE
                //printList(*start);
                insert(start, end, bottomUndo, bottomRedo, row, col, f);
                ok = 1;
            }
            else
            {
                if (ok == 1)
                {
                    push(bottomUndo, input);
                    input[1] = '\n';
                    input[2] = '\0';
                }
                // TEXT MODE
                for (i = 0; i < strlen(str); i++)
                {
                    addChr(start, end, line, row, col, bottomUndo, bottomRedo, str[i], i, ok);
                    ok = 0;
                }

                //printSeq((*bottomUndo)->start_seq[0], (*bottomUndo)->end_seq[0]);
            }
        }
    }
    else
    {
        printf("Can't open file!\n");
    }
    fclose(f);
}