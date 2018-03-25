
#include "Shared.h"
#include "GPU_PgmUtility.h"

// TODO:Implement or define each function prototypes listed in pgmUtility.h file.
// NOTE: You can NOT change the input, output, and argument type of the functions in pgmUtility.h
// NOTE: You can NOT change the prototype of any functions listed in pgmUtility.h
__device__ float distance( int p1[], int p2[] )
{
	return sqrtf(powf((p1[0] - p1[1]),2) + powf((p2[0] - p2[1]), 2));
}

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
__host__ int* pgmRead( char **header, int *numRows, int *numCols, FILE *in  )
{
	//TODO:
	char buffer[maxSizeHeadRow];
	int i = 0, j = 0;
	for( ; i < rowsInHeader; i++)
	{
		fgets(buffer, maxSizeHeadRow, in);
		header[i] =(char *) calloc((strlen(buffer)+1), sizeof(char));
		memcpy(header[i], buffer, strlen(buffer));
	}//end of for loop
	sscanf(header[2], "%d %d", numCols, numRows);
	int * array = (int *)malloc((*numRows) * (*numCols) * sizeof(int));

	for(i = 0; i < *numRows; i++)
	{
		for(j = 0; j < *numCols; j++)
		{
			fscanf(in, "%d", &array[i * *numCols + j]);
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
__global__ void pgmDrawCircle( int * pixels, int numRows, int numCols, int centerRow, int centerCol, int radius, char **header )
{
	//TODO:
	int id = (blockDim.x *blockIdx.x) + threadIdx.x;
	int p1[2];
	int p2[2];
	int y =  id % numCols;
	int x = id / numCols;
	p1[0] = y;
	p2[0] = x;
	p1[1] = centerRow;
	p2[1] = centerCol;
	if(id < (numRows * numCols))
	{
		float d = distance(p1, p2);//sqrtf(powf((p1[0] - p1[1]),2) + powf((p2[0] - p2[1]), 2));
		if(d < radius)
		{
			pixels[id] = 0;
		}
	}//end of if statement to check that id is in a grid
}//end of pgmDrawCircle.


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
__global__ void pgmDrawEdge( int * pixels, int numRows, int numCols, int edgeWidth, char **header )
{
	int id = (blockDim.x * blockIdx.x) + threadIdx.x;
	int y =  id % numCols;
	int x = id / numCols;
	if(id < (numRows* numCols))
	{
		if(x < edgeWidth || x > (numRows - edgeWidth -1))
		{
			pixels[id] = 0;
		}//end of if satement to check the top and bottom of the picture.
		if(y < edgeWidth || y > (numCols -edgeWidth - 1))
		{
			pixels[id] = 0;
		}
	}//end of if statment to make sure that it is in thread is in the gird
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
__global__ void pgmDrawLine( int *pixels, int numRows, int numCols, char **header, int p1row, int p1col, int p2row, int p2col )
{
	double slope = (p2row - p1row)/(p2col - p1col);
	double b = p2row - (p2col * slope);
	int id = (blockDim.x * blockIdx.x) + threadIdx.x;
	int y =  id / numCols;
	int x = id % numCols;
	if(id < (numRows * numCols))
	{
		if((x >= p1col && x <= p2col) && (y >= p1row && y <= p2row))
		{
			if(y == ((slope * x) + b))
				pixels[id] = 0;
		}//end of if statement
	}//end of outer if statement
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
__host__ int pgmWrite( const char **header, const int *pixels, int numRows, int numCols, FILE *out )
{
	//printf("It is in the pgmWrite method\n");
	int i, j;
	//printf("numRows, numCols, %d, %d\n", numRows, numCols);
	for(i = 0; i < rowsInHeader; i++)
	{
	  //printf("%s", header[i]);
	  fprintf(out, "%s", header[i]);
	}
	printf("finished printing the header\n");
	for(i = 0; i < numRows; i++)
	{
	  for(j = 0; j < numCols; j++)
	  {
		 //printf("%5d", pixels[i][j]);
		 fprintf(out, "%d ", pixels[i * numCols + j]);
	  }//end of loop for numCols
	  //printf("\n");
	  fprintf(out,"\n");
	}//end of for loop for numRows
	return 0;
}//end of pgmWrite

