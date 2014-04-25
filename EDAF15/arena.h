#include "fix_p.h"
#define T1 1
#define T2 -1
#define Q1 2
#define Q2 -2

typedef struct Arena{
	int init_rows;
	int init_cols;
	fix_p** t1;
	fix_p** t2;
	fix_p* q1;
	fix_p* q2;
	int t1_curr_rows;
	int t2_curr_rows;
	int q1_curr_elems;
	int q2_curr_elems;
	int t1_available;
   	int t2_available;
	int q1_available;
	int q2_available;
} Arena;

Arena* init_arena_basic(int rows, int cols);
Arena* init_arena(int rows, int cols, fix_p** A, fix_p* c, fix_p*** t, fix_p** q);
fix_p** check_out_matrix(Arena* arena, int rows);
fix_p** check_out_matrix_copy(Arena* arena, fix_p** A, int rows, int cols);
fix_p* check_out_vector(Arena* arena, int elems);
fix_p* check_out_vector_copy(Arena* arena, fix_p* c, int elems);
void hand_back_matrix(Arena* arena, fix_p*** t);
void hand_back_vector(Arena* arena, fix_p** q);
void destroy_arena(Arena* arena);