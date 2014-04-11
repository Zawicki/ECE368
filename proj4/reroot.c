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
	char * out_file = argv[2];

	// arr is an array implementation of a binary tree
	// the root node is the node of index num_n
	Node * head = Load_File(in_file);
	printf("\nLoading Complete\n");
	Postorder(head);
	
	Find_Area(head);
	printf("\n\nWidth: %le\nHeight: %le\n\n", head -> width, head -> height);
	
	double x_new = 0;
	double y_prev = head -> height;
	
	Find_XCoords(head, &x_new);
	Find_YCoords(head, &y_prev);

	FILE * f = fopen(out_file, "w");
	Save_File(f, head);
	fclose(f);

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
			n -> x = 0;
			n -> y = 0;
				
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
			n -> x = 0;
			n -> y = 0;
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

void Save_File(FILE * f, Node * h)
{
	if (h == NULL)
		return;

	Save_File(f, h -> lc);
	Save_File(f, h -> rc);
	
	if (h -> cut == '-')
		fprintf(f, "%le %le %le %le\n", h -> width, h -> height, h -> x, h -> y);
}

void Find_Area(Node * h)
{
	if (h -> cut == 'V')
	{
		Find_Area(h -> lc);
		Find_Area(h -> rc);
		
		h -> width = h -> lc -> width + h -> rc -> width;
	
		if (h -> lc -> height >= h -> rc -> height)
			h -> height = h -> lc -> height;
		else
			h -> height = h -> rc -> height;
	}
	else if (h -> cut == 'H')
	{
		Find_Area(h -> rc);
		Find_Area(h -> lc);

		h -> height = h -> lc -> height + h -> rc -> height;

		if (h -> lc -> width >= h -> rc -> width)
			h -> width = h -> lc -> width;
		else
			h -> width = h -> rc -> width;
	}
	else
		return;
}

void Find_XCoords(Node * h, double * x_new)
{
	if (h == NULL)
		return;

	if (h -> par != NULL)
	{
		if (h -> par -> cut == 'H' && h -> par -> rc == h)
			*x_new = 0;
	}

	Find_XCoords(h -> lc, x_new);
	Find_XCoords(h -> rc, x_new);
	
	if (h -> cut == '-')
	{
		if (h -> par -> cut == 'V')
		{
			if (h -> par -> lc == h)
				h -> x = *x_new;
			else
				h -> x = h -> par -> width - h -> width;
			*x_new = *x_new + h -> width;
		}
		else
		{
			if (h -> par -> lc -> width > h -> par -> rc -> width)
			{
				if (*x_new - h -> par -> lc -> width > 0)
					h -> x = *x_new - h -> par -> lc -> width;
				else
					h -> x = 0;
			}
			else
			{
				if (*x_new - h -> par -> rc -> width > 0)
					h -> x = *x_new - h -> par -> rc -> width;
				else
					h -> x = 0;
			}
		}
	}
}

void Find_YCoords(Node * h, double * y_prev)
{
	if (h == NULL)
		return;

	Find_YCoords(h -> lc, y_prev);
	Find_YCoords(h -> rc, y_prev);
	
	if (h -> cut == '-')
	{
		if (h -> par -> cut == 'V')
		{
			if (*y_prev - h -> par -> height > 0)
				h -> y = *y_prev - h -> par -> height;
			else
				h -> y = 0;
		}
		else
		{
			if (h -> par -> lc == h)
			{
				h -> y = *y_prev - h -> height;
				*y_prev = h -> y;
			}
			else
			{
				h -> y = *y_prev - h -> par -> height;
				*y_prev = h -> y;
			}
		}
	}
}

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
