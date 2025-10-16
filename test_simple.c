#include <stdio.h>
#include <math.h>

int main() {
    int a = 1, b = 1, c = 1, d = 1;
    
    printf("Testing: a=%d, b=%d, c=%d, d=%d\n", a, b, c, d);
    
    double discriminant = a * a + 4.0 * b;
    printf("Discriminant: %f\n", discriminant);
    
    double sqrt_d = sqrt(discriminant);
    double r1 = (a + sqrt_d) / 2.0;
    double r2 = (a - sqrt_d) / 2.0;
    printf("Roots: r1=%f, r2=%f\n", r1, r2);
    
    double A = (d - c * r2) / (r1 - r2);
    double B = (c * r1 - d) / (r1 - r2);
    printf("Coefficients: A=%f, B=%f\n", A, B);
    
    printf("Formula: x_n = %.6f * %.6f^(n-1) + %.6f * %.6f^(n-1)\n", A, r1, B, r2);
    
    return 0;
}