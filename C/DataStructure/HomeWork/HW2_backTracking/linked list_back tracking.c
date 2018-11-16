#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef int item;
typedef struct tStackNode
{
	item data;
	struct tStackNode *next;
} StackNode;

typedef struct
{
	int count;
	StackNode *top;
} Stack;

Stack* CreateStack(int size)
{
	Stack *pStack = (Stack *)malloc(sizeof(Stack));

	if (pStack == NULL)
		return NULL;

	(*pStack).count = -1;
	(*pStack).top = NULL;

	return pStack;
}


void Push(Stack *pStack, item item)
{
	StackNode *pNewNode = (StackNode *)malloc(sizeof(StackNode));

	if (pNewNode == NULL)
		return;

	(*pNewNode).data = item;
	(*pNewNode).next = (*pStack).top;
	(*pStack).top = pNewNode;
	(*pStack).count++;
}

item pop(Stack *pStack)
{
	if ((*pStack).top == NULL)
		return NULL;

	item out = (*(*pStack).top).data;
	StackNode*pOrigin = (*pStack).top;

	(*pStack).top = (*pOrigin).next;
	free(pOrigin);
	(*pStack).count--;

	return out;
}

item top(Stack*pStack)
{
	if ((*pStack).count == 0)
		return NULL;

	return (*(*pStack).top).data;
}

void DestroyStack(Stack *pStack)
{
	StackNode*pOrigin;

	for (int i = 0; i < (*pStack).count; i++)
	{
		pOrigin = (*pStack).top;
		(*pStack).top = (*pOrigin).next;
		free(pOrigin);
	}

	free(pStack);
}

// linked list 방식은 정해진 크기가 없으므로 IsFullStack 함수는 구현하지 않았습니다. 

bool IsEmptyStack(Stack *pStack)
{
	if ((*pStack).count == 0)
		return true;
	else
		return false;
}

int CountStackItem(Stack *pStack)
{
	return (*pStack).count;
}

void ClearStack(Stack *pStack)
{
	StackNode*pOrigin;

	for (int i = 0; i < (*pStack).count; i++)
	{
		pOrigin = (*pStack).top;
		(*pStack).top = (*pOrigin).next;
		free(pOrigin);
	}
}

int main()
{
	FILE *f;
	Stack *pStack = CreateStack(20);
	char file_name[15];
	int item, num = 0, num2 = 0, size, start, goal, data[50][50], test, test2 = 0, open = 0;
	int open2[10] = { 0,0,0,0,0,0,0,0,0,0 }, ban = 2, branch[50], ag, test3 = 0;

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
			num2 = 0;
			num++;
		}
		else
			num2 = 1;


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
			while (pStack->count != branch[ban - 1])
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

	while (pStack->count != 0)
		Push(pStack2, pop(pStack));

	Push(pStack2, pop(pStack));

	printf("Route : ");

	while (pStack2->count != 0)
	{
		printf("%d, ", pop(pStack2));
	}
	printf("%d", pop(pStack2));

	return 0;
}