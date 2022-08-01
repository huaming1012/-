#ifndef __LINKLIST_H__
#define __LINKLIST_H__
#include "LinkList.h"


#define ListInitSize 100
#define LISTINCREMENT 10
//#define OVERFLOW -2
#define OK 1
#define ERROR 0

typedef int ElemType;
typedef int Status;


typedef struct{
    double coef;  //ϵ��
    int exp;   //ָ��
}term; //һԪ����ʽ��ÿһ��

typedef struct LNode{
    term data;
    struct LNode *next;
}LNode,*LinkList;
typedef LinkList polynomail;

//================�����һϵ�в���==========================
//һԪ����ʽ����Ľ���
Status CreatePolyn(polynomail &P);
//һԪ����ʽ����Ĵݻ�
Status DestoryPolyn(polynomail &P);
//ɾ�������е�pָ����ָ����ĺ�һ��
Status ListDelete_L(polynomail &Pa, polynomail p);
//��ӡ���һԪ����ʽ
Status PrintPolyn(polynomail P);
//�Զ���ʽ���д�������
void SortPolyn(polynomail &P);
//���ض���ʽ������
int PolynLength(polynomail P);
//������β�˲�����e
Status ListInsert_L(polynomail &Pa, term e);
//����ʽ�ļӷ�������
Status AddPolyn(polynomail Pa, polynomail Pb, polynomail &Pc);
//����ʽ�ļ���������
Status SubtractPolyn(polynomail Pa, polynomail Pb, polynomail &Pc);
//����ʽ�ĳ˷�������
Status MultiplyPolyn(polynomail Pa,polynomail Pb);
//����ʽ����n�ε��������� 
Status DerivationPolyn(polynomail Pc, int n);
//����ʽ�����㣨����
void cal_polynomial_L(); 
//x������ֵ
void calvalue_x(polynomail P, double x); 
#endif // LINKLIST_H
