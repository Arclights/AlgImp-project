#ifndef MATRIXHANDLER_H
#define MATRIXHANDLER_H
#include <stdio.h>
#include "fix_p.h"

typedef struct _matrix _matrix;

struct _matrix
{
    int rows;
    int columns;
    fix_p** cells;
};

fix_p** init_matrix(int rows, int columns);

_matrix* parseMatrix(FILE* file);

/*
 * Sorts the matrix depending on how the coefficient in the specified column relates to zero
 */
void sort_matrix(int rows, int col_to_sort_by, int* n1, int* n2, fix_p** m, fix_p* c);

fix_p** resize_matrix(fix_p** matrix, int rows, int cols, int new_rows);

void print_system(int rows, int columns, fix_p** matrix, fix_p* vector);

#endif