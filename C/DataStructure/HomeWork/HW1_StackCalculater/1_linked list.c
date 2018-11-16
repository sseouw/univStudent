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
	
	if(pStack == NULL) 
		return NULL; 
	
	(*pStack).count = 0; 
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
	if((*pStack).count == 0)
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
	int item,out,out2;

	Stack*pStack = CreateStack(10);

	printf("Enter 10 numbers : ");
	for (int i = 0; i < 10; i++)
	{
		scanf_s("%d", &item);
		Push(pStack, item);
	}

	out = pop(pStack);
	out2 = pop(pStack);

	printf("%d,%d\n",out,out2);

	DestroyStack(pStack);
	pStack = NULL;

	return 0;
}