#include<stdio.h>
#include<stdlib.h>
#include"CPU_PgmUtility.h"


void clearArray(void ** array, int row)
{
	int i = 0;
	for( ; i < row; i++)
	{
		free(array[i]);
	}//end of for loop
	free(array);
}//end of clearArray

void callCircle(int centerRow, int centerColumn, int radius, FILE * in, FILE * out)
{
	char ** header = (char **)calloc(rowsInHeader, sizeof(char *));
	int numRows= 0, numCols = 0;
	printf("starting to read in file\n");
	int ** pixels = pgmRead(header, &numRows, &numCols, in);
	printf("header[0] = %s\n", header[0]);
	fclose(in);

	pgmDrawCircle(pixels, numRows, numCols, centerRow,centerColumn, radius, header);
	pgmWrite((const char **)header, (const int **)pixels, numRows, numCols, out);
	fclose(out);
	printf("Wrote out the file\n");

	clearArray((void **)header, rowsInHeader);
	clearArray((void **)pixels, numRows);
}//end of call circle

void callEdge(int edgeWidth, FILE * in, FILE * out)
{
	char ** header = (char **)calloc(rowsInHeader, sizeof(char *));
	int numRows= 0, numCols = 0;
	printf("starting to read in file\n");
	int ** pixels = pgmRead(header, &numRows, &numCols, in);
	printf("header[0] = %s\n", header[0]);
	fclose(in);

	pgmDrawEdge( pixels, numRows, numCols, edgeWidth, header);
	pgmWrite((const char **)header, (const int **)pixels, numRows, numCols, out);
	fclose(out);
	printf("Wrote out the file\n");

	clearArray((void **)header, rowsInHeader);
	clearArray((void **)pixels, numRows);
}//end of callEdge

void callLine(int p1row, int p1col, int p2row, int p2col, FILE * in,  FILE * out)
{
	char ** header = (char **)calloc(rowsInHeader, sizeof(char *));
	int numRows= 0, numCols = 0;
	printf("starting to read in file\n");
	int ** pixels = pgmRead(header, &numRows, &numCols, in);
	printf("header[0] = %s\n", header[0]);
	fclose(in);

	pgmDrawLine(pixels, numRows, numCols, header, p1row, p1col, p2row, p2col);
	pgmWrite((const char **)header, (const int **)pixels, numRows, numCols, out);
	fclose(out);
	printf("Wrote out the file\n");

	clearArray((void **)header, rowsInHeader);
	clearArray((void **)pixels, numRows);
}

/*int main()
{
	FILE * in = fopen("baboon.ascii.pgm", "r");
	FILE * out = fopen("out.pgm", "w");
	char ** header = calloc(rowsInHeader, sizeof(char *));
	int numRows= 0, numCols = 0;
	printf("starting to read in file\n");
	int ** pixels = pgmRead(header, &numRows, &numCols, in);
	printf("header[0] = %s\n", header[0]);
	fclose(in);
	printf("Read in file \n");
	pgmDrawLine(pixels, numRows, numCols, header, 0, 3, 10, 30);
	printf("Drew a Line\n");
	pgmWrite((const char **)header, (const int **)pixels, numRows, numCols, out);
	fclose(out);
	printf("Wrote out the file\n");

	clearArray((void **)header, rowsInHeader);
	clearArray((void **)pixels, numRows);
	/*int i;
	for(i = 0 ; i < rowsInHeader; i++)
	{
		free(header[i]);
	}//end of for loop to free the strings in the header
	free(header);
	printf("finished clearing header\n");
	int j = 0;
	for(j = 0; j < numRows; j++);
	{
		printf("j = %d\n", j);
		free(pixels[j]);
	}//end of for loop to clear rows;
	//free(pixels);
	printf("finished clearing grid\n");

}//end of main*/
