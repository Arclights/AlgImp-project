#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include "matrixhandler.h"
#include "fix_p.h"
#include "vectorhandler.h"
#include "arena.h"

static unsigned long long   fm_count;
static volatile bool        proceed = false;

static void done(int unused)
{
    proceed = false;
    unused = unused;
}

/**
Working
Global arena
Score: 33 914 097
**/

//unsigned long long fm_elim(int rows, int cols, int** A, int* c)
unsigned long long fm_elim(Arena* arena, int rows, int cols, fix_p** A, fix_p* c)
{
//1
    int r;
    int s;
    fix_p** t;
    fix_p* q;
    int n1;
    int n2;
    int i;
    int j;
    long br;
    long Br;
    int qj_lt_0;
    int s_p;
    fix_p** old_t;
    fix_p* old_q;
    int k;
    int l;
    int curr_row;

    fix_p tjr;
    fix_p* qj;
    fix_p* tj;

    r = cols;
    s = rows;

    t = check_out_matrix_copy(arena, A, rows, cols);
    q = check_out_vector_copy(arena, c, rows);
    
    printf("\n\nNew system\n");
    // print_system(s, r, t, q);
    // printf("\n");
    

    while(1){
    //2
        sort_matrix(s, r-1, &n1, &n2, t, q);

        printf("s: %d\nn1: %d\nn2: %d\n", s, n1, n2);
        printf("\n");
        printf("After sort:\n");
        print_system(s, r, t, q);
        printf("\n");

    // 3
    
    qj = q;
    for(j = 0; j < n2; j++){
        tjr = fix_p_div(65536, t[j][r-1]); //65536 = 1
        *qj = fix_p_mul(*qj, tjr);
        qj++;
        tj = t[j];
        for(i = 0; i < r; i++){
            *tj = fix_p_mul(*tj, tjr);
            tj++;
        }
    }

    printf("After div:\n");
    print_system(s, r, t, q);
    printf("\n");

    

//     printf("br: %f\tBr: %f\n", fix_p2double(br), fix_p2double(Br));
// printf("r == %d\n", r);
    // 5
    if(r == 1){
        // printf("r == 1\n");

        // 4
        br = 0;
    // printf("brs:\n");
        if(n2 > n1){
            for(j = n1; j < n2; j++){
                if(q[j] > br){
                    br = q[j];
                }
            }
        }else{
            br = LONG_MIN;
        }

        Br = LONG_MAX;
    // printf("\nBrs:\n");
        if(n1 > 0){
            for(j = 0; j < n1; j++){
                if(q[j] < Br){
                    Br = q[j];
                }
            }
        }else{
            Br = LONG_MAX;
        }

        qj_lt_0 = 0;
        for(i = n2; i < s; i++){
            if(q[i] < 0){
                qj_lt_0 = 1;
                break;
            }
        }


        // printf("br > Br: %d\nqj_lt_0: %d\n", br > Br, qj_lt_0);

        if(br > Br || qj_lt_0){
            // printf("br > Br || qj_lt_0\n");
            hand_back_matrix(arena, &t);
            hand_back_vector(arena, &q);
            return 0;
        }else{
            // printf("not br > Br || qj_lt_0\n");
            hand_back_matrix(arena, &t);
            hand_back_vector(arena, &q);
            return 1;
        }
    }

    // 6
    s_p = s - n2 + n1 * (n2 - n1);
    if(s_p == 0){
        // printf("s_p == 0\n");

        // print_system(s, r, t, q);

        for(j = 0; j < n1; j++){
            fix_p sum = 0;
            for(i = 0; i < r; i++){
                sum += t[j][i];
            }
            if(sum != q[j]){
                // printf("i:%d j:%d sum:%f q:%f\n", i,j,fix_p2double(sum),fix_p2double(q[j]));
                // free_up_t_q(s,t,q);
                hand_back_matrix(arena, &t);
                hand_back_vector(arena, &q);
                return 0;
            }
            // printf("+ %f\n",fix_p2double(q[j]));
        }

        hand_back_matrix(arena, &t);
        hand_back_vector(arena, &q);
        return 1;
    }

        // printf("\n");

    // 7
    old_t = t;
    old_q = q;
    // t = init_matrix(s_p, r - 1);
    // q = init_vector(s_p);
    t = check_out_matrix(arena, s_p);
    q = check_out_vector(arena, s_p);

        // printf("s_p: %d\n", s_p);

    // printf("\n");
    //     print_system(s, r, old_t, old_q);
    //     printf("\n");

    curr_row = 0;
    fix_p old_qk;
    fix_p* old_tk;
    fix_p* old_tl;
    for(k = 0; k < n1; k++){
        old_qk = old_q[k];
        old_tk = old_t[k];
        for(l = n1; l < n2; l++){
            old_tl = old_t[l];
            for(i = 0; i < r-1; i++){
                // printf("%ld\n",t[curr_row][i]);
                // printf("k:%d i:%d l:%d\n", k ,i, l);
                t[curr_row][i] = old_tk[i] - old_tl[i];
            }
            q[curr_row] = old_qk - old_q[l];
            curr_row++;
        }
    }

    for(j = n2; j < s; j++){
        for(i = 0; i < r-1; i++){
            t[curr_row][i] = old_t[j][i];
        }
        q[curr_row] = old_q[j];
        curr_row++;
    }

    hand_back_matrix(arena, &old_t);
    hand_back_vector(arena, &old_q);

    r = r - 1;
    s = s_p;

    // printf("\n");
    // print_system(s, r, t, q);
    // printf("\n");

}


}

void free_up(_matrix* matA, _vector* vecC){
    int i;
    for(i = 0; i < matA->rows; i++){
        free(matA->cells[i]);
    }
    free(matA->cells);
    matA->cells = NULL;
    free(matA);
    matA = NULL;
    free(vecC->elements);
    vecC->elements = NULL;
    free(vecC);
    vecC = NULL;
}


unsigned long long TomKva_v5(char* aname, char* cname, int seconds)
{
    FILE*       afile = fopen(aname, "r");
    FILE*       cfile = fopen(cname, "r");

    fm_count = 0;

    if (afile == NULL)
    {
        fprintf(stderr, "could not open file A\n");
        exit(1);
    }

    if (cfile == NULL)
    {
        fprintf(stderr, "could not open file c\n");
        exit(1);
    }

    _matrix* matA = parseMatrix(afile);
    _vector* vecC = parseVector(cfile);

    fclose(afile);
    fclose(cfile);

    Arena* arena = init_arena_basic(6, 6);

    if (seconds == 0)
    {
        /* Just run once for validation. */

        // Uncomment when your function and variables exist...
        int result = fm_elim(arena, matA->rows, matA->columns, matA->cells, vecC->elements);
        free_up(matA,vecC);
        destroy_arena(arena);
        return result;
        //return 1; // return one, i.e. has a solution for now...
    }

    /* Tell operating system to call function DONE when an ALARM comes. */
    signal(SIGALRM, done);
    alarm(seconds);

    /* Now loop until the alarm comes... */
    proceed = true;
    while (proceed)
    {
        // Uncomment when your function and variables exist...
        // fm_elim(rows, cols, a, c);
        fm_elim(arena, matA->rows, matA->columns, matA->cells, vecC->elements);
        fm_count++;
    }

    // Clean up
    free_up(matA,vecC);
    destroy_arena(arena);

    return fm_count;
}