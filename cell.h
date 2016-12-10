/*
File containing the declaration of the cell type and the functions pertainting to this type
Author : William
Creation date : 11/29/2016
*/

#ifndef CELL_H_INCLUDED
#define CELL_H_INLCUDED

#include <bool.h>

/*
Cells of a Matrix
	colIndex : an integer indicating in which column of the Latrix this element is
	rowIndex : an integer indicating in which row this element is located
	value : the Boolean value contained in this element
	nextCol : a pointer toward the next element on the row 
	newtRow : a pointer toward the next element on this column
*/
typedef struct cellEl
{
	int colIndex;
	int rowIndex;
	struct cellEl* nextCol;
	struct cellEl* nextRow;
}cellElement;

#endif