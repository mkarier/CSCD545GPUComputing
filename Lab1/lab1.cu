#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<sys/time.h>

typedef unsigned long long bignum;

__host__ __device__ int isPrime(bignum x)
{

   bignum i;
   bignum lim = (bignum) sqrt((float)x) + 1.0;
      
   for(i=2; i<lim; i++){
      if ( x % i == 0)
         return 0;
   }//end of for loop

   return 1;
}//end of isPrime

__global__ void findPrime(int * arr, bignum n)
{
	bignum id = blockIdx.x * blockDim.x + threadIdx.x;
	bignum num = (2*(id + 1) -1);
	if(num < n)
	{
		arr[num] = isPrime(num);
		//arr[num] = 10;
	}//end of if	
}//end of kernal



int main(int argc, char ** argv)
{
	clock_t start = clock();
	if(argc < 2)
	{
		perror("Not Enough Arguments");
		exit(-1);
	}//end of if
	bignum N = atoi(argv[1]);
	int blockSize = atoi(argv[2]);
	bignum gridsize = (bignum)ceil((N+1)/2.0/blockSize);

	if(N <= 0)
	{
		printf("N isn't a valid number");
		exit(-99);
	}//end of if statment
	int * d_array;
	
	cudaMalloc(&d_array, sizeof(int)*(N+1));
	cudaMemset(d_array, 0, sizeof(int)*(N+1));
	
	findPrime<<<gridsize, blockSize>>>(d_array, N+1);
	int * h_array = (int *)calloc(N+1, sizeof(int));
	cudaMemcpy(h_array, d_array, (N+1)*sizeof(int), cudaMemcpyDeviceToHost);
	int i;
	int prime =0;
	for(i = 0; i <= N; i++)
	{
		printf("%d is %d\n", i, h_array[i]);
		if(h_array[i] == 1)
			prime++;
	}//end for loop
	free(h_array);
	cudaFree(d_array);
	
	
	clock_t end = clock();
	printf("primes = %d, time = %f\n", prime,(float) (end-start)/ CLOCKS_PER_SEC);
	
}//end of main
