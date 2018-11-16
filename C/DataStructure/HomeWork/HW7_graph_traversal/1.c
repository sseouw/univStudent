#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct {
	int Count;
	int **matrix;
}matrixGRAPH;

matrixGRAPH* creMatrixGraph(int count)
{
	matrixGRAPH *graph = (matrixGRAPH *)malloc(sizeof(matrixGRAPH) * count);
	graph->matrix = (int **)malloc(sizeof(int*) * count);

	graph->Count = count;

	for (int i = 0; i < count; i++)
	{
		graph->matrix[i] = (int *)malloc(sizeof(int) * count);
		for (int j = 0; j < count; j++)
			graph->matrix[i][j] = 0;
	}
	return graph;
}

void MatrixAddEdge(matrixGRAPH *graph, char start, char goal)
{
	int a = start - 'A', b = goal - 'A';
	graph->matrix[a][b] = 1;
}

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

typedef struct vertex{
	struct vertex* pNextVertex;
	void* dataPtr;
	int inDegree;
	int outDegree;
	short prosessed;
	struct arc* pArc;
}VERTEX;

typedef struct arc{
	struct vertex* destination;
	struct arc* pNextArc;
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

void insertVertex(listGRAPH* graph,void* data)
{
	VERTEX * temp,*temp2;
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
		graph->first= pVertex;
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

void insertArc(listGRAPH*graph, void* from, void* to)
{
	VERTEX* temp,*temp2;
	ARC* pArc = (ARC*)malloc(sizeof(ARC)),*temp3,*temp4;
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
}

int main()
{
	VERTEX* temp;
	ARC* temp2;

	matrixGRAPH *MAgraph = creMatrixGraph(5);
	listGRAPH* LIgraph = creListGraph();

	MatrixAddEdge(MAgraph, 'A', 'B');
	MatrixAddEdge(MAgraph, 'A', 'C');
	MatrixAddEdge(MAgraph, 'B', 'C');
	MatrixAddEdge(MAgraph, 'B', 'E');
	MatrixAddEdge(MAgraph, 'C', 'E');
	MatrixAddEdge(MAgraph, 'E', 'D');

	for (int i = 0; i < MAgraph->Count; i++) {
		for (int j = 0; j < MAgraph->Count; j++) {
			printf("%d ", MAgraph->matrix[i][j]);
		}
		printf("\n");
	}

	insertVertex(LIgraph, (char *)'A');
	insertVertex(LIgraph, (char *)'B');
	insertVertex(LIgraph, (char *)'C');
	insertVertex(LIgraph, (char *)'D');
	insertVertex(LIgraph, (char *)'E');

	insertArc(LIgraph, (char *)'A', (char *)'B');
	insertArc(LIgraph, (char *)'A', (char *)'C');
	insertArc(LIgraph, (char *)'B', (char *)'C');
	insertArc(LIgraph, (char *)'B', (char *)'E');
	insertArc(LIgraph, (char *)'C', (char *)'E');
	insertArc(LIgraph, (char *)'E', (char *)'D');

	temp = LIgraph->first;
	for (int i = 0; i < LIgraph->count; i++)
	{
		printf("%c -> ", temp->dataPtr);
		temp2 = temp->pArc;
		for (int j = 0; temp2 != NULL; j++)
		{
			printf("%c", temp2->destination->dataPtr);
			temp2 = temp2->pNextArc;
		}
		temp = temp->pNextVertex;
		printf("\n");
	}
	return 0;
}