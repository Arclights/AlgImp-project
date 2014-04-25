#include <stdio.h>
#include <sys/time.h>
#include "vectorhandler.h"
#include "matrixhandler.h"

void test_parseMatrix(){
	printf("Test parseMatrix:\n");

    FILE*		afile = fopen("input/2/A", "r");

	_matrix* matrix = parseMatrix(afile);

	int i;
	int j;
	for(i = 0; i < matrix->rows; i++){
		for(j = 0; j < matrix->columns; j++){
			printf("%f ",fix_p2double(matrix->cells[i][j]));
		}
		printf("\n");
	}
}

void test_sort_matrix(){
	printf("Test sort_matrix:\n");

    FILE*		afile = fopen("input/2/A", "r");

	_matrix* matrix = parseMatrix(afile);


    FILE*		cfile = fopen("input/2/c", "r");

	_vector* vector = parseVector(cfile);

	print_system(matrix->rows, matrix->columns, matrix->cells, vector->elements);

	int n1;
	int n2;
	sort_matrix(matrix->rows, matrix->columns - 1, &n1, &n2, matrix->cells, vector->elements);
	printf("\n");

	print_system(matrix->rows, matrix->columns, matrix->cells, vector->elements);

	printf("n1: %d\nn2: %d\n", n1, n2);
}

void test_vectorhandler(){
	printf("Test vectorhandler:\n");

    FILE*		cfile = fopen("input/2/c", "r");

	_vector* vector = parseVector(cfile);

	int i;
	for(i = 0; i < vector->nbr_of_elements; i++){
		printf("%f\n", fix_p2double(vector->elements[i]));
	}
}

// Testing fixed point
void test_int2fix_p(){
	printf("Test int2fix_p:\n");
	printf("%ld\n", int2fix_p(20));
}

void test_fix_p2double(){
	printf("Test fix_p2double:\n");
	printf("%f\n", fix_p2double(int2fix_p(3)>>1)); // 1.5
	printf("%f\n", fix_p2double(int2fix_p(-3))); 
}

void test_fix_p_mul(){
	printf("Test fix_p_mul:\n");
	printf("%f\n", fix_p2double(fix_p_mul(int2fix_p(3), int2fix_p(5)))); // 3 * 5 = 15
}

void test_fix_p_div(){
	printf("Test fix_p_div:\n");
	printf("%f\n", fix_p2double(fix_p_div(int2fix_p(3), int2fix_p(5)))); // 3 / 5 = 0.6
	printf("%f\n", fix_p2double(fix_p_div(int2fix_p(-3), int2fix_p(5)))); // -3 / 5 = -0.6
	printf("%f\n", fix_p2double(fix_p_div(int2fix_p(3), int2fix_p(-5)))); // 3 / -5 = -0.6
	printf("%f\n", fix_p2double(fix_p_div(int2fix_p(-3), int2fix_p(-5)))); // -3 / -5 = 0.6
}

/* Return 1 if the difference is negative, otherwise 0.  */
int timeval_subtract(struct timeval *result, struct timeval *t2, struct timeval *t1)
{
    long int diff = (t2->tv_usec + 1000000 * t2->tv_sec) - (t1->tv_usec + 1000000 * t1->tv_sec);
    result->tv_sec = diff / 1000000;
    result->tv_usec = diff % 1000000;

    return (diff<0);
}

void speed_test_fix_p_div(){
	printf("Speed test fix_p_div:\n");
	fix_p a = int2fix_p(3);
	fix_p b = int2fix_p(5);
	printf("Should be 0.6 is %f\n", fix_p2double(fix_p_div(a,b)));
	printf("Should be 0.75 is %f\n", fix_p2double(fix_p_div(a,int2fix_p(4))));
	// struct timeval tvBegin, tvEnd, tvDiff;
	// gettimeofday(&tvBegin, NULL);
	// int i;
	// for(i = 0; i < 100000000; ++i){
	// 	fix_p_div(a,b);
	// }
	// gettimeofday(&tvEnd, NULL);
	// timeval_subtract(&tvDiff, &tvEnd, &tvBegin);
	// printf("Time: %ld.%06ld s\n", tvDiff.tv_sec, tvDiff.tv_usec);

	a = int2fix_p(3);
	b = int2fix_p(2);
	printf("Should be 1.5 is %f\n", fix_p2double(fix_p_div(a,b)));
	// gettimeofday(&tvBegin, NULL);
	// for(i = 0; i < 100000000; ++i){
	// 	fix_p_div(a,b);
	// }
	// gettimeofday(&tvEnd, NULL);
	// timeval_subtract(&tvDiff, &tvEnd, &tvBegin);
	// printf("Time: %ld.%06ld s\n", tvDiff.tv_sec, tvDiff.tv_usec);
}

int main(void)
{
	// printf("%lu\n",sizeof(long long)*8);
	// test_parseMatrix();
	// printf("\n");
	// test_sort_matrix();
	// printf("\n");
	// test_vectorhandler();
	// printf("\n");
	// test_int2fix_p();
	// printf("\n");
	// test_fix_p2double();
	// printf("\n");
	// test_fix_p_mul();
	// printf("\n");
	// test_fix_p_div();
	// printf("\n");
	// speed_test_fix_p_div();
	printf("%lu\n", int2fix_p(1));
	printf("%lu\n", int2fix_p(3));
	printf("%f\n", fix_p2double(fix_p_div(int2fix_p(2), int2fix_p(-11))));
	printf("%f\n", fix_p2double(fix_p_mul(int2fix_p(2), fix_p_div(int2fix_p(1),int2fix_p(-11)))));
	printf("%f\n", fix_p2double(fix_p_div(65536,33759)));
	printf("%f\n", fix_p2double(fix_p_mul(33759,fix_p_div(65536,33759))));
}

