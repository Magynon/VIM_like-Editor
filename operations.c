#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "print.h"
#include "list.h"
#include "stack.h"

List *saveS = NULL;
List *saveE = NULL;

int identifier(char *str)
{
    if (str[0] == 'u')
    {
        return 1;
    }
    if (str[0] == 'r' && str[1] == '\n')
    {
        return 2;
    }
    if (str[0] == 's')
    {
        return 3;
    }
    if (str[0] == 'q')
    {
        return 4;
    }
    if (str[0] == 'b')
    {
        return 5;
    }
    if (strstr(str, "dl") != NULL)
    {
        return 6;
    }
    if (strstr(str, "gl") != NULL)
    {
        return 7;
    }
    if (strstr(str, "gc") != NULL)
    {
        return 8;
    }
    if (str[0] == 'd' && (str[1] == ' ' || str[1] == '\0'))
    {
        return 9;
    }
    if (strstr(str, "re") != NULL)
    {
        return 10;
    }
    if (strstr(str, "ra") != NULL)
    {
        return 11;
    }
    if (strstr(str, "dw") != NULL)
    {
        return 12;
    }
    if (strstr(str, "da") != NULL)
    {
        return 13;
    }
    return 4;
}

void goto_line(List **start, List **end, Stack **bottomUndo, Stack **bottomRedo, char *str, List **row, List **col, int *EMPTY)
{
    (*bottomUndo)->number_of_addresses = 1;
    printf("GOTO_LINE\n");
    if (*col == NULL)
    {
        (*bottomUndo)->old_row[0] = *start;
        (*bottomUndo)->old_col[0] = *start;
    }
    else
    {
        (*bottomUndo)->old_row[0] = *row;
        (*bottomUndo)->old_col[0] = *col;
    }
    int i = 3, n = 0;
    while (str[i] != '\0')
    {
        n = n * 10 + (str[i] - 48);
        i++;
    }
    List *cursor = *start;
    for (i = 1; i < n; i++)
    {
        cursor = cursor->l_up;
    }
    (*row) = cursor;
    (*col) = cursor;
    //printCurrentRow(*row, *col);
}

void goto_chr(List **start, List **end, Stack **bottomUndo, Stack **bottomRedo, char *str, List **row, List **col, int *EMPTY)
{
    (*bottomUndo)->number_of_addresses = 1;
    printf("GOTO_CHR\n");
    if (*col == NULL)
    {
        (*bottomUndo)->old_row[0] = *start;
        (*bottomUndo)->old_col[0] = *start;
    }
    else
    {
        (*bottomUndo)->old_row[0] = *row;
        (*bottomUndo)->old_col[0] = *col;
    }
    int i = 3, m = 0, n = 0;
    List *cursor;
    while (str[i] != '\0' && str[i] != ' ')
    {
        m = m * 10 + (str[i] - 48);
        i++;
    }

    // receives both chr and row args
    if (str[i] == ' ')
    {
        i++;

        while (str[i] != '\0')
        {
            n = n * 10 + (str[i] - 48);
            i++;
        }
        cursor = *start;
        for (i = 1; i < n; i++)
        {
            printf("i = %d\n", i);
            while (cursor->x != '\n')
            {
                cursor = cursor->asc;
            }
            cursor = cursor->asc;
            if (cursor->x == '\n')
            {
                cursor = cursor->asc;
            }
        }

        (*row) = cursor;
    }

    cursor = *row;
    for (i = 1; i < m; i++)
    {
        cursor = cursor->asc;
    }
    (*col) = cursor;
    //printf("Place: %c\n", (*bottomUndo)->old_col[0]->x);
}

void undo(List **start, List **end, Stack **bottomUndo, Stack **bottomRedo, char *str, List **row, List **col, int *EMPTY)
{
    printf("UNDO\n");

    if (*bottomUndo == NULL)
    {
        return;
    }
    undoPop(bottomUndo, bottomRedo);
    printStack(*bottomUndo, *bottomRedo);
}

