#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef int Element;

typedef struct tListNode
{
	Element data;
	struct tListNode *next;
} ListNode;

typedef struct
{
	int  count;
	ListNode *head;
	ListNode * pos;
} List;

List *createList()
{
	List *pNewList = (List*)malloc(sizeof(List));

	if (pNewList == NULL)
		return NULL;

	pNewList->count = 0;
	pNewList->head = NULL;
	return pNewList;
}

void _insertList(List *pList, ListNode *pPre, Element data)
{
	ListNode *pNewNode = (ListNode*)malloc(sizeof(ListNode));
	pNewNode->data = data;

	if (pPre == NULL)
	{
		pNewNode->next = pList->head;
		pList->head = pNewNode;
	}
	else
	{
		pNewNode->next = pPre->next;
		pPre->next = pNewNode;
	}
	pList->count++;
}

bool _searchList(List *pList, ListNode **pPre, ListNode **pLoc, Element data)
{
	for (*pPre = NULL, *pLoc = pList->head; *pLoc != NULL; *pPre = *pLoc, *pLoc = (*pLoc)->next)
	{
		if ((*pLoc)->data == data)
			return 1;
		else if ((*pLoc)->data > data)
			break;
	}
	return 0;
}

void addNodeList(List *pList, Element data)
{
	ListNode *pPre = NULL, *pLoc = NULL;
	bool found = _searchList(pList, &pPre, &pLoc, data);
	if (!found)
		_insertList(pList, pPre, data);
}

void _deleteList(List *pList, ListNode *pPre, ListNode *pLoc)
{
	if (pPre == NULL)
		pList->head = pLoc->next;
	else pPre->next = pLoc->next;
	free(pLoc);
	pList->count--;
}

void removeList(List *pList, Element data)
{
	ListNode*pPre = NULL, *pLoc = NULL;
	bool found = _searchList(pList, &pPre, &pLoc, data);
	if (found)
		_deleteList(pList, pPre, pLoc);
}

void destroyList(List *pList) {
	ListNode *pDel = NULL, *pNext = NULL;
	for (pDel = pList->head; pDel != NULL; pDel = pNext)
	{
		pNext = pDel->next; free(pDel);
	}
	free(pList);
}

bool traverseList(List *pList, int fromWhere, Element *pDataOut)
{
	if (fromWhere == 0 || pList->pos == NULL)
		pList->pos = pList->head;
	else
		pList->pos = pList->pos->next;

	if (pList->pos != NULL)
	{
		*pDataOut = pList->pos->data;
		return 1;
	}
	else
	{
		*pDataOut = 0;
		return 0;
	}
}

int main()
{
	int pan, pan2, num, n = 0, data = 0, ret = 0;
	ListNode *pPre = NULL, *pLoc = NULL;
	List *pList = createList();

	do {
		printf("In (0), Search (1), Out(2), Exit (3) : ");
		scanf("%d", &pan);
		switch (pan)
		{
		case 0:
			printf("enter : ");
			scanf("%d", &num);

			addNodeList(pList, num);
			break;
		case 1:
			printf("search : ");
			scanf("%d", &num);

			pan2 = _searchList(pList, &pPre, &pLoc, num);

			if (pan2)
				printf("%d is exist\n", num);
			else
				printf("%d isn't exist\n", num);

			break;
		case 2:
			printf("Output : ");
			scanf("%d", &num);

			removeList(pList, num);

			printf("%d exits.\n", num);
			break;
		case 3:
			return 0;
			break;
		}

		printf("Current Status of List : ");
		do
		{
			ret = traverseList(pList, n++, &data);
			if (ret)
				printf("%d ", data);
		} while (ret);
		printf("\n");
	} while (pan != 3);


	return 0;
}