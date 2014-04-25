#include <stdio.h>
typedef struct _rational _rational;

struct _rational{
	long long numerator;
	long long denominator;
};

void create_rational(_rational* r, long long numerator, long long denominator){
    if(denominator < 0){
    	numerator = numerator * -1;
    	denominator = denominator * -1;
    }

    r->numerator = numerator;
    r->denominator = denominator;
}

_rational* allocate_rational(long long numerator, long long denominator){
	_rational* rat = malloc(sizeof(_rational));

	if(rat == NULL){
        fprintf(stderr,"Out of memory");
    }

    create_rational(rat, numerator, denominator);

    return rat;
}

void print_rational(_rational* rat, int end_line){
	if(rat->denominator == 1){
		if(end_line){
			printf("%lli\n", rat->numerator);
		}else{
			printf("%lli", rat->numerator);
		}
	}else{
		if(end_line){
			printf("%lli/%lli\n", rat->numerator, rat->denominator);
		}else{
			printf("%lli/%lli", rat->numerator, rat->denominator);
		}
	}
}

_rational* add_rationals(_rational* rat1, _rational* rat2){
	return allocate_rational(rat1->numerator * rat2->denominator + rat2->numerator * rat1->denominator, rat1->denominator * rat2->denominator);
}

_rational* mult_rationals(_rational* r1, _rational* r2){
	return allocate_rational(r1->numerator * r2->numerator, r1->denominator * r2->denominator);
}