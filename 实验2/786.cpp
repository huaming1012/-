#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <algorithm>

void add(int** A, int** B, int** C, int row, int col){  //两矩阵相加
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void sub(int** A, int** B, int** C, int row, int col){  //矩阵相减
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void Strassen(int N, int** A, int** B, int** C){
    int newSize = N / 2;
    if(N < 2){   //边界情况
        C[0][0] = A[0][0]*B[0][0];
    }else{
        int** A11;    //矩阵分块
		int** A12;
		int** A21;
		int** A22;
 
		int** B11;
		int** B12;
		int** B21;
		int** B22;
 
		int** C11;
		int** C12;
		int** C21;
		int** C22;

        int** M1;
		int** M2;
		int** M3;
		int** M4;
		int** M5;
		int** M6;
		int** M7;
		int** AResult;
		int** BResult;

        A11 = new int *[newSize];   //分别分配空间
		A12 = new int *[newSize];
		A21 = new int *[newSize];
		A22 = new int *[newSize];
 
		B11 = new int *[newSize];
		B12 = new int *[newSize];
		B21 = new int *[newSize];
		B22 = new int *[newSize];
 
		C11 = new int *[newSize];
		C12 = new int *[newSize];
		C21 = new int *[newSize];
		C22 = new int *[newSize];

		M1 = new int *[newSize];			
        M2 = new int *[newSize];
		M3 = new int *[newSize];
		M4 = new int *[newSize];
		M5 = new int *[newSize];
		M6 = new int *[newSize];
		M7 = new int *[newSize];
 
		AResult = new int *[newSize];
		BResult = new int *[newSize];
        for(int i = 0; i < newSize; i++){
            A11[i] = new int[newSize];
            A12[i] = new int[newSize];
            A21[i] = new int[newSize];
            A22[i] = new int[newSize];

            B11[i] = new int[newSize];
            B12[i] = new int[newSize];
            B21[i] = new int[newSize];
            B22[i] = new int[newSize];

            C11[i] = new int[newSize];
            C12[i] = new int[newSize];
            C21[i] = new int[newSize];
            C22[i] = new int[newSize];

            M1[i] = new int[newSize];
            M2[i] = new int[newSize];
            M3[i] = new int[newSize];
            M4[i] = new int[newSize];
            M5[i] = new int[newSize];
            M6[i] = new int[newSize];
            M7[i] = new int[newSize];

            AResult[i] = new int[newSize];
            BResult[i] = new int[newSize];
        }

        for(int i = 0; i < N / 2; i++){    //分块矩阵赋值
            for(int j = 0; j < N / 2; j++){
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + N/2];
                A21[i][j] = A[i + N/2][j];
                A22[i][j] = A[i + N/2][j + N/2];

                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + N/2];
                B21[i][j] = B[i + N/2][j];
                B22[i][j] = B[i + N/2][j + N/2];
            }
        }

        //M1=A11(B12-B22)
        sub(B12, B22, BResult, newSize, newSize);
        Strassen(newSize, A11, BResult, M1);
        //M2=(A11+A12)B22
        add(A11, A12, AResult, newSize, newSize);
        Strassen(newSize, AResult, B22, M2);
        //M3=(A21+A22)B11
        add(A21, A22, AResult, newSize, newSize);
        Strassen(newSize, AResult, B11, M3);
        //M4=A22(B21-B11)
        sub(B21, B11, BResult, newSize, newSize);
        Strassen(newSize, A22, BResult, M4);
        //M5=(A11+A22)(B11+B22)
        add(A11, A22, AResult, newSize, newSize);
        add(B11, B22, BResult, newSize, newSize);
        Strassen(newSize, AResult, BResult, M5);
        //M6=(A12-A22)(B21+B22)
        sub(A12, A22, AResult, newSize, newSize);
        add(B21, B22, BResult, newSize, newSize);
        Strassen(newSize, AResult, BResult, M6);
        //M7=(A11-A21)(B11+B12)
        sub(A11, A21, AResult, newSize, newSize);
        add(B11, B12, BResult, newSize, newSize);
        Strassen(newSize, AResult, BResult, M7);

        //C11=M5+M4-M2+M6
        add(M5, M4, AResult, newSize, newSize);
        sub(M6, M2, BResult, newSize, newSize);
        add(AResult, BResult, C11, newSize, newSize);
        //C12=M1+M2
        add(M1, M2, C12, newSize, newSize);
        //C21=M3+M4
        add(M3, M4, C21, newSize, newSize);
        //C22=M5+M1-M3-M7
        add(M5, M1, AResult, newSize, newSize);
        add(M3, M7, BResult, newSize, newSize);
        sub(AResult, BResult, C22, newSize, newSize);


        for(int i = 0; i < N/2; i++){   //拼接成矩阵C
            for(int j = 0; j < N/2; j++){
                C[i][j] = C11[i][j];
                C[i][j + N/2] = C12[i][j];
                C[i + N/2][j] = C21[i][j];
                C[i + N/2][j + N/2] = C22[i][j];
            }
        }
        
        //释放动态分配的空间
        for(int i = 0; i < newSize; i++){
            delete[] A11[i];
            delete[] A12[i];
            delete[] A21[i];
            delete[] A22[i];
            delete[] B11[i];
            delete[] B12[i];
            delete[] B21[i];
            delete[] B22[i];
            delete[] C11[i];
            delete[] C12[i];
            delete[] C21[i];
            delete[] C22[i];

            delete[] M1[i];
            delete[] M2[i];
            delete[] M3[i];
            delete[] M4[i];
            delete[] M5[i];
            delete[] M6[i];
            delete[] M7[i];

            delete[] AResult[i];
            delete[] BResult[i];
        }

        delete[] A11;
        delete[] A12;
        delete[] A21;
        delete[] A22;
        delete[] B11;
        delete[] B12;
        delete[] B21;
        delete[] B22;
        delete[] C11;
        delete[] C12;
        delete[] C21;
        delete[] C22;

        delete[] M1;
        delete[] M2;
        delete[] M3;
        delete[] M4;
        delete[] M5;
        delete[] M6;
        delete[] M7;
        delete[] AResult;
        delete[] BResult;
    }
}

int main(){
    int n, m, p;
    scanf("%d %d %d", &n, &m, &p);
    int tmp = std::max(std::max(n, m),p) - 1;
    int k = 0;
    while(tmp){
        tmp /= 2;
        k++;
    }
    int N = pow(2, k);   //扩充成2的幂次
    int** A = (int**)malloc(sizeof(int*)*N);
    int** B = (int**)malloc(sizeof(int*)*N);
    int** C = (int**)malloc(sizeof(int*)*N);
    for(int i = 0; i < N; i++){
        A[i] = (int*)malloc(sizeof(int)*N);
        B[i] = (int*)malloc(sizeof(int)*N);
        C[i] = (int*)malloc(sizeof(int)*N);
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            A[i][j] = 0;
            B[i][j] = 0;
            C[i][j] = 0;
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            scanf("%d", &A[i][j]);
        }
    }
    for(int i = 0; i < m; i++){
        for(int j = 0; j < p; j++){
            scanf("%d", &B[i][j]);
        }
    }
    Strassen(N, A, B, C);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < p; j++){
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
    return 0;
}