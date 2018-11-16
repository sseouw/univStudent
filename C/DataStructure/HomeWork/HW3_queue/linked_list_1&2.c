#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "malloc.h"

typedef char* Item;

typedef struct node{
	struct node *next;
	Item data;
}Qnode;
typedef struct {
	int size;
	int count;
	Qnode *front,*rear;
}Queue;

Queue* CreateQueue(int size) 
{ 
	Queue *pNewQueue = (Queue*)malloc(sizeof(Queue)); 
	if(pNewQueue == NULL) 
		return NULL;

	(*pNewQueue).size = 0;
	(*pNewQueue).count = 0;
	(*pNewQueue).front = NULL;
	(*pNewQueue).rear = NULL;
	
	return pNewQueue;
}

void Enqueue(Queue *pQueue, Item item) 
{
	Qnode *pNewNode = (Qnode*)malloc(sizeof(Qnode)); 
	
	if (pNewNode == NULL) 
		return; 
	
	(*pNewNode).data = item; 
	(*pNewNode).next = NULL;
	
	if ((*pQueue).count <= 0)
	{ 
		(*pQueue).front = (*pQueue).rear = pNewNode;
	}
	else
	{
		(*(*pQueue).rear).next = pNewNode;
		(*pQueue).rear = pNewNode;
	}
	(*pQueue).count++;
}

Item Dequeue(Queue *pQueue) 
{
	Qnode *pFront = NULL; 
	Item* item = 0;

	if ((*pQueue).count <= 0)
		return 0;

	pFront = (*pQueue).front;
	item = &(*pFront).data;

	if ((*pQueue).count == 1)
	{ 
		(*pQueue).front = NULL;
		(*pQueue).rear = NULL;
	}
	else 
	{ 
		(*pQueue).front = (*pFront).next;
	}
	free(pFront); 
	(*pQueue).count--;
	return *item;
}

void DestroyQueue(Queue *pQueue)
{
	Qnode *pCur = NULL, *pNext = NULL;

	for (pCur = (*pQueue).front; pCur != NULL; pCur = pNext)
	{
		pNext = (*pCur).next;
		free(pCur);
	}
	(*pQueue).count = 0;
	(*pQueue).front = NULL;
	(*pQueue).rear = NULL;
	free(pQueue);
}

int main()
{
	Item* name = (Item*)malloc(sizeof(char) * 15);
	char* name2 = (char*)malloc(sizeof(char) * 15);
	int bran,num;

	Queue *Qu=CreateQueue(6);
	Queue *Qu2= CreateQueue(6);
	Qnode *Qn;

	do {
		printf("IN(0) OUT(1) EXIT(2) : ");
		scanf("%d", &bran);

		switch (bran)
		{
			case 0:
				printf("customer name : ");
				scanf("%s", name);
				Enqueue(Qu, *name);
				break;
		
			case 1 :
				printf("customer name : ");
				scanf("%s", name);
				name2 = (*(*Qu).front).data;
				if(*name == name2)
					*name=Dequeue(Qu);
				break;

			case 2 :
				return 0;
				break;
		}
	
		printf("Current state of Queue : ");

		Qn = Qu->front;
		for (int i = 0 ; i < (*Qu).count ; i++)
		{
			*name = Qn->data;
			Qn = Qn->next;
			printf("%s%d ",name,i+1);	
		}
		printf("\n");

	} while (bran != 2);

	DestroyQueue(Qu);

	return 0;
}