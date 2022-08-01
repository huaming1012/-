#include "List.h"
#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

#define ListInitSize 100
#define LISTINCREMENT 10
//#define OVERFLOW -2
#define OK 1
#define ERROR 0


//===================˳������������Ͷ���ʽ����һϵ�в���
//˳���Ĵ���
Status InitList(List &L){
    L.elem = (ElemType*)malloc(ListInitSize*sizeof(ElemType));
    if(!L.elem)     //����ʧ�����˳�
        exit(OVERFLOW);
    L.listsize = ListInitSize;  //��ʼ������
    L.length = 0;  //��ʼ��Ϊ��
    return OK;
}
//˳��������
Status DestroyList(List &L){
    free(L.elem);
    L.elem = NULL;
    L.length = 0;
    L.listsize = 0;
    return OK;
}
//˳���ı���
void ShowList(List L){
    for(int i = 0; i < L.length; i++){
        printf("%d ", L.elem[i]);
    }
    printf("\n");
}

//˳�������
void ClearList(List &L){
    L.length = 0;
    L.listsize = ListInitSize;
}


//�ж��Ƿ�Ϊ��(˳���)
int ListEmpty(List L){
    if(L.length == 0)
        return 1;
    else 
        return 0;
}

//��ȡ�б���(˳���)
Status ListLength(List L){
    if(!L.elem)
		exit(OVERFLOW);
    return L.length;
}


//����L�е�i��Ԫ�ص�e(˳���)
Status GetElem(List L, int i, ElemType &e){
    e = L.elem[i];
    return OK;
}

//��i������Ԫ��e(˳���)
Status ListInsert(List &L, int i, ElemType e){
    if(i < 1 || i > L.length + 1) return ERROR;
    if(L.length >= L.listsize){
        ElemType *newbase = (ElemType *)realloc(L.elem, (L.listsize + LISTINCREMENT)*sizeof(ElemType));
        if(!newbase) exit(OVERFLOW); 
        L.elem = newbase;
        L.listsize += LISTINCREMENT;
    }
    if(!L.length){
		L.elem[0]=e;
		L.length++;
		return 1;
	}
    ElemType *q = &(L.elem[i-1]);
    for(ElemType *p = &L.elem[L.length - 1]; p >= q; --p){
        *(p + 1) = *p;
    } 
    *q = e;
    ++L.length;
    return OK;
}


//ɾ��i��Ԫ��,��ֵ���ص�e(˳���)
Status ListDelete(List &L, int i, ElemType &e){
    if(i < 1 || i > L.length) return ERROR;
    ElemType *p = &L.elem[i-1];
    e = *p;
    ElemType *q = L.elem + L.length - 1;
    for(++p; p <= q; ++p){
        *(p - 1) = *p;
    }
    --L.length;
    return OK;
}


//=========�������������=============
//���Ա������ļӷ�
List add(List L1, List L2){
    List L3;
    InitList(L3);
    for(int i = 0; i < L1.length; i++){
        ListInsert(L3, i+1, L1.elem[i] + L2.elem[i]);
    }
    return L3;
}

//���Ա������ļ���
List sub(List L1, List L2){
    List L3;
    InitList(L3);
    for(int i = 0; i < L1.length; i++){
        ListInsert(L3, i+1, L1.elem[i] - L2.elem[i]);
    }
    return L3;
}

//���Ա������ĳ˷� 
List multiply(List L1, List L2){
    List L3;
    InitList(L3);
    for(int i = 0; i < L1.length; i++){
        ListInsert(L3, i+1, L1.elem[i] * L2.elem[i]);
    }
    return L3;
}

//�����ļн�����ֵ
double cosvalue(List L1, List L2){
    double sum_xy = 0, sum_xx = 0, sum_yy = 0;
    for(int i = 0; i < L1.length; i++){
        sum_xy += L1.elem[i]*L2.elem[i];
        sum_xx += L1.elem[i]*L1.elem[i];
        sum_yy += L2.elem[i]*L2.elem[i];
    }
    sum_xx = sqrt(sum_xx);
    sum_yy = sqrt(sum_yy);
    return sum_xy / (sum_xx * sum_yy);
}

void cal_vactor(){   //ͬά�������ļ��㣬�����ӷ����������˷�����н�����ֵ
    int dim = -1,ans1=-1;
    List L1, L2, L3;
    int tmp;

    printf("========ͬά�����������㣺=======\n");
    printf("������������ά��\n");
    scanf("%d",&dim); 

	printf("�������һ������������\n");
    InitList(L1);
    for(int i = 0; i < dim; i++){
        cin >> tmp;
        ListInsert(L1, i+1, tmp);
    }

    printf("������ڶ�������������\n"); 
    InitList(L2);
    for(int i = 0; i < dim; i++){
        cin >> tmp;
        ListInsert(L2, i+1, tmp);
    }

    printf("���мӷ����㣬������1����������������2�������ĳ˷�������3������нǵ�����ֵ������4\n");
    scanf("%d" ,&ans1);
    if(ans1 == 1){
        L3 = add(L1, L2);
        printf("����ǣ�\n"); 
        ShowList(L3);
    }else if(ans1 == 2){
        printf("Ĭ�ϵ�һ������Ϊ����������Ҫ����������1����������0\n");
        int change;
        cin >> change;
        if(change){
            L3 = sub(L2, L1);
            printf("����ǣ�\n"); 
            ShowList(L3);
        }else{
            L3 = sub(L1, L2);
            printf("����ǣ�\n"); 
            ShowList(L3);
        }
    }else if(ans1 == 3){
        L3 = multiply(L1, L2);
        printf("����ǣ�\n"); 
        ShowList(L3);
    }else{
    	printf("����ǣ�\n"); 
        cout << cosvalue(L1, L2) << endl;
    }

    cout << "���ڣ����е����ݽ����������" << endl;
    DestroyList(L1);
    DestroyList(L2);
    DestroyList(L3);
    
}
