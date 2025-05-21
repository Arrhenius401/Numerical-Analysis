#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// SOR迭代法求解线性方程组 Ax = b
// 参数：A-系数矩阵，b-常数向量，x-解向量，n-方程阶数，
//       omega-松弛因子，iterations-迭代次数
void sor_iteration(double **A, double *b, double *x, int n, double omega, int iterations) {
    int i, j, iter;
    double sum;
    
    // 初始化解向量为零向量
    for (i = 0; i < n; i++) {
        x[i] = 0.0;
    }
    
    // 执行指定次数的迭代
    for (iter = 0; iter < iterations; iter++) {
        printf("迭代 %d 次后的解 (ω=%.1f):\n", iter+1, omega);
        
        // 对每个未知数进行更新
        for (i = 0; i < n; i++) {
            sum = b[i];
            
            // 计算sum = b[i] - Σ(a[i][j]*x[j]) (j≠i)
            for (j = 0; j < n; j++) {
                if (j != i) {
                    sum -= A[i][j] * x[j];
                }
            }
            
            // SOR更新公式: x[i] = (1-ω)*x[i] + ω*(sum / A[i][i])
            x[i] = (1.0 - omega) * x[i] + omega * (sum / A[i][i]);
            printf("x%d = %.6f\n", i+1, x[i]);
        }
        printf("\n");
    }
}

int main() {
    int n = 3;  // 方程组阶数
    int iterations = 5;  // 迭代次数
    double omega = 1.1;  // 松弛因子
    
    // 动态分配矩阵和向量内存
    double **A = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        A[i] = (double *)malloc(n * sizeof(double));
    }
    double *b = (double *)malloc(n * sizeof(double));
    double *x = (double *)malloc(n * sizeof(double));
    
    // 示例方程组:
    // 4x + y - z = 3
    // 2x + 5y + z = 9
    // x - 2y + 6z = -4
    A[0][0] = 4.0; A[0][1] = 1.0; A[0][2] = -1.0; b[0] = 3.0;
    A[1][0] = 2.0; A[1][1] = 5.0; A[1][2] = 1.0; b[1] = 9.0;
    A[2][0] = 1.0; A[2][1] = -2.0; A[2][2] = 6.0; b[2] = -4.0;
    
    // 使用SOR方法求解
    printf("SOR迭代法 (松弛因子ω=%.1f，迭代 %d 次):\n\n", omega, iterations);
    sor_iteration(A, b, x, n, omega, iterations);
    
    // 释放内存
    for (int i = 0; i < n; i++) {
        free(A[i]);
    }
    free(A);
    free(b);
    free(x);
    
    return 0;
}   