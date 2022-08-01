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
    double coef;  //系数
    int exp;   //指数
}term; //一元多项式的每一项

typedef struct LNode{
    term data;
    struct LNode *next;
}LNode,*LinkList;
typedef LinkList polynomail;

//================链表的一系列操作==========================
//一元多项式链表的建立
Status CreatePolyn(polynomail &P);
//一元多项式链表的摧毁
Status DestoryPolyn(polynomail &P);
//删除链表中的p指针所指的项的后一项
Status ListDelete_L(polynomail &Pa, polynomail p);
//打印输出一元多项式
Status PrintPolyn(polynomail P);
//对多项式进行次数排序
void SortPolyn(polynomail &P);
//返回多项式的项数
int PolynLength(polynomail P);
//在链表尾端插入项e
Status ListInsert_L(polynomail &Pa, term e);
//多项式的加法（链表）
Status AddPolyn(polynomail Pa, polynomail Pb, polynomail &Pc);
//多项式的减法（链表）
Status SubtractPolyn(polynomail Pa, polynomail Pb, polynomail &Pc);
//多项式的乘法（链表）
Status MultiplyPolyn(polynomail Pa,polynomail Pb);
//多项式的求n次导数（链表） 
Status DerivationPolyn(polynomail Pc, int n);
//多项式的运算（链表）
void cal_polynomial_L(); 
//x带入求值
void calvalue_x(polynomail P, double x); 
#endif // LINKLIST_H
