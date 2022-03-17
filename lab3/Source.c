#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable : 4996)
#define ERROR -1


/***************************************Matrix and queue structure****************************************************/
typedef struct matrix
{
	int size;
	int** items;
}matrix_t;
typedef struct queue
{
	int size;
	int* items;
	int head;
	int tail;
} queue_t;

//Matrix
matrix_t* CreateMatrix(int size)
{
	int** items = (int**)malloc(size * sizeof(int*) + size * size * sizeof(int));
	if (items == NULL)
	{
		printf("Error of memory allocation \n");
		exit(1);
	}

	char* ptr = (char*)items + size * sizeof(int*);

	int i;
	for (i = 0; i < size; i++)
	{
		items[i] = (int*)(ptr + i * size * sizeof(int));
	}

	matrix_t* matrix = malloc(sizeof(matrix_t));
	if (matrix == NULL)
	{
		printf("Error of memory allocation\n");
		free(items);
		exit(1);
	}

	matrix->size = size;
	matrix->items = items;

	return matrix;
}

void InitMatrix(matrix_t* matrix)
{
	for (int i = 0; i < matrix->size; i++)
	{
		for (int j = 0; j < matrix->size; j++)
		{
			matrix->items[i][j] = 0;
		}
	}
}

void DestroyMatrix(matrix_t* matrix)
{
	free(matrix->items);
	free(matrix);
}

//Queue
queue_t* CreateQueue(int capacity)
{

	int* items = (int*)malloc((capacity + 1) * sizeof(int));
	if (items == NULL)
	{
		printf("Error of memory allocation\n");
		exit(1);
	}

	queue_t* queue = (queue_t*)malloc(sizeof(queue_t));
	if (queue == NULL)
	{
		printf("Error of memory allocation\n");
		free(items);
		exit(1);
	}


	queue->size = capacity + 1;
	queue->items = items;
	queue->head = 0;
	queue->tail = 0;

	return queue;
}

int SizeQueue(queue_t* q)
{
	if (q->head > q->tail)
		return (q->size - q->head + q->tail);

	else
		return (q->tail - q->head);
}

void AddElement(queue_t* q, int elem)
{
	if (SizeQueue(q) != q->size - 1)
	{
		q->items[q->tail] = elem;
		q->tail = (q->tail + 1) % q->size;
	}
}

int isEmpty(queue_t* q)
{
	return (q->head == q->tail);
}

int DeleteElement(queue_t* q)
{
	if (isEmpty(q))
		return ERROR;

	int elem = q->items[q->head];
	q->items[q->head] = 0;
	q->head = (q->head + 1) % q->size;
	return elem;
}

matrix_t* GetGraph(void)
{
	int check;
	int vertices;
	int ver1, ver2;

	check = fscanf(stdin, "%d", &vertices);
	if (check != 1)
	{
		printf("Invalid file.\n");
		exit(1);
	}

	matrix_t* graph = CreateMatrix(vertices);
	InitMatrix(graph);

	while (1)
	{
		check = fscanf(stdin, "%d %d", &ver1, &ver2);

		if (check == EOF)
			break;

		graph->items[ver1][ver2] = 1;
		graph->items[ver2][ver1] = 1;
	}

	return graph;
}
// Breadth-first graph search
void BFS(matrix_t* graph)
{
	int* visited = (int*)calloc(graph->size, sizeof(int));
	if (visited == NULL)
	{
		printf("Memory allocation error\n");
		DestroyMatrix(graph);
		exit(EXIT_FAILURE);
	}
	queue_t* q = CreateQueue(graph->size);

	visited[0] = 1;
	AddElement(q, 0);

	while (isEmpty(q) == 0)
	{
		int i = DeleteElement(q);
		for (int j = 1; j < graph->size; j++)
			if (graph->items[i][j] == 1 && visited[j] == 0)
			{
				visited[j] = 1;
				AddElement(q, j);
			}

		printf("%d ", i);
	}

	free(visited);
	DestroyMatrix(q);
}

void StressTest()
{
	int check;
	int ver1, ver2;
	time_t start, end;


	int vertices = 1;
	start = time(NULL);
	while (1)
	{
		if (time(NULL) - start < 30)
		{
			matrix_t* graph = CreateMatrix(vertices);
			check = fscanf(stdin, "%d %d", &ver1, &ver2);
			InitMatrix(graph);
			while (1)
			{
				if (check == EOF)
					break;

				graph->items[ver1][ver2] = 1;
				graph->items[ver2][ver1] = 1;
			}
			BFS(graph);

			vertices++;
			free(graph);
			//end = clock();
		}
		else
		{
			break;
		}
	}
	printf("Vertices: %d", vertices);
}
int main()
{
	matrix_t* graph = GetGraph();
	BFS(graph);
	DestroyMatrix(graph);
	//StressTest();
	return 0;
}