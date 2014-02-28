#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "sorting.h"

int main (int argc, char * * argv)
{
	if (argc != 3)
	{
		printf("\nInvalid number of arguments");
		return EXIT_FAILURE;
	}

	//Assign inputs to variables
	char * in_file = argv[1];
	char * out_file = argv[2];

	clock_t sort_t = 0; //keeps track of sort time
	clock_t io_sum = 0; //keeps track of total I/O time
		
	clock_t io = clock();
	Node * head = Load_File(in_file); //Load the fille and store the contents in arr
	io_sum = clock() - io;

	sort_t = clock();
	head = Shell_Sort(head);
	sort_t = clock() - sort_t;
	
	io = clock();
	Save_File(out_file, head);
	io_sum += clock() - io;

	Destroy_List(head);
	printf("I/O Time: %le\n", ((double)io_sum) / CLOCKS_PER_SEC);
	printf("Sorting Time: %le\n", ((double)sort_t) / CLOCKS_PER_SEC);

	return EXIT_SUCCESS;
}
