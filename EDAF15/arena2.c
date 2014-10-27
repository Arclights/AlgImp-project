#include <string.h>
#include <stdlib.h>
#include "arena2.h"
#include "matrixhandler.h"
#include "vectorhandler.h"

static Matrix* matrices;
static Vector* vectors;

// Creates a list of available matrices and vectors and searches it for a fitting matrix/vector

Matrix* allocate_matrix(int rows, int columns){
	printf("Allocating matrix %dx%d\n",rows,columns);
	Matrix* out = malloc(sizeof(Matrix));
	out->rows = rows;
	out->columns = columns;
	out->next = NULL;
	out->prev = NULL;
	out->matrix = init_matrix(rows, columns);
	return out;
}

fix_p** check_out_matrix(int rows, int columns){
	Matrix* matrix = matrices;
	fix_p** out;
	while(matrix != NULL){
		if(matrix->rows == rows && matrix->columns == columns && matrix->matrix != NULL){
			out = matrix->matrix;
			matrix->matrix = NULL;
			return out;
		}
		matrix = matrix->next;
	}

	matrix = allocate_matrix(rows, columns);
	if(matrices != NULL){
		matrix->next = matrices;
		matrix->next->prev = matrix;
	}
	matrices = matrix;
	out = matrix->matrix;
	matrix->matrix = NULL;
	return out;
}

fix_p** check_out_matrix_copy(fix_p** A, int rows, int cols){
	fix_p** out = check_out_matrix(rows, cols);
	int i;
	for(i = 0; i < rows; i++){
		memcpy(out[i], A[i], sizeof(fix_p*)*cols);
    }

	return out;
}


void hand_back_matrix(fix_p** matrixIn, int rows, int columns){
			// printf("\n");
	// printf("hand_back_matrix: %p\n", matrixIn);
	Matrix* matrix = matrices;
	while(matrix != NULL){
		if(matrix->rows == rows && matrix->columns == columns && matrix->matrix == NULL){
			matrix->matrix = matrixIn;
			// printf("Found spot\n");
			return;
		}
		matrix = matrix->next;
	}
	printf("Can't find spot for matrix\n");
}

Vector* allocate_vector(int elements){
	Vector* out = malloc(sizeof(Vector));
	out->next = NULL;
	out->prev = NULL;
	out->elements = elements;
	out->vector = init_vector(elements);
	return out;
}

fix_p* check_out_vector(int elements){
	Vector* vector = vectors;
	fix_p* out;
	while(vector != NULL){
		if(vector->elements == elements && vector->vector != NULL){
			out = vector->vector;
			vector->vector = NULL;
			return out;
		}
		vector = vector->next;
	}

	vector = allocate_vector(elements);
	if(vectors != NULL){
		vector->next = vectors;
		vector->next->prev = vector;
	}
	vectors = vector;
	out = vector->vector;
	vector->vector = NULL;
	return out;
}

void hand_back_vector(fix_p* vectorIn, int elements){
	Vector* vector = vectors;
	while(vector != NULL){
		if(vector->elements == elements && vector->vector == NULL){
			vector->vector = vectorIn;
			return;
		}
		vector = vector->next;
	}
	printf("Can't find spot for vector\n");
}

fix_p* check_out_vector_copy(fix_p* c, int elems){
	fix_p* out = check_out_vector(elems);
	memcpy(out, c, sizeof(fix_p)*elems);
    return out;
}

void clear_arena(){
	Matrix* matrix = matrices;
	Matrix* m_next;
	while(matrix != NULL){
		m_next = matrix->next;
		free(matrix->matrix);
		free(matrix);
		matrix = m_next;
	}
	matrices = NULL;

	Vector* vector = vectors;
	Vector* v_next;
	while(vector != NULL){
		v_next = vector->next;
		free(vector->vector);
		free(vector);
		vector = v_next;
	}

	vectors = NULL;

}