void redo(List **start, List **end, Stack **bottomUndo, Stack **bottomRedo, char *str, List **row, List **col, int *EMPTY)
{
    printf("REDO\n");
    if ((*bottomRedo) == NULL)
    {
        return;
    }
    redoPop(bottomUndo, bottomRedo);
    printStack(*bottomUndo, *bottomRedo);
    if ((*bottomUndo)->x[0] == 'i')
    {
        List *placeStart = (*bottomUndo)->old_col[0];
        List *startSeq = (*bottomUndo)->start_seq[0];
        List *endSeq = (*bottomUndo)->end_seq[0];
        placeStart->asc = startSeq;
        startSeq->desc = placeStart;
        endSeq->asc = NULL;
        (*end) = endSeq;
        //printList(*start);
        //printSeq(placeStart->desc, placeEnd);
        //addSeq(start, end, &placeStart, &placeEnd, &startSeq, &endSeq);
    }
}

void save(List **start, List **end, Stack **bottomUndo, Stack **bottomRedo, char *str, List **row, List **col, int *EMPTY)
{
    printf("SAVE\n");
    int n;
    printList(*start);
    // while undo stack is not empty
    while ((*bottomUndo) != NULL)
    {
        // n = number of addreses modified by command
        n = (*bottomUndo)->number_of_addresses;

        // free memory of all addresses used by commands
        // up to save command
        for (int i = 0; i < n; i++)
        {
            //free((*bottomUndo)->start_seq[i]);
            if ((*bottomUndo)->start_seq[i] != (*bottomUndo)->end_seq[i])
            {
                free((*bottomUndo)->end_seq[i]);
            }
        }

        // pop current command out of stack
        pop(bottomUndo);
    }

    // while redo stack is not empty
    while ((*bottomRedo) != NULL)
    {
        // n = number of addreses modified by command
        n = (*bottomRedo)->number_of_addresses;

        // free memory of all addresses used by commands
        // up to save command
        for (int i = 0; i < n; i++)
        {
            free((*bottomRedo)->start_seq[i]);
            if ((*bottomRedo)->start_seq[i] != (*bottomRedo)->end_seq[i])
            {
                free((*bottomRedo)->end_seq[i]);
            }
        }

        // pop current command out of stack
        pop(bottomRedo);
    }
}

void quit(List **start, List **end, Stack **bottomUndo, Stack **bottomRedo, char *str, List **row, List **col, int *EMPTY)
{
    printf("QUIT\n");
    if ((*bottomUndo) != NULL)
    {
        ;
    }
    else
    {
        printList(*start);
    }

    // while (tmp != NULL)
    // {
    //     p = tmp;
    //     tmp = tmp->asc;
    //     free(p);
    // }
    //printStack(*bottomUndo, *bottomRedo);
    exit(0);
}

void backspace(List **start, List **end, Stack **bottomUndo, Stack **bottomRedo, char *str, List **row, List **col, int *EMPTY)
{
    (*bottomUndo)->number_of_addresses = 1;
    printf("BACKSPACE\n");
    if ((*col) == NULL)
    {
        return;
    }
    (*bottomUndo)->start_seq[0] = *col;
    (*bottomUndo)->end_seq[0] = *col;
    delSeq(start, end, row, col, bottomUndo, 1);
    //printCurrentRow(*row, *col);
    //printList(*start);
}

void del_chr(List **start, List **end, Stack **bottomUndo, Stack **bottomRedo, char *str, List **row, List **col, int *EMPTY)
{
    (*bottomUndo)->number_of_addresses = 1;
    printf("DEL_CHR\n");
    int i = 2, n = 0;
    if (str[1] == ' ')
    {
        while (str[i] != '\0')
        {
            n = n * 10 + (str[i] - 48);
            i++;
        }
    }
    if (n == 0)
    {
        n = 1;
    }
    (*bottomUndo)->old_col[0] = *col;
    (*bottomUndo)->old_row[0] = (*col)->asc->asc;
    (*bottomUndo)->start_seq[0] = (*col)->asc;
    *col = (*col)->asc;
    (*bottomUndo)->end_seq[0] = delSeq(start, end, row, col, bottomUndo, n);
    //printStack(*bottomUndo, *bottomRedo);
    //printCurrentRow(*row, *col);
    //printSeq((*bottomUndo)->start_seq[0], (*bottomUndo)->end_seq[0]);
}

