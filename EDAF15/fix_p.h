#ifndef FIX_P_H
#define FIX_P_H

typedef long fix_p;

fix_p int2fix_p(int in);

double fix_p2double(fix_p in);

// Maybe not exact!
// Maybe not needed
fix_p fix_p_mul(fix_p fp1, fix_p fp2);

fix_p fix_p_div(fix_p fp1, fix_p fp2);

#endif