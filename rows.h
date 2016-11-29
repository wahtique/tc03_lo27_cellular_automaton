/*
File containing the prototypes of the functions pertaining to the rows list
Author : William
Creation date : 11/29/2016
*/

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



