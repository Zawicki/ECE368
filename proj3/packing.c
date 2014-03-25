#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "packing.h"

int main (int argc, char * * argv)
{
	if (argc != 3)
	{
		printf("\nInvalid number of arguments\n");
		return EXIT_FAILURE;
	}

	char * in_file = argv[1];
	char * out_file = argv[2];
	
	int num_b; // number of boxes
	int num_n; // nubmer of nodes

	//arr is an array implementation of a binary tree
	//the root node is the node of index num_n
	Node * arr = Load_File(in_file, &num_b, &num_n);

	double x_tot = 0;
	double y_tot = 0;

	clock_t pack_t = clock();
	Coord * crd = Pack(arr, num_n, num_b, &x_tot, &y_tot);
	pack_t = clock() - pack_t;

	printf("\n\nElapsed Time:  %le\n\n", ((double) pack_t) / CLOCKS_PER_SEC);

	Save_File(out_file, arr, crd, num_b);

	free(arr);
	free(crd);

	return EXIT_SUCCESS;
}

Node * Load_File(char * Filename, int * num_b, int * num_n)
{
	FILE * f = fopen(Filename, "r");

	if (f == NULL)
		return 0;

	fscanf(f, "%d", num_b);
	fscanf(f, "%d", num_n);

	// a nodes id is stored as it's index
	Node * arr = malloc(sizeof(Node) * (*num_n + 1));

	int i;
	int ind;
	char w;
	char h;

	for (i = 1; i <= *num_n; i++)
	{
		//printf("i = %d\n", i);
		fscanf(f, "%d", &ind);
		fscanf(f, "%d %d %d %c %c %c\n", &(&arr[ind]) -> par, &(&arr[ind]) -> lc, &(&arr[ind]) -> rc, &(&arr[ind]) -> cut, &w, &h);

		if (w != '-')
			(&arr[ind]) -> width = w - '0';
		else
			(&arr[ind]) -> width = 0;
		
		if (h != '-')
			(&arr[ind]) -> height = h - '0';
		else
			(&arr[ind]) -> height = 0;

		//printf("%d %d %d %c %lf %lf\n", (&arr[ind]) -> par, (&arr[ind]) -> lc, (&arr[ind]) -> rc, (&arr[ind]) -> cut, (&arr[ind]) -> width, (&arr[ind]) -> height);
	}

	return arr;
}

void Save_File(char * Filename, Node * arr, Coord * crd, int num_b)
{
	FILE * f = fopen(Filename, "w");

	if (f == NULL)
		return;

	fprintf(f, "%d\n", num_b);

	int i = 1;
	while (i <= num_b)
	{
		fprintf(f, "%d %le %le %le %le\n", i, (&arr[i]) -> width, (&arr[i]) -> height, (&crd[i]) -> x, (&crd[i]) -> y);
		i++;
	}

	fclose(f);
}

Coord * Pack(Node * arr, int size, int num_b, double * x_tot, double * y_tot)
{
	if (size < 1)
		return NULL;
	
	Coord * crd = malloc(sizeof(Coord) * (num_b + 1));
	
	if (size == 1)
	{
		*x_tot = 0;
		*y_tot = 0;

		(&crd[1]) -> x = 0;
		(&crd[1]) -> y = 0;
	}

	printf("\nPreorder:  ");
	Preorder(arr, size);
	
	printf("\n\nInorder:  ");
	Inorder(arr, size);
	
	printf("\n\nPostorder:  ");
	Postorder(arr, size);

	printf("\n\nCoord Order:  ");
	Find_Coords(crd, arr, size, x_tot, y_tot);

	printf("\n\nWidth:  %le", *x_tot);
	printf("\nHeight:  %le", *y_tot);
	
	printf("\n\nX-coordinate:  %le", (&crd[num_b]) -> x);
	printf("\nY-coordinate:  %le", (&crd[num_b]) -> y);
	
	return crd;
}

void Find_Coords(Coord * crd, Node * arr, int ind, double * x_tot, double * y_tot)
{	
/*	if ((&arr[ind]) -> cut == 'V')
	{
		Find_Coords(crd, arr, (&arr[ind]) -> lc, x_tot, y_tot);
		Find_Coords(crd, arr, (&arr[ind]) -> rc, x_tot, y_tot);
	}
	else if ((&arr[ind]) -> cut == 'H')
	{
		Find_Coords(crd, arr, (&arr[ind]) -> rc, x_tot, y_tot);
		Find_Coords(crd, arr, (&arr[ind]) -> lc, x_tot, y_tot);
	}
	else
	{
		printf("%d ", ind);
		(&crd[ind]) -> x = *x_tot;
		(&crd[ind]) -> y = *y_tot;

		if ((&arr[(&arr[ind]) -> par]) -> cut == 'V')
			*x_tot += (&arr[ind]) -> width;
		if ((&arr[(&arr[ind]) -> par]) -> cut == 'H')
			*y_tot += (&arr[ind]) -> height;
	}
*/
	if ((&arr[ind]) -> cut == 'V')
	{
		Find_Coords(crd, arr, (&arr[ind]) -> lc, x_tot, y_tot);
		Find_Coords(crd, arr, (&arr[ind]) -> rc, x_tot, y_tot);
	}
	if (((&arr[ind]) -> cut != 'V') && ((&arr[ind]) -> cut != 'H'))
	{
		printf("%d ", ind);
		(&crd[ind]) -> x = *x_tot;
		(&crd[ind]) -> y = *y_tot;
		
		*x_tot += (&arr[ind]) -> width;
	}
	if ((&arr[ind]) -> cut == 'H')
	{
		Find_Coords(crd, arr, (&arr[ind]) -> rc, x_tot, y_tot);
		Find_Coords(crd, arr, (&arr[ind]) -> lc, x_tot, y_tot);
	}
	if (((&arr[ind]) -> cut != 'V') && ((&arr[ind]) -> cut != 'H'))
	{
		printf("%d ", ind);
		(&crd[ind]) -> x = *x_tot;
		(&crd[ind]) -> y = *y_tot;
		
		*y_tot += (&arr[ind]) -> height;
	}
}

void Preorder(Node * arr, int ind)
{
	printf("%d ", ind);

	if ((&arr[ind]) -> lc != -1)
		Preorder(arr, (&arr[ind]) -> lc);
	if ((&arr[ind]) -> rc != -1)
		Preorder(arr, (&arr[ind]) -> rc);
}

void Inorder(Node * arr, int ind)
{
	if ((&arr[ind]) -> lc != -1)
		Inorder(arr, (&arr[ind]) -> lc);
	
	printf("%d ", ind);

	if ((&arr[ind]) -> rc != -1)
		Inorder(arr, (&arr[ind]) -> rc);
}

void Postorder(Node * arr, int ind)
{
	if ((&arr[ind]) -> lc != -1)
		Postorder(arr, (&arr[ind]) -> lc);
	if ((&arr[ind]) -> rc != -1)
		Postorder(arr, (&arr[ind]) -> rc);
	
	printf("%d ", ind);
}





