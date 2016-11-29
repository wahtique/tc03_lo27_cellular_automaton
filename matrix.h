/*
File containing the prototypes of the functions pertaining to the matrix data type
Author : William 
Creation date : 11/23/16
*/

#include <stdio.h>
#include <stdlib.h>
#include <rows.h>
#include <cols.h>

/*
THE Matrix structure
	colcount : integer indicating the number of columns the Matrix contains
	rowCount : integer indicating the number of rows the Matrix contains
	cols : a pointer toward the first element of the list of colElement representing the columns of the Matrix
	rows : a pointer toward the first element of the list of rowElement representing the rows of the Matrix
*/
typedef struct
{
	int colCount;
	int rowCount;
	colElement* cols;
	rowElement* rows;
}Matrix;


