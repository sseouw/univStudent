#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

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

int main()
{
	FILE *f;
	Stack *pStack = CreateStack(20);
	char file_name[15];
	int item, num = 0, num2 = 0, size, start, goal, data[50][50], test, test2 = 0, open = 0;
	int open2[10] = { 0,0,0,0,0,0,0,0,0,0 }, ban = 2, branch[50], ag, test3=0;

	printf("Miro File Myung : ");
	scanf("%s", &file_name);

	f = fopen(file_name, "r");

	fscanf(f, "%d", &start);
	fscanf(f, "%d", &goal);//시작점,골 지정

	while (fscanf(f, "%d", &item) != EOF)
	{
		data[num][num2] = item;

		if (num2 == 1)
		{
			num2 =0;
			num++;
		}
		else
			num2=1;


	}//파일의 데이터를 2차원 배열에 받아옴

	size = num;
	fclose(f);

	Push(pStack, start);
	Push(pStack, data[open][1]);

	while (data[1][open] != goal)
	{
		while (data[test3][0] != top(pStack))
		{
			test3++;
			if (test3 > size)
				break;
		}
		for (int i = 0; i < size; i++)
		{
			if (data[i][0] == top(pStack))
			{
				test = i;
				test2++;//갈래길 수
			}
		}
	
		open = test3;//하나의 길이 새로 나타나는곳

		if (test2 > 1)
		{
			open2[ban] = open;
			branch[ban] = data[open][0];
			pop(pStack);
			Push(pStack, branch[ban]);
			Push(pStack, data[open][1]);
			ban++;
		}// 갈래길인 경우, 위치지정 
		else if (test2 == 0 && top(pStack) != goal)
		{
			ag = open2[ban - 1];
			if (data[ag + 1][0] != data[ag][0])
				ban--;
			open = open2[ban - 1] + 1;
			open2[ban - 1]++;
			while (pStack->top != branch[ban - 1])
				pop(pStack);
			pop(pStack);
			Push(pStack, data[open][1]);
		}// 끝에 도달시, goal이 아니면 이전 갈래길로,갈래길을 전부 조사했다면 그이전 갈래길로
		else if (test2 == 1)
			Push(pStack, data[open][1]);//길이 하나일때 그대로 Push
		else
			break;

		test2 = 0;
		test3 = 0;
	}

	Stack *pStack2 = CreateStack(20);

	while (pStack->top != NULL)
		Push(pStack2,pop(pStack));

	Push(pStack2, pop(pStack));

	printf("Route : ");

	while(pStack2->top != NULL)
		printf("%d, ", pop(pStack2));

	printf("%d", pop(pStack2));

	return 0;
}