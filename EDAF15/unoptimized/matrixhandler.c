#include <stdlib.h>
#include <stdio.h>
#include "matrixhandler.h"

fix_p** init_matrix(int rows, int columns)
{
    fix_p** m;
    int i;
    m = calloc(rows, sizeof(fix_p*));
    for (i = 0; i < rows; i += 1)
        m[i] = calloc(columns, sizeof(fix_p));
    return m;
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

    matrix->cells = init_matrix(rows, columns);

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
    for(i = curr_row; i < rows; i++){
        if(m[i][col_to_sort_by] > 0){
            if(i == curr_row){

            }else{
                row_tmp = m[curr_row];
                elem_tmp = c[curr_row];
                m[curr_row] = m[i];
                c[curr_row] = c[i];
                m[i] = row_tmp;
                c[i] = elem_tmp;
            }
            curr_row ++;
        }
    }
    *n1 = curr_row;

    for(i = curr_row; i < rows; i++){
        if(m[i][col_to_sort_by] < 0){
            if(i == curr_row){

            }else{
                row_tmp = m[curr_row];
                elem_tmp = c[curr_row];
                m[curr_row] = m[i];
                c[curr_row] = c[i];
                m[i] = row_tmp;
                c[i] = elem_tmp;
            }
            curr_row ++;
        }
    }

    *n2 = curr_row;
}

fix_p** resize_matrix(fix_p** matrix, int rows, int cols, int new_rows){
    fix_p** new_matrix = init_matrix(new_rows, cols);
    // printf("Resize\n");
    if(new_matrix == NULL){
        fprintf(stderr,"Out of memory");
    }
    fix_p* temp_row;
    // memcpy
    int i;
    for(i = 0; i < rows; i++){
        temp_row = new_matrix[i];
        new_matrix[i] = matrix[i];
        free(temp_row);
    }
    free(matrix);
    return new_matrix;
}
