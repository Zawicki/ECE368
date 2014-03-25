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
	//char * out_file = argv[2];

	//clock_t pack_t = 0;

	int num_b; // number of boxes
	int num_n; // nubmer of nodes

	//arr is an array implementation of a binary tree
	//the root node is the node of index num_n
	Node * arr = Load_File(in_file, &num_b, &num_n);

	double x_tot;
	double y_tot;

	Coord * crd = Pack(arr, num_n, num_b, &x_tot, &y_tot);

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

	for (i = 0; i < *num_n; i++)
	{
		//printf("i = %d\n", i);
		fscanf(f, "%d", &ind);
		fscanf(f, "%d %d %d %c %c %c\n", &(&arr[ind]) -> par, &(&arr[ind]) -> lc, &(&arr[ind]) -> rc, &(&arr[ind]) -> cut, &w, &h);

		if (w != '-')
			(&arr[ind]) -> width = atoi(&w);
		else
			(&arr[ind]) -> width = 0;
		
		if (h != '-')
			(&arr[ind]) -> height = atoi(&h);
		else
			(&arr[ind]) -> height = 0;

		//printf("%d %d %d %c %lf %lf\n", (&arr[ind]) -> par, (&arr[ind]) -> lc, (&arr[ind]) -> rc, (&arr[ind]) -> cut, (&arr[ind]) -> width, (&arr[ind]) -> height);
	}

	return arr;
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

	Find_Coords(crd, arr, size, x_tot, y_tot);

	printf("\n\nWidth:  %lf", *x_tot);
	printf("\nHeight:  %lf", *y_tot);
	
	printf("\n\nX-coordinate:  %lf", (&crd[num_b]) -> x);
	printf("\nY-coordinate:  %lf", (&crd[num_b]) -> y);
	
	return crd;
}

void Find_Coords(Coord * crd, Node * arr, int ind, double * x_tot, double * y_tot)
{	
	if ((&arr[ind]) -> lc != -1)
		Find_Coords(crd, arr, (&arr[ind]) -> lc, x_tot, y_tot);
	if ((&arr[ind]) -> rc != -1)
		Find_Coords(crd, arr, (&arr[ind]) -> rc, x_tot, y_tot);
	
	if ( (&arr[ind]) -> cut != 'V' || (&arr[ind]) -> cut != 'H')
	{
		(&crd[ind]) -> x = *x_tot;
		(&crd[ind]) -> y = *y_tot;

		*x_tot += (&arr[ind]) -> width;
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





