#include "Listpolyn.h"
#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

#define ListInitSize 100
#define LISTINCREMENT 10
//#define OVERFLOW -2
#define OK 1
#define ERROR 0


int seek_p(term* a, int exp);
Status ListInsert_p(List_p &L, int i, term e);

Status InitList_p(List_p &L){  //多项式顺序表
    L.elem = (term*)malloc(ListInitSize*sizeof(term));
    if(!L.elem)     //分配失败则退出
        exit(OVERFLOW);
    L.listsize = ListInitSize;  //初始表容量
    L.length = 0;  //初始表为空
    return OK;
}
Status DestroyList_p(List_p &L){
    free(L.elem);
    L.elem = NULL;
    L.length = 0;
    L.listsize = 0;
    return OK;
}
void ShowList_p(List_p L){
	List_p L3;
	InitList_p(L3);
	term a[100];
	for(int i = 0; i < 100; i++){  //a数组初始化为0
        a[i].coef = 0;
        a[i].exp = 0;
    }
    for(int i = 0; i < L.length; i++){
    	int t = seek_p(a,L.elem[i].exp);
    	a[t].exp = L.elem[i].exp;
    	a[t].coef += L.elem[i].coef;
	}
	int k = 1;//L3索引
    for(int i = 0; i < 100; i++){
        if(!a[i].coef)
            continue;
        ListInsert_p(L3, i + 1, a[i]);
    }
    for(int i = 0; i < L3.length; i++){
        if(L3.elem[i].coef == 0) continue;
        if(L3.elem[i].coef > 0 && i != 0)
        	printf("+");
        if(L3.elem[i].exp && L3.elem[i].coef)
        	printf("%.2lfx^%d",L3.elem[i].coef, L3.elem[i].exp);
    	else if(L3.elem[i].exp == 0 && L3.elem[i].coef)
    		printf("%.2lf",L3.elem[i].coef);
    }
    printf("\n");
}
void ClearList_p(List_p &L){
    L.length = 0;
    L.listsize = ListInitSize;
}
Status ListLength_p(List_p L){
    if(!L.elem)
		exit(OVERFLOW);
    return L.length;
}
Status ListInsert_p(List_p &L, int i, term e){
    if(i < 1 || i > L.length + 1) return ERROR;
    if(L.length >= L.listsize){
        term *newbase = (term *)realloc(L.elem, (L.listsize + LISTINCREMENT)*sizeof(term));
        if(!newbase) exit(OVERFLOW); 
        L.elem = newbase;
        L.listsize += LISTINCREMENT;
    }
    if(!L.length){
		L.elem[0].coef = e.coef;
        L.elem[0].exp = e.exp;
		L.length++;
		return 1;
	}
    term *q = &(L.elem[i-1]);
    for(term *p = &L.elem[L.length - 1]; p >= q; --p){
        *(p + 1) = *p;
    } 
    *q = e;
    ++L.length;
    return OK;
}
Status ListDelete_p(List_p &L, int i, term &e){
    if(i < 1 || i > L.length) return ERROR;
    term *p = &L.elem[i-1];
    e = *p;
    term *q = L.elem + L.length - 1;
    for(++p; p <= q; ++p){
        *(p - 1) = *p;
    }
    --L.length;
    return OK;
}

//============顺序表多项式的运算操作===============
//对多项式顺序表进行排序
void Sort_p(List_p &L){
    int min_e = 999;  //最小的次数
    int min_pos = -1;  //次数最小的项所在位置
    for(int i = 0; i < L.length; i++){
        for(int j = i; j < L.length; j++){
            if(L.elem[j].exp < min_e){
                min_e = L.elem[j].exp;
                min_pos = j;
            }
        }
        int tmp_e = L.elem[i].exp;
        double tmp_x = L.elem[i].coef;
        L.elem[i].exp = min_e;
        L.elem[i].coef = L.elem[min_pos].coef;
        L.elem[min_pos].exp = tmp_e;
        L.elem[min_pos].coef = tmp_x; 
        min_e = 999; //重置最小值
    }
}

