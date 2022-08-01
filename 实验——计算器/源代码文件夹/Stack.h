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


//�����ջS
Status InitStack(Stack &S);

//����ջS
Status DestroyStack(Stack &S);

//���ջS
Status ClearStack(Stack &S);

//����Ԫ��e��ջ��
Status Push(Stack &S, SElemType e);

//��ջ���գ�����e����S��ջ��Ԫ�أ�����OK�����򷵻�ERROR
SElemType GetTop(Stack S);

//��ջ���գ���ɾ��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR
Status Pop(Stack &S, SElemType &e);

//�ж��ַ�e�Ƿ��������
int isOPTR(char e);

//�ж��ַ�e�Ƿ�����ĸ
int isLetter(char e);

//����
double calculate(double num1, char e, double num2);

//�Ƚ�ab��������ȼ�
char Compare(char a, char b);

//������ʽ��ֵ
double EvaluateExpression(char *s);

int isEmpty(Stack &s);

//���ݺ�����h������vector�е�λ��
int findIndex(char h[]);

//��variable��ǰn���ַ�����value
void str_replace(char* variable, int n, char value[]);

//��F�е�valȫ���滻��VAL 
void replace(char F[],char val[],char VAL[]);

//���������thefx�ĸ�ʽ
void changefx2exps();
#endif
