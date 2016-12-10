/*
File containing the prototypes of the functions pertaining to the rows list
Author : William
Creation date : 11/29/2016
*/

#ifndef ROWS_H_INCLUDED
#define ROWS_H_INCLUDED
#include <cell.h>

/*
A doubly chained list containing the rows of a Matrix
	rowN : an integer, the index of the row represented by this rowElement
	nextRow : a pointer toward the next rowElement, or NULL if last row, in the Matrix
	prevRow : a pointer toward the previous rowElement in the Matrix, or NULL if it's the first row
	row : a pointer toward the first cellElement of the row
*/
typedef struct rowEl
{
	int rowN;
	struct rowEl* nextRow;
	struct rowEl* prevRow;
	cellElement* row;
}rowElement;



/*
Function inserting an empty column at the end of a rows list
Arguments :
arg rows : the pointer column in which we will insert an empty column
Result:
a pointer toward this updated doubly linked list  
*/
rowElement* insertTailRow(rowElement* row);
#endif