//多项式的加法
void add_p(List_p L1, List_p L2){
    List_p L3;
    InitList_p(L3);
    int i = 0, j = 0, k = 1;  //分别作为L1，L2，L3的索引
    while(i < L1.length && j < L2.length){
        if(L1.elem[i].exp < L2.elem[j].exp){
            ListInsert_p(L3, k++, L1.elem[i]);
            i++;
        }else if(L1.elem[i].exp > L2.elem[j].exp){
            ListInsert_p(L3, k++, L2.elem[j]);
            j++;
        }else{
            term t;
            t.exp = L1.elem[i].exp;
            t.coef = L1.elem[i].coef + L2.elem[j].coef;
            if(t.coef){
                ListInsert_p(L3, k++, t);
                i++;
                j++;
            }
        }
    }
    if(i >= L1.length){
        for(j; j < L2.length; j++){
            ListInsert_p(L3, j+1, L2.elem[j]);
        }
    }else{
        for(i; i < L1.length; i++){
            ListInsert_p(L3, i+1, L1.elem[i]);
        }
    }
    Sort_p(L3);
    printf("结果是：\n"); 
    ShowList_p(L3);
}
//多项式的减法
void sub_p(List_p L1, List_p L2){
    List_p L3;
    InitList_p(L3);
    int i = 0, j = 0, k = 1;  //分别作为L1，L2，L3的索引
    while(i < L1.length && j < L2.length){
        if(L1.elem[i].exp < L2.elem[j].exp){
            ListInsert_p(L3, k++, L1.elem[i]);
            i++;
        }else if(L1.elem[i].exp > L2.elem[j].exp){
            L2.elem[j].coef = 0-L2.elem[j].coef;
            ListInsert_p(L3, k++, L2.elem[j]);
            j++;
        }else{
            term t;
            t.exp = L1.elem[i].exp;
            t.coef = L1.elem[i].coef - L2.elem[j].coef;
            if(t.coef){
                ListInsert_p(L3, k++, t);
                
            }
            i++;
            j++;
        }
    }
    if(i >= L1.length){
        for(j; j < L2.length; j++){
            L2.elem[j].coef = 0-L2.elem[j].coef;
            ListInsert_p(L3, j+1, L2.elem[j]);
        }
    }else{
        for(i; i < L1.length; i++){
            ListInsert_p(L3, i+1, L1.elem[i]);
        }
    }
    Sort_p(L3);
    printf("结果是：\n"); 
    ShowList_p(L3);
}
//寻找指数为exp的项所在位置，若不存在则返回第一个空位置
int seek_p(term* a, int exp){
    int i = 0; 
    for(i = 0; i < 100; i++){
        if(a[i].exp == exp)
            return i;
        if(a[i].exp == 0 && a[i].coef == 0)
            break;
    }
    return i;
}
//多项式相乘
void multiply_p(List_p L1, List_p L2){
    term a[100];
    term b;
    List_p L3;
    InitList_p(L3);
    int exp = 0;
    double coef;
    for(int i = 0; i < 100; i++){  //a数组初始化为0
        a[i].coef = 0;
        a[i].exp = 0;
    }
    for(int i = 0; i < L1.length; i++){
        for(int j = 0; j < L2.length; j++){
            exp = L1.elem[i].exp + L2.elem[j].exp;
            coef = L1.elem[i].coef * L2.elem[j].coef;
            
            int t = seek_p(a, exp);

            a[t].exp = exp;
            a[t].coef += coef;
            
        }
    }
    
    int k = 1;//L3索引
    for(int i = 0; i < 100; i++){
        if(a[i].coef){  //插入系数非0的元素
            b.coef = a[i].coef;
            b.exp = a[i].exp;
            ListInsert_p(L3, k++, b);
        }
    }
    Sort_p(L3);
    printf("结果是：\n"); 
    ShowList_p(L3);
}
//多项式求n次导
void derivation_p(List_p L, int n){
    term a[100];
    List_p L1;
    InitList_p(L1);
    int exp = 0;
    double coef = 0;
    for(int i = 0; i < 100; i++){  //a数组初始化为0
        a[i].coef = 0;
        a[i].exp = 0;
    }
    if(n > L.elem[L.length - 1].exp){  //次数大于最高次项的指数则为0
        printf("导数为0\n");
        return;
    }
    for(int i = 0; i < L.length; i++){
        if(L.elem[i].exp >= n){
            exp = L.elem[i].exp;
            coef = L.elem[i].coef;
            for(int j = 0; j < n; j++){
                coef = coef * exp;
                exp--;
            }
            exp = L.elem[i].exp - n;
            int t = seek_p(a,exp);
            a[t].coef += coef;
            a[t].exp = exp;
        }
    }
    for(int i = 0; i < 100; i++){
        if(!a[i].coef)
            continue;
        ListInsert_p(L1, i + 1, a[i]);
    }
    Sort_p(L1);
    printf("结果是：\n"); 
    ShowList_p(L1);
}

