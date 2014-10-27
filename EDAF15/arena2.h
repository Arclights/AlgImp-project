#include "fix_p.h"

typedef struct Matrix Matrix;

struct Matrix{
	Matrix* next;
	Matrix* prev;
	int rows;
	int columns;
	fix_p** matrix;
};

typedef struct Vector Vector;

struct Vector{
	Vector* next;
	Vector* prev;
	int elements;
	fix_p* vector;
};

fix_p** check_out_matrix(int rows, int columns);
fix_p** check_out_matrix_copy(fix_p** A, int rows, int cols);
void hand_back_matrix(fix_p** matrixIn, int rows, int columns);
fix_p* check_out_vector(int elements);
fix_p* check_out_vector_copy(fix_p* c, int elems);
void hand_back_vector(fix_p* vectorIn, int elements);
void clear_arena();