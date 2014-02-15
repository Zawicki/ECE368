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
		//printf("\n%ld", Array[i]);
		if (fprintf(f, "%ld\n", Array[i]) > 0)
			num_writes++;
		i++;
	}

	fclose(f);
	
	return num_writes;
}

void Shell_Insertion_Sort(long * Array, int Size, double * N_Comp, double * N_Move)
{
	int * k;
	int k_size;
	k_Size = Gen_K_Seq(k, Size);
}

int Gen_K_Seq(int * arr, int Size)
{
	//find the largest k needed for the k sequence
	int last_k = 1;
	while(last_k*3 < size)
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
			arr = malloc(sizeof(int));
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
		k_seq_line_number++;
	}while(arr[ind] != last_k);

	return ind + 1; //returns the size of the array
}

int Print_Seq(char * Filename, int Size)
{
	int * k;
	int k_size;
	k_Size = Gen_K_Seq(k, Size);

	FILE * f = fopen(Filename, "w");

	if (f == NULL)
		return 0;

	fprintf(f, "%d\n", k_size);

	int i;
	for (i = 0; i < k_Size; i++)
	{
		fprintf(f, "%d\n", arr[i]);
	}

	return k_Size
}
