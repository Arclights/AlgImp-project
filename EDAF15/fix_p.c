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

fix_p fix_p_mul(fix_p fp1, fix_p fp2){
	return ((fp1 * fp2) >> DECIMALS);
}

fix_p fix_p_div(fix_p fp1, fix_p fp2){
	// // printf("%f\n", fix_p2double(fp2));
	// printf("%f/%f\n", fix_p2double(fp1),fix_p2double(fp2));
	// int sign2;
	// int sign1;
	// sign2 = ((fp2 >> 63) & 1) ? -1 : (fp2 != 0);
	// sign1 = ((fp1 >> 63) & 1) ? -1 : (fp1 != 0);
	// int sign;
	// if(((fp1 >> 63) & 1)&&((fp2 >> 63) & 1)){
	// 	sign = 1;
	// } else if((!((fp1 >> 63) & 1)&&((fp2 >> 63) & 1))||(((fp1 >> 63) & 1)&&!((fp2 >> 63) & 1))){
	// 	sign = -1;
	// }else{
	// 	sign = 1;
	// }
	// // printf("sign1: %d\n",sign1);
	// fp1 = fp1 * sign1;
	// fp2 = fp2 * sign2;
	// if(fp2 != 0 && (fp2 & (fp2-1)) == 0){
	// 	fp1 = fp1 << DECIMALS;
	// 	// int pow = 0;
	// 	// fp2 = fp2 >> 1;
	// 	// printf("%ld\n", ((int2fix_p(2)>>1) & 0x0000000100000001));
	// 	do{
	// 		fp2 = fp2 >> 1;
	// 		// pow++;
	// 		fp1 = fp1 >> 1;
	// 	}while(!(fp2 & 0x0000000100000001));
	// 	// printf("%d\n", pow);
	// 	// return (fp1 >> pow) * sign2;
	// 	return fp1 * sign2;

	// }


	// unsigned long sign2;
	// unsigned long sign1;
	// sign2 = ((fp2 >> 63) & 1) ? 0x7FFFFFFFFFFFFFFF : 0xFFFFFFFFFFFFFFFF;
	// sign1 = ((fp1 >> 63) & 1) ? 0x7FFFFFFFFFFFFFFF : 0xFFFFFFFFFFFFFFFF;
	// unsigned long sign = sign1&sign2;
	// unsigned long fp1_ul = fp1;
	// printf("%f/%f\n", fix_p2double(fp1),fix_p2double(fp2));
	// printf("%f/%f\n", fix_p2double(fp1&sign1),fix_p2double(fp2&sign2));
	// // // printf("%f/%f\n", fix_p2double(((unsigned long)fp1)),fix_p2double(((unsigned long)fp2)));
	// // // return ((((unsigned long)fp1)<<DECIMALS) / ((unsigned long)fp2))*sign2;
	// return (((unsigned long)(fp1&sign1<<DECIMALS)) / ((unsigned long)fp2&sign2))| sign;


	// printf("%f/%f\n", fix_p2double((fp1& 0x7FFFFFFFFFFFFFFF)),fix_p2double(fp2));
	// printf("%f/%f\n", fix_p2double((fp1& 0x7FFFFFFFFFFFFFFF)| 0x8000000000000000),fix_p2double(fp2));
	// return ((((unsigned long)fp1)<<DECIMALS) / ((unsigned long)fp2))*sign;

	return (fp1 << DECIMALS) / fp2;
}
