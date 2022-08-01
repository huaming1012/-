#include "LinkList.h"
#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

#define ListInitSize 100
#define LISTINCREMENT 10
//#define OVERFLOW -2
#define OK 1
#define ERROR 0

//================�����һϵ�в���==========================
//һԪ����ʽ����Ľ���
Status CreatePolyn(polynomail &P){
    P = (polynomail)malloc(sizeof(LNode));
    if(!P)
        exit(OVERFLOW);
    P->next = NULL;
    return OK;
}
//һԪ����ʽ����Ĵݻ�
Status DestoryPolyn(polynomail &P){
    polynomail tmp;
    while (P)
    {
        tmp = P->next;
        free(P);
        P = tmp;
    }
    return OK;
}
//ɾ�������е�pָ����ָ����ĺ�һ��
Status ListDelete_L(polynomail &Pa, polynomail p){
    polynomail tmp = p->next;
    p->next = p->next->next;
    free(tmp);
    return OK;
}
//��ӡ���һԪ����ʽ
Status PrintPolyn(polynomail P){
    polynomail q = P->next;
    int j = 1;
    while(q){
        if(q->data.coef > 0 && j != 1)
            printf("+");
        if(q->data.exp && q->data.coef)
            printf("%.2fx^%d",q->data.coef,q->data.exp);
        else if(q->data.coef && q->data.exp == 0)
            printf("%.2f",q->data.coef);
        q = q->next;
        j++;
    }
    printf("\n");
    return OK;
}
//�Զ���ʽ���д�������
void SortPolyn(polynomail &P){
    int min = 999;
    polynomail min_pos = P;
    polynomail q = P, p = P;
    if(!q->next->next)//ֻ��һ����
        return;
    while(q->next){
        min = q->next->data.exp;
        p = q->next;
        while(p){
            if(p->data.exp < min){
                min = p->data.exp;
                min_pos = p;
            }
            p = p->next;
        }
        if(q->next->data.exp > min){
            int exp = q->next->data.exp;
            double coef = q->next->data.coef;
            q->next->data.coef = min_pos->data.coef;
            q->next->data.exp = min_pos->data.exp;
            min_pos->data.coef = coef;
            min_pos->data.exp = exp;
        }
        p = q;
        while(p->next){
        	if(p->next->data.exp == q->data.exp){
        		q->data.coef += p->next->data.coef;
        		ListDelete_L(P,p);
			}
			p = p->next;
		}
        q = q->next;
        min = 999;
    }
}
//���ض���ʽ������
int PolynLength(polynomail P){
    polynomail q=P;
    int j=0;
    while(q->next){
        q=q->next;
        j++;
    }
    return j;
}
//������β�˲�����e
Status ListInsert_L(polynomail &Pa, term e){  //�������β�˼���eԪ��
    polynomail p=Pa;
    while(p->next)
        p=p->next;
    polynomail p3=(polynomail)malloc(sizeof(LNode));
    p3->data=e;
    p->next=p3;
    p3->next=NULL;
    return OK;
}
//����ʽ�ļӷ�������
Status AddPolyn(polynomail Pa, polynomail Pb, polynomail &Pc){
    polynomail la = Pa->next, lb = Pb->next;
    polynomail lc;
    Pc = lc = Pa;
    while(la && lb){
        if(la->data.exp < lb->data.exp){//la��ָ����lbС
            lc->next = la;
            lc = la;
            la = la->next;
        }
        else if(la->data.exp > lb->data.exp){  //la��ָ����lb��
            lc->next = lb;
            lc = lb;
            lb = lb->next;
        }
        else if(la->data.exp == lb->data.exp){  //laָ����lbָ����ͬ
            la->data.coef = la->data.coef + lb->data.coef;
            lc->next = la;
            lc = la;
            la = la->next;
            lb = lb->next; //lb��ָ��Ҳ�����һλ
        }
    }
    lc->next = la?la:lb;
    //free(Pb);
    return OK;
}
//����ʽ�ļ���������
Status SubtractPolyn(polynomail Pa, polynomail Pb, polynomail &Pc){
    polynomail la = Pa->next, lb = Pb->next;
    polynomail lc;
    Pc = lc = Pa;
    while(la && lb){
        if(la->data.exp < lb->data.exp){//la��ָ����lbС
            lc->next = la;
            lc = la;
            la = la->next;
        }
        else if(la->data.exp > lb->data.exp){  //la��ָ����lb��
            lb->data.coef = 0 - lb->data.coef;
            lc->next = lb;
            lc = lb;
            lb = lb->next;
        }
        else if(la->data.exp == lb->data.exp){  //laָ����lbָ����ͬ
            la->data.coef = la->data.coef - lb->data.coef;
            lc->next = la;
            lc = la;
            la = la->next;
            lb = lb->next; //lb��ָ��Ҳ�����һλ
        }
    }
    if(la)
        lc->next = la;
    else{
        polynomail lb1 = lb;
        while(lb){
            lb->data.coef = 0 - lb->data.coef;
            lb = lb->next;
        }
        lc->next = lb1;
    }
    //free(Pb);
    return OK;
}
//����ʽ�ĳ˷�������
Status MultiplyPolyn(polynomail Pa,polynomail Pb){
    polynomail Pc;
    CreatePolyn(Pc);
    polynomail p1 = Pa, p2 = Pb;
    term t;
    int exp;
    double coef;
    while(p1->next){
        while(p2->next){   //�Ե�һ������ʽ��ÿһ������ڶ�������ʽ��ÿһ��
            exp = p1->next->data.exp + p2->next->data.exp;
            coef = p1->next->data.coef * p2->next->data.coef;
            t.exp = exp;
            t.coef = coef;
            ListInsert_L(Pc,t);  //�����������Ԫ��
            p2 = p2->next;
        }
        p1 = p1->next;
        p2 = Pb;
    }  //��ʱ����˵����Ѿ����Ž�������Pc,�����ظ�
    polynomail p3 = Pc, p4;
    while(p3->next){
        p4=p3->next;
        while(p4->next){
            if(p4->next->data.exp == p3->next->data.exp){
                p3->next->data.coef = p3->next->data.coef + p4->next->data.coef;
                ListDelete_L(Pc, p4);
            }
            p4 = p4->next;   //�ڵ�����ƶ�
        }
        p3 = p3->next;
    }
    PrintPolyn(Pc);
    return OK;
}
//����ʽ��n�ε�������
Status DerivationPolyn(polynomail Pc, int n){
    polynomail p = Pc;
    double coef = 0;
    int exp = 0;
    while (p->next)
    {
        p = p->next;
    }
    if(p->data.exp < n){
        printf("����Ϊ0\n");
        return 0;
    }
    p = Pc;
    while (p->next)
    {
        exp = p->next->data.exp;
        coef = p->next->data.coef;
        for(int i = 0; i < n; i++){
            coef = coef * exp;
            exp--;
        }
        exp = p->next->data.exp - n;
        p->next->data.exp = exp;
        p->next->data.coef = coef;
        p = p->next;
    }
    printf("����ǣ�\n"); 
	PrintPolyn(Pc);
    return OK;
}

