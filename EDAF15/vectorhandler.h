#ifndef VECTORHANDLER_H
#define VECTORHANDLER_H
#include <stdio.h>
#include "fix_p.h"

typedef struct _vector _vector;

struct _vector
{
    int nbr_of_elements;
    fix_p* elements;
};

fix_p* init_vector(int nbr_of_elements);

long* init_vector_long(int nbr_of_elements, long elements);

_vector* parseVector(FILE* file);

fix_p* resize_vector(fix_p* vector, int elems, int new_elems);

void print_vector(fix_p* vector, int nbr_of_elements);

#endif