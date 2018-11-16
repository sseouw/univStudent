#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include <stdlib.h>
#include <string.h>

typedef int item;
typedef struct node
{
	item* stack;
	int max_size;
	int top;
} Stack;

Stack *CreateStack(int size)
{
	Stack *pStack = (Stack *)malloc(sizeof(Stack));

	if (pStack == NULL)
		return NULL;

	(*pStack).stack = (item *)malloc(size * sizeof(item));

	if ((*pStack).stack == NULL)
	{
		free(pStack);
		return NULL;
	}

	(*pStack).max_size = size;
	(*pStack).top = -1;

	return pStack;
}

void Push(Stack *pStack, item item)
{
	if ((*pStack).top == (*pStack).max_size - 1)
		return;

	(*pStack).stack[++(*pStack).top] = item;
}

item pop(Stack *pStack)
{
	item pop;

	if ((*pStack).top == -1)
		return NULL;

	pop = (*pStack).stack[(*pStack).top];
	(*pStack).stack[(*pStack).top] = NULL;
	(*pStack).top--;

	return pop;
}

item top(Stack*pStack)
{
	if ((*pStack).top == -1)
		return NULL;

	return (*pStack).stack[(*pStack).top];
}

void DestroyStack(Stack *pStack)
{
	free((*pStack).stack);
	free(pStack);
}

bool IsFullStack(Stack *pStack)
{
	if ((*pStack).top == (*pStack).max_size - 1)
		return 1;
	else
		return 0;
}

bool IsEmptyStack(Stack *pStack)
{
	if ((*pStack).top == -1)
		return 1;
	else
		return 0;
}

int CountStackItem(Stack *pStack)
{
	return (*pStack).top + 1;
}

void ClearStack(Stack *pStack)
{
	for (int i = 0; i < (*pStack).top + 1; i++)
	{
		(*pStack).stack[(*pStack).top] = NULL;
		(*pStack).top--;
	}
}

int grade(char item);
void converToPostfix(char *input,char *out,int*p);
int eval(char* postfix,  int*p);


int main()
{
	char input[50],out[20];
	int num2 = 0, brt1 = 0, brt2 = 0,value,len,num;
	int*p;
	p = &num;
	
	Stack*qStack = CreateStack(20);

	printf("Enter an equation : ");
	scanf("%[^\n]s", input);//수식 받아오기

	len = strlen(input);

	printf("test bracket : ");

	while (input[num2] != NULL)
	{
		if (input[num2] == '(')
			brt1++;
		else if (input[num2] == ')')
			brt2++;

		num2++;
	}
	
	if (brt1 == brt2)
		printf("pass\n");
	else
	{
		printf("There's a problem at bracket\n");
		return 0;
	}//괄호 검사,닫는괄호와 여는괄호의 수가 다르면 종료

	printf("Postfix : ");
	converToPostfix(input,out,p);//postfix로 나열

	value = eval(out,p);//나열한 postfix를 계산

	printf("\nvalue : %d\n", value);

	return 0;
}

int grade(char item) //우선순위 반환  
{
	switch (item)
	{
	case '(': case ')': return 0;
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	}

	return -1;
}

void converToPostfix(char *input,char *out,int*p) // postfix로 수식을 변경
{
	Stack *qStack = CreateStack(30);
	char ch, ch2, Top;
	int i, len = strlen(input), num=0;
	char *oper = (char *)malloc(sizeof(len));

	
	for (i = 0; i<len; i++)
	{
		ch = input[i];

		switch (ch)
		{
		case '+':    case '-':    case '*':    case '/':
			while (!IsEmptyStack(qStack) && grade(ch) <= grade(top(qStack)))
			{
				Top = pop(qStack);
				printf("%c", Top);
				out[num] = Top;
				num++;
			}

			Push(qStack, ch);
			break;

		case '(':
			Push(qStack, ch);
			break;

		case ')':
			Top = pop(qStack);

			while (Top != '(')
			{
				printf("%c", Top);
				out[num] = Top;
				num++;
				Top = pop(qStack);
			}
			break;

		default:
			printf("%c", ch);
			out[num] = ch;
			num++;
			break;
		}
	}
	while (!IsEmptyStack(qStack))
	{
		ch2 = pop(qStack);
		printf("%c", ch2);
		out[num] = ch2;
		num++;
	}
	*p = num;
}

int eval(char* postfix, int*p) //postfix 계산
{
	Stack*pStack = CreateStack(20);
	int pop1, pop2, value, i;
	int len = (int)strlen(postfix);
	char ch;

	for (i = 0; i<*p; i++) {
		ch = postfix[i];

		if (ch != '+' && ch != '-' && ch != '*' && ch != '/') {
			value = ch - '0';
			Push(pStack, value);
			
		}
		else
		{
			pop1 = pop(pStack);
			pop2 = pop(pStack);

			switch (ch) {
			case '+': value = pop1 + pop2;
				break;
			case '-': value = pop2 - pop1;
				break;
			case '*': value = pop1*pop2;
				break;
			case '/': value = pop2 / pop1;
				break;
			}
			Push(pStack, value);
		}
	}
	
	return pop(pStack);
}