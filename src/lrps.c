#include "../include/lrps.h"
#include <math.h>
#include <stdio.h>

Formula find_formula(int a, int b, int c, int d) {
    Formula result;
    
    double D = (double)(a * a) + 4.0 * (double)b;
    
    if (D < -0.0000001) {
        result.case_type = -1;
        return result;
    }
    
    double root_D = sqrt(D);
    result.r1 = ((double)a + root_D) / 2.0;
    result.r2 = ((double)a - root_D) / 2.0;
    
    if (fabs(result.r1 - result.r2) < 0.0000001) {
        result.case_type = 2;
        result.coef1 = (double)c;
        result.coef2 = ((double)d - (double)c * result.r1) / result.r1;
    } else {
        result.case_type = 1;
        result.coef1 = ((double)d - (double)c * result.r2) / (result.r1 - result.r2);
        result.coef2 = ((double)c * result.r1 - (double)d) / (result.r1 - result.r2);
    }
    
    return result;
}

void show_formula(Formula f) {
    if (f.case_type == -1) {
        printf("Complex roots case\n");
        return;
    }
    
    printf("x_n = ");
    
    if (f.case_type == 1) {
        printf("%.6f * %.6f^(n-1) + %.6f * %.6f^(n-1)", f.coef1, f.r1, f.coef2, f.r2);
    } else {
        printf("(%.6f + %.6f*(n-1)) * %.6f^(n-1)", f.coef1, f.coef2, f.r1);
    }
    printf("\n");
}