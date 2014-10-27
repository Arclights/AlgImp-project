#include <string.h>
#include <stdlib.h>
#include "arena3.h"
#include "matrixhandler2.h"
#include "vectorhandler.h"

static Matrix* matrices;
static Vector* vectors;

// Creates a list of available matrices and vectors and searches it for a fitting matrix/vector

Matrix* allocate_matrix(int rows, int columns){
	size_t* tmp = malloc(sizeof(Matrix) + rows * sizeof(fix_p*));
	Matrix* out = (Matrix*) tmp;
	out->rows = rows;
	out->columns = columns;
	out->next = NULL;
	out->prev = NULL;
	init_matrix((fix_p**)out->matrix, rows, columns);
	return out;
}


fix_p** check_out_matrix(int rows, int columns){
	Matrix* matrix = matrices;
	fix_p** out;
	while(matrix != NULL){
		if(matrix->rows >= rows && matrix->columns >= columns){
			out = (fix_p**)matrix->matrix;
			if(matrix->prev != NULL){
				matrix->prev->next = matrix->next;
			}else{
				matrices = matrix->next;
			}
			if(matrix->next != NULL){
				matrix->next->prev = matrix->prev;
			}
			if(matrix->next == NULL && matrix->prev == NULL){
				matrices = NULL;
			}
			return out;
		}
		matrix = matrix->next;
	}

	matrix = allocate_matrix(rows, columns);
	out = (fix_p**)matrix->matrix;
	return out;
}

fix_p** check_out_matrix_copy(fix_p** A, int rows, int columns){
	fix_p** out = check_out_matrix(rows, columns);
	int i;
	for(i = 0; i < rows; i++){
		memcpy(out[i], A[i], sizeof(fix_p*)*columns);
    }
	return out;
}


void hand_back_matrix(void* matrixIn){
	Matrix* m = (Matrix*)((char*)matrixIn - sizeof(Matrix));
	m->next = matrices;
	if(m->next != NULL){
		m->next->prev = m;
	}
	m->prev = NULL;
	matrices = m;
}

Vector* allocate_vector(int elements){
	size_t* tmp = malloc(sizeof(Vector) + elements * sizeof(fix_p));
	Vector* out = (Vector*)tmp;
	out->next = NULL;
	out->prev = NULL;
	out->elements = elements;
	return out;
}

fix_p* check_out_vector(int elements){
	Vector* vector = vectors;
	fix_p* out;
	while(vector != NULL){
		if(vector->elements >= elements && vector->vector != NULL){
			out = (fix_p*)vector->vector;
			if(vector->prev != NULL){
				vector->prev->next = vector->next;
			}else{
				vectors = vector->next;
			}
			if(vector->next != NULL){
				vector->next->prev = vector->prev;
			}
			if(vector->next == NULL && vector->prev == NULL){
				vectors = NULL;
			}
			return out;
		}
		vector = vector->next;
	}

	vector = allocate_vector(elements);
	out = (fix_p*)vector->vector;
	return out;
}

void hand_back_vector(void* vectorIn){
	Vector* v = (Vector*)((char*)vectorIn - sizeof(Vector));
	v->next = vectors;
	if(v->next != NULL){
		v->next->prev = v;
	}
	v->prev = NULL;
	vectors = v;
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
		fix_p** m = (fix_p**)matrix->matrix;
		int i;
		for(i = 0; i < matrix->rows; i++){
				free(m[i]);
		}
		free(matrix);
		matrix = m_next;
	}
	matrices = NULL;

	Vector* vector = vectors;
	Vector* v_next;
	while(vector != NULL){
		v_next = vector->next;
		free(vector);
		vector = v_next;
	}

	vectors = NULL;

}