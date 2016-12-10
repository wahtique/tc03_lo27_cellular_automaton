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

colElement* insertCol(colElement* col, int index)
{
	colElement* newel = (colElement*)malloc(sizeof(colElement));
	colElement* tmp = col;
	if (tmp->colN>index)

	{
		newel->colN = index;
		newel->nextCol = tmp;
		tmp->prevCol = newel;
	}else{

		while(index<tmp->colN)
		{
			tmp=col->nextCol;
		}
		if (index!=tmp->colN)
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
	cellElement* rowCell = A->rows->row;
	cellElement* colCell = A->cols->col;

	points* newMat = (points*)malloc(sizeof(points));
	points* newOne = (points*)malloc(sizeof(points));
	if(A->colCount == B->rowCount )
	{
		newMat-> x = A->rowCount; /* Definition to the size of the new matrix*/
		newMat-> y = B->colCount;
		while()

		while( rowCell!=NULL && colCell!=NULL && rowCell->colIndex == colCell->rowIndex ) /* For 1 lines et 1 columm*/
		{
			if (rowCell->colIndex == colCell->rowIndex)
			{
				newOne = insertTailPoints(rowCell->colIndex,  colCell->rowIndex, newOne);
			}
			if (rowCell->rowIndex > colCell->colIndex)
			{
				colCell = colCell-> nextCol;
			} else {
				rowCell = rowCell-> nextRow;
			}

		}
			
	}
	




}


/*colElement* removeColHead( colElement* col)
{
	colElement* tmpEle= col->nextCol;
	colElement* tmpRow = 

}
*/
/* ROWS */

BOOL isRowEmpty(rowElement* row){
	return(row==NULL || row->row==NULL);
}

rowElement* insertRow(rowElement* row, int index)
{
	rowElement* newel = (rowElement*)malloc(sizeof(rowElement));
	rowElement* tmp = row;
	if (tmp->rowN>index)
	{
		newel->rowN= index;
		newel->nextRow = tmp;
		tmp->prevRow = newel;
	}else{

		while(index<tmp->rowN)
		{
			tmp=row->nextRow;
		}
		if (index != tmp->rowN)
		{
			newel->rowN= index;
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
	colElement* colA;
	colElement* colB;
	cellElement* cellA; 
	cellElement* cellB;

	if (A->colCount != B->colCount || A->rowCount != B->rowCount || (isMatrixEmpty(A) && (isMatrixEmpty(B)==0)) || (isMatrixEmpty(B) && (isMatrixEmpty(A)==0)))
	{
		return FALSE;
	}

	if(isMatrixEmpty(A) && isMatrixEmpty(B))
	{
		return TRUE;
	}

	/*I then check each column and row; if the indexes are different then I know its false */
	colA = A->cols;
	colB = B->cols;
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

/*
Matrix* sumMatrix(Matrix A, Matrix B)
{

}
*/


Matrix* newMatrix(arrayMatrix* m)
{
	points* pt = NULL; /* the point pointer toward the point I am going to insert */
	colElement* currCol;
	rowElement* currRow;  

	Matrix* newMat = (Matrix*)malloc(sizeof(Matrix));
	newMat->colCount = m->p;
	newMat->rowCount = m->n;
	newMat->cols = NULL;
	newMat->rows = NULL;

	/*I insert the cell elements defined by ths listPoints in m*/

	pt = m->list;

	if (pt == NULL)
	{
		return newMat; /* no ones in this Matrix, then I return an empty Matrix */
	}



	while(pt != NULL)
	{
		currCol = newMat->cols;
		currRow = newMat->rows;
		/* I find the right column*/

		while(curr)
		/* if I have create a new column and or row */

	}
}
