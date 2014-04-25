/* Anything may be changed, except matrix sizes and float type. 
 *
 * The output when defining CHECK should be the same with and without tuning.
 * 
 */

#include <stdio.h>
#include <string.h>
#include <sys/time.h>

// #define CHECK

#define I	(10000)
#define S	(10)
#define B (20)

#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))

#ifdef CHECK
#define TYPE	int
#define N (3)
#else
#define TYPE	float
#define N (512)
#endif

TYPE a[N][N];
TYPE b[N][N];
TYPE c[N][N];

/**
Original
**/
void f0()
{
	size_t	i, j, k;

	for (i = 0; i < N; i += 1) {
		for (j = 0; j < N; j += 1) {
			a[i][j] = 0;
			for (k = 0; k < N; k += 1)
				a[i][j] += b[i][k] * c[k][j];
		}
	}
}

/**
Rearanged the loops
**/
void f1()
{
	size_t	i, j, k;

	for (i = 0; i < N; i += 1) {
		memset(a[i], 0, N);
		for (k = 0; k < N; k += 1){
			for (j = 0; j < N; j += 1) {
				a[i][j] += b[i][k] * c[k][j];
			}
		}
	}
}

/**
Rearanged the loops
Extracted b[i][k]
Unraveled loop
**/
void f2()
{
	size_t	i, j, k;

	int bik;

	for (i = 0; i < N; i += 1) {
		memset(a[i], 0, N);
		for (k = 0; k < N; k += 1){
			bik = b[i][k];
			for (j = 0; j < N-1; j += 2) {
				a[i][j] += bik * c[k][j];
				a[i][j+1] += bik * c[k][j+1];
			}
			for (; j < N; j += 1) {
				a[i][j] += bik * c[k][j];
			}
		}
	}
}

/**
Rearanged the loops
Extracted b[i][k]
Unraveled loop
Using pointers instead
**/
void f3()
{
	size_t	i, j, k;

	TYPE* bi;
	TYPE* ai;
	TYPE* ck;

	for (i = 0; i < N; i += 1) {
		memset(a[i], 0, N);
		bi = b[i];
		for (k = 0; k < N; k += 1){
			ai = a[i];
			ck = c[k];
			for (j = 0; j < N-2; j += 3) {
				*ai++ += *bi * *ck++;
				*ai++ += *bi * *ck++;
				*ai++ += *bi * *ck++;
			}
			for (; j < N; j += 1) {
				*ai += *bi * *ck;
			}
			bi++;
		}
	}
}

/**
Rearanged the loops
Tiling
**/
void f4()
{
	size_t	i, j, k;
	size_t jj, kk;

	memset(a, 0, sizeof a);
	for(kk = 0; kk < N; kk += B){
		for(jj = 0; jj < N; jj += B){
			for (i = 0; i < N; ++i) {
				for (k = kk; k < MIN(N, kk+B); ++k){
					for (j = jj; j < MIN(N, jj+B); ++j) {
						a[i][j] += b[i][k] * c[k][j];
					}
				}
			}
		}
	}
}

void init()
{
#ifdef CHECK
	size_t	i, j;

	for (i = 0; i < N; i += 1) {
		for (j = 0; j < N; j += 1) {
			b[i][j] = 12 + i * j * 13;
			c[i][j] = -13 + i + j * 21;
		}
	}
#endif
}

void output()
{
#ifdef CHECK
	size_t	i, j;

	for (i = 0; i < N; i += 1)
		for (j = 0; j < N; j += 1)
			printf("a[%3zu][%3zu] = %d\n", i, j, a[i][j]);
#endif
}

void (*fun[])() = { 
	f0,
	f1,
	f2,
	f3,
	f4
};

/* Return 1 if the difference is negative, otherwise 0.  */
int timeval_subtract(struct timeval *result, struct timeval *t2, struct timeval *t1)
{
    long int diff = (t2->tv_usec + 1000000 * t2->tv_sec) - (t1->tv_usec + 1000000 * t1->tv_sec);
    result->tv_sec = diff / 1000000;
    result->tv_usec = diff % 1000000;

    return (diff<0);
}

int main(void)
{
	size_t	i;
	size_t	j;

	struct timeval tvBegin, tvEnd, tvDiff;
	
	for (j = 0; j < sizeof fun/sizeof fun[0]; ++j) {
		memset(a, 0, sizeof a);
		gettimeofday(&tvBegin, NULL);
		for (i = 0; i < I; ++i)
			init();
			fun[j]();
		gettimeofday(&tvEnd, NULL);
		output();
		timeval_subtract(&tvDiff, &tvEnd, &tvBegin);
		printf("%ld.%06ld s\n", tvDiff.tv_sec, tvDiff.tv_usec);
	}
}