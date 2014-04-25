#include <stdlib.h>
#include <string.h>
#include "arena.h"
#include "matrixhandler.h"
#include "vectorhandler.h"

Arena* init_arena_basic(int rows, int cols){
	Arena* arena = malloc(sizeof(Arena));
	arena->init_cols = cols;
    arena->init_rows = rows;
    arena->t1 = init_matrix(rows, cols);
    arena->t2 = init_matrix(rows, cols);
    arena->q1 = init_vector(rows);
    arena->q2 = init_vector(rows);
    arena->t1_curr_rows = rows;
	arena->t2_curr_rows = rows;
	arena->q1_curr_elems = rows;
	arena->q2_curr_elems = rows;
    arena->t1_available = 1;
    arena->t2_available = 1;
	arena->q1_available = 1;
	arena->q2_available = 1;
    return arena;
}

Arena* init_arena(int rows, int cols, fix_p** A, fix_p* c, fix_p*** t, fix_p** q){
	Arena* arena = malloc(sizeof(Arena));
	arena->init_cols = cols;
    arena->init_rows = rows;
    arena->t1 = init_matrix(rows, cols);
    arena->t2 = init_matrix(rows, cols);
    arena->q1 = init_vector(rows);
    arena->q2 = init_vector(rows);
    arena->t1_curr_rows = rows;
	arena->t2_curr_rows = rows;
	arena->q1_curr_elems = rows;
	arena->q2_curr_elems = rows;
    arena->t1_available = 0;
    arena->t2_available = 1;
	arena->q1_available = 0;
	arena->q2_available = 1;

	int i;
	// int j;
    
    for(i = 0; i < rows; i++){
    	memcpy(arena->t1[i], A[i], sizeof(fix_p*)*cols);
        // for(j = 0; j < cols; j++){
        //     arena->t1[i][j] = A[i][j];
        // }
    }

    memcpy(arena->q1, c, sizeof(fix_p)*rows);
    // for(i = 0; i <  rows; i++){
    //     arena->q1[i] = c[i];
    // }

    *t = arena->t1;
    *q = arena->q1;

    return arena;
}

fix_p** check_out_matrix(Arena* arena, int rows){
			// printf("Trying to check out t2\n");
	if(arena->t2_available){
				// printf("Checking out t2\n");
		if(rows > arena->t2_curr_rows){
			arena->t2 = resize_matrix(arena->t2, arena->t2_curr_rows, arena->init_cols, rows);
			arena->t2_curr_rows = rows;
		}
		arena->t2_available = 0;
		return arena->t2;
	}
	if(arena->t1_available){
			// printf("Trying to check out t1\n");
				// printf("Checking out t1\n");
		if(rows > arena->t1_curr_rows){
			arena->t1 = resize_matrix(arena->t1, arena->t1_curr_rows, arena->init_cols, rows);
			arena->t1_curr_rows = rows;
		}
		arena->t1_available = 0;
		return arena->t1;
	}
	return NULL;
}

fix_p** check_out_matrix_copy(Arena* arena, fix_p** A, int rows, int cols){
			// printf("Trying to check out t2\n");
	fix_p** out = check_out_matrix(arena, rows);
	int i;
	for(i = 0; i < rows; i++){
		memcpy(out[i], A[i], sizeof(fix_p*)*cols);
    }

	return out;
}

fix_p* check_out_vector(Arena* arena, int elems){
		// printf("Trying to check out q2\n");
	if(arena->q2_available){
				// printf("Checking out q2\n");
		if(elems > arena->q2_curr_elems){
			arena->q2 = resize_vector(arena->q2, arena->q2_curr_elems, elems);
			arena->q2_curr_elems = elems;
		}
		arena->q2_available = 0;
		return arena->q2;
	}
		// printf("Trying to check out q1\n");
	if(arena->q1_available){
				// printf("Checking out q1\n");
		if(elems > arena->q1_curr_elems){
			arena->q1 = resize_vector(arena->q1, arena->q1_curr_elems, elems);
			arena->q1_curr_elems = elems;
		}
		arena->q1_available = 0;
		return arena->q1;
	}
	return NULL;
}

fix_p* check_out_vector_copy(Arena* arena, fix_p* c, int elems){
		// printf("Trying to check out q2\n");
	fix_p* out = check_out_vector(arena, elems);
	memcpy(out, c, sizeof(fix_p)*elems);
    return out;
}

void hand_back_matrix(Arena* arena, fix_p*** t){
	if(*t == arena->t1){
		// printf("Handing back t1\n");
		arena->t1_available = 1;
	}else if(*t == arena->t2){
		// printf("Handing back t2\n");
		arena->t2_available = 1;
	}
	*t = NULL;
}

void hand_back_vector(Arena* arena, fix_p** q){
	if(*q == arena->q1){
		// printf("Handing back q1\n");
		arena->q1_available = 1;
	}else if(*q == arena->q2){
		// printf("Handing back q2\n");
		arena->q2_available = 1;
	}
	*q = NULL;
}

void destroy_arena(Arena* arena){
	int i;
	for(i = 0; i < arena->t1_curr_rows; i++){
		free(arena->t1[i]);
		arena->t1[i] = NULL;
	}
	free(arena->t1);
	arena->t1 = NULL;
	for(i = 0; i < arena->t2_curr_rows; i++){
		free(arena->t2[i]);
		arena->t2[i] = NULL;
	}
	free(arena->t2);
	arena->t2 = NULL;

	free(arena->q1);
	free(arena->q2);
	arena->q1 = NULL;
	arena->q2 = NULL;

	free(arena);
}