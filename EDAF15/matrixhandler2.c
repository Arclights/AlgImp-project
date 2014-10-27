#include <stdlib.h>
#include <stdio.h>
#include "matrixhandler2.h"

void init_matrix(fix_p** m, int rows, int columns)
{
    int i;
    int row_length = columns*sizeof(fix_p);
    for (i = 0; i < rows; i += 1)
        m[i] = malloc(row_length);
}


_matrix* parseMatrix(FILE* file)
{
    _matrix* matrix = malloc(sizeof(_matrix));

    if(matrix == NULL){
        fprintf(stderr,"Out of memory");
    }

    int rows;
    int columns;

    int r = fscanf(file, "%d %d\n", &rows, &columns);
    matrix->rows = rows;
    matrix->columns = columns;

    matrix->cells = malloc(rows*sizeof(fix_p*));
    init_matrix(matrix->cells, rows, columns);

    int rowCounter = 0;
    int columnCounter = 0;
    int cell;
    r = fscanf(file, "%d", &cell);
    while(r!=EOF)
    {
        matrix->cells[rowCounter][columnCounter] = int2fix_p(cell);
        columnCounter++;
        if(columnCounter>=columns)
        {
            columnCounter=0;
            rowCounter++;
        }
        r = fscanf(file, "%d", &cell);
    }

    return matrix;
}

void print_system(int rows, int columns, fix_p** matrix, fix_p* vector){
    int i;
    int j;
    for(i = 0; i < rows; i++){
        for(j = 0; j < columns; j++){
            printf("%f(%ld) ",fix_p2double(matrix[i][j]), matrix[i][j]);
        }
        printf("= %f(%ld)\n", fix_p2double(vector[i]), vector[i]);
    }
}

/*
 * Sorts the matrix depending on how the coefficient in the specified column relates to zero
 */
void sort_matrix(int rows, int col_to_sort_by, int* n1, int* n2, fix_p** m, fix_p* c){
    int curr_row = 0;
    fix_p* row_tmp;
    fix_p elem_tmp;
    int i;
    fix_p** mi;
    fix_p* ci;
    mi = m;
    ci = c;
    for(i = curr_row; i < rows; i++){
        if((*mi)[col_to_sort_by] > 0){
            row_tmp = m[curr_row];
            elem_tmp = c[curr_row];
            m[curr_row] = *mi;
            c[curr_row] = *ci;
            *mi = row_tmp;
            *ci = elem_tmp;
            curr_row ++;
        }
        mi++;
        ci++;
    }
    *n1 = curr_row;
    mi = &m[curr_row];
    ci = &c[curr_row];
    for(i = curr_row; i < rows; i++){
        if((*mi)[col_to_sort_by] < 0){
            row_tmp = m[curr_row];
            elem_tmp = c[curr_row];
            m[curr_row] = *mi;
            c[curr_row] = *ci;
            *mi = row_tmp;
            *ci = elem_tmp;
            curr_row ++;
        }
        mi++;
        ci++;
    }

    *n2 = curr_row;
}