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

//˳���Ĵ���
Status InitList(List &L);
//˳��������
Status DestroyList(List &L);
//˳���ı���
void ShowList(List L);
//˳�������
void ClearList(List &L);
//�ж��Ƿ�Ϊ��(˳���)
int ListEmpty(List L);
//��ȡ�б���(˳���)
Status ListLength(List L);
//����L�е�i��Ԫ�ص�e(˳���)
Status GetElem(List L, int i, ElemType &e);

//��i������Ԫ��e(˳���)
Status ListInsert(List &L, int i, ElemType e);
//ɾ��i��Ԫ��,��ֵ���ص�e(˳���)
Status ListDelete(List &L, int i, ElemType &e);

//���Ա������ļӷ�
List add(List L1, List L2);
//���Ա������ļ���
List sub(List L1, List L2);
//���Ա�����������
List multiply(List L1, List L2);
//�����ļн�����ֵ
double cosvalue(List L1, List L2);

void cal_vactor();
#endif
