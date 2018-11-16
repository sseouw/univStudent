#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef int Element;

typedef struct tListNode
{
	int num;
	int max_size;
	Element* data;
} List;

List *createList(int size)
{
	List *pNewList = (List*)malloc(sizeof(List));

	if (pNewList == NULL)
		return NULL;

	pNewList->data = (Element*)malloc(sizeof(Element));
	
	if ((*pNewList).data == NULL)
	{
		free(pNewList);
		return NULL;
	}

	pNewList->max_size = size;
	pNewList->num = -1;
	return pNewList;
}

void InsertList(List *pList, Element data)
{
	int temp;

	if ((*pList).num == (*pList).max_size - 1)
		return;

	pList->num++;
	pList->data[pList->num] = data;

	for (int i = 0; i < (pList->num) + 1; i++)
	{
		for (int j = 0; j < (pList->num); j++)
		{
			if (pList->data[j] > pList->data[j + 1])
			{
				temp = pList->data[j];
				pList->data[j] = pList->data[j + 1];
				pList->data[j + 1] = temp;
			}
		}
	}
}

bool search(List *pList, Element data)
{
	int i=0;
	while (pList->data[i] != NULL)
	{
		if (pList->data[i] == data)
			return 1;
		i++;
	}
	return 0;
}

void remove(List *pList, Element data)
{
	int i = 0;

	while(pList->data[i]!=NULL)
	{
		if (pList->data[i] == data)
			break;
		i++;
	}
	for (i; i < pList->num ; i++)
		pList->data[i] = pList->data[i + 1];

	pList->num--;
}

void DestroyList(List* pList)
{
	free(pList->data);
	free(pList);
}

void print(List*pList)
{
	for (int i = 0; i < pList->num + 1; i++)
		printf(" %d ",pList->data[i]);
}

int main()
{
	int pan, pan2, num, n = 0, data = 0, ret = 0;
	List *pList = createList(100);

	do {
		printf("In (0), Search (1), Out(2), Exit (3) : ");
		scanf("%d", &pan);
		switch (pan)
		{
		case 0:
			printf("enter : ");
			scanf("%d", &num);

			InsertList(pList, num);
			break;
		case 1:
			printf("search : ");
			scanf("%d", &num);

			pan2 = search(pList, num);

			if (pan2)
				printf("%d is exist\n", num);
			else
				printf("%d isn't exist\n", num);

			break;
		case 2:
			printf("Output : ");
			scanf("%d", &num);

			remove(pList, num);

			printf("%d exits.\n", num);
			break;
		case 3:
			return 0;
			break;
		}

		printf("Current Status of List : ");
		print(pList);
		printf("\n");
	} while (pan != 3);


	return 0;
}