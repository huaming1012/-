#include <iostream>
#include <stdio.h>
#include "List.h"
#include "Listpolyn.h"
#include "LinkList.h"
#include "Stack.h"
#include "matrix.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	int tmp;
    printf("���������ͬά������������,������1,���������һԪ����ʽ������,������2,�������Ա��ʽ��ֵ��������3,����������Զ��庯����ص����㣬������4,���������������ص����㣬������5\n");
    scanf("%d", &tmp);
    if(tmp == 1){
        cal_vactor();
    }else if(tmp == 2){
        printf("���������˳������һԪ����ʽ��ص����㣬������1�������������������2\n");
        int choose;
        scanf("%d", &choose);
        if(choose == 1)
            cal_polynomial_list();
        else
            cal_polynomial_L();
    }else if(tmp == 3){
    	printf("��������ı��ʽ\n");
    	char s[100];
    	scanf("%s", s);
    	EvaluateExpression(s);
	}else if(tmp == 4){
		changefx2exps();
	}else if(tmp == 5){
		calMatrix();
	}else{
		printf("ERROR!!");
	}

	return 0;
}
