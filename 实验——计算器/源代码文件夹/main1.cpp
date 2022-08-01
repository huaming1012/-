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
    printf("如果你想做同维度向量的运算,请输入1,如果你想做一元多项式的运算,请输入2,如果你想对表达式求值，请输入3,如果你想做自定义函数相关的运算，请输入4,如果你想做矩阵相关的运算，请输入5\n");
    scanf("%d", &tmp);
    if(tmp == 1){
        cal_vactor();
    }else if(tmp == 2){
        printf("如果你想用顺序表完成一元多项式相关的运算，请输入1，如果想用链表请输入2\n");
        int choose;
        scanf("%d", &choose);
        if(choose == 1)
            cal_polynomial_list();
        else
            cal_polynomial_L();
    }else if(tmp == 3){
    	printf("请输入你的表达式\n");
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
