#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long * Load_File(char * Filename, int * Size);
int Save_File(char * Filename, long * Array, int Size);
void Shell_Insertion_Sort(long * Array, int Size, double * N_Comp, double * N_Move);
void Shell_Selection_Sort(long * Array, int Size, double * N_Comp, double * N_Move);
int Print_Seq(char * Filename, int Size);
int * Gen_K_Seq(int * arr_Size, int Size); //Generates the k sequence

int main (int argc, char ** argv)
{
	if (argc != 5)
	{
		printf("\nInvalid number of arguments");
		return EXIT_FAILURE;
	}

	char * mode = argv[1];
	char * in_file = argv[2];
	char * seq_file = argv[3];
	char * out_file = argv[4];

	int Size = 0;	
	long * arr;


	double N_Comp = 0;
	double N_Move = 0;

	clock_t sort_t = 0;
	clock_t io_sum = 0; //keeps track of total I/O time
	
	clock_t io = clock();
	arr = Load_File(in_file, &Size); //Load the fille and store the contents in arr
	io_sum = clock() - io;

	if (*mode == 'i')
	{	
		sort_t = clock();
		Shell_Insertion_Sort(arr, Size, &N_Comp, &N_Move);
		sort_t = clock() - sort_t;
	}
	else if (*mode == 's')
	{
		sort_t = clock();
		Shell_Selection_Sort(arr, Size, &N_Comp, &N_Move);
		sort_t = clock() - sort_t;
	}
	else
		printf("\nInvalid argument for sort type");

	io = clock();
	Print_Seq(seq_file, Size);	
	Save_File(out_file, arr, Size);
	io_sum += clock() - io;
	
	free(arr);

	printf("Number of comparisons: %le\n", N_Comp);
	printf("Number of moves: %le\n", N_Move);
	printf("I/O Time: %le\n", ((double)io_sum) / CLOCKS_PER_SEC);
	printf("Sorting Time: %le\n", ((double)sort_t) / CLOCKS_PER_SEC);

	return EXIT_SUCCESS;
}
