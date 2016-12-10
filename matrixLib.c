/*
File containing all the functions manipulating a matrix
Author : William & Yann
Date : 09/12/16
*/

/* INCLUDES */
#include <stdio.h>
#include <stdlib.h> 
#include <matrixLib.h>
/* CELL */

/* COLS */
Bool isColumnEmpty(colElement* column) {
	return(column==NULL || column->col==NULL);
}

colElement* insertCol(colElement* col, int index);
{
	colElement* newel = (colElement*)malloc(sizeof(colElement));
	colElement* tmp= col;
	if (tmp>index)
	{
		newel->colN= index;
		newel->nextCol = tmp;
		tmp->prevCol = newel;
	}else{

		while(index<tmp)
		{
			tmp=col->nextCol;
		}
		if (index=!tmp)
		{
			newel->colN= index;
			tmp->nextCol->prevCol = newel;
			newel->nextCol = tmp->nextCol;
			newel->prevCol = tmp;
			tmp->nextCol =	newel;
		}
	} 
return col;
}

colElement* removeColHead( colElement* col)
{
	colElement* tmp= col;

}

/* ROWS */

Bool isRowEmpty(rowElement* row) {
	return(row==NULL || row->Row==NULL);
}

rowElement* insertRow(rowElement* row, int index);
{
	rowElement* newel = (rowElement*)malloc(sizeof(rowElement));
	rowElement* tmp= row;
	if (tmp>index)
	{
		newel->RowN= index;
		newel->nextRow = tmp;
		tmp->prevRow = newel;
	}else{

		while(index<tmp)
		{
			tmp=row->nextRow;
		}
		if (index=!tmp)
		{
			newel->RowN= index;
			tmp->nextRow->prevRow = newel;
			newel->nextRow = tmp->nextRow;
			newel->prevRow = tmp;
			tmp->nextRow =	newel;
		}
	} 
return row;
}


/* MATRIX */

BOOL isMatrixEmpty(Matrix* m)
{
	if (m == NULL)
	{
		return TRUE;
	}

	return (m->colCount < 1 && m->rowCount < 1 );
}

BOOL isMatrixSquare(Matrix* m)
{
	if (m==NULL)
	{
		return TRUE;
	}
	return (m->colCount == m->rowCount);
}

BOOL equalsMatrix(Matrix* A, Matrix* B)
{
	if (A->colCount != B->colCount || A->rowCount != B->rowCount)
	{
		return FALSE;
	}

	/*I then check each column and row; if the indexes are different then I know its false */
	colElement* currColA = A->cols;
	colElement* currColB = B->cols;
	rowElement* currRowA = A->rows;
	rowElement* currRowB = B->rows;

	while currColA->nextCol != NULL &&  currColB->next


}