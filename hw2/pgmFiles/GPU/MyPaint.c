/*
 * MyPaint.c
 *
 *  Created on: Apr 29, 2017
 *      Author: mkarier
 */

#include"Shared.h"
#include<time.h>

void usage()
{
	printf("-e edgeWidth oldImageFile newImageFile\n");
	printf("-c circleCenterRow circleCenterCol radius  oldImageFile  newImageFile\n");
	printf("-l  p1row  p1col  p2row  p2col  oldImageFile  newImageFile\n");
}
int main(int argc, char ** args)
{
	/*
	 * TODO: Create a menu so when it is run with arguments it knows what method is to run
	 * Also make it so It can call different methods
	 */
	clock_t start = clock();
	if(argc < 3)
	{
		printf("Not enough arguments");
		usage();
		exit(-99);
	}
	int wantEdge = 0, wantCircle = 0, wantLine = 0;
	int centerRow, centerCol, radius, p1row, p1col, p2row, p2col, edgeWidth;
	FILE * in, * out;
	if(strcmp("-e", args[1]) == 0)
	{
		//TODO:what to do with the edge draw
		printf("entered -e menu\n");
		if(strcmp("-c", args[1]) == 0)
		{
			wantEdge = 1;
			wantCircle =1;
			centerRow = atoi(args[2]);
			centerCol = atoi(args[3]);
			radius = atoi(args[4]);
			edgeWidth = atoi(args[5]);
			in = fopen(args[6], "r");
			out = fopen(args[7], "w");
			if(in == NULL || out == NULL)
			{
				printf("File was not open\n");
				usage();
				exit(-99);

			}//end of inner if to make sure that the files were ope

		}//end of if -c along -e
		else
		{
			wantEdge = 1;
			edgeWidth = atoi(args[2]);
			in = fopen(args[3], "r");
			out = fopen(args[4], "w");
			if(in == NULL || out == NULL)
			{
				printf("File was not open\n");
				usage();
				exit(-99);

			}//end of inner if to make sure that the files were open
		}//end of else
	}//end of if
	else if(strcmp("-l", args[1]) == 0)
	{
		//TODO: make sure you deal with drawing a line
		wantLine = 1;
		p1row = atoi(args[2]);
		p1col = atoi(args[3]);
		p2row = atoi(args[4]);
		p2col = atoi(args[5]);
		in = fopen(args[6], "r");
		out = fopen(args[7], "w");
		if(in == NULL || out == NULL)
		{
			printf("File was not open\n");
			usage();
			exit(-99);
		}//end if
	}//end of else if
	else if(strcmp("-c", args[1]) == 0)
	{
		//TODO: make sure to deal with drawing a circle
		if(strcmp("-e", args[2]) == 0)
		{
			wantEdge = 1;
			wantCircle =1;
			centerRow = atoi(args[3]);
			centerCol = atoi(args[4]);
			radius = atoi(args[5]);
			edgeWidth = atoi(args[6]);
			in = fopen(args[7], "r");
			out = fopen(args[8], "w");
			if(in == NULL || out == NULL)
			{
				printf("File was not open\n");
				usage();
				exit(-99);

			}//end of inner if to make sure that the files were open

		}//end of inner if
		else
		{
			wantCircle = 1;
			centerRow = atoi(args[2]);
			centerCol = atoi(args[3]);
			radius = atoi(args[4]);
			in = fopen(args[5], "r");
			out = fopen(args[6], "w");
			if(in == NULL || out == NULL)
			{
				printf("File was not open\n");
				usage();
				exit(-99);

			}//end of inner if to make sure that the files were open
		}//end of else statement for circle
	}//end of else if
	else if(strcmp("-ce", args[1]) == 0 || strcmp("-ec", args[1]) == 0)
	{
		//TODO: make sure that it deals with both out puts.
		wantEdge = 1;
		wantCircle =1;
		centerRow = atoi(args[2]);
		centerCol = atoi(args[3]);
		radius = atoi(args[4]);
		edgeWidth = atoi(args[5]);
		in = fopen(args[6], "r");
		out = fopen(args[7], "w");
		if(in == NULL || out == NULL)
		{
			printf("File was not open\n");
			usage();
			exit(-99);

		}//end of inner if to make sure that the files were open
	}//end of else
	else
	{
		printf("no initial menu option found");
		usage();
		exit(-99);
	}//end of else statment


	//End of parsing the line
	if(wantLine)
	{
		callLine(p1row, p1col, p2row, p2col, in, out);
	}//end of wantLine
	else if(wantEdge && wantCircle)
	{
		//TODO: make this handle both
		FILE * temp = fopen("awioejf", "w");
		callEdge(edgeWidth, in, temp);
		in = fopen("awioejf", "r");
		callCircle(centerRow, centerCol, radius, in, out);
		remove("awioejf");

	}//end of else if wantEdge and wantCircle
	else if(wantEdge)
	{
		callEdge(edgeWidth, in, out);
	}//end of else if statmen for edge
	else if(wantCircle)
	{
		callCircle(centerRow, centerCol, radius, in, out);

	}//end of else if for want Circle

	clock_t end = clock();
	printf("time = %f\n",(float) (end-start)/ CLOCKS_PER_SEC);
}//end of main
