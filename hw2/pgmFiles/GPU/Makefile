GPU: Main.o Utility.o Methods.o
	nvcc -arch=sm_30 -o gpu Main.o Utility.o Methods.o
	
Main.o:
	g++ -x c++ -o Main.o -c MyPaint.c

Utility.o:
	nvcc -arch=sm_30 -c -o Utility.o pgmUtility.cu

Methods.o:
	nvcc -arch=sm_30 -c -o Methods.o GPU_methods.cu


clean:
	rm Main.o;
	rm Utility.o;
	rm Methods.o
	rm gpu;



