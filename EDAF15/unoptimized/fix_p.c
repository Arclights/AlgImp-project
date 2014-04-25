#define DECIMALS 16
#define FIX2DOUBLE_DIVIDER 65536.0
#include <stdio.h>
#include "fix_p.h"

fix_p int2fix_p(int in){
	return ((long) in) << DECIMALS;
}

double fix_p2double(fix_p in){
	return in / FIX2DOUBLE_DIVIDER;
}

// Maybe not exact!
// Maybe not needed
fix_p fix_p_mul(fix_p fp1, fix_p fp2){
	return ((fp1 >> DECIMALS) * fp2);
}

fix_p fix_p_div(fix_p fp1, fix_p fp2){
	return (fp1 << DECIMALS) / fp2;
}
