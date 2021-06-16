#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "stack.h"
#include "list.h"
#include "print.h"
#include "read.h"

int main()
{
    List *start = NULL;
    List *end = NULL;
    List *line = NULL;
    List *row = NULL;
    List *col = NULL;
    Stack *bottomUndo = NULL;
    Stack *bottomRedo = NULL;

    delOut();

    //                   -----------
    //                  | TEST AREA |
    //                   -----------

    read(&start, &end, &line, &row, &col, &bottomUndo, &bottomRedo);
    return 0;
}