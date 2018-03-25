#include"wordCount.h"
int main(int argc, char ** argv)
{
	if(argc < 2)
	{
		perror("Not enough arguments");
		exit(-1);
	}
	int howToSort = 0;
	if(strcmp(argv[2], "alpha") == 0)
	{
		howToSort = 1;
	}
	printf("hello \n");
	clock_t begin = clock();
	int size;
	//int (*compar)(void *, void *) = *compare;
	Word * array = ReadInFile(argv[1], &size);
	//printf("back in main array size %d\n", size);
	Word * warray[size];
	Word * ptr = array;
	int i = 0;

	for(i = 0; i < size; i++)
	{
		warray[i] = ptr;
		ptr = ptr->next;
	}//end of for loop

	//printf("sorting\n");
	if(howToSort)
		qsort(warray, size, sizeof(Word *), compare);
	else
		qsort(warray, size, sizeof(Word *), compareCount);
	//printf("back from sorting\n");

	array = warray[0];
	ptr = warray[0];
	ptr->next = NULL;
	array = ptr;

	for(i = 1; i < size; i++)
	{
		//printWord(ptr);
		ptr->next = warray[i];
		ptr = ptr->next;
	}//end of for loop

	ptr->next = NULL;//*/
	printList(array);
	clearList(&array);
	clock_t end = clock();
	double time_spent = (double)(end - begin)/ CLOCKS_PER_SEC;
	printf("It took %f seconds\n", time_spent);
	return 0;
}//end of main