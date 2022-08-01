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
    double coef;  //系数
    int exp;   //指数
}term; //一元多项式的每一项
typedef struct{
    term *elem;
    int length;
    int listsize;
}List_p; //一元多项式的顺序表

//多项式顺序表
//创建 
Status InitList_p(List_p &L);
//摧毁 
Status DestroyList_p(List_p &L);
//遍历输出 
void ShowList_p(List_p L);
void ClearList_p(List_p &L);
Status ListLength_p(List_p L);
Status ListInsert_p(List_p &L, int i, term e);
Status ListDelete_p(List_p &L, int i, term &e);
//============顺序表多项式的运算操作===============
//对多项式顺序表进行排序
void Sort_p(List_p &L);

//多项式的加法
void add_p(List_p L1, List_p L2);
//多项式的减法
void sub_p(List_p L1, List_p L2);
//寻找指数为exp的项所在位置，若不存在则返回第一个空位置
int seek_p(term* a, int exp);
//多项式相乘
void multiply_p(List_p L1, List_p L2);
//多项式求n次导
void derivation_p(List_p L, int n);
//一元多项式的计算，包括加法、减法、乘法
void cal_polynomial_list();
//x带入求值
void calvalue_x_p(List_p L, double x); 

#endif

