/*
File containing the declaration of the cell type and the functions pertainting to this type
Author : William
Creation date : 11/29/2016
*/

#include <bool.h>

/*
Cells of a Matrix
	colIndex : an integer indicating in which column of the Latrix this element is
	rowIndex : an integer indicating in which row this element is located
	value : the Boolean value contained in this element
	nextCol : a pointer toward the next element on the row 
	newtRow : a pointer toward the next element on this column
*/
typedef struct cell
{
	int colIndex;
	int rowIndex;
	bool value;
	struct cell* nextCol;
	struct cell* nextRow;
}cellElement;


/*
Insert a cell in a matrix at the given index
Arguments :
Result :
*/

void insertTailCell(arrayMatrix matA, Matrix matN, int i, int j);