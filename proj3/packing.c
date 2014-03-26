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

	// arr is an array implementation of a binary tree
	// the root node is the node of index num_n
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
	char w [15];
	char h [15];

	for (i = 1; i <= *num_n; i++)
	{
		fscanf(f, "%d", &ind);
		fscanf(f, "%d %d %d %c %s %s\n", &(&arr[ind]) -> par, &(&arr[ind]) -> lc, &(&arr[ind]) -> rc, &(&arr[ind]) -> cut, w, h);

		if (w[0] != '-')
			(&arr[ind]) -> width = atof(w);
		else
			(&arr[ind]) -> width = 0;
		
		if (h[0] != '-')
			(&arr[ind]) -> height = atof(h);
		else
			(&arr[ind]) -> height = 0;	

		//printf("%d %d %d %c %le %le\n", (&arr[ind]) -> par, (&arr[ind]) -> lc, (&arr[ind]) -> rc, (&arr[ind]) -> cut, (&arr[ind]) -> width, (&arr[ind]) -> height);
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

	double xt = 0;
	double max_h = 0;

	printf("\n\nCoords1: ");
	Find_Coords1(crd, arr, size, x_tot, &max_h);

	*y_tot += max_h;
	max_h = 0;

	printf("\n\nCoords2: ");
	Find_Coords2(crd, arr, size, &xt, &max_h, *y_tot);

	*y_tot += max_h;
	max_h = 0;
	if (xt > *x_tot)
		*x_tot = xt;
	xt = 0;

	printf("\n\nCoords3: ");
	Find_Coords3(crd, arr, size, &xt, &max_h, *y_tot);
	
	*y_tot += max_h;
	max_h = 0;
	if (xt > *x_tot)
		*x_tot = xt;
	xt = 0;

	printf("\n\nCoords4: ");
	Find_Coords4(crd, arr, size, &xt, &max_h, *y_tot);
	
	*y_tot += max_h;
	if (xt > *x_tot)
		*x_tot = xt;

	printf("\n\nWidth:  %le", *x_tot);
	printf("\nHeight:  %le", *y_tot);
	
	printf("\n\nX-coordinate:  %le", (&crd[num_b]) -> x);
	printf("\nY-coordinate:  %le", (&crd[num_b]) -> y);
	
	return crd;
}

void Find_Coords1(Coord * crd, Node * arr, int ind, double * x_tot, double * max_h)
{
	//printf("%d ", ind);	
	if ((&arr[ind]) -> cut == 'V')
	{
		Find_Coords1(crd, arr, (&arr[ind]) -> lc, x_tot, max_h);
		Find_Coords1(crd, arr, (&arr[ind]) -> rc, x_tot, max_h);
	}
	else if ((&arr[ind]) -> cut == 'H')
	{
		Find_Coords1(crd, arr, (&arr[ind]) -> rc, x_tot, max_h);
	}
	else
	{
		printf("%d ", ind);
		(&crd[ind]) -> x = *x_tot;
		(&crd[ind]) -> y = 0;

		//if ((&arr[(&arr[ind]) -> par]) -> cut == 'V')
			*x_tot += (&arr[ind]) -> width;
	
		if (*max_h < (&arr[ind]) -> height)
			*max_h = (&arr[ind]) -> height;
	}
}

void Find_Coords2(Coord * crd, Node * arr, int ind, double * x_tot, double * max_h, double yt)
{
	//printf("%d ", ind);	
	if ((&arr[ind]) -> cut == 'V')
	{
		if ((&arr[ind]) -> par != -1)	
			Find_Coords2(crd, arr, (&arr[ind]) -> lc, x_tot, max_h, yt);
	}
	else if ((&arr[ind]) -> cut == 'H')
	{
		if ((&arr[(&arr[ind]) -> par]) -> cut != 'V')
			Find_Coords2(crd, arr, (&arr[ind]) -> rc, x_tot, max_h, yt);
		if ((&arr[(&arr[ind]) -> par]) -> cut != 'H' && (&arr[ind]) -> par != -1)
			Find_Coords2(crd, arr, (&arr[ind]) -> lc, x_tot, max_h, yt);
	}
	else
	{
		printf("%d ", ind);
		(&crd[ind]) -> x = *x_tot;
		(&crd[ind]) -> y = yt;

		if ((&arr[(&arr[ind]) -> par]) -> cut == 'V')
			*x_tot += (&arr[ind]) -> width;
	
		if (*max_h < (&arr[ind]) -> height)
			*max_h = (&arr[ind]) -> height;
	}
}

void Find_Coords3(Coord * crd, Node * arr, int ind, double * x_tot, double * max_h, double yt)
{
	//printf("%d ", ind);	
	if ((&arr[ind]) -> cut == 'V')
	{
		if ((&arr[ind]) -> par != -1)
			Find_Coords3(crd, arr, (&arr[ind]) -> lc, x_tot, max_h, yt);
		Find_Coords3(crd, arr, (&arr[ind]) -> rc, x_tot, max_h, yt);
	}
	else if ((&arr[ind]) -> cut == 'H')
	{
		if ( (&arr[(&arr[ind]) -> par]) -> cut != 'V' && (&arr[ind]) -> par != -1)
			Find_Coords3(crd, arr, (&arr[ind]) -> rc, x_tot, max_h, yt);
		if ((&arr[(&arr[ind]) -> par]) -> cut != 'H')
			Find_Coords3(crd, arr, (&arr[ind]) -> lc, x_tot, max_h, yt);
	}
	else
	{
		printf("%d ", ind);
		(&crd[ind]) -> x = *x_tot;
		(&crd[ind]) -> y = yt;

		if ((&arr[(&arr[ind]) -> par]) -> cut == 'V')
			*x_tot += (&arr[ind]) -> width;
	
		if (*max_h < (&arr[ind]) -> height)
			*max_h = (&arr[ind]) -> height;
	}
}

void Find_Coords4(Coord * crd, Node * arr, int ind, double * x_tot, double * max_h, double yt)
{
	//printf("%d ", ind);	
	if ((&arr[ind]) -> cut == 'V')
	{
		if ((&arr[ind]) -> par != -1)
			Find_Coords4(crd, arr, (&arr[ind]) -> lc, x_tot, max_h, yt);
		Find_Coords4(crd, arr, (&arr[ind]) -> rc, x_tot, max_h, yt);
	}
	else if ((&arr[ind]) -> cut == 'H')
	{
		if ((&arr[(&arr[ind]) -> par]) -> cut != 'V')
		Find_Coords4(crd, arr, (&arr[ind]) -> lc, x_tot, max_h, yt);
	}
	else
	{
		printf("%d ", ind);
		(&crd[ind]) -> x = *x_tot;
		(&crd[ind]) -> y = yt;

		if ((&arr[(&arr[ind]) -> par]) -> cut == 'V')
			*x_tot += (&arr[ind]) -> width;
	
		if (*max_h < (&arr[ind]) -> height)
			*max_h = (&arr[ind]) -> height;
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





