#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Stack.h"
#include <vector>

using namespace std;

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define OK 1
#define ERROR 0
#define MAX 100

typedef char SElemType;
typedef int Status;
struct thefx
{
	char expression[200];//表达式
	char title[20];//函数名
	char val[20];//变量名
};
vector<thefx> myfs;

//构造空栈S
Status InitStack(Stack &S){
    S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if(!S.base) exit(OVERFLOW);
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return OK;
}

//销毁栈S
Status DestroyStack(Stack &S){
    free(S.base);
    S.base = NULL;
    S.top = NULL;
    S.stacksize = 0;
    return OK;
}

//清空栈S
Status ClearStack(Stack &S){
    S.top = S.base;
    return OK;
}

int isEmpty(Stack &S){
	if (S.top == S.base){
		return 1;
	}
	return 0;
}

//插入元素e到栈顶
Status Push(Stack &S, SElemType e){
    if(S.top - S.base >= S.stacksize){  //栈满则追加存储空间
        S.base = (SElemType *)realloc(S.base, (S.stacksize + STACKINCREMENT)*sizeof(SElemType));
    if(!S.base) exit(OVERFLOW);
    S.top = S.base + S.stacksize;
    S.stacksize += STACKINCREMENT;
    }
    *S.top++ = e;
    return OK;
}

//若栈不空，则用e返回S的栈顶元素，返回OK；否则返回ERROR
SElemType GetTop(Stack S){
    if(S.top == S.base) return ERROR;
    SElemType e = *(S.top - 1);
    return e;
}

//若栈不空，则删除栈顶元素，用e返回其值，并返回OK；否则返回ERROR
Status Pop(Stack &S, SElemType &e){
    if(S.top == S.base) return ERROR;
    e = *(--S.top);
    return OK;
}

//判断字符e是否是运算符
int isOPTR(char e){
    if(e=='+'||e=='-'||e=='*'||e=='/'||e=='('||e==')'||e=='#'||e == '^')
		return 1;  //是运算符
	else 
		return 0;//不是运算符
}

//判断字符e是否是字母或下划线 
int isLetter(char e){
    if((e>='a'&&e<='z')||(e>='A'&&e<='Z')||(e == '_'))
		return 1;
	else
		return 0;
}

//比较ab运算符优先级
char Compare(char a, char b){
    char f;
	if(a=='+'||a=='-'){
		if(b=='+'||b=='-'||b==')'||b=='#')
			f='>';
		else if(b=='('||b=='*'||b=='/'||b == '^')
			f='<';
	}
	else if(a=='*'||a=='/'){
		if(b=='+'||b=='-'||b=='*'||b=='/'||b==')'||b=='#')
			f='>';
		else if(b=='('||b == '^')
			f='<';
	}
	else if(a=='('){
		if(b=='+'||b=='-'||b=='*'||b=='/'||b=='('||b == '^')
			f='<';
		else if(b==')')
			f='=';		
	}
	else if(a==')'){
		if(b=='+'||b=='-'||b=='*'||b=='/'||b==')'||b=='#'||b == '^')
			f='>';
	}
	else if(a=='#'){
		if(b=='+'||b=='-'||b=='*'||b=='/'||b=='('||b == '^')
			f='<';
		else if(b=='#')
			f='=';
	}
	else if(a=='^'){
		if(b=='+'||b=='-'||b=='*'||b=='/'||b==')'||b=='#'||b =='^')
			f = '>';
		else if(b == '(')
			f = '<';
	}
	return f;
}
//计算
double calculate(double num1, char e, double num2){
    double ans;
    if(e == '+')
        ans = num1 + num2;
    else if(e == '-')
        ans = num2 - num1;
    else if(e == '*')
        ans = num1 * num2;
    else if(e == '/')
        ans = num2 / num1;
    else if(e == '^')
        ans = pow(num2, num1);

    //printf("%lf\n",ans); 
    return ans;
}

