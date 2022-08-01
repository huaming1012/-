#ifndef __LISTPOLYN_H__
#define __LISTPOLYN_H__
#include "Listpolyn.h"

typedef int ElemType;
typedef int Status;

#define ListInitSize 100
#define LISTINCREMENT 10
//#define OVERFLOW -2
#define OK 1
#define ERROR 0


typedef struct{
    double coef;  //ϵ��
    int exp;   //ָ��
}term; //һԪ����ʽ��ÿһ��
typedef struct{
    term *elem;
    int length;
    int listsize;
}List_p; //һԪ����ʽ��˳���

//����ʽ˳���
//���� 
Status InitList_p(List_p &L);
//�ݻ� 
Status DestroyList_p(List_p &L);
//������� 
void ShowList_p(List_p L);
void ClearList_p(List_p &L);
Status ListLength_p(List_p L);
Status ListInsert_p(List_p &L, int i, term e);
Status ListDelete_p(List_p &L, int i, term &e);
//============˳������ʽ���������===============
//�Զ���ʽ˳����������
void Sort_p(List_p &L);

//����ʽ�ļӷ�
void add_p(List_p L1, List_p L2);
//����ʽ�ļ���
void sub_p(List_p L1, List_p L2);
//Ѱ��ָ��Ϊexp��������λ�ã����������򷵻ص�һ����λ��
int seek_p(term* a, int exp);
//����ʽ���
void multiply_p(List_p L1, List_p L2);
//����ʽ��n�ε�
void derivation_p(List_p L, int n);
//һԪ����ʽ�ļ��㣬�����ӷ����������˷�
void cal_polynomial_list();
//x������ֵ
void calvalue_x_p(List_p L, double x); 

#endif