void del_line(List **start, List **end, Stack **bottomUndo, Stack **bottomRedo, char *str, List **row, List **col, int *EMPTY)
{
    (*bottomUndo)->number_of_addresses = 1;
    printf("DEL_LINE\n");
    int i = 3, n = 0, nr = 0;
    char new_str[6] = "gl \0";
    char n_char[3];

    // parsing input string
    if (str[2] != '\0')
    {
        while (str[i] != '\0')
        {
            n = n * 10 + (str[i] - 48);
            i++;
        }
        if (n / 10 == 0)
        {
            n_char[0] = n + '0';
            n_char[1] = '\0';
        }
        else
        {
            n_char[0] = n / 10 + '0';
            n_char[1] = n % 10 + '0';
            n_char[2] = '\0';
        }

        strcat(new_str, n_char);

        // if currently on other line
        goto_line(start, end, bottomUndo, bottomRedo, new_str, row, col, NULL);
    }
    else
    {
        // if currently on the same line
        goto_chr(start, end, bottomUndo, bottomRedo, "gc 1\0", row, col, NULL);
    }

    List *tmp = *row, *old_col = *col;

    // go to end of line
    while (tmp != (*row)->l_up)
    {
        nr++;
        tmp = tmp->asc;
    }

    // if NOT first line
    if ((*col)->l_down != NULL)
    {
        (*col)->l_down->l_up = (*col)->l_up;
    }

    // if NOT last line
    if ((*col)->l_up != NULL)
    {
        (*col)->l_up->l_down = (*col)->l_down;
    }

    // check vars
    int ok1 = 0, ok2 = 0;

    // if first line
    if ((*col)->l_down == NULL)
    {
        ok1 = 1;
    }

    // if last line
    if ((*col)->l_up == NULL)
    {
        ok2 = 1;
    }

    // memorize old sequence
    (*bottomUndo)->start_seq[0] = *col;
    (*bottomUndo)->end_seq[0] = delSeq(start, end, row, col, bottomUndo, nr);

    if (ok1 == 1)
    {
        *start = old_col->l_up;
    }
    if (ok2 == 1)
    {
        *end = old_col->l_down;
    }

    // printSeq((*bottomUndo)->start_seq[0], (*bottomUndo)->end_seq[0]);
    // printList(*start);
}

void del_word(List **start, List **end, Stack **bottomUndo, Stack **bottomRedo, char *str, List **row, List **col, int *found)
{
    (*bottomUndo)->number_of_addresses = 1;
    printf("DEL_WORD\n");
    List *tmp = *start, *add;
    char word[5];
    int i, address = 0;
    if (*found != -1)
    {
        address = *found - 1;
    }
    *found = 0;
    word[0] = '\0';
    strcpy(word, str + 3);
    // printf("cuvant: %s\n", word);
    while (tmp != NULL && *found == 0)
    {
        i = 0;
        while (tmp->x == word[i] && i < strlen(word))
        {
            *found = 1;
            //printf("litera: %c = %c\n", tmp->x, word[i]);
            if (i == 0)
            {
                add = tmp;
            }
            i++;
            tmp = tmp->asc;
        }
        if (*found == 1)
        {
            tmp = add;
            *found = 0;
        }

        if (i == strlen(word))
        {
            *col = tmp;
            while (tmp->new_line != 'y')
            {
                tmp = tmp->desc;
            }

            //printf("litera: %c\n", tmp->x);
            (*row) = tmp;

            (*bottomUndo)->old_col[address] = (*col)->desc;

            //printf("start: \"%c\"\n", (*col)->x);
            (*bottomUndo)->start_seq[address] = *col;
            (*bottomUndo)->end_seq[address] = delSeq(start, end, row, col, bottomUndo, strlen(word));

            (*bottomUndo)->old_row[address] = (*col)->asc;

            if (address != -1)
            {
                *found = address + 1;
            }

            //printSeq((*bottomUndo)->start_seq[0], (*bottomUndo)->end_seq[0]);
            //printList(*start);
        }
        tmp = tmp->asc;
    }
}

