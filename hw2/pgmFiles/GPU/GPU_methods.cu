/*
 * Author; Marco Karier
 *
 * This is where the main method for the cuda
 */

#include "Shared.h"
#include "GPU_PgmUtility.h"
#define BLOCKSIZE 16

void callCircle(int centerRow, int centerColumn, int radius, FILE * in, FILE * out)
{
	char ** header = (char **)calloc(rowsInHeader, sizeof(char *));
	int numRows= 0, numCols = 0;
	printf("Reading in file for single array\n");
	int * h_pixels = pgmRead(header, &numRows, &numCols, in);
	int size = numRows * numCols *sizeof(int);
	printf("read in file\n");
	fclose(in);

	int * d_pixels;
	cudaMalloc(&d_pixels, size);
	cudaMemset(d_pixels, 0, size);
	cudaMemcpy(d_pixels, h_pixels, size, cudaMemcpyHostToDevice);
	int gridSize =(int)ceil((double)size/ BLOCKSIZE);// (int)ceil((float)n/BLOCKSIZE);
	pgmDrawCircle<<<gridSize, BLOCKSIZE>>>(d_pixels, numRows, numCols, centerRow, centerColumn, radius, header);
	cudaMemcpy(h_pixels, d_pixels, size, cudaMemcpyDeviceToHost);

	pgmWrite((const char **)header, (const int *)h_pixels, numRows, numCols, out);
	int i;
	for(i = 0; i < rowsInHeader; i++)
	{
		free(header[i]);
	}//end of for loop to clear header
	free(header);
	free(h_pixels);
	cudaFree(d_pixels);
	fclose(out);
}//end of callCircle

void callEdge(int edgeWidth, FILE * in, FILE * out)
{
	char ** header = (char **)calloc(rowsInHeader, sizeof(char *));
	int numRows= 0, numCols = 0;
	printf("Reading in file for single array\n");
	int * h_pixels = pgmRead(header, &numRows, &numCols, in);
	int size = numRows * numCols *sizeof(int);
	printf("read in file\n");
	fclose(in);

	int * d_pixels;
	cudaMalloc(&d_pixels, size);
	cudaMemset(d_pixels, 0, size);
	cudaMemcpy(d_pixels, h_pixels, size, cudaMemcpyHostToDevice);
	int gridSize =(int)ceil((double)size/ BLOCKSIZE);// (int)ceil((float)n/BLOCKSIZE);
	pgmDrawEdge<<<gridSize, BLOCKSIZE>>>(d_pixels, numRows, numCols, edgeWidth, header);
	cudaMemcpy(h_pixels, d_pixels, size, cudaMemcpyDeviceToHost);

	pgmWrite((const char **)header, (const int *)h_pixels, numRows, numCols, out);
	int i;
	for(i = 0; i < rowsInHeader; i++)
	{
		free(header[i]);
	}//end of for loop to clear header
	free(header);
	free(h_pixels);
	cudaFree(d_pixels);
	fclose(out);
}//end of callEdge

void callLine(int p1row, int p1col, int p2row, int p2col, FILE * in,  FILE * out)
{
	char ** header = (char **)calloc(rowsInHeader, sizeof(char *));
	int numRows= 0, numCols = 0;
	printf("Reading in file for single array\n");
	int * h_pixels = pgmRead(header, &numRows, &numCols, in);
	int size = numRows * numCols *sizeof(int);
	printf("read in file\n");
	fclose(in);

	int * d_pixels;
	cudaMalloc(&d_pixels, size);
	cudaMemset(d_pixels, 0, size);
	cudaMemcpy(d_pixels, h_pixels, size, cudaMemcpyHostToDevice);
	int gridSize =(int)ceil((double)size/ BLOCKSIZE);// (int)ceil((float)n/BLOCKSIZE);
	pgmDrawLine<<<gridSize, BLOCKSIZE>>>(d_pixels, numRows, numCols, header, p1row, p1col, p2row, p2col);
	cudaMemcpy(h_pixels, d_pixels, size, cudaMemcpyDeviceToHost);

	pgmWrite((const char **)header, (const int *)h_pixels, numRows, numCols, out);
	int i;
	for(i = 0; i < rowsInHeader; i++)
	{
		free(header[i]);
	}//end of for loop to clear header
	free(header);
	free(h_pixels);
	cudaFree(d_pixels);
	fclose(out);
}//end of calline

