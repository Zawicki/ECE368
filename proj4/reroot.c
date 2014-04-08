#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "reroot.h"

int main (int argc, char * * argv)
{
	if (argc != 3)
	{
		printf("\nInvalid number of arguments\n");
		return EXIT_FAILURE;
	}

	char * in_file = argv[1];
	//char * out_file = argv[2];

	// arr is an array implementation of a binary tree
	// the root node is the node of index num_n
	Node * head = Load_File(in_file);
	printf("\nLoading Complete\n");
	Postorder(head);
	printf("\n\n");
	/*double x_tot = 0;
	double y_tot = 0;

	clock_t pack_t = clock();
	Coord * crd = Pack(arr, num_n, num_b, &x_tot, &y_tot);
	pack_t = clock() - pack_t;*/

	//printf("\n\nElapsed Time:  %le\n\n", ((double) pack_t) / CLOCKS_PER_SEC);

	//Save_File(out_file, arr, crd, num_b);

	return EXIT_SUCCESS;
}

Node * Load_File(char * Filename)
{
	FILE * f = fopen(Filename, "r");

	if (f == NULL)
		return NULL;

	double w;
	double h;

	Stack * s = NULL;
	Node * n = NULL;

	char ch = fgetc(f);

	do
	{
		//printf("\nch = %c\n", ch);
		if (ch == 'V' || ch == 'H')
		{
			n = malloc(sizeof(Node));
			n -> par = NULL;

			//Set the children of the cut node
			n -> rc = s -> n;
			s = Stack_pop(s);
			n -> lc = s -> n;
			s = Stack_pop(s);

			n -> cut = ch;
			n -> width = 0;
			n -> height = 0;
				
			//Set the parents of the cut nodes children
			n -> rc -> par = n;
			n -> lc -> par = n;

			s = Stack_push(s, n);
		}
		else	
		{
			fscanf(f, "%le,%le)", &w, &h);
			n = malloc(sizeof(Node));
			n -> par = NULL;
			n -> lc = NULL;
			n -> rc = NULL;
			n -> cut = '-';
			n -> width = w;
			n -> height = h;
			s = Stack_push(s, n);
		//	printf("\nWidth = %le, Height = %le\n", n -> width, n -> height);
		}
		ch = fgetc(f);
	}while (ch != EOF);

	fclose(f);

	Stack_pop(s);

	return n;
}

Stack * Stack_push(Stack * s, Node * t)
{
	Stack * st = malloc(sizeof(Stack));
	st -> n = t;
	st -> next = s;

	return st; 
}

Stack * Stack_pop(Stack * s)
{
	if (s == NULL)
		return NULL;

	Stack * st = s -> next;
	free(s);

	return st;
}

/*void Save_File(char * Filename, Node * arr, Coord * crd, int num_b)
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
}*/

void Preorder(Node * h)
{
	if (h == NULL)
		return;
	if (h -> cut == 'V' || h -> cut == 'H')
		printf("%c", h -> cut);
	else
		printf("(%le,%le)", h -> width, h-> height);
	Preorder(h -> lc);
	Preorder(h -> rc);
}

void Inorder(Node * h)
{
	if (h == NULL)
		return;

	Inorder(h -> lc);
	if (h -> cut == 'V' || h -> cut == 'H')
		printf("%c", h -> cut);
	else
		printf("(%le,%le)", h -> width, h-> height);
	Inorder(h -> rc);
}

void Postorder(Node * h)
{
	if (h == NULL)
		return;

	Postorder(h -> lc);
	Postorder(h -> rc);
	if (h -> cut == 'V' || h -> cut == 'H')
		printf("%c", h -> cut);
	else
		printf("(%le,%le)", h -> width, h-> height);
}
