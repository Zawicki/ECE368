#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long * Load_File(char * Filename, int * Size);
int Save_File(char * Filename, long * Array, int Size);
void Shell_Insertion_Sort(long * Array, int Size, double * N_Comp, double * N_Move);
void Shell_Selection_Sort(long * Array, int Size, double * N_Comp, double * N_Move);
int Print_Seq(char * Filename, int Size);
int Gen_K_Seq(int * arr, int Size);

int main (int argc, char ** argv)
{
	if (argc != 5)
	{
		printf("\nInvalid number of arguments");
		return EXIT_FAILURE;
	}

	char * in_file = argv[2];
	char * seq_file = argv[3];
	char * out_file = argv[4];
	int Size = 0;	
	long * arr;
	arr = Load_File(in_file, &Size); //Load the fille and store the contents in arr

	double * N_Comp;
	double * N_Move;

	if (strcmp(argv[1], "i") == 0)
		Shell_Insertion_Sort(arr, Size, N_Comp, N_Move);
	else if (strcmp(argv[1], "i") == 0)
		Shell_Selection_Sort(arr, Size, N_Comp, N_Move);
	else
		printf("\nInvalid argument for sort type");
	
	int num_saved;
	num_saved = Save_File(out_file, arr, Size);
	
	free(arr);

	return EXIT_SUCCESS;
}
