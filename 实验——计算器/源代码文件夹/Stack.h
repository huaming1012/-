#ifndef __STACK_H__
#define __STACK_H__

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define OK 1
#define ERROR 0

typedef char SElemType;
typedef int Status;

typedef struct{
    SElemType *base;
    SElemType *top;
    int stacksize;
}Stack;


//构造空栈S
Status InitStack(Stack &S);

//销毁栈S
Status DestroyStack(Stack &S);

//清空栈S
Status ClearStack(Stack &S);

//插入元素e到栈顶
Status Push(Stack &S, SElemType e);

//若栈不空，则用e返回S的栈顶元素，返回OK；否则返回ERROR
SElemType GetTop(Stack S);

//若栈不空，则删除栈顶元素，用e返回其值，并返回OK；否则返回ERROR
Status Pop(Stack &S, SElemType &e);

//判断字符e是否是运算符
int isOPTR(char e);

//判断字符e是否是字母
int isLetter(char e);

//计算
double calculate(double num1, char e, double num2);

//比较ab运算符优先级
char Compare(char a, char b);

//计算表达式的值
double EvaluateExpression(char *s);

int isEmpty(Stack &s);

//根据函数名h找其在vector中的位置
int findIndex(char h[]);

//把variable的前n个字符换成value
void str_replace(char* variable, int n, char value[]);

//将F中的val全部替换成VAL 
void replace(char F[],char val[],char VAL[]);

//将函数变成thefx的格式
void changefx2exps();
#endif
