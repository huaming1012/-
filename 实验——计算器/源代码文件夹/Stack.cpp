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
	char expression[200];//���ʽ
	char title[20];//������
	char val[20];//������
};
vector<thefx> myfs;

//�����ջS
Status InitStack(Stack &S){
    S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if(!S.base) exit(OVERFLOW);
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return OK;
}

//����ջS
Status DestroyStack(Stack &S){
    free(S.base);
    S.base = NULL;
    S.top = NULL;
    S.stacksize = 0;
    return OK;
}

//���ջS
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

//����Ԫ��e��ջ��
Status Push(Stack &S, SElemType e){
    if(S.top - S.base >= S.stacksize){  //ջ����׷�Ӵ洢�ռ�
        S.base = (SElemType *)realloc(S.base, (S.stacksize + STACKINCREMENT)*sizeof(SElemType));
    if(!S.base) exit(OVERFLOW);
    S.top = S.base + S.stacksize;
    S.stacksize += STACKINCREMENT;
    }
    *S.top++ = e;
    return OK;
}

//��ջ���գ�����e����S��ջ��Ԫ�أ�����OK�����򷵻�ERROR
SElemType GetTop(Stack S){
    if(S.top == S.base) return ERROR;
    SElemType e = *(S.top - 1);
    return e;
}

//��ջ���գ���ɾ��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR
Status Pop(Stack &S, SElemType &e){
    if(S.top == S.base) return ERROR;
    e = *(--S.top);
    return OK;
}

//�ж��ַ�e�Ƿ��������
int isOPTR(char e){
    if(e=='+'||e=='-'||e=='*'||e=='/'||e=='('||e==')'||e=='#'||e == '^')
		return 1;  //�������
	else 
		return 0;//���������
}

//�ж��ַ�e�Ƿ�����ĸ���»��� 
int isLetter(char e){
    if((e>='a'&&e<='z')||(e>='A'&&e<='Z')||(e == '_'))
		return 1;
	else
		return 0;
}

//�Ƚ�ab��������ȼ�
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
//����
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

//������ʽ��ֵ
double EvaluateExpression(char *s){
    Stack OPTR;  //�����ջ
    double OPND[MAX];  //������ջ
    InitStack(OPTR);
    Push(OPTR,'#');
    bool isfloat = false, tmpfloat = false;//�ж��Ƿ���С��
    char c, e, x;
    double num1, num2, tmpans;
    int i = 0, k = 0;  //iΪs��������kΪ������ջ�����飩����
    int lastflag = 0;
    c = s[i++];
    while(c != '#' || GetTop(OPTR) != '#'){
        if(!isOPTR(c) && !isLetter(c)){   //����ֵ 
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
        }else if(isLetter(c)){ //��������
        	lastflag = 1;
            while(!isOPTR(c))  //������һ�������Ϊֹ 
                c = s[i++];
            printf("�����������ֵ\n");
            double tmp;
            cin >> tmp;
            OPND[k++] = tmp;
        }else if(isOPTR(c)){   //�ǲ����� 
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
		printf("���Ϊ��%lf\n",ttmp);
		return ttmp;
	}else{
	    if(isfloat){
	        printf("���Ϊ��%lf\n",ttmp);
	        return ttmp;
	    }else{
	        printf("���Ϊ��%d\n",(int)ttmp);
	        return (int)ttmp;
	    }
	}
    
}

//���ݺ�����h������vector�е�λ��
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

//��variable��ǰn���ַ�����value
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
//��F�е�valȫ���滻��VAL 
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
	for(t; t < strlen(expression); t++){//����Ƿ����������ʷ����
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
//���������һ��ֻ�����ֵı��ʽ��Ȼ����ñ��ʽ��ֵ�ĺ������ 
void changefx2exps(){
    char f[100];
    int goon = 0;
    cout << "��������Ҫ��������еĺ���,��ʽ����DEF:f(x)=����������ӿո�" << endl;
    do{
    cin >> f;
    char option[5];   //�������Ƕ��廹������ 
    strncpy(option,f,3);
    if(!strcmp(option,"DEF")){
        thefx myf;
        int length = strlen(f);
        int i = 4, j = 4, k = 0;
        for(i = 4; i < length; i++){   //���뺯���� 
            j++;
            if(f[i] == '(')
                break;
            else
                myf.title[j-5] = f[i];
        }
        for(i = j; i < length; i++){   //��������� 
            if(f[i] == ')')
                break;
            else{
                myf.val[k] = f[i];
                k++;    
            }
        }
        k = 0;
        i += 2;
        for(i; i < length; i++){   //������ʽ 
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
        for(i = 4; i < length; i++){  //���뺯���� 
            if(f[i] == '('){
                break;
            }else{
                fname[j++] = f[i];
            }
        }
        fname[j] = '\0';
        i++;
        char tmpfloat = false;
        while(f[i] != ')'){   //����val��ֵ
            VAL[k] = f[i];
            i++;
            k++;
        }
        VAL[k++] = ')';
        VAL[k] = '\0';

        int index = findIndex(fname);  //�ҵ��ú�������vector��Ӧ�� 
        char Fexpression[200] = "\0";
        strcpy(Fexpression,myfs[index].expression);
        replace(Fexpression,myfs[index].val, VAL);
        int history = 0, t = 0;
        for(t; t < strlen(Fexpression); t++){//����Ƿ����������ʷ����
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
            for(t = 0; t < strlen(Fexpression); t++){//����Ƿ����������ʷ����
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
    
    cout << "����������������1����������0" << endl;
    cin >> goon; 
	}while(goon);
}
