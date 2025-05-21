#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 列主元高斯消去法求解线性方程组 Ax = b
// 参数：A-系数矩阵，b-常数向量，x-解向量，n-方程阶数
// 返回：0-成功，1-矩阵奇异
int gauss_elimination(double **A, double *b, double *x, int n) {
    int i, j, k, pivot_row;
    double max_val, factor, temp;
    for (k = 0; k < n-1; k++) {
        // 选主元：找到当前列绝对值最大的元素
        max_val = fabs(A[k][k]);
        pivot_row = k;
        for (i = k+1; i < n; i++) {
            if (fabs(A[i][k]) > max_val) {
                max_val = fabs(A[i][k]);
                pivot_row = i;
            }
        }      
        // 如果主元为0，则矩阵奇异
        if (max_val < 1e-10) {
            return 1;
        }  
        // 交换行
        if (pivot_row != k) {
            for (j = k; j < n; j++) {
                temp = A[k][j];
                A[k][j] = A[pivot_row][j];
                A[pivot_row][j] = temp;
            }
            temp = b[k];
            b[k] = b[pivot_row];
            b[pivot_row] = temp;
        }   
        // 消元
        for (i = k+1; i < n; i++) {
            factor = A[i][k] / A[k][k];
            for (j = k+1; j < n; j++) {
                A[i][j] -= factor * A[k][j];
            }
            A[i][k] = 0.0;  // 显式置零
            b[i] -= factor * b[k];
        }
    } 
    // 检查最后一个主元
    if (fabs(A[n-1][n-1]) < 1e-10) {
        return 1;
    }
    // 回代求解
    x[n-1] = b[n-1] / A[n-1][n-1];
    for (i = n-2; i >= 0; i--) {
        double sum = b[i];
        for (j = i+1; j < n; j++) {
            sum -= A[i][j] * x[j];
        }
        x[i] = sum / A[i][i];
    }  
    return 0;  // 成功
}

int main() {
    int n = 3;  // 方程组阶数
    
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
    
    // 求解方程组
    if (gauss_elimination(A, b, x, n) == 0) {
        printf("方程组的解为:\n");
        for (int i = 0; i < n; i++) {
            printf("x%d = %.6f\n", i+1, x[i]);
        }
    } else {
        printf("错误: 矩阵奇异，方程组无解或有无穷多解\n");
    }
    
    // 释放内存
    for (int i = 0; i < n; i++) {
        free(A[i]);
    }
    free(A);
    free(b);
    free(x);
    
    return 0;
}    