void del_all(List **start, List **end, Stack **bottomUndo, Stack **bottomRedo, char *str, List **row, List **col, int *EMPTY)
{
    printf("DEL_ALL\n");
    char word[5];
    int found = 1, max = 1;
    word[0] = '\0';
    strcpy(word, str + 3);
    // printf("cuvant: %s\n", word);
    char new_str[9] = "dw \0";
    strcat(new_str, word);
    while (found > 0)
    {
        del_word(start, end, bottomUndo, bottomRedo, new_str, row, col, &found);
        if (found != 0)
        {
            found++;
            max = found - 1;
        }
    }
    (*bottomUndo)->number_of_addresses = max;

    // for (int i = 0; i < max; i++)
    // {
    //     printSeq((*bottomUndo)->start_seq[i], (*bottomUndo)->end_seq[i]);
    // }
    //printList(*start);
}

void rep_word(List **start, List **end, Stack **bottomUndo, Stack **bottomRedo, char *str, List **row, List **col, int *found)
{
    (*bottomUndo)->number_of_addresses = 1;
    printf("REP_WORD\n");
    int i, j = 0, y;
    char old_word[10];
    char new_word[10];
    for (i = 3; str[i] != ' '; i++)
    {
        old_word[j] = str[i];
        j++;
    }
    old_word[j] = '\0';
    j = 0;
    i++;
    for (y = i; str[y] != '\0'; y++)
    {
        new_word[j] = str[y];
        j++;
    }
    new_word[j] = '\0';
    // printf("new: %s, old: %s\n", new_word, old_word);
    char word[10] = "dw \0";
    strcat(word, old_word);
    i = -1;
    del_word(start, end, bottomUndo, bottomRedo, word, row, col, &i);
    *col = (*col)->asc;
    for (i = 0; i < strlen(new_word); i++)
    {
        addByKey(start, end, col, new_word[i]);
        *col = (*col)->asc;
    }
}

void rep_all(List **start, List **end, Stack **bottomUndo, Stack **bottomRedo, char *str, List **row, List **col, int *EMPTY)
{
    printf("REP_ALL\n");
    int i, j = 0, y;
    char old_word[10];
    char new_word[10];
    for (i = 3; str[i] != ' '; i++)
    {
        old_word[j] = str[i];
        j++;
    }
    old_word[j] = '\0';
    j = 0;
    i++;
    y = i;
    for (i = y; str[i] != '\0'; i++)
    {
        new_word[j] = str[i];
        j++;
    }
    new_word[j] = '\0';
    char word[10] = "dw \0";
    strcat(word, old_word);

    int found = 1, max;
    while (found > 0)
    {
        del_word(start, end, bottomUndo, bottomRedo, word, row, col, &found);

        if ((*col)->desc != NULL)
        {
            *col = (*col)->asc;
        }

        if (found != 0)
        {
            for (i = 0; i < strlen(new_word); i++)
            {

                addByKey(start, end, col, new_word[i]);
                *col = (*col)->asc;
            }
            //printList(*start);

            found++;
            max = found - 1;
        }
    }
    (*bottomUndo)->number_of_addresses = max;
    // for (i = 0; i < max; i++)
    // {
    //     printSeq((*bottomUndo)->start_seq[i], (*bottomUndo)->end_seq[i]);
    // }
}