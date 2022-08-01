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

//================链表的一系列操作==========================
//一元多项式链表的建立
Status CreatePolyn(polynomail &P){
    P = (polynomail)malloc(sizeof(LNode));
    if(!P)
        exit(OVERFLOW);
    P->next = NULL;
    return OK;
}
//一元多项式链表的摧毁
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
//删除链表中的p指针所指的项的后一项
Status ListDelete_L(polynomail &Pa, polynomail p){
    polynomail tmp = p->next;
    p->next = p->next->next;
    free(tmp);
    return OK;
}
//打印输出一元多项式
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
//对多项式进行次数排序
void SortPolyn(polynomail &P){
    int min = 999;
    polynomail min_pos = P;
    polynomail q = P, p = P;
    if(!q->next->next)//只有一项或空
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
//返回多项式的项数
int PolynLength(polynomail P){
    polynomail q=P;
    int j=0;
    while(q->next){
        q=q->next;
        j++;
    }
    return j;
}
//在链表尾端插入项e
Status ListInsert_L(polynomail &Pa, term e){  //往链表的尾端加入e元素
    polynomail p=Pa;
    while(p->next)
        p=p->next;
    polynomail p3=(polynomail)malloc(sizeof(LNode));
    p3->data=e;
    p->next=p3;
    p3->next=NULL;
    return OK;
}
//多项式的加法（链表）
Status AddPolyn(polynomail Pa, polynomail Pb, polynomail &Pc){
    polynomail la = Pa->next, lb = Pb->next;
    polynomail lc;
    Pc = lc = Pa;
    while(la && lb){
        if(la->data.exp < lb->data.exp){//la的指数比lb小
            lc->next = la;
            lc = la;
            la = la->next;
        }
        else if(la->data.exp > lb->data.exp){  //la的指数比lb大
            lc->next = lb;
            lc = lb;
            lb = lb->next;
        }
        else if(la->data.exp == lb->data.exp){  //la指数与lb指数相同
            la->data.coef = la->data.coef + lb->data.coef;
            lc->next = la;
            lc = la;
            la = la->next;
            lb = lb->next; //lb的指针也需后移一位
        }
    }
    lc->next = la?la:lb;
    //free(Pb);
    return OK;
}
//多项式的减法（链表）
Status SubtractPolyn(polynomail Pa, polynomail Pb, polynomail &Pc){
    polynomail la = Pa->next, lb = Pb->next;
    polynomail lc;
    Pc = lc = Pa;
    while(la && lb){
        if(la->data.exp < lb->data.exp){//la的指数比lb小
            lc->next = la;
            lc = la;
            la = la->next;
        }
        else if(la->data.exp > lb->data.exp){  //la的指数比lb大
            lb->data.coef = 0 - lb->data.coef;
            lc->next = lb;
            lc = lb;
            lb = lb->next;
        }
        else if(la->data.exp == lb->data.exp){  //la指数与lb指数相同
            la->data.coef = la->data.coef - lb->data.coef;
            lc->next = la;
            lc = la;
            la = la->next;
            lb = lb->next; //lb的指针也需后移一位
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
//多项式的乘法（链表）
Status MultiplyPolyn(polynomail Pa,polynomail Pb){
    polynomail Pc;
    CreatePolyn(Pc);
    polynomail p1 = Pa, p2 = Pb;
    term t;
    int exp;
    double coef;
    while(p1->next){
        while(p2->next){   //对第一个多项式的每一项，遍历第二个多项式的每一项
            exp = p1->next->data.exp + p2->next->data.exp;
            coef = p1->next->data.coef * p2->next->data.coef;
            t.exp = exp;
            t.coef = coef;
            ListInsert_L(Pc,t);  //往链表里插入元素
            p2 = p2->next;
        }
        p1 = p1->next;
        p2 = Pb;
    }  //此时，相乘的项已经都放进了链表Pc,但有重复
    polynomail p3 = Pc, p4;
    while(p3->next){
        p4=p3->next;
        while(p4->next){
            if(p4->next->data.exp == p3->next->data.exp){
                p3->next->data.coef = p3->next->data.coef + p4->next->data.coef;
                ListDelete_L(Pc, p4);
            }
            p4 = p4->next;   //节点向后移动
        }
        p3 = p3->next;
    }
    PrintPolyn(Pc);
    return OK;
}
//多项式求n次导（链表）
Status DerivationPolyn(polynomail Pc, int n){
    polynomail p = Pc;
    double coef = 0;
    int exp = 0;
    while (p->next)
    {
        p = p->next;
    }
    if(p->data.exp < n){
        printf("导数为0\n");
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
    printf("结果是：\n"); 
	PrintPolyn(Pc);
    return OK;
}

//x带入求值
void calvalue_x(polynomail P, double x){
	double ans = 0;
	polynomail p1 = P->next;
	while(p1){
		ans += p1->data.coef*pow(x, p1->data.exp);
		p1 = p1->next;
	}
	printf("结果是：\n"); 
    cout << ans << endl;
}

//多项式的运算（链表）
void cal_polynomial_L(){
    int dim = -1, choice1 = -1, ans1 = -1, ans2 = -1;
    term tmp;
    polynomail L1, L2, L3;
    printf("如果想进项两个多项式的运算，请输入1；想进行一个多项式的求导或代值运算，请输入2\n");
	scanf("%d", &choice1);
	if(choice1 == 1){
	
	    printf("请输入第一个一元多项式的项数\n");
	    scanf("%d",&dim); 
	    CreatePolyn(L1);
	    printf("请输入第一个一元多项式的系数和次数\n");
	    for(int i = 0; i < dim; i++){
	        cin >> tmp.coef >> tmp.exp;
	        ListInsert_L(L1, tmp);
	    }
	    SortPolyn(L1);
	    printf("请输入第二个一元多项式的项数\n");
	    scanf("%d",&dim); 
	    CreatePolyn(L2);
	    printf("请输入第二个一元多项式的系数和次数\n"); 
	    for(int i = 0; i < dim; i++){
	        cin >> tmp.coef >> tmp.exp;
	        ListInsert_L(L2, tmp);
	    }
	    SortPolyn(L2);
	
	    printf("进行加法运算，请输入1，减法运算请输入2，乘法运算请输入3\n");
	    CreatePolyn(L3);
	    scanf("%d" ,&ans1);
	    if(ans1 == 1){
	        AddPolyn(L1, L2, L3);
	        printf("结果是：\n"); 
	        PrintPolyn(L3);
	    }else if(ans1 == 2){
	        printf("默认第一个多项式为被减数，若要更改第二个多项式为被减数请输入1，否则输入0\n");
	        int change;
	        cin >> change;
	        if(change){
	            SubtractPolyn(L2, L1, L3);
	            printf("结果是：\n"); 
	            PrintPolyn(L3);
	        }else{
	            SubtractPolyn(L1, L2, L3);
	            printf("结果是：\n"); 
	            PrintPolyn(L3);
	        }
	    }else if(ans1 == 3){
	    	
	        MultiplyPolyn(L1, L2);
	    }/*else if(ans1 == 4){
	    	printf("对第一个多项式求导请输入1，对第二个多项式求导请输入2\n");
	    	cin >> ans2;
	    	printf("请输入你要求导的次数\n");
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
		printf("请输入一元多项式的项数\n");
	    scanf("%d",&dim); 
	    CreatePolyn(L1);
	    CreatePolyn(L2);
	    CreatePolyn(L3);
	    printf("请输入一元多项式的系数和次数\n");
	    for(int i = 0; i < dim; i++){
	        cin >> tmp.coef >> tmp.exp;
	        ListInsert_L(L1, tmp);
	    }
	    SortPolyn(L1);
	    printf("求导运算请输入1，代值运算请输入2\n");
		cin >> ans2;
		if(ans2 == 1){
			printf("请输入你要求导的次数\n");
	    	int nn;
			cin >> nn;
			SortPolyn(L1);
			DerivationPolyn(L1, nn);
		}else if(ans2 == 2){
			printf("请输入你要带入的x的值\n");
			double xx;
			cin >> xx;
			calvalue_x(L1, xx);
		}
	}

    cout << "现在，所有的数据将被清空销毁" << endl;
    DestoryPolyn(L1);
    DestoryPolyn(L2);
    DestoryPolyn(L3);
}


