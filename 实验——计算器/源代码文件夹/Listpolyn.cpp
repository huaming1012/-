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

Status InitList_p(List_p &L){  //����ʽ˳���
    L.elem = (term*)malloc(ListInitSize*sizeof(term));
    if(!L.elem)     //����ʧ�����˳�
        exit(OVERFLOW);
    L.listsize = ListInitSize;  //��ʼ������
    L.length = 0;  //��ʼ��Ϊ��
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
	for(int i = 0; i < 100; i++){  //a�����ʼ��Ϊ0
        a[i].coef = 0;
        a[i].exp = 0;
    }
    for(int i = 0; i < L.length; i++){
    	int t = seek_p(a,L.elem[i].exp);
    	a[t].exp = L.elem[i].exp;
    	a[t].coef += L.elem[i].coef;
	}
	int k = 1;//L3����
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

//============˳������ʽ���������===============
//�Զ���ʽ˳����������
void Sort_p(List_p &L){
    int min_e = 999;  //��С�Ĵ���
    int min_pos = -1;  //������С��������λ��
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
        min_e = 999; //������Сֵ
    }
}

//����ʽ�ļӷ�
void add_p(List_p L1, List_p L2){
    List_p L3;
    InitList_p(L3);
    int i = 0, j = 0, k = 1;  //�ֱ���ΪL1��L2��L3������
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
    printf("����ǣ�\n"); 
    ShowList_p(L3);
}
//����ʽ�ļ���
void sub_p(List_p L1, List_p L2){
    List_p L3;
    InitList_p(L3);
    int i = 0, j = 0, k = 1;  //�ֱ���ΪL1��L2��L3������
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
    printf("����ǣ�\n"); 
    ShowList_p(L3);
}
//Ѱ��ָ��Ϊexp��������λ�ã����������򷵻ص�һ����λ��
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
//����ʽ���
void multiply_p(List_p L1, List_p L2){
    term a[100];
    term b;
    List_p L3;
    InitList_p(L3);
    int exp = 0;
    double coef;
    for(int i = 0; i < 100; i++){  //a�����ʼ��Ϊ0
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
    
    int k = 1;//L3����
    for(int i = 0; i < 100; i++){
        if(a[i].coef){  //����ϵ����0��Ԫ��
            b.coef = a[i].coef;
            b.exp = a[i].exp;
            ListInsert_p(L3, k++, b);
        }
    }
    Sort_p(L3);
    printf("����ǣ�\n"); 
    ShowList_p(L3);
}
//����ʽ��n�ε�
void derivation_p(List_p L, int n){
    term a[100];
    List_p L1;
    InitList_p(L1);
    int exp = 0;
    double coef = 0;
    for(int i = 0; i < 100; i++){  //a�����ʼ��Ϊ0
        a[i].coef = 0;
        a[i].exp = 0;
    }
    if(n > L.elem[L.length - 1].exp){  //����������ߴ����ָ����Ϊ0
        printf("����Ϊ0\n");
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
    printf("����ǣ�\n"); 
    ShowList_p(L1);
}

//x������ֵ
void calvalue_x_p(List_p L, double x){
	double ans = 0;
	for(int i = 0; i < L.length; i++){
		ans += L.elem[i].coef * pow(x, L.elem[i].exp);
	}
	printf("����ǣ�\n"); 
    cout << ans << endl;
}

//һԪ����ʽ�ļ��㣬�����ӷ����������˷�
void cal_polynomial_list(){
    int dim = -1, choice1 = -1, ans1 = -1, ans2 = -1;
    term tmp;
    List_p L1, L2;
    printf("����������������ʽ�����㣬������1�������һ������ʽ���󵼻��ֵ���㣬������2\n");
	scanf("%d", &choice1); 
	if(choice1 == 1){
	    printf("�������һ��һԪ����ʽ������\n");
	    scanf("%d",&dim); 
	    printf("�������һ��һԪ����ʽ��ϵ���ʹ���\n");
	    InitList_p(L1);
	    for(int i = 0; i < dim; i++){
	        cin >> tmp.coef >> tmp.exp;
	        ListInsert_p(L1, i+1, tmp);
	    }
	    Sort_p(L1);
	    printf("������ڶ���һԪ����ʽ������\n");
	    scanf("%d",&dim); 
	    printf("������ڶ���һԪ����ʽ��ϵ���ʹ���\n"); 
	    InitList_p(L2);
	    for(int i = 0; i < dim; i++){
	        cin >> tmp.coef >> tmp.exp;
	        ListInsert_p(L2, i+1, tmp);
	    }
	    Sort_p(L2);
	
	    printf("���мӷ����㣬������1����������������2���˷�����������3\n");
	    scanf("%d" ,&ans1);
	    if(ans1 == 1){
	        add_p(L1, L2);
	    }else if(ans1 == 2){
	        printf("Ĭ�ϵ�һ������ʽΪ����������Ҫ���ĵڶ�������ʽΪ������������1����������0\n");
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
		printf("������һԪ����ʽ������\n");
	    scanf("%d",&dim); 
	    printf("������һԪ����ʽ��ϵ���ʹ���\n");
	    InitList_p(L1);
	    for(int i = 0; i < dim; i++){
	        cin >> tmp.coef >> tmp.exp;
	        ListInsert_p(L1, i+1, tmp);
	    }
	    Sort_p(L1);
	    printf("������������1����ֵ����������2\n");
		cin >> ans2;
		if(ans2 == 1){
			printf("��������Ҫ�󵼵Ĵ���\n");
	    	int nn;
			cin >> nn;
			Sort_p(L1);
			derivation_p(L1, nn);
		}else if(ans2 == 2){
			printf("��������Ҫ�����x��ֵ\n");
			double xx;
			cin >> xx;
			calvalue_x_p(L1, xx);
		}
	}

    cout << "���ڣ����е����ݽ����������" << endl;
    DestroyList_p(L1);
    DestroyList_p(L2);
}



