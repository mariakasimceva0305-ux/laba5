#include "../include/lrps.h"
#include <math.h>
#include <stdio.h>

Formula find_formula(int a, int b, int c, int d) {
    Formula result;
    
    // Характеристическое уравнение: r² - a*r - b = 0
    // D = a² + 4b
    double discriminant = (double)(a * a) + 4.0 * (double)b;
    
    // Проверка на комплексные корни
    if (discriminant < -1e-12) {
        result.case_type = -1;
        return result;
    }
    
    double root_D = sqrt(fabs(discriminant));
    result.r1 = ((double)a + root_D) / 2.0;
    result.r2 = ((double)a - root_D) / 2.0;
    
    // Проверка на кратные корни
    if (fabs(discriminant) < 1e-12) {
        // Кратные корни x_n = C1 * r^(n-1) + C2 * (n-1) * r^(n-1)
        result.case_type = 2;
        result.coef1 = (double)c; // C1 = x1
        
        if (fabs(result.r1) < 1e-12) {
            // При r = 0
            result.coef2 = (double)d; // При r=0: x2 = C2
        } else {
            result.coef2 = ((double)d - (double)c * result.r1) / result.r1; // C2 = (x2 - x1*r)/r
        }
    } else {
        // Разные x_n = C1*r1^(n-1) + C2*r2^(n-1)
        result.case_type = 1;
       
        //  система, C1 + C2 = x1
        // C1*r1 + C2*r2 = x2
        double denominator = result.r1 - result.r2;
        
        if (fabs(denominator) < 1e-12) {
            // иф деления на ноль 
            result.case_type = 2;
            result.coef1 = (double)c;
            result.coef2 = 0.0;
        } else {
            result.coef1 = ((double)d - (double)c * result.r2) / denominator;
            result.coef2 = ((double)c * result.r1 - (double)d) / denominator;
        }
    }
    
    return result;
}


void show_formula(Formula f) {
    if (f.case_type == -1) {
        printf("Complex roots case - formula cannot be expressed in real numbers\n");
        return;
    }
    
    printf("x_n = ");
    
    if (f.case_type == 1) {
        // Разные к. x_n = C1*r1^(n-1) + C2*r2^(n-1)
        
        // 1 слаг
        if (fabs(f.coef1) > 1e-10) {
            if (fabs(f.coef1 - 1.0) > 1e-10 && fabs(f.coef1 + 1.0) > 1e-10) {
                printf("%.6f", f.coef1);
            } else if (fabs(f.coef1 + 1.0) < 1e-10) {
                printf("-");
            }
            
            if (fabs(f.r1 - 1.0) > 1e-10 && fabs(f.r1 + 1.0) > 1e-10) {
                printf(" * %.6f", f.r1);
            } else if (fabs(f.r1 + 1.0) < 1e-10) {
                printf(" * (-1)");
            }
            printf("^(n-1)");
        }
        
        // 2ое слаг
        if (fabs(f.coef2) > 1e-10) {
            if (fabs(f.coef1) > 1e-10) {
                printf(" %c ", (f.coef2 > 0) ? '+' : '-');
            } else if (f.coef2 < 0) {
                printf("-");
            }
            
            if (fabs(fabs(f.coef2) - 1.0) > 1e-10) {
                printf("%.6f", fabs(f.coef2));
            }
            
            if (fabs(f.r2 - 1.0) > 1e-10 && fabs(f.r2 + 1.0) > 1e-10) {
                if (fabs(fabs(f.coef2) - 1.0) > 1e-10) printf(" * ");
                printf("%.6f", f.r2);
            } else if (fabs(f.r2 + 1.0) < 1e-10) {
                if (fabs(fabs(f.coef2) - 1.0) > 1e-10) printf(" * ");
                printf("(-1)");
            }
            printf("^(n-1)");
        }
        
        // кк оба 0
        if (fabs(f.coef1) < 1e-10 && fabs(f.coef2) < 1e-10) {
            printf("0");
        }
    } else {
        // Кратные к. x_n = (C1 + C2*(n-1)) * r^(n-1)
        printf("(");
        
        if (fabs(f.coef1) > 1e-10) {
            printf("%.6f", f.coef1);
            if (fabs(f.coef2) > 1e-10) {
                printf(" + %.6f*(n-1)", f.coef2);
            }
        } else if (fabs(f.coef2) > 1e-10) {
            printf("%.6f*(n-1)", f.coef2);
        } else {
            printf("0");
        }
        printf(")");
        
        if (fabs(f.r1 - 1.0) > 1e-10 && fabs(f.r1 + 1.0) > 1e-10) {
            printf(" * %.6f", f.r1);
        } else if (fabs(f.r1 + 1.0) < 1e-10) {
            printf(" * (-1)");
        }
        printf("^(n-1)");
    }
    
    printf("\n");
}