//x带入求值
void calvalue_x_p(List_p L, double x){
	double ans = 0;
	for(int i = 0; i < L.length; i++){
		ans += L.elem[i].coef * pow(x, L.elem[i].exp);
	}
	printf("结果是：\n"); 
    cout << ans << endl;
}

//一元多项式的计算，包括加法、减法、乘法
void cal_polynomial_list(){
    int dim = -1, choice1 = -1, ans1 = -1, ans2 = -1;
    term tmp;
    List_p L1, L2;
    printf("如果想进行两个多项式的运算，请输入1；想进行一个多项式的求导或代值运算，请输入2\n");
	scanf("%d", &choice1); 
	if(choice1 == 1){
	    printf("请输入第一个一元多项式的项数\n");
	    scanf("%d",&dim); 
	    printf("请输入第一个一元多项式的系数和次数\n");
	    InitList_p(L1);
	    for(int i = 0; i < dim; i++){
	        cin >> tmp.coef >> tmp.exp;
	        ListInsert_p(L1, i+1, tmp);
	    }
	    Sort_p(L1);
	    printf("请输入第二个一元多项式的项数\n");
	    scanf("%d",&dim); 
	    printf("请输入第二个一元多项式的系数和次数\n"); 
	    InitList_p(L2);
	    for(int i = 0; i < dim; i++){
	        cin >> tmp.coef >> tmp.exp;
	        ListInsert_p(L2, i+1, tmp);
	    }
	    Sort_p(L2);
	
	    printf("进行加法运算，请输入1，减法运算请输入2，乘法运算请输入3\n");
	    scanf("%d" ,&ans1);
	    if(ans1 == 1){
	        add_p(L1, L2);
	    }else if(ans1 == 2){
	        printf("默认第一个多项式为被减数，若要更改第二个多项式为被减数请输入1，否则输入0\n");
	        int change;
	        cin >> change;
	        if(change){
	            sub_p(L2, L1);
	        }else{
	            sub_p(L1, L2);
	        }
	    }else if(ans1 == 3){
	        multiply_p(L1, L2);
	    }
	}else if(choice1 == 2){
		printf("请输入一元多项式的项数\n");
	    scanf("%d",&dim); 
	    printf("请输入一元多项式的系数和次数\n");
	    InitList_p(L1);
	    for(int i = 0; i < dim; i++){
	        cin >> tmp.coef >> tmp.exp;
	        ListInsert_p(L1, i+1, tmp);
	    }
	    Sort_p(L1);
	    printf("求导运算请输入1，代值运算请输入2\n");
		cin >> ans2;
		if(ans2 == 1){
			printf("请输入你要求导的次数\n");
	    	int nn;
			cin >> nn;
			Sort_p(L1);
			derivation_p(L1, nn);
		}else if(ans2 == 2){
			printf("请输入你要带入的x的值\n");
			double xx;
			cin >> xx;
			calvalue_x_p(L1, xx);
		}
	}

    cout << "现在，所有的数据将被清空销毁" << endl;
    DestroyList_p(L1);
    DestroyList_p(L2);
}



