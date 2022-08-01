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


//===================顺序表（包括向量和多项式）的一系列操作
//顺序表的创建
Status InitList(List &L){
    L.elem = (ElemType*)malloc(ListInitSize*sizeof(ElemType));
    if(!L.elem)     //分配失败则退出
        exit(OVERFLOW);
    L.listsize = ListInitSize;  //初始表容量
    L.length = 0;  //初始表为空
    return OK;
}
//顺序表的销毁
Status DestroyList(List &L){
    free(L.elem);
    L.elem = NULL;
    L.length = 0;
    L.listsize = 0;
    return OK;
}
//顺序表的遍历
void ShowList(List L){
    for(int i = 0; i < L.length; i++){
        printf("%d ", L.elem[i]);
    }
    printf("\n");
}

//顺序表的清空
void ClearList(List &L){
    L.length = 0;
    L.listsize = ListInitSize;
}


//判断是否为空(顺序表)
int ListEmpty(List L){
    if(L.length == 0)
        return 1;
    else 
        return 0;
}

//获取列表长度(顺序表)
Status ListLength(List L){
    if(!L.elem)
		exit(OVERFLOW);
    return L.length;
}


//返回L中第i个元素到e(顺序表)
Status GetElem(List L, int i, ElemType &e){
    e = L.elem[i];
    return OK;
}

//在i处插入元素e(顺序表)
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


//删除i处元素,其值返回到e(顺序表)
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


//=========向量的运算操作=============
//线性表向量的加法
List add(List L1, List L2){
    List L3;
    InitList(L3);
    for(int i = 0; i < L1.length; i++){
        ListInsert(L3, i+1, L1.elem[i] + L2.elem[i]);
    }
    return L3;
}

//线性表向量的减法
List sub(List L1, List L2){
    List L3;
    InitList(L3);
    for(int i = 0; i < L1.length; i++){
        ListInsert(L3, i+1, L1.elem[i] - L2.elem[i]);
    }
    return L3;
}

//线性表向量的乘法 
List multiply(List L1, List L2){
    List L3;
    InitList(L3);
    for(int i = 0; i < L1.length; i++){
        ListInsert(L3, i+1, L1.elem[i] * L2.elem[i]);
    }
    return L3;
}

//向量的夹角余弦值
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

void cal_vactor(){   //同维度向量的计算，包括加法、减法、乘法和求夹角余弦值
    int dim = -1,ans1=-1;
    List L1, L2, L3;
    int tmp;

    printf("========同维度向量的运算：=======\n");
    printf("请输入向量的维数\n");
    scanf("%d",&dim); 

	printf("请输入第一组向量的数据\n");
    InitList(L1);
    for(int i = 0; i < dim; i++){
        cin >> tmp;
        ListInsert(L1, i+1, tmp);
    }

    printf("请输入第二组向量的数据\n"); 
    InitList(L2);
    for(int i = 0; i < dim; i++){
        cin >> tmp;
        ListInsert(L2, i+1, tmp);
    }

    printf("进行加法运算，请输入1，减法运算请输入2，向量的乘法请输入3，计算夹角的余弦值请输入4\n");
    scanf("%d" ,&ans1);
    if(ans1 == 1){
        L3 = add(L1, L2);
        printf("结果是：\n"); 
        ShowList(L3);
    }else if(ans1 == 2){
        printf("默认第一个向量为被减数，若要更改请输入1，否则输入0\n");
        int change;
        cin >> change;
        if(change){
            L3 = sub(L2, L1);
            printf("结果是：\n"); 
            ShowList(L3);
        }else{
            L3 = sub(L1, L2);
            printf("结果是：\n"); 
            ShowList(L3);
        }
    }else if(ans1 == 3){
        L3 = multiply(L1, L2);
        printf("结果是：\n"); 
        ShowList(L3);
    }else{
    	printf("结果是：\n"); 
        cout << cosvalue(L1, L2) << endl;
    }

    cout << "现在，所有的数据将被清空销毁" << endl;
    DestroyList(L1);
    DestroyList(L2);
    DestroyList(L3);
    
}
