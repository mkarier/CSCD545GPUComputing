#include "wordCount.h"


/*
This method is to read in a file. 
TODO: make it parse the line and create an array of words to be sent to a different method.
*/
Word * ReadInFile(char * filename, int * size)
{
	FILE * fp = fopen(filename, "r");
	if(fp == NULL)
	{
		perror("file not found\n");
		exit(1);
	}
	pthread_t threads[NUMBER_OF_THREADS];
	char buffer[BUF_SIZE];
	//printf("making list pointer\n");
	LinkedList * master = llconstruct(); // =(Word *)malloc(sizeof(Word *));
	LinkedList * tempList;
	void * temp;
	int count = 0, threadsindex = 0, i, firstTimeThrough = 0;
	//printf("begin reading\n");
	while(fgets(buffer, BUF_SIZE, fp) != NULL)
	{
		strip(buffer);
		if(buffer[0] == '\0' || buffer[0] == '\r' || buffer[0] == '\n' || strlen(buffer) <=1)
			continue;
		else
		{
			
			char * line = (char *)calloc(strlen(buffer)+1, sizeof(char));
			memcpy(line, buffer, strlen(buffer));
			
			if(firstTimeThrough++ > NUMBER_OF_THREADS -1)
			{
				LinkedList * list;
				void * temp;
				firstTimeThrough = NUMBER_OF_THREADS;
				pthread_join(threads[(count)], &temp);
				tempList = (LinkedList *)temp;
				mergeList(&master, &tempList);
			}

			pthread_create(&threads[count], 0, (void *)searchTokenList, line);
			//printf("started %p thread\n", threads[count]);
			//if(&threads[(count +1) % NUMBER_OF_THREADS] != NULL)
			//{
				//pthread_join(threads[(count)], NULL);
			//}
			
			count = (count +1) % NUMBER_OF_THREADS;

			//printf("searching for: %s\n", toFind);
			//findWord(toFind, list);//*/
		}//end of else
		buffer[0] = '\0';
	}//end of while loop
	for(i = 0; i < NUMBER_OF_THREADS; i ++)
	{
		pthread_join(threads[i], &temp);//
		tempList = (LinkedList *)temp;
		mergeList(&master, &tempList);
	}//*/
	
	fclose(fp);
	Word * head = master->head;
	*size = master->size;
	free(master);
	return head;
}//end of ReadInFile


LinkedList * searchTokenList(char * args)
{
	if(args == NULL || strlen(args) <= 3)
		return NULL;
	int i, count;
	char ** array = tokenize(args, &count);
	if(array == NULL)
	{
		free(args);
		return NULL;
	}
	LinkedList * list = llconstruct();
	if(count == 0 && *array != NULL)
	{
		printf("count is zero so increasing by one.\n");
		count++;
	}
	for(i = 0; i < count; i++)
	{
		//printf("search for: %s", array[i]);
		findWord(array[i], list);
	}
	clearTokenList(array, count);
	free(array);
	free(args);
	return list;

}//end of searchTokenList

/*
This method searches for the word in the link list and updates the count if it finds it. 
TODO; make it compatiable with threading
*/
void findWord(char * toFind, LinkedList * list)
{
	if(toFind == NULL)
		return;
	if(list->size == 0)
	{
		//printf("\nBuilding list\n");
		if(want_locks)
			pthread_mutex_lock(&lock);
		
		list->head = construct(toFind);
		list->size += 1;
		
		if(want_locks)
			pthread_mutex_unlock(&lock);
		//printWord(list->head);
	}//end of if
	else
	{
		Word * current = list->head;
		while(current->next != NULL)
		{
			if(strcmp(toFind, current->input) == 0)
			{
				if(want_locks)
					pthread_mutex_lock(&lock);
				current->count += 1;
				if(want_locks)
					pthread_mutex_unlock(&lock);
				//free(toFind);
				return;
			}//end of if
			current = current->next;
		}//end of if
		
		//printf("past while loop\n");
		if(strcmp(toFind, current->input) == 0)
		{
			if(want_locks)
				pthread_mutex_lock(&lock);
			current->count += 1;
			if(want_locks)
				pthread_mutex_unlock(&lock);
			//free(toFind);
			return;
		}//end of inner if
		else
		{
			if(want_locks)
				pthread_mutex_lock(&lock);
			//printf("added ot the list\n");
			current->next = construct(toFind);
			//printWord(current->next);
			list->size += 1;
			if(want_locks)
				pthread_mutex_unlock(&lock);
		}//end of inner else
	}//end of else
		
}//end of findWord
