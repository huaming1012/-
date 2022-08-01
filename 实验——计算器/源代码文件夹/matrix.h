#ifndef __MATRIX_H__
#define __MATRIX_H__


class Matrix {
public:
	Matrix(){}
    Matrix(int m, int n);   //构造函数，m行n列
    Matrix(const Matrix & c)
	{
		row=c.row;
		column=c.column;
	}

    ~Matrix(); //析构函数
    
    
	void display(); //输出矩阵
    void getnum();   //输入矩阵元素
    friend void add(Matrix &A, Matrix &B, Matrix &C);  //相加  
    friend void sub(Matrix &A, Matrix &B, Matrix &C);  //相减  
    friend void mul(Matrix &A, Matrix &B, Matrix &C);  //相乘 
    friend double det(double **M, int m ,int n);   //求行列式
    void T(Matrix &temp); //转置
    
    friend bool canAdd(const Matrix &,const Matrix &);        //检查是否可加
    friend bool canMul(const Matrix &, const Matrix &);       //检查是否可乘

    
    int row;   
    int column; 
    double ** matrix;   //指向矩阵的二维数组
 
};

void calMatrix();
 

#endif