//计算表达式的值
double EvaluateExpression(char *s){
    Stack OPTR;  //运算符栈
    double OPND[MAX];  //运算数栈
    InitStack(OPTR);
    Push(OPTR,'#');
    bool isfloat = false, tmpfloat = false;//判断是否是小数
    char c, e, x;
    double num1, num2, tmpans;
    int i = 0, k = 0;  //i为s的索引，k为运算数栈（数组）索引
    int lastflag = 0;
    c = s[i++];
    while(c != '#' || GetTop(OPTR) != '#'){
        if(!isOPTR(c) && !isLetter(c)){   //是数值 
        	lastflag = 1;
            double d = 0;
            int pos_point = -1;
            while(!isOPTR(c)){
                if(tmpfloat == false){
                    d = d * 10 + c - '0';
                    c = s[i++];
                }
                if(c == '.'){
                    tmpfloat = true;
                    isfloat = true;
                    pos_point = i;
                    c = s[i++];
            	}
            	if(c == 'e'){
            		char tmpexp[10] = {"\0"};
            		int k = 0;
            		c = s[i++];
            		if(c == '-'){
						c = s[i++];
	            		while(!isOPTR(c)){
	            			//cout << c << endl;
	            			tmpexp[k++] = c;
	            			c = s[i++];
						}
						int exp;
						tmpexp[k] = '\0';
						sscanf(tmpexp, "%d", &exp);
						//cout << exp;
						exp = 0-exp;
						d = d * pow(10,exp);
						//cout << d;
					}else{
						while(!isOPTR(c)){
	            			//cout << c << endl;
	            			tmpexp[k++] = c;
	            			c = s[i++];
						}
						int exp;
						tmpexp[k] = '\0';
						
						sscanf(tmpexp, "%d", &exp);
						//cout << d << endl;
						//cout << exp;
						d = d * pow(10,exp);
						//cout << d;
					}
				}else if(tmpfloat == true){
                    d = (d * pow(10,i-pos_point) + c - '0')/pow(10,i-pos_point);
                    c = s[i++];
                }
            }
            OPND[k++] = d;
            tmpfloat = false;
        }else if(isLetter(c)){ //变量出现
        	lastflag = 1;
            while(!isOPTR(c))  //读到下一个运算符为止 
                c = s[i++];
            printf("请输入变量的值\n");
            double tmp;
            cin >> tmp;
            OPND[k++] = tmp;
        }else if(isOPTR(c)){   //是操作符 
        	//int flag = 0;
        	//while(c != '#' || GetTop(OPTR) != '#'){
			if(lastflag == 0 && c == '-'){
				OPND[k++] = 0;
			}
			lastflag = 0;
            switch(Compare(GetTop(OPTR),c))
            {
            case '<':
                Push(OPTR,c);
                //flag = 1;
                c = s[i++];
                break;
            
            case '>':
                Pop(OPTR,e);
                num1 = OPND[--k];
                num2 = OPND[--k];
                tmpans = calculate(num1, e, num2);
                OPND[k++] = tmpans;
                break;
            case '=':
                Pop(OPTR, x);
                c = s[i++];
                break;
            }
        //}

        }
    }
    while(GetTop(OPTR) != '#'||k>1){
    	Pop(OPTR,e);
        num1 = OPND[--k];
        num2 = OPND[--k];
        tmpans = calculate(num1, e, num2);
        OPND[k++] = tmpans;
	}
	double ttmp = OPND[--k];
	if(ttmp != (int)ttmp){
		printf("结果为：%lf\n",ttmp);
		return ttmp;
	}else{
	    if(isfloat){
	        printf("结果为：%lf\n",ttmp);
	        return ttmp;
	    }else{
	        printf("结果为：%d\n",(int)ttmp);
	        return (int)ttmp;
	    }
	}
    
}

//根据函数名h找其在vector中的位置
int findIndex(char h[])
{
	for(int i = 0; i < myfs.size(); i++)
	{
		if(strcmp(myfs[i].title, h)==0)
		{
			return i;
		}
	}
	return -1;
}

