#ifndef __LIST_H__
#define __LIST_H__
#include "List.h"

#define ListInitSize 100
#define LISTINCREMENT 10
//#define OVERFLOW -2
#define OK 1
#define ERROR 0

typedef int ElemType;
typedef int Status;

typedef struct{
    ElemType *elem;
    int length;
    int listsize;
}List;

//顺序表的创建
Status InitList(List &L);
//顺序表的销毁
Status DestroyList(List &L);
//顺序表的遍历
void ShowList(List L);
//顺序表的清空
void ClearList(List &L);
//判断是否为空(顺序表)
int ListEmpty(List L);
//获取列表长度(顺序表)
Status ListLength(List L);
//返回L中第i个元素到e(顺序表)
Status GetElem(List L, int i, ElemType &e);

//在i处插入元素e(顺序表)
Status ListInsert(List &L, int i, ElemType e);
//删除i处元素,其值返回到e(顺序表)
Status ListDelete(List &L, int i, ElemType &e);

//线性表向量的加法
List add(List L1, List L2);
//线性表向量的减法
List sub(List L1, List L2);
//线性表向量的数乘
List multiply(List L1, List L2);
//向量的夹角余弦值
double cosvalue(List L1, List L2);

void cal_vactor();
#endif
