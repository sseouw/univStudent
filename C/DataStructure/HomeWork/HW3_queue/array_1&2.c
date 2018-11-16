#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "malloc.h"

typedef char* Item;
typedef struct {
	Item* queue;
	int size;
	int front, rear;
	int count;
}Queue;

Queue* CreateQueue(int size) {
	Queue *pQueue = (Queue *)malloc(sizeof(Queue)); 
	
	if (pQueue == NULL) 
		return NULL;
	
	(*pQueue).queue = (Item *)malloc(size * sizeof(Item)); 
	
	if ((*pQueue).queue == NULL) 
	{ 
		free(pQueue); 
		return NULL; 
	} 
	(*pQueue).size = size; 
	(*pQueue).front = 0;
	(*pQueue).rear = 0;
	(*pQueue).count = 0;
	return pQueue;
}

bool IsFullQueue(Queue *q)
{
	if (((*q).rear + 1) % (*q).size == (*q).front)
		return 1;
	else
		return 0;
}

bool IsEmptyQueue(Queue *q)
{
	if ((*q).front == (*q).rear)
		return 1;
	else
		return 0;
}

void DestroyQueue(Queue* q)
{
	free((*q).queue);
	free(q);
}

void Enqueue(Queue *q, Item item) 
{ 
	if (IsFullQueue(q)) 
		return; 
	else 
	{ 
		(*q).rear = ((*q).rear + 1) % (*q).size;
		(*q).queue[(*q).rear] = item;
		(*q).count++;
	} 
}

Item Dequeue(Queue *q) 
{ 
	if (IsEmptyQueue(q)) 
		return NULL; 
	else 
	{ 
		(*q).front = ((*q).front + 1) % (*q).size;
		(*q).count--;

		return (*q).queue[(*q).front]; 
	} 
}

int main()
{
	Item* name = (Item*)malloc(sizeof(char) * 15);
	char* name2 = (char*)malloc(sizeof(char) * 15);
	int bran;
	char temp[20];

	Queue *Qu=CreateQueue(6);

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
				name2 = (*Qu).queue[(*Qu).front+1];
				if(*name == name2)
					*name=Dequeue(Qu);
				break;

			case 2 :
				return 0;
				break;
		}
	
		printf("Current state of Queue : ");

		for (int i = 0 ; i < (*Qu).count ; i++)
		{
			*name = (*Qu).queue[((*Qu).front+1+i)%(*Qu).size];
			printf("%s%d ",name,i+1);	
		}
		printf("\n");

	} while (bran != 2);

	DestroyQueue(Qu);

	return 0;
}