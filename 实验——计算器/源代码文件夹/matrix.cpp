#include "matrix.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
using namespace std;


Matrix::Matrix(int m, int n) {
    row = m;
    column = n;
    matrix = new double*[row];    //ָ��һ��ָ������
    for (int i = 0; i < row; i++) 
	{
        matrix[i] = new double[column];  //ָ��һά����
    }
}

void Matrix::getnum()   //��������
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
    if (L.column == R.row) {            //����������ұ�������Ȳſɳ�
        return true;
    }
    return false;
}
//����L��R��ӣ��������temp��
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
        cout << "�޷����" << endl;
        exit(0);
    }
}
//����L��R������������temp��
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
        cout << "�޷����" << endl;
        exit(0);
    }
}
//����L��R��ˣ��������temp��
void mul(Matrix &L, Matrix &R, Matrix &temp)
{
    if (canMul(L, R)) {        //�ж��Ƿ�Ϸ�
        for (int i = 0; i < L.row; i++) {
            for (int j = 0; j < R.column; j++) {
                double sum=0;
                for (int k = 0; k < L.column; k++) {
                    sum += L.matrix[i][k] * R.matrix[k][j];    //�ۼӵ�i�����j�е�Ԫ�س˻�
                }
                temp.matrix[i][j] = sum; 
            }
        }
        return;
    }
    else {
        cout << "�޷����" << endl;
        exit(0);
    }
}
//����ת�ã��������temp��
void Matrix::T(Matrix &temp){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            temp.matrix[j][i] = matrix[i][j];
        }
    }
    return;
}

//m��n�еľ���M������ʽ
double det(double **M, int m, int n){
    double ans = 0;
    if(m != n){
        cout << "����������ʽ" << endl;
        return 0;
    }
    if(n == 1)
        ans = M[0][0];
    else if(n == 2)
        ans = M[0][0]*M[1][1] - M[0][1]*M[1][0];
    else{
        for(int k = 0; k < n; k++){
            double **A;//��������ʽ
            //�����ڴ�
            A = (double**)malloc((n-1)*sizeof(double*));
            for(int i = 0; i < n-1; i++){
                A[i] = (double*)malloc((n-1)*sizeof(double));
            }

            //��ֵ
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
    cout << "��������ļӷ�����������1����������������2���˷�����������3��ת������������4��������ʽ������5" << endl;
    cin >> tmp1;
    if(tmp1 == 1){
        cout << "�������һ�����������������" << endl;
        cin >> m1 >> n1;
        Matrix A(m1, n1);
        cout << "�������һ�������Ԫ��" << endl;
        A.getnum();
        cout << "������ڶ������������������" << endl;
        cin >> m2 >> n2;
        Matrix B(m2, n2);
        cout << "������ڶ��������Ԫ��" << endl;
        B.getnum();

        Matrix C(m1, n1);
        add(A, B, C);
        cout << "����ǣ�" << endl;
        C.display();
    }else if(tmp1 == 2){
        cout << "�������һ�����������������" << endl;
        cin >> m1 >> n1;
        Matrix A(m1, n1);
        cout << "�������һ�������Ԫ��" << endl;
        A.getnum();
        cout << "������ڶ������������������" << endl;
        cin >> m2 >> n2;
        Matrix B(m2, n2);
        cout << "������ڶ��������Ԫ��" << endl;
        B.getnum();

        Matrix C(m1, n1);
        sub(A, B, C);
        cout << "����ǣ�" << endl;
        C.display();
    }else if(tmp1 == 3){
        cout << "�������һ�����������������" << endl;
        cin >> m1 >> n1;
        Matrix A(m1, n1);
        cout << "�������һ�������Ԫ��" << endl;
        A.getnum();
        cout << "������ڶ������������������" << endl;
        cin >> m2 >> n2;
        Matrix B(m2, n2);
        cout << "������ڶ��������Ԫ��" << endl;
        B.getnum();

        Matrix C(m1, n2);
        mul(A, B, C);
        cout << "����ǣ�" << endl;
        C.display();
    }else if(tmp1 == 4){
        cout << "��������������������" << endl;
        cin >> m1 >> n1;
        Matrix A(m1, n1);
        cout << "����������Ԫ��" << endl;
        A.getnum();

        Matrix C(n1, m1);
        A.T(C);
        cout << "����ǣ�" << endl;
        C.display();
    }else if(tmp1 == 5){
        cout << "��������������������" << endl;
        cin >> m1 >> n1;
        Matrix A(m1, n1);
        cout << "����������Ԫ��" << endl;
        A.getnum();

        double ans = det(A.matrix, m1, n1);
        cout << "����ǣ�" << endl;
        cout << ans << endl;
    }else{
        cout << "ERROR!!" << endl;
    }
}


