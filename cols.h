/*
File containing declaration of the rowElement type and the prototypes of the functions pertaining to it
Author : William
Creation date : 11/29/2016
*/

#include <cell.h>

/*
A doubly chained list containing the columns of a Matrix
	colN : an integer, the index of the column represented by this colElement
	nextCol : a pointer toward the next colElement in the Matrix, or NULL if it's the last column
	prevCol : a pointer toward the previous colElement in the Matrix, or NULL if it's the first column
	col : a pointer toward the first cellElement of the column
*/
typedef struct colEl
{
	int colN;
	struct colEl* nextCol;
	struct ColEl* prevCol;
	cellElement* col;
}colElement;
