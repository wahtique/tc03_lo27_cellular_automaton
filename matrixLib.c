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
BOOL isColumnEmpty(colElement* column) {
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

Matrix* mulMatrix(Matrix* A, Matrix* B)
{
	
	rowElement* row = A->rows;
	colElement* col = B->cols ;

	points* newMat = (points*)malloc(sizeof(points));
	points* newOne = (points*)malloc(sizeof(points));
	if(A->colCount == B->rowCount )
	{
		newMat-> x = A->rowCount;
		newMat-> y = B->colCount;
		while( row!=NULL && col!=NULL &&  )
	}
	




}

/*colElement* removeColHead( colElement* col)
{
	colElement* tmpEle= col->nextCol;
	colElement* tmpRow = 

}
*/
/* ROWS */

BOOL isRowEmpty(rowElement* row) {
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
	colElement* colA,colB;
	cellElement* cellA,cellB;

	if (A->colCount != B->colCount || A->rowCount != B->rowCount || isMatrixEmpty(A) && NOT(isMatrixEmpty(B)) || isMatrixEmpty(B) && NOT(isMatrixEmpty(A))))
	{
		return FALSE;
	}

	if(isMatrixEmpty(A) && isMatrixEmpty(B))
	{
		return TRUE;
	}

	/*I then check each column and row; if the indexes are different then I know its false */
	colA = A->cols;
	colB = b->cols;
	cellA = colA->col;
	cellB = colB->col;

	while (colA != NULL &&  colB != NULL) 
	{
		if (colA->colN != colB->colN)
		{
			return FALSE;
		}
		/*else we have the same columns and we check the cells of the columns*/
		while(cellA != NULL && cellB != NULL)
		{
			if(cellA->rowIndex != cellB->rowIndex)
			{
				return FALSE;
			}
			cellA = cellA->nextCol;
			cellB = cellB->nextCol;
		}
		/* if we are still there, then the two columns are equals and we move to the next */
		colA = colA->nextCol;
		colB = colB->nextCol;
	}
	/* finally, if we re still here, then we can say we cant prove the matrices ar not equals */
	return TRUE;

}