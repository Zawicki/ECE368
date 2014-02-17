#include <stdio.h>
#include <stdlib.h>

long * Load_File(char * Filename, int * Size)
{
	FILE * f = fopen(Filename, "r");

	if (f == NULL)
		return NULL;

	int numInts;
	fscanf(f, "%d", &numInts);

	long * arr = malloc(sizeof(long)*numInts);

	int i = 0;
	while (i < numInts)
	{
		fscanf(f, "%ld", &arr[i]);
		i++;
	}
	
	fclose(f);

	*Size = numInts;

	return arr;
}

int Save_File(char * Filename, long * Array, int Size)
{
	FILE * f = fopen(Filename, "w");

	if (f == NULL)
		return 0;

	int num_writes = 0;
	
	if(fprintf(f, "%d\n", Size) > 0)
		num_writes++;

	int i = 0;
	while (i < Size)
	{
		if (fprintf(f, "%ld\n", Array[i]) > 0)
			num_writes++;
		i++;
	}

	fclose(f);
	
	return num_writes;
}

int Gen_K_Seq(int * arr, int Size)
{
	//find the largest k needed for the k sequence
	int last_k = 1;
	while(last_k*3 < Size)
	{
		last_k *= 3;
	}

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
			arr = (int *)realloc(arr, (ind + 1) * sizeof(int));
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

	return ind + 1; //returns the size of the array
}

void Shell_Insertion_Sort(long * Array, int Size, double * N_Comp, double * N_Move)
{
	int * k = malloc(sizeof(int));
	int k_Size;
	k_Size = Gen_K_Seq(k, Size);
	
	int k_ind; //the index of the current for the current element in the array k
	int j;
	int i;
	long temp;

	for (k_ind = k_Size - 1; k_ind >= 0; k_ind--)
	{
		for (j = k[k_ind]; j < Size; j++)
		{
			temp = Array[j];
			(*N_Move)++;
			i = j;
			while((i >= k[k_ind]) && (Array[i - k[k_ind]] > temp))
			{
				(*N_Comp)++;
				Array[i] = Array[i - k[k_ind]];
				(*N_Move)++;
				i = i - k[k_ind];
			}
			(*N_Comp)++;
			Array[i] = temp;
			(*N_Move)++;
		}
	}

	free(k);
}

void Shell_Selection_Sort(long * Array, int Size, double * N_Comp, double * N_Move)
{
	int * k = malloc(sizeof(int));
	int k_Size;
	k_Size = Gen_K_Seq(k, Size);
	
	int k_ind; //the index of the current for the current element in the array k
	int min_ind;
	int j;
	int i;
	long temp;

	for (k_ind = k_Size - 1; k_ind >= 0; k_ind--)
	{
		for (j = 0; j < Size; j++)
		{
			min_ind = j;
			for (i = j + k[k_ind]; i < Size; i++)
			{
				if(Array[i] < Array[min_ind])
					min_ind = i;
				(*N_Comp)++;
			}
			if (min_ind != j)
			{
				temp = Array[j];
				Array[j] = Array[min_ind];
				Array[min_ind] = temp;
				*N_Move += 3;
			}
		}
	}

	free(k);
}
int Print_Seq(char * Filename, int Size)
{
	int * k = malloc(sizeof(int));
	int k_Size;
	k_Size = Gen_K_Seq(k, Size);

	FILE * f = fopen(Filename, "w");

	if (f == NULL)
		return 0;
	fprintf(f, "%d\n", k_Size);

	int i;
	for (i = 0; i < k_Size; i++)
	{
		fprintf(f, "%d\n", k[i]);
	}

	free(k);

	return k_Size;
}
