#ifndef __MATRIX_H__
#define __MATRIX_H__


class Matrix {
public:
	Matrix(){}
    Matrix(int m, int n);   //���캯����m��n��
    Matrix(const Matrix & c)
	{
		row=c.row;
		column=c.column;
	}

    ~Matrix(); //��������
    
    
	void display(); //�������
    void getnum();   //�������Ԫ��
    friend void add(Matrix &A, Matrix &B, Matrix &C);  //���  
    friend void sub(Matrix &A, Matrix &B, Matrix &C);  //���  
    friend void mul(Matrix &A, Matrix &B, Matrix &C);  //��� 
    friend double det(double **M, int m ,int n);   //������ʽ
    void T(Matrix &temp); //ת��
    
    friend bool canAdd(const Matrix &,const Matrix &);        //����Ƿ�ɼ�
    friend bool canMul(const Matrix &, const Matrix &);       //����Ƿ�ɳ�

    
    int row;   
    int column; 
    double ** matrix;   //ָ�����Ķ�ά����
 
};

void calMatrix();
 

#endif
