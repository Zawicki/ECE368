#include <stdio.h>
#include <stdlib.h>

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

	char * mode = argv[1];
	char * in_file = argv[2];
	//char * seq_file = argv[3];
	char * out_file = argv[4];

	int Size = 0;	
	long * arr;
	
	arr = Load_File(in_file, &Size); //Load the fille and store the contents in arr

	double N_Comp = 0;
	double N_Move = 0;

	if (*mode == 'i')
		Shell_Insertion_Sort(arr, Size, &N_Comp, &N_Move);
	else if (*mode == 's')
		Shell_Selection_Sort(arr, Size, &N_Comp, &N_Move);
	else
		printf("\nInvalid argument for sort type");
	
	Save_File(out_file, arr, Size);
	free(arr);

	printf("Number of comparisons: %le\n", N_Comp);
	printf("Number of moves: %le\n", N_Move);
	printf("I/O Time: %le\n", (double)0);
	printf("Sorting Time: %le\n", (double)0);

	return EXIT_SUCCESS;
}
