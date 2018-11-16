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

void insertArc(listGRAPH*graph, void* from, void* to)
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
}

void DFT(listGRAPH* graph, VERTEX*temp, ARC*temp2)
{
	if (temp->prosessed == 0)
	{
		printf("%c", temp->dataPtr);
		temp->prosessed = 1;
	}


	if (temp->pArc)
	{
		temp2 = temp->pArc;
		for (int j = 0; temp2 != NULL; j++)
		{
			DFT(graph, temp2->destination, temp2);
			temp2 = temp2->pNextArc;
		}
	}
	return;
}

void BFT(listGRAPH*graph, VERTEX* start, VERTEX**temp, ARC*temp2, int num, int num2)
{
	int i = 1, test = 0;

	if (start->prosessed == 1)
	{
		printf("%c", start->dataPtr);
		start->prosessed = 0;
	}
	if (!start->pArc)
		return;

	if (start->pArc)
	{
		temp2 = start->pArc;
		for (i; temp2 != NULL; i++)
		{
			temp[num + i] = temp2->destination;
			temp2 = temp2->pNextArc;
		}
	}
	BFT(graph, temp[num2], temp, temp2, num + i - 1, num2 + 1);
}

int main()
{
	FILE *f;
	char file_name[15], start, item, data[2][50], test = 'A',stack[20];
	int num = 0, num2 = 0;
	VERTEX* temp,**temp3=(VERTEX**)malloc(sizeof(VERTEX*));
	ARC* temp2;

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

			if (num == 2)
			{
				num = 0;
				num2 += 1;
			}
		}
		if (item > test)
			test = item;
	}

	fclose(f);
	matrixGRAPH *MAgraph = creMatrixGraph(num2 - 1);

	for (int i = 0; 'A' + i <= test; i++)
		insertVertex(LIgraph, (char*)'A' + i);
	for (int i = 0; i < num2; i++)
		insertArc(LIgraph, (char*)data[0][i], (char*)data[1][i]);
	for (int i = 0; i < num2; i++)
		MatrixAddEdge(MAgraph, data[0][i], data[1][i]);

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
	for (int i = 0; i < MAgraph->Count; i++) {
	for (int j = 0; j < MAgraph->Count; j++) {
	printf("%d ", MAgraph->matrix[i][j]);
	}
	printf("\n");
	}

	printf("Depth-first traversal : ");
	DFT(LIgraph, LIgraph->first, LIgraph->first->pArc);
	printf("\n");
	printf("Breath-first traversal : ");
	BFT(LIgraph, LIgraph->first,temp3,LIgraph->first->pArc,0,1);
	printf("\n");
	return 0;
}
