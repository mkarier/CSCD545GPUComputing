
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "CPU_PgmUtility.h"

// TODO:Implement or define each function prototypes listed in pgmUtility.h file.
// NOTE: You can NOT change the input, output, and argument type of the functions in pgmUtility.h
// NOTE: You can NOT change the prototype of any functions listed in pgmUtility.h

/**
 *  Function Name:
 *      pgmRead()
 *      pgmRead() reads in a pgm image using file I/O, you have to follow the file format. All code in this function are exectured on CPU.
 *
 *  @param[in,out]  header  holds the header of the pgm file in a 2D character array
 *                          After we process the pixels in the input image, we write the origianl
 *                          header (or potentially modified) back to a new image file.
 *  @param[in,out]  numRows describes how many rows of pixels in the image.
 *  @param[in,out]  numCols describe how many pixels in one row in the image.
 *  @param[in]      in      FILE pointer, points to an opened image file that we like to read in.
 *  @return         If successful, return all pixels in the pgm image, which is an int **, equivalent to
 *                  a 2D array. Otherwise null.
 *
 */
int ** pgmRead( char **header, int *numRows, int *numCols, FILE *in  )
{
	//TODO:
	char buffer[maxSizeHeadRow];

	int i = 0, j;
	for( ; i < rowsInHeader; i++)
	{
		fgets(buffer, maxSizeHeadRow, in);
		/*while(buffer[0] == '\n')
		{
			fgets(buffer, maxSizeHeadRow, in);
		}*/
		header[i] = (char *)calloc(strlen(buffer) + 1, sizeof(char));
		memcpy(header[i], buffer, strlen(buffer));
		//printf("header[%d] = %s\n", i, header[i]);
	}//end of for loop
	sscanf(header[2], "%d %d", numCols, numRows);
	int ** array = (int **)calloc(*numRows, sizeof(int *));

	for(i = 0; i < *numRows; i++)
	{
		array[i] = (int *)calloc(*numCols, sizeof(int));
		for(j = 0; j < *numCols; j++)
		{
			fscanf(in, "%d", &array[i][j]);
		}//end of inner for loop
	}//end of outer for loop

	return array;
}//end of pgmRead()


/**
 *  Function Name:
 *      pgmDrawCircle()
 *      pgmDrawCircle() draw a circle on the image by setting relavant pixels to Zero.
 *                      In this function, you have to invoke a CUDA kernel to perform all image processing on GPU.
 *
 *  @param[in,out]  pixels  holds all pixels in the pgm image, which a 2D integer array. The array
 *                          are modified after the drawing.
 *  @param[in]      numRows describes how many rows of pixels in the image.
 *  @param[in]      numCols describes how many columns of pixels in one row in the image.
 *  @param[in]      centerCol specifies at which column you like to center your circle.
 *  @param[in]      centerRow specifies at which row you like to center your circle.
 *                        centerCol and centerRow defines the center of the circle.
 *  @param[in]      radius    specifies what the radius of the circle would be, in number of pixels.
 *  @param[in,out]  header returns the new header after draw.
 *                  the circle draw might change the maximum intensity value in the image, so we
 *                  have to change maximum intensity value in the header accordingly.
 *  @return         return 1 if max intensity is changed, otherwise return 0;
 */
int pgmDrawCircle( int **pixels, int numRows, int numCols, int centerRow, int centerCol, int radius, char **header )
{
	//TODO:
	int i, j;
	double p1[2];
	double p2[2];
	p1[1] = centerRow;
	p2[1] = centerCol;
	for(i = 0; i < numRows; i++)
	{
		p1[0] = i;
		for(j = 0; j < numCols; j++)
		{
			p2[0] = j;
			double d = distance(p1, p2);
			if(d < radius)
				pixels[i][j] = 0;
		}//end of inner for loop
	}//end of outer for loop
	return 0;
}//end of pgmDrawCircle.

double distance(double p1[], double p2[])
{
	return sqrt(pow((p1[0] - p1[1]),2) + pow((p2[0] - p2[1]), 2));
}//end of distance