//x������ֵ
void calvalue_x(polynomail P, double x){
	double ans = 0;
	polynomail p1 = P->next;
	while(p1){
		ans += p1->data.coef*pow(x, p1->data.exp);
		p1 = p1->next;
	}
	printf("����ǣ�\n"); 
    cout << ans << endl;
}

//����ʽ�����㣨����
void cal_polynomial_L(){
    int dim = -1, choice1 = -1, ans1 = -1, ans2 = -1;
    term tmp;
    polynomail L1, L2, L3;
    printf("����������������ʽ�����㣬������1�������һ������ʽ���󵼻��ֵ���㣬������2\n");
	scanf("%d", &choice1);
	if(choice1 == 1){
	
	    printf("�������һ��һԪ����ʽ������\n");
	    scanf("%d",&dim); 
	    CreatePolyn(L1);
	    printf("�������һ��һԪ����ʽ��ϵ���ʹ���\n");
	    for(int i = 0; i < dim; i++){
	        cin >> tmp.coef >> tmp.exp;
	        ListInsert_L(L1, tmp);
	    }
	    SortPolyn(L1);
	    printf("������ڶ���һԪ����ʽ������\n");
	    scanf("%d",&dim); 
	    CreatePolyn(L2);
	    printf("������ڶ���һԪ����ʽ��ϵ���ʹ���\n"); 
	    for(int i = 0; i < dim; i++){
	        cin >> tmp.coef >> tmp.exp;
	        ListInsert_L(L2, tmp);
	    }
	    SortPolyn(L2);
	
	    printf("���мӷ����㣬������1����������������2���˷�����������3\n");
	    CreatePolyn(L3);
	    scanf("%d" ,&ans1);
	    if(ans1 == 1){
	        AddPolyn(L1, L2, L3);
	        printf("����ǣ�\n"); 
	        PrintPolyn(L3);
	    }else if(ans1 == 2){
	        printf("Ĭ�ϵ�һ������ʽΪ����������Ҫ���ĵڶ�������ʽΪ������������1����������0\n");
	        int change;
	        cin >> change;
	        if(change){
	            SubtractPolyn(L2, L1, L3);
	            printf("����ǣ�\n"); 
	            PrintPolyn(L3);
	        }else{
	            SubtractPolyn(L1, L2, L3);
	            printf("����ǣ�\n"); 
	            PrintPolyn(L3);
	        }
	    }else if(ans1 == 3){
	    	
	        MultiplyPolyn(L1, L2);
	    }/*else if(ans1 == 4){
	    	printf("�Ե�һ������ʽ��������1���Եڶ�������ʽ��������2\n");
	    	cin >> ans2;
	    	printf("��������Ҫ�󵼵Ĵ���\n");
	    	int nn;
			cin >> nn;
			if(ans2 == 1){
			
				SortPolyn(L1);
				DerivationPolyn(L1, nn);
			}else if(ans2 == 2){
				SortPolyn(L2);
				DerivationPolyn(L2, nn); 
			}
		}*/ 
	}else if(choice1 == 2){
		printf("������һԪ����ʽ������\n");
	    scanf("%d",&dim); 
	    CreatePolyn(L1);
	    CreatePolyn(L2);
	    CreatePolyn(L3);
	    printf("������һԪ����ʽ��ϵ���ʹ���\n");
	    for(int i = 0; i < dim; i++){
	        cin >> tmp.coef >> tmp.exp;
	        ListInsert_L(L1, tmp);
	    }
	    SortPolyn(L1);
	    printf("������������1����ֵ����������2\n");
		cin >> ans2;
		if(ans2 == 1){
			printf("��������Ҫ�󵼵Ĵ���\n");
	    	int nn;
			cin >> nn;
			SortPolyn(L1);
			DerivationPolyn(L1, nn);
		}else if(ans2 == 2){
			printf("��������Ҫ�����x��ֵ\n");
			double xx;
			cin >> xx;
			calvalue_x(L1, xx);
		}
	}

    cout << "���ڣ����е����ݽ����������" << endl;
    DestoryPolyn(L1);
    DestoryPolyn(L2);
    DestoryPolyn(L3);
}


