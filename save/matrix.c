/*File containing the C code pertaining to the matrix data type
Author : William 
Creation date : 11/23/16
*/

#include <matrix.h>

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