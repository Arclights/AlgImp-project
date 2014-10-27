#include <stdlib.h>
#include <string.h>
#include "vectorhandler2.h"

fix_p* init_vector(int nbr_of_elements)
{
    fix_p* v;
    v = malloc(nbr_of_elements*sizeof(fix_p));
    return v;
}

_vector* parseVector(FILE* file)
{
    _vector* vector = malloc(sizeof(_vector));

    if(vector == NULL){
        fprintf(stderr,"Out of memory");
    }

    int nbr_of_elements;

    int r = fscanf(file,"%d\n", &nbr_of_elements);
    vector->nbr_of_elements = nbr_of_elements;

    vector->elements = init_vector(nbr_of_elements);

    int elementCounter=0;
    int element;
    r = fscanf(file,"%d", &element);
    while(r!=EOF)
    {
        vector->elements[elementCounter] = int2fix_p(element);
        elementCounter++;
        r = fscanf(file,"%d",&element);
    }

    return vector;
}

fix_p* resize_vector(fix_p* vector, int elems, int new_elems){
    fix_p* new_vector = init_vector(new_elems);
    if(new_vector == NULL){
        fprintf(stderr,"Out of memory");
    }
    int i;
    // Realloc?
    for(i = 0; i < elems; i++){
        new_vector[i] = vector[i];
    }
    free(vector);
    return new_vector;
}

void print_vector(fix_p* vector, int nbr_of_elements){
    int i;
    printf("[");
    for(i = 0; i < nbr_of_elements; i++){
        printf("%f ", fix_p2double(vector[i]));
    }
     printf("]\n");
}
