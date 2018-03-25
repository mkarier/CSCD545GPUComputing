#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define R 4
#define C 40 

/*
 * It returns the length of a string pointed by pointer s,
 * It acts like the cpu strlen() function
 */
__device__ int gpu_strlen(char * s)
{
	int size = 0;
	while(s[size] != '\n' && s[size] != '\0')
	{
		size++;
	}//end of while loop
	return size;
}//end of gpu_strlen

/*
 * It returns 0 if input character ch is NOT an alphabetical letter
 * Otherwise, it returns one.
 */
__device__ int gpu_isAlpha(char ch)
{
	char lowerletter = 'a', upperletter = 'A';
	int i = 0;
	for(i = 0; i < 26; i++, lowerletter++, upperletter++)
	{
		if(lowerletter == ch || upperletter == ch)
			return 1;
		if(ch == ' ' || ch == '\0')
			return 0;
	}
	return 0;
}

/* Cuda kernel to count number of words in each line of text pointed by a.
 * The output is stored back in 'out' array.
 * numLine specifies the num of lines in a, maxLineLen specifies the maximal
 * num of characters in one line of text.
 */
__global__ void wordCount( char **a, int **out, int numLine, int maxLineLen )
{
	int col = blockDim.x * blockIdx.x + threadIdx.x;
	int row = blockDim.y * blockIdx.y + threadIdx.y;
	if(col < maxLineLen && row < numLine)
	{
		out[row][col] = 0;
		if(col < gpu_strlen(a[row]))
		{
			if(gpu_isAlpha(a[row][col]))
				out[row][col] = 0;
			else
				out[row][col] = 1;
		}//end of inner if
	}//end of if statement to check the wordCount

}//end of wordCount

/* Print out the all lines of text in a on stdout
 */ 
void printArr( char **a, int lines )
{
    int i;
    for(i=0; i<lines; i++)
    {
        printf("%s\n", a[i]);
    }
}


int main()
{
    int i; 
    char **d_in, **h_in, **h_out;
    int h_count_in[R][C], **h_count_out, **d_count_in;

    //allocate
    h_in = (char **)malloc(R * sizeof(char *));
    h_out = (char **)malloc(R * sizeof(char *));
    h_count_out = (int **)malloc(R * sizeof(int *));

    cudaMalloc((void ***)&d_in, sizeof(char *) * R);
    cudaMalloc((void ***)&d_count_in, sizeof(int *) * R);

    //alocate for string data
    for(i = 0; i < R; ++i) 
    {
        cudaMalloc((void **) &h_out[i],C * sizeof(char));
        h_in[i]=(char *)calloc(C, sizeof(char));//allocate or connect the input data to it
        strcpy(h_in[i], "good morning and I'm a good student!");
        cudaMemcpy(h_out[i], h_in[i], strlen(h_in[i]) + 1, cudaMemcpyHostToDevice);
    }
    cudaMemcpy(d_in, h_out, sizeof(char *) * R,cudaMemcpyHostToDevice);

    //alocate for output occurrence
    for(i = 0; i < R; ++i) 
    {
        cudaMalloc((void **) &h_count_out[i], C * sizeof(int));
        cudaMemset(h_count_out[i], 0, C * sizeof(int));
    }
    cudaMemcpy(d_count_in, h_count_out, sizeof(int *) * R,cudaMemcpyHostToDevice);

    printArr(h_in, R);
    printf("\n\n");
     
    //set up kernel configuartion variables
    dim3 grid, block;
    block.x = 2;
    block.y = 2;
    grid.x  = ceil((float)C / block.x);
    grid.y  = ceil((float)R / block.y); //careful must be type cast into float, otherwise, integer division used
    printf("grid.x = %d, grid.y=%d\n", grid.x, grid.y );

    //launch kernel
    wordCount<<<grid, block>>>( d_in, d_count_in, R, C);

    //copy data back from device to host
    for(i = 0; i < R; ++i) {
        cudaMemcpy(h_count_in[i], h_count_out[i], sizeof(int) * C,cudaMemcpyDeviceToHost);
    }
    printf("Occurrence array obtained from device:\n");

    for(i = 0; i < R; i ++) {
        for(int j = 0; j < C; j ++)
            printf("%4d", h_count_in[i][j]);
        printf("\n");
    }
 
    return 0;
}

