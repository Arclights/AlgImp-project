#include "fix_p.h"

typedef struct Matrix Matrix;

struct Matrix{
	int rows;
	int columns;
	Matrix* next;
	Matrix* prev;
	char matrix[];
};

typedef struct Vector Vector;

struct Vector{
	int elements;
	Vector* next;
	Vector* prev;
	char vector[];
};

fix_p** check_out_matrix(int rows, int columns);
fix_p** check_out_matrix_copy(fix_p** A, int rows, int cols);
void hand_back_matrix(void* matrixIn);
fix_p* check_out_vector(int elements);
fix_p* check_out_vector_copy(fix_p* c, int elems);
void hand_back_vector(void* vectorIn);
void clear_arena();