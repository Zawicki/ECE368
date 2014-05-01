#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

typedef struct _graph
{
	int weight;
}Graph;

Graph * * Load_Graph(char * Filename, int * size);
//void Dijkstra(Graph * *, int * size, int src, int dest);

int main (int argc, char * * argv)
{
	if (argc != 2)
	{
		printf("\nInvalid number of arguments\n");
		return EXIT_FAILURE;
	}

	char * in_file = argv[1];

	int size;
	Graph * * g = Load_Graph(in_file, &size);

	printf("\n  Adjacency Matrix\n\n");
	printf("     0 1 2 3 4 5 6 7 8 9 A B C D\n");
	printf("     ---------------------------\n");
	int i, j;
	for (i = 0; i < size; i++)
	{
		printf("%3d:", i);
		for (j = 0; j < size; j++)
		{
			printf(" %d", g[i][j].weight);
		}
		printf("\n");
	}
	printf("\n\n");

	for (i = 0; i < size; i++)
		free(g[i]);
	free(g);

	return EXIT_SUCCESS;
}

Graph * * Load_Graph(char * Filename, int * size)
{
	FILE * f = fopen(Filename, "r");

	if (f == NULL)
		return NULL;

	int n;
	fscanf(f, "%d", &n);
	*size = 2*(n-1)*n + 2;
	Graph * * g = malloc(sizeof(Graph *) * (*size));
	
	//initialize all weights to a large number
	int i, j;
	for (i = 0; i < (*size); i++)
	{
		g[i] = malloc(sizeof(Graph) * (*size));
		for (j = 0; j < (*size); j++)
		{
			g[i][j].weight = 9;
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
	g[*size - 1][*size - 1].weight = 0;
	g[0][0].weight = 0;
	for (i = n; i < (*size) - 1; i += 2*n - 1)
	{
		if (planks[ct][0] == 1)
			g[0][i].weight = 0;
		else
			g[0][i].weight = 1;
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
							g[i][j].weight = 0;
						else
							g[i][j].weight = 1;
				}
			
				//down right
				if (j == i + n)
				{
						if (planks[row + 1][col + 1] == 1)
							g[i][j].weight = 0;
						else
							g[i][j].weight = 1;	
				}
			}

			//last horizontal set of planks
			else if (i > (*size) - 1 - n && i < (*size) - 1)
			{
				//up left
				if (j == i - n)
				{
						if (planks[row - 1][col] == 1)
							g[i][j].weight = 0;
						else
							g[i][j].weight = 1;	
				}

				//up right
				if (j == i - n + 1)
				{
						if (planks[row - 1][col + 1] == 1)
							g[i][j].weight = 0;
						else
							g[i][j].weight = 1;	
				}
			}
			//first vertical set of planks
			else if (i == n + (2*n - 1)*row)
			{
				if (j == (i - n + 1) || j == (i + n))
					g[i][j].weight = 1;
			}
			//last vertical set of planks
			else if (i == n + n - 1 + (2*n - 1)*row)
			{
				if (j == ((*size) - 1))
					g[i][j].weight = 1;
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
							g[i][j].weight = 0;
						else
							g[i][j].weight = 1;	
					}
	
					//up right
					if (j == i - n + 1)
					{
						if (planks[row][col + 1] == 1)
							g[i][j].weight = 0;
						else
							g[i][j].weight = 1;	
					}
	
					//down left
					if (j == i + n - 1)
					{
						if (planks[row + 1][col] == 1)
							g[i][j].weight = 0;
						else
							g[i][j].weight = 1;	
					}
				
					//down right
					if (j == i + n)
					{
						if (planks[row + 1][col + 1] == 1)
							g[i][j].weight = 0;
						else
							g[i][j].weight = 1;	
					}
				}
				else
				{
					if (j == i - n + 1 || j == i - n || j == i + n - 1 || j == i + n)
					{
						if (j != *size - 1)
							g[i][j].weight = 1;
					}
					else if (j == i - 2*n + 1)
					{
						if (planks[row - 1][col] == 1)
							g[i][j].weight = 0;
					}
					else if (j == i + 2*n - 1)
					{
						if (planks[row + 1][col] == 1)
							g[i][j].weight = 0;
					}
				}
			}

			if (j == i)
				g[i][j].weight = 0;
		}
		//determine if plank is vertical or horizontal
		col++;
		if ((col == n - 1) & (h == 1))
		{
			h = 0;
			col = 0;
			printf("row = %d", row);
			row++;
		}
		if ((col == n) & (h == 0))
		{
			h = 1;
			col = 0;
		}
	}
	
	return g;
}






