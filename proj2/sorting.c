#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"

Node * Create_Node(long val)
{
	Node * n = malloc(sizeof(Node));
	n -> value = val;
	n -> next = NULL;
	return n;
}

Node * Load_File(char *Filename)
{
	FILE * f = fopen(Filename, "r");
	
	if (f ==  NULL)
		return 0;

	Node * head = NULL;
	Node * n = NULL;
	long size = 0;
	long value = 0;

	while (fscanf(f, "%ld", &value) != EOF)
	{
		n = Create_Node(value);
		n -> next = head;
		head = n;
		size++;
	}

	n = Create_Node(size);
	n -> next = head;
	head = n;
	
	return head;
}

int Save_File(char * Filename, Node * head)
{
	FILE * f = fopen(Filename, "w");

	if (f == NULL)
		return 0;

	int num_writes = 0;
	Node * n = head -> next;	
	while (n != NULL)
	{
		if (fprintf(f, "%ld\n", n -> value) < 0)
			num_writes++;
		n = n -> next;
	}

	fclose(f);
	
	return num_writes;
}

/*
 * Generates the k sequence used for shell sort
 * Inputs:
 * 	1. A pointer to the size of the k sequence (its value doesn't matter)
 * 	2. The number of elements to be sorted
 *
 * Outputs:
 * 	A pointer to an array holding the k sequence
 */
int * Gen_K_Seq(int * arr_Size, long Size)
{
	//find the largest k needed for the k sequence as well as the number of elements to be stored in the array
	int last_k = 1;
	int n = 0;
	int k_Size = 1;
	while(last_k*3 < Size)
	{
		last_k *= 3;
		n++;
		k_Size += n + 1;
	}

	int * arr = malloc(sizeof(int) * k_Size);

	int k_seq_line_num = 1; //the current line number of the k sequence triangle
	int i; //the current column number of k sequence triangle

	int p; //the exponent of 2 in the k triangle
	int q; //the exponent of 3 in the k triangle
	int j; //keeps track of number of multiplications for finding the exponents of the k triangle

	int ind = -1;
	do
	{
		for (i = 1; i <= k_seq_line_num; i++)
		{
			ind++;
			arr[ind] = 1;
			p = k_seq_line_num - i;
			q = i - 1;

			//multiply arr[ind] by 2^p
			j = 0;
			while (j < p)
			{
				arr[ind] *= 2;
				j++;
			}
			
			//multiply arr[ind] by 3^q
			j = 0;
			while (j < q)
			{
				arr[ind] *= 3;
				j++;
			}
		}
		k_seq_line_num++;
	}while(arr[ind] != last_k);

	(*arr_Size) = k_Size; //allows the size of the array to be known outside of this frame
	return arr; //returns the size of the array
}

Node * Shell_Sort(Node * head)
{
	//find size of list
	int k_Size = 0;
	int * k = Gen_K_Seq(&k_Size, head -> value);
	
	int k_ind; //the index for the current element in the array k
	int i;
	int order;
	
	if (k_Size % 2 == 1)
		order = 1;
	else
		order = 0;
	
	//printf("Size = %ld, Order = %d", head -> value, order);

	Node * new_head = head -> next;
	Node * iter;
	Node * temp;
	List * list;

	printf("Starting sort\n");
	for (k_ind = k_Size - 1; k_ind >= 0; k_ind--)
	{
		list = malloc(sizeof(List)*k[k_ind]);
		//initialize each element of list to NULL
		for(i = 0; i < k[k_ind]; i++)
		{
			list[i].node = NULL;
		}

		iter = new_head;
		i = 0;
		//Insert nodes into sub arrays
		//Nodes are sorted as they are inserted
		while (iter != NULL)
		{
			temp = iter -> next;
			if (order == 1)
				list[i].node = insert_Node_Asc(list[i].node, iter);
			else
				list[i].node = insert_Node_Desc(list[i].node, iter);
			iter = temp;
			i++;
			if (i == k[k_ind])
				i = 0;
		}
		if (order == 1)
			order = 0;
		else
			order = 1;
		//reassemble the k sorted linked list
		new_head = assemble_List(list, k[k_ind]);
		free(list);
	}
		
	free(k);

	head -> next = new_head;

	return head;
}

//Assemble one linked list form a set of linked list arrays
Node * assemble_List(List * list, int Size)
{
	//printf("Assembling List\n");
	//printf("Size: %d\n", Size);
	
	int i = 0;
	Node * head = list[0].node;
	Node * iter = head;

	while(iter != NULL)
	{
		list[i].node = list[i].node -> next;
		if (i < Size - 1)
			iter -> next = list[i + 1].node;
		else if (list[0].node != NULL)
		{
			iter -> next = list[0].node;
		}
		else
			iter -> next = NULL;
		iter = iter -> next;
		i++;
		if (i == Size)
			i = 0;
	}

	return head;
}

//insert a node into a linked list
Node * insert_Node_Asc(Node * head, Node * n)
{
	if (head ==  NULL)
	{
		head = n;
		head -> next = NULL;
		return head;
	}

	Node * prev = NULL;
	Node * curr = head;
	
	while (curr != NULL && curr -> value < n -> value)
	{
		prev = curr;
		curr = curr -> next;
	}

	if (prev != NULL)
	{
		prev -> next = n;
		n -> next = curr;
	}
	else
	{
		n -> next = head;
		head = n;
	}

	return head;
}

Node * insert_Node_Desc(Node * head, Node * n)
{
	if (head ==  NULL)
	{
		head = n;
		head -> next = NULL;
		return head;
	}

	Node * prev = NULL;
	Node * curr = head;
	
	while (curr != NULL && curr -> value > n -> value)
	{
		prev = curr;
		curr = curr -> next;
	}

	if (prev != NULL)
	{
		prev -> next = n;
		n -> next = curr;
	}
	else
	{
		n -> next = head;
		head = n;
	}

	return head;
}

//Destroy the linked list
void Destroy_List(Node * head)
{
	Node * t = NULL;
	while(head != NULL)
	{
		t = head -> next;
		free(head);
		head = t;
	}
}

/*int Print_Seq(char * Filename, long Size)
{
	int k_Size;
	int * k = Gen_K_Seq(&k_Size, Size);
	
	FILE * f = fopen(Filename, "w");

	if (f == NULL)
		return 0;
	fprintf(f, "%d\n", k_Size);

	int i;
	for (i = 0; i < k_Size; i++)
	{
		fprintf(f, "%d\n", k[i]);
	}

	fclose(f);

	free(k);

	return k_Size;
}*/