/**
 *  Function Name:
 *      pgmDrawEdge()
 *      pgmDrawEdge() draws a black edge frame around the image by setting relavant pixels to Zero.
 *                    In this function, you have to invoke a CUDA kernel to perform all image processing on GPU.
 *
 *  @param[in,out]  pixels  holds all pixels in the pgm image, which a 2D integer array. The array
 *                          are modified after the drawing.
 *  @param[in]      numRows describes how many rows of pixels in the image.
 *  @param[in]      numCols describes how many columns of pixels in one row in the image.
 *  @param[in]      edgeWidth specifies how wide the edge frame would be, in number of pixels.
 *  @param[in,out]  header returns the new header after draw.
 *                  the function might change the maximum intensity value in the image, so we
 *                  have to change the maximum intensity value in the header accordingly.
 *
 *  @return         return 1 if max intensity is changed by the drawing, otherwise return 0;
 */
int pgmDrawEdge( int **pixels, int numRows, int numCols, int edgeWidth, char **header )
{
	//TODO:
	int i, j;
	for(i = 0; i < numRows; i++)
	{
		for(j = 0; j < numCols; j++)
		{
			if(i < edgeWidth || i > (numRows - edgeWidth -1))
			{
				pixels[i][j] = 0;
			}//end of if statement
			if(j < edgeWidth || j > (numCols - edgeWidth - 1))
			{
				pixels[i][j] = 0;
			}
		}//end of inner for loop
	}//end of outer loop
	return 0;
}//end of pgmDrawEdge


/**
 *  Function Name:
 *      pgmDrawLine()
 *      pgmDrawLine() draws a straight line in the image by setting relavant pixels to Zero.
 *                      In this function, you have to invoke a CUDA kernel to perform all image processing on GPU.
 *
 *  @param[in,out]  pixels  holds all pixels in the pgm image, which a 2D integer array. The array
 *                          are modified after the drawing.
 *  @param[in]      numRows describes how many rows of pixels in the image.
 *  @param[in]      numCols describes how many columns of pixels in one row in the image.
 *  @param[in]      p1row specifies the row number of the start point of the line segment.
 *  @param[in]      p1col specifies the column number of the start point of the line segment.
 *  @param[in]      p2row specifies the row number of the end point of the line segment.
 *  @param[in]      p2col specifies the column number of the end point of the line segment.
 *  @param[in,out]  header returns the new header after draw.
 *                  the function might change the maximum intensity value in the image, so we
 *                  have to change the maximum intensity value in the header accordingly.
 *
 *  @return         return 1 if max intensity is changed by the drawing, otherwise return 0;
 */
int pgmDrawLine( int **pixels, int numRows, int numCols, char **header, int p1row, int p1col, int p2row, int p2col )
{
	//TODO:figure out y=mx+b
	double slope = (p2col-p1col)/(p2row - p1row);
	int b = p2row - (p2col * slope);
	int y, x;
	for(y = 0; y < numRows; y++)
	{
		for(x = 0; x < numCols; x++)
		{
			if(y == ((slope * x) + b))
				pixels[x][y] = 0;
		}//end of for loop
	}//end of outer for loop
	return 0;
}//end of pgmDrawLine



/**
 *  Function Name:
 *      pgmWrite()
 *      pgmWrite() writes headers and pixels into a pgm image using file I/O.
 *                 writing back image has to strictly follow the image format. All code in this function are exectured on CPU.
 *
 *  @param[in]  header  holds the header of the pgm file in a 2D character array
 *                          we write the header back to a new image file on disk.
 *  @param[in]  pixels  holds all pixels in the pgm image, which a 2D integer array.
 *  @param[in]  numRows describes how many rows of pixels in the image.
 *  @param[in]  numCols describe how many columns of pixels in one row in the image.
 *  @param[in]  out     FILE pointer, points to an opened text file that we like to write into.
 *  @return     return 0 if the function successfully writes the header and pixels into file.
 *                          else return -1;
 */
int pgmWrite( const char **header, const int **pixels, int numRows, int numCols, FILE *out )
{
	//printf("It is in the pgmWrite method\n");
   int i, j;
   //printf("numRows, numCols, %d, %d\n", numRows, numCols);
   for(i = 0; i < rowsInHeader; i++)
   {
	  //printf("%s", header[i]);
	  fprintf(out, "%s", header[i]);
   }
   printf("finished printing the header");
   for(i = 0; i < numRows; i++)
   {
	  for(j = 0; j < numCols; j++)
	  {
		 //printf("%5d", pixels[i][j]);
		 fprintf(out, "%d ", pixels[i][j]);
	  }//end of loop for numCols
	  //printf("\n");
	  fprintf(out,"\n");
   }//end of for loop for numRows
   return 0;
}

