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

