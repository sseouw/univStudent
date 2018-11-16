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
	int item,nam,num,lar,out;

	Stack*pStack = CreateStack(10);

	printf("Enter a dacimal number : ");
	scanf_s("%d", &num);
	
	while (num!=1)
	{
		item = num%2;
		num = num/2;
		Push(pStack, item);
	}
	Push(pStack, num);

	lar = CountStackItem(pStack);

	printf("Convert to binary : ");
	for (int i = 0; i < lar; i++)
	{
		out = pop(pStack);
		printf("%d",out);
	}

	printf("\n");

	DestroyStack(pStack);
	pStack = NULL;

	return 0;
}