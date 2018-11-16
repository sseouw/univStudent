#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

int compare(void *first, void *second)
{
	if (first > second)
		return 1;
	else if (first < second)
		return -1;
	else
		return 0;
}

typedef struct {
	int count;
	struct vertex *first;
	int(*compare) (void* argu1, void* argu2);
}listGRAPH;

typedef struct vertex {
	struct vertex* pNextVertex;
	void* dataPtr;
	int inDegree;
	int outDegree;
	short prosessed;
	struct arc* pArc;
}VERTEX;

typedef struct arc {
	struct vertex* destination;
	struct arc* pNextArc;
	int m;
}ARC;

listGRAPH* creListGraph()
{
	listGRAPH *graph = (listGRAPH *)malloc(sizeof(listGRAPH));
	if (graph == NULL)
		return NULL;
	graph->count = 0;
	graph->first = NULL;
	return graph;
}

void insertVertex(listGRAPH* graph, void* data)
{
	VERTEX * temp, *temp2;
	VERTEX* pVertex = (VERTEX *)malloc(sizeof(VERTEX));
	if (pVertex == NULL)
		return;
	pVertex->pNextVertex = NULL;
	pVertex->dataPtr = data;
	pVertex->outDegree = 0;
	pVertex->inDegree = 0;
	pVertex->prosessed = 0;
	pVertex->pArc = NULL;
	graph->count++;

	temp = graph->first;
	if (!temp)
		graph->first = pVertex;
	else
	{
		temp2 = NULL;
		while (temp && (compare(data, temp->dataPtr)> 0))
		{
			temp2 = temp;
			temp = temp->pNextVertex;
		}
		if (!temp2)
			graph->first = pVertex;
		else
			temp2->pNextVertex = pVertex;
		pVertex->pNextVertex = temp;
	}
	return;
}

void insertArc(listGRAPH*graph, void* from, void* to, int m)
{
	VERTEX* temp, *temp2;
	ARC* pArc = (ARC*)malloc(sizeof(ARC)), *temp3, *temp4;
	if (!pArc)
		return;
	temp = graph->first;
	while (temp && (compare(from, temp->dataPtr) > 0))
		temp = temp->pNextVertex;

	temp2 = graph->first;
	while (temp2 && (compare(to, temp2->dataPtr) > 0))
		temp2 = temp2->pNextVertex;

	temp->outDegree++;
	temp2->inDegree++;

	pArc->destination = temp2;

	if (temp->pArc == NULL)
	{
		temp->pArc = pArc;
		pArc->pNextArc = NULL;
	}
	temp3 = NULL;
	temp4 = temp->pArc;
	while (temp4 && (compare(to, temp4->destination->pArc) > 0))
	{
		temp3 = temp4;
		temp4 = temp4->pNextArc;
	}
	if (!temp3)
		temp->pArc = pArc;
	else
		temp3->pNextArc = pArc;
	pArc->pNextArc = temp4;
	pArc->m = m;
}

void minSP(listGRAPH* graph, VERTEX* start, ARC** arc, int num, VERTEX* test, int test2)
{
	VERTEX* newV;
	ARC* newA, *newA2;
	int M[10], i = 1;
	newA = start->pArc, newA2 = start->pArc;

	if ((char)test->dataPtr == 'A' + test2 - 1)
		return;

	while (newA != NULL)
	{
		if (newA == NULL || start->outDegree == i)
			break;
		arc[num] = newA;
		newA = newA->pNextArc;
		i++;
		if (newA->destination == start)
			break;

		num++;
	}
	for (int i = 0; i < num; i++)
		if (arc[i]->m < newA2->m && start != newA2->destination)
			newA2 = arc[i];
	newV = newA2->destination;
	for (int i = 0; i < num; i++)
		if (arc[i]->destination == newV)
			arc[i]->m = 100;
	if (newA2->destination->prosessed == 0)
		printf("\n%c  %c", start->dataPtr, newV->dataPtr);
	newV->prosessed = 1;
	minSP(graph, newV, arc, num, newV, test2);
}

int main()
{
	FILE *f;
	char file_name[15], start, item, data[3][30], test = 'A';
	int num = 0, num2 = 0, num3 = 0, i = 0, **M = (int**)malloc(sizeof(int*));
	VERTEX* temp, *testV = (VERTEX*)malloc(sizeof(VERTEX));
	ARC* temp2, **arc = (ARC**)malloc(sizeof(ARC*)), **arc2 = (ARC**)malloc(sizeof(ARC*));

	listGRAPH* LIgraph = creListGraph();

	printf("File Myung : ");
	scanf("%s", &file_name);

	f = fopen(file_name, "r");

	fscanf(f, "%c", &start);
	while (fscanf(f, "%c", &item) != EOF)
	{
		if (item != '\n'&& item != ' ')
		{
			data[num][num2] = item;
			num++;

			if (num == 3)
			{
				num = 0;
				num2 += 1;
			}
		}
		if (item > test)
			test = item;
	}
	fclose(f);

	for (i = 0; 'A' + i <= test; i++)
		insertVertex(LIgraph, (char*)'A' + i);
	for (int i = 0; i < num2; i++)
		insertArc(LIgraph, (char*)data[0][i], (char*)data[1][i], (int)(data[2][i] - '0'));


	printf("minimum spanning tree : ");
	minSP(LIgraph, LIgraph->first, arc, 0, testV, i);
	printf("\nshortest path from A :\n ");


	return 0;
}