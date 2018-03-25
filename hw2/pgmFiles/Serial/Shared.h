
#ifndef SHARED_H
#define SHARED_H

#define rowsInHeader 4      // number of rows in image header
#define maxSizeHeadRow 200  // maximal number characters in one row in the header

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>


void callCircle(int centerRow, int centerColumn, int radius, FILE * in, FILE * out);
void callEdge(int edgeWidth, FILE * in, FILE * out);
void callLine(int p1row, int p1col, int p2row, int p2col, FILE * in,  FILE * out);

#endif
