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
	int item,test,num,out;

	Stack*pStack = CreateStack(100);

	printf("Enter numbers (for stop, enter<EOP>): ");
	for (int i = 0; i < 100; i++)
	{
		test=scanf_s("%d", &item);
		if (test == 0)
			break;
		Push(pStack, item);
	}

	num = CountStackItem(pStack);

	printf("Reversed data :");
	for (int i = 0; i < num; i++)
	{
		out = pop(pStack);
		printf(" %d",out);
	}

	printf("\n");

	DestroyStack(pStack);
	pStack = NULL;

	return 0;
}