//把variable的前n个字符换成value
void str_replace(char* variable, int n, char value[])
{
	int m=strlen(value);
	char * p;
	
	//strlen(value) < strlen(variable)
	if(m < n)  
	{
		p = variable+n;
		while(*p)
		{
			//the distance to move is n-lenofstr
			*(p-(n-m)) = *p; 
			p++;
		}
		*(p-(n-m)) =*p; //move '\0'	
	}
	else if(m > n)
	{
		p = variable;
		while(*p) p++;
		while(p>=variable+n)
		{
			*(p+(m-n)) = *p;
			p--;
		}   
	}
	strncpy(variable,value,m);
}
//将F中的val全部替换成VAL 
void replace(char F[],char val[],char VAL[])
{
	char *p = strstr(F,val);
   	while(p)
	{

		str_replace(p,strlen(val),VAL);
		p = p+strlen(VAL);
		p = strstr(p,val);
	}  
	return;
}
/*
int TestHistoryF(char expression[]){
	int t = 0, pos = -1, flag = 0; 
	for(t; t < strlen(expression); t++){//检测是否调用其他历史函数
        if(isLetter(expression[t])){
        	pos = t;
            flag = 1;
            break;
        }
    }
    if(!flag){
    	return 0;
	}else if(expression[pos] == 'e' && expression[pos+1] != '()'){
    	return 1;
	}
}
*/
//将函数变成一个只含数字的表达式，然后调用表达式求值的函数求解 
void changefx2exps(){
    char f[100];
    int goon = 0;
    cout << "请输入你要定义或运行的函数,格式形如DEF:f(x)=……（不添加空格）" << endl;
    do{
    cin >> f;
    char option[5];   //看操作是定义还是运行 
    strncpy(option,f,3);
    if(!strcmp(option,"DEF")){
        thefx myf;
        int length = strlen(f);
        int i = 4, j = 4, k = 0;
        for(i = 4; i < length; i++){   //分离函数名 
            j++;
            if(f[i] == '(')
                break;
            else
                myf.title[j-5] = f[i];
        }
        for(i = j; i < length; i++){   //分离变量名 
            if(f[i] == ')')
                break;
            else{
                myf.val[k] = f[i];
                k++;    
            }
        }
        k = 0;
        i += 2;
        for(i; i < length; i++){   //分离表达式 
            myf.expression[k] = f[i];
            k++;
        }
        myf.expression[k] = '\0';
        myfs.push_back(myf);
    }else if(!strcmp(option,"RUN")){
        char VAL[20] = "\0";
        VAL[0] = '('; 
        char fname[20] = "\0";
        int length = strlen(f);
        int i = 4, j = 0, k = 1;
        for(i = 4; i < length; i++){  //分离函数名 
            if(f[i] == '('){
                break;
            }else{
                fname[j++] = f[i];
            }
        }
        fname[j] = '\0';
        i++;
        char tmpfloat = false;
        while(f[i] != ')'){   //读入val的值
            VAL[k] = f[i];
            i++;
            k++;
        }
        VAL[k++] = ')';
        VAL[k] = '\0';

        int index = findIndex(fname);  //找到该函数名在vector对应的 
        char Fexpression[200] = "\0";
        strcpy(Fexpression,myfs[index].expression);
        replace(Fexpression,myfs[index].val, VAL);
        int history = 0, t = 0;
        for(t; t < strlen(Fexpression); t++){//检测是否调用其他历史函数
            if(isLetter(Fexpression[t])){
                history = 1;
                break;
            }
        }
        while(history){
            char hfname[20] = "\0";
            int eflags[10] = {0};
            j = 0;
            int p = 0;
            while(Fexpression[t] != '('){
                hfname[j++] = Fexpression[t++];
            }
            /*if(hfname == "e"){
            	eflags[p++] = t-1;
			}*/
            hfname[j] = '\0';
            if(!strcmp(hfname,fname)){
            	cout << "ERROR!!" << endl;
            	return;
			}
            int hfindex = findIndex(hfname);
            char Gexpression[200] = "\0";
            Gexpression[0] = '(';
            Gexpression[1] = '\0';
            strcpy(Gexpression+1,myfs[hfindex].expression);
            replace(Gexpression,myfs[hfindex].val, VAL);
            strcat(Gexpression, ")");
            strcat(hfname,"(");
            strcat(hfname, VAL);
            strcat(hfname, ")");
            replace(Fexpression,hfname,Gexpression);
            
            history = 0;
            for(t = 0; t < strlen(Fexpression); t++){//检测是否调用其他历史函数
                if(isLetter(Fexpression[t])){
                    history = 1;
                    break;
                    /*int fflag = 0;
                    for(int s = 0; s < p; s++){
                		if(t == eflags[s]){
                			history = 0;
                			fflag = 1;
							break; 
						} 		
					}*/
					/*if(fflag){
						continue;
					}else{
						break;
					}
                    */
                }
            }
			
        }
        strcat(Fexpression,"#");
        EvaluateExpression(Fexpression);
    }
    
    cout << "如果想继续，请输入1，否则输入0" << endl;
    cin >> goon; 
	}while(goon);
}
