#include "matrix.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
using namespace std;


Matrix::Matrix(int m, int n) {
    row = m;
    column = n;
    matrix = new double*[row];    //指向一级指针数组
    for (int i = 0; i < row; i++) 
	{
        matrix[i] = new double[column];  //指向一维数组
    }
}

void Matrix::getnum()   //输入数据
{
	for(int i = 0; i < row; i++)
	for(int j = 0; j < column; j++)
	{
		cin >> matrix[i][j];
	}
	return;
}

void Matrix::display()
{
	for(int i = 0; i < row; i++)
	{
		for(int j = 0; j < column; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	return;
}

Matrix::~Matrix(){
    for(int i = 0; i < row; i++){
        delete[] matrix[i];
    }
    delete[] matrix;
}

bool canAdd(const Matrix & L, const Matrix & R) {
    if (L.row == R.row && L.column == R.column) {
        return true;
    }
    return false;
}

bool canMul(const Matrix & L, const Matrix & R) 
{
    if (L.column == R.row) {            //左边列数与右边行数相等才可乘
        return true;
    }
    return false;
}
//矩阵L与R相加，结果放在temp内
void add(Matrix &L, Matrix &R, Matrix &temp)
{
    if (canAdd(L, R)) {
        for (int i = 0; i < L.row; i++) {
            for (int j = 0; j < L.column; j++) {
                temp.matrix[i][j] = L.matrix[i][j] + R.matrix[i][j];
            }
        }
        return;
    }
    else {
        cout << "无法相加" << endl;
        exit(0);
    }
}
//矩阵L与R相减，结果放在temp内
void sub(Matrix &L, Matrix &R, Matrix &temp)
{
    if (canAdd(L, R)) {
        for (int i = 0; i < L.row; i++) {
            for (int j = 0; j < L.column; j++) {
                temp.matrix[i][j] = L.matrix[i][j] - R.matrix[i][j];
            }
        }
        return;
    }
    else {
        cout << "无法相减" << endl;
        exit(0);
    }
}
//矩阵L与R相乘，结果放在temp内
void mul(Matrix &L, Matrix &R, Matrix &temp)
{
    if (canMul(L, R)) {        //判断是否合法
        for (int i = 0; i < L.row; i++) {
            for (int j = 0; j < R.column; j++) {
                double sum=0;
                for (int k = 0; k < L.column; k++) {
                    sum += L.matrix[i][k] * R.matrix[k][j];    //累加第i行与第j列的元素乘积
                }
                temp.matrix[i][j] = sum; 
            }
        }
        return;
    }
    else {
        cout << "无法相乘" << endl;
        exit(0);
    }
}
//矩阵转置，结果放在temp内
void Matrix::T(Matrix &temp){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            temp.matrix[j][i] = matrix[i][j];
        }
    }
    return;
}

//m行n列的矩阵M求行列式
double det(double **M, int m, int n){
    double ans = 0;
    if(m != n){
        cout << "不能求行列式" << endl;
        return 0;
    }
    if(n == 1)
        ans = M[0][0];
    else if(n == 2)
        ans = M[0][0]*M[1][1] - M[0][1]*M[1][0];
    else{
        for(int k = 0; k < n; k++){
            double **A;//代数余子式
            //分配内存
            A = (double**)malloc((n-1)*sizeof(double*));
            for(int i = 0; i < n-1; i++){
                A[i] = (double*)malloc((n-1)*sizeof(double));
            }

            //赋值
            for(int i = 0; i < n-1; i++){
                for(int j = 0; j < n-1; j++){
                    if(j < k)
                        A[i][j] = M[i+1][j];
                    else
                        A[i][j] = M[i+1][j+1];
                }
            }

            if(M[0][k]){
                if((k+2)%2)
                    ans += M[0][k] * det(A, n-1, n-1)*(-1);
                else
                    ans += M[0][k] * det(A, n-1, n-1);
            }

            for(int i = 0; i < n-1; i++){
                free(A[i]);
            }
            free(A);
        }
    }
    return ans;
}


void calMatrix(){
    int tmp1 = -1;
    int m1, m2, n1, n2;
    //Matrix A, B, C;
    cout << "想做矩阵的加法运算请输入1，减法运算请输入2，乘法运算请输入3，转置运算请输入4，求行列式请输入5" << endl;
    cin >> tmp1;
    if(tmp1 == 1){
        cout << "请输入第一个矩阵的行数和列数" << endl;
        cin >> m1 >> n1;
        Matrix A(m1, n1);
        cout << "请输入第一个矩阵的元素" << endl;
        A.getnum();
        cout << "请输入第二个矩阵的行数和列数" << endl;
        cin >> m2 >> n2;
        Matrix B(m2, n2);
        cout << "请输入第二个矩阵的元素" << endl;
        B.getnum();

        Matrix C(m1, n1);
        add(A, B, C);
        cout << "结果是：" << endl;
        C.display();
    }else if(tmp1 == 2){
        cout << "请输入第一个矩阵的行数和列数" << endl;
        cin >> m1 >> n1;
        Matrix A(m1, n1);
        cout << "请输入第一个矩阵的元素" << endl;
        A.getnum();
        cout << "请输入第二个矩阵的行数和列数" << endl;
        cin >> m2 >> n2;
        Matrix B(m2, n2);
        cout << "请输入第二个矩阵的元素" << endl;
        B.getnum();

        Matrix C(m1, n1);
        sub(A, B, C);
        cout << "结果是：" << endl;
        C.display();
    }else if(tmp1 == 3){
        cout << "请输入第一个矩阵的行数和列数" << endl;
        cin >> m1 >> n1;
        Matrix A(m1, n1);
        cout << "请输入第一个矩阵的元素" << endl;
        A.getnum();
        cout << "请输入第二个矩阵的行数和列数" << endl;
        cin >> m2 >> n2;
        Matrix B(m2, n2);
        cout << "请输入第二个矩阵的元素" << endl;
        B.getnum();

        Matrix C(m1, n2);
        mul(A, B, C);
        cout << "结果是：" << endl;
        C.display();
    }else if(tmp1 == 4){
        cout << "请输入矩阵的行数和列数" << endl;
        cin >> m1 >> n1;
        Matrix A(m1, n1);
        cout << "请输入矩阵的元素" << endl;
        A.getnum();

        Matrix C(n1, m1);
        A.T(C);
        cout << "结果是：" << endl;
        C.display();
    }else if(tmp1 == 5){
        cout << "请输入矩阵的行数和列数" << endl;
        cin >> m1 >> n1;
        Matrix A(m1, n1);
        cout << "请输入矩阵的元素" << endl;
        A.getnum();

        double ans = det(A.matrix, m1, n1);
        cout << "结果是：" << endl;
        cout << ans << endl;
    }else{
        cout << "ERROR!!" << endl;
    }
}


