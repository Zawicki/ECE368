#include <stdlib.h>
#include <stdio.h>

typedef struct _node
{
	int id;
	int dist;
}Node;

typedef struct _heap
{
	Node * v;
}Queue;

int * * Load_Graph(char * Filename, int * size);
int Dijkstra(int size, int src, int dest, int * * matrix);
void Downward_heapify(Queue * pq, int i, int n);
int compHeap(const void * p1, const void * p2);

int main (int argc, char * * argv)
{
	if (argc != 2)
	{
		printf("\nInvalid number of arguments\n");
		return EXIT_FAILURE;
	}

	char * in_file = argv[1];

	int size;
	int * * matrix = Load_Graph(in_file, &size);

	/*printf("\n  Adjacency Matrix\n\n");
	printf("     0 1 2 3 4 5 6 7 8 9 A B C D\n");
	printf("     ---------------------------\n");
	int i, j;
	for (i = 0; i < size; i++)
	{
		printf("%3d:", i);
		for (j = 0; j < size; j++)
		{
			printf(" %d", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");*/

	int answer = Dijkstra(size, 0, size - 1, matrix);
	printf("%d\n", answer);

	int i;
	for (i = 0; i < size; i++)
		free(matrix[i]);
	free(matrix);

	return EXIT_SUCCESS;
}

int Dijkstra(int size, int src, int dest, int * * matrix)
{
	Node * graph = malloc(sizeof(Node) * size);
	Queue * PQ = malloc(sizeof(Queue) * size);

	int n = size;

	int i;
	for (i = 0; i < size; i++)
	{
		graph[i].id = i;
		graph[i].dist = 10000;
		PQ[i].v = &graph[i];
	}
	graph[src].dist = 0;

	Node u;
	while (size > 0)
	{
		u = *(PQ[0].v);
		PQ[0] = PQ[size - 1];
		size--;
		qsort(PQ, size, sizeof(Queue), compHeap);

		for (i = 0; i < n; i++)
		{
			if (matrix[u.id][i] >= 0)
			{
				if (graph[i].dist > (u.dist + matrix[u.id][i]))
					graph[i].dist = u.dist + matrix[u.id][i];
			}
		}
	}

	int answer = graph[dest].dist;

	free(PQ);
	free(graph);
	return answer;
}

int compHeap(const void * p1, const void * p2)
{
	Queue * ptr1 = (Queue *)p1;
	Queue * ptr2 = (Queue *)p2;

	Queue elem1 = * ptr1;
	Queue elem2 = * ptr2;

	if (elem1.v -> dist < elem2.v -> dist)
		return -1;
	if (elem1.v -> dist == elem2.v -> dist)
		return 0;
	return 1;
}

int * * Load_Graph(char * Filename, int * size)
{
	FILE * f = fopen(Filename, "r");

	if (f == NULL)
		return NULL;

	int n;
	fscanf(f, "%d", &n);
	*size = 2*(n-1)*n + 2;
	int * * matrix = malloc(sizeof(int *) * (*size));
	
	//initialize all weights to a large number
	int i, j;
	for (i = 0; i < (*size); i++)
	{
		matrix[i] = malloc(sizeof(int) * (*size));
		for (j = 0; j < (*size); j++)
		{
			matrix[i][j] = -1;
		}
	}

	//read plank locations from file
	char c = fgetc(f);
	int planks[n - 1][n];
	int row = 0;
	int col = 0;
	while (c != EOF)
	{
		if (c == '0' || c == '1')
		{
			planks[row][col] = c - '0';
			col++;
			if (col > n - 1)
			{
				col = 0;
				row++;
			}
		}
		c = fgetc(f);
	}
	fclose(f);

	//find weights from source to first column
	int ct = 0;
	matrix[*size - 1][*size - 1] = 0;
	matrix[0][0] = 0;
	for (i = n; i < (*size) - 1; i += 2*n - 1)
	{
		if (planks[ct][0] == 1)
			matrix[0][i] = 0;
		else
			matrix[0][i] = 1;
		ct++;
	}

	row = -1;
	col = 0;
	int h = 1;
	for (i = 1; i < (*size) - 1; i++)
	{
		for (j = 1; j < (*size); j++)
		{
			//first horizontal set of planks
			if (i < n)
			{	
				//down left
				if (j == i + n - 1)
				{
						if (planks[row + 1][col] == 1)
							matrix[i][j] = 0;
						else
							matrix[i][j] = 1;
				}
			
				//down right
				if (j == i + n)
				{
						if (planks[row + 1][col + 1] == 1)
							matrix[i][j] = 0;
						else
							matrix[i][j] = 1;
				}
			}

			//last horizontal set of planks
			else if (i > (*size) - 1 - n && i < (*size) - 1)
			{
				//up left
				if (j == i - n)
				{
						if (planks[row - 1][col] == 1)
							matrix[i][j] = 0;
						else
							matrix[i][j] = 1;
				}

				//up right
				if (j == i - n + 1)
				{
						if (planks[row - 1][col + 1] == 1)
							matrix[i][j] = 0;
						else
							matrix[i][j] = 1;
				}
			}
			//first vertical set of planks
			else if (i == n + (2*n - 1)*row)
			{
				if (j == (i - n + 1) || j == (i + n))
					matrix[i][j] = 1;
			}
			//last vertical set of planks
			else if (i == n + n - 1 + (2*n - 1)*row)
			{
				if (j == ((*size) - 1))
					matrix[i][j] = 1;
			}
			//planks not on perimeter
			else
			{
				if (h == 1)
				{
					//up left
					if (j == i - n)
					{
						if (planks[row][col] == 1)
							matrix[i][j] = 0;
						else
							matrix[i][j] = 1;
					}
	
					//up right
					if (j == i - n + 1)
					{
						if (planks[row][col + 1] == 1)
							matrix[i][j] = 0;
						else
							matrix[i][j] = 1;
					}
	
					//down left
					if (j == i + n - 1)
					{
						if (planks[row + 1][col] == 1)
							matrix[i][j] = 0;
						else
							matrix[i][j] = 1;
					}
				
					//down right
					if (j == i + n)
					{
						if (planks[row + 1][col + 1] == 1)
							matrix[i][j] = 0;
						else
							matrix[i][j] = 1;
					}
				}
				else
				{
					if (j == i - n + 1 || j == i - n || j == i + n - 1 || j == i + n)
					{
						if (j != *size - 1)
							matrix[i][j] = 1;
					}
					else if (j == i - 2*n + 1)
					{
						if (planks[row - 1][col] == 1)
							matrix[i][j] = 0;
					}
					else if (j == i + 2*n - 1)
					{
						if (planks[row + 1][col] == 1)
							matrix[i][j] = 0;
					}
				}
			}

			if (j == i)
				matrix[i][j] = 0;
		}
		//determine if plank is vertical or horizontal
		col++;
		if ((col == n - 1) & (h == 1))
		{
			h = 0;
			col = 0;
			row++;
		}
		if ((col == n) & (h == 0))
		{
			h = 1;
			col = 0;
		}
	}
	
	return matrix;
}






