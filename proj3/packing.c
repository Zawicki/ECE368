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

	Pack(arr, num_n);

	Delete_Nodes(arr, num_n);

	return EXIT_SUCCESS;
}

Node * Load_File(char * Filename, int * num_b, int * num_n)
{
	FILE * f = fopen(Filename, "r");

	if (f == NULL)
		return 0;

	fscanf(f, "%d", num_b);
	fscanf(f, "%d", num_n);

	Node * arr = malloc(sizeof(Node) * (*num_n + 1));

	int i;
	int ind;

	for (i = 0; i < *num_n; i++);
	{
		fscanf(f, "%d", &ind);
		fscanf(f, "%d %d %d %c %lf %lf", &(&arr[ind]) -> par, &(&arr[ind]) -> lc, &(&arr[ind]) -> rc, &(&arr[ind]) -> cut, &(&arr[ind]) -> width, &(&arr[ind]) -> height);
	}

	return arr;
}

void Pack(Node * arr, int size)
{
	printf("\nPreorder:  ");
	Preorder(arr, size);
	printf("\n\nInorder:  ");
	Inorder(arr, size);
	Postorder(arr, size);
	printf("\n\nPostorder:  ");
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

void Delete_Nodes(Node * arr, int size)
{
	int i;
	
	for (i = 0; i < size; i++)
	{
		free(&arr[i]);
	}
}





