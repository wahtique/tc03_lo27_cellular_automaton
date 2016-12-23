/*
File containing all the functions manipulating a matrix
Author : William & Yann
Date : 09/12/16
*/

/* ----------------------------- INCLUDES ----------------------------- */
#include <stdio.h>
#include <stdlib.h> 
#include <matrixLib.h>

/* ----------------------------- CELLS ----------------------------- */

/* ----------------------------- COLS ----------------------------- */

BOOL isColumnEmpty(colElement* column) 
{
	return(column==NULL || column->col==NULL);
}

Matrix* insertCol(Matrix* m, int index)
{
	colElement* newel = (colElement*)malloc(sizeof(colElement)); /* we define a new columm element for add it to the matrix and a pointers to a columm */
	colElement* tmp = m->cols;

	if(tmp == NULL)
	{
		/*in this case, there are no element, the new element is the new first. */
		newel->colN = index;

		/*the new first element of the list of cols is now the newel*/
		m->cols = newel;

		/*we make sure the previous element of the first is NULL*/
		newel->prevCol = NULL;

		/*we make sure the next element of the first is NULL*/
		newel->nextCol = NULL;


		/*we do the same for the col of the newel*/
		newel->col = NULL;

	}else{
		/* we search the position of the new columm with 3 cases : the new element is the first, in the middle of the matrix or the last */
		if (tmp->colN > index) 
		{
			/*in this case, the first element has an index greater than the index of the new element. The new element is the new first. */
			
			/* we assign the index to the new element*/
			newel->colN = index;
			/* his next is the former first */
			newel->nextCol = tmp;
			/*the former first's previous is now the new first*/
			tmp->prevCol = newel;
			/*the new first element of the list of cols is now the newel*/
			m->cols = newel;
			/*we make sure the previous element of the first is NULL*/
			newel->prevCol = NULL;
			/*we do the same for the col of the newel*/
			newel->col = NULL;

		}
		else /* which means newel will not be the new first */
		{

			while(tmp->nextCol != NULL && index < tmp->colN) /* while we are not at the end and we are sure we are still not after where the new element should be*/
			{
				tmp=tmp->nextCol; /* we advance to the next */
			}
			/* now, either we are at the end of the list or we have tmp pointing toward an element whose next have an index greater than the one we want to insert */
			if (index != tmp->colN) /* if the element doesnt yet exist. If it does, we do nothing */
			{
				if (tmp->nextCol == NULL) /* if we are pointing toward the current last element*/
				{
					newel->colN = index;
					newel->nextCol = NULL; /* since it's the new last element */
					newel->prevCol = tmp; /* same, new last. the old last become the penultimate element */
					newel->col = NULL; /* always better to initialise at NULL*/
					tmp->nextCol = newel; /* we update the formet last element*/
				}
				else /* this means we have to insert newel between 2 other elements */
				{
					
					/*we start by updating the newel*/
					newel->colN= index;
					newel->nextCol = tmp->nextCol;
					newel->prevCol = tmp;
					newel->col = NULL;
					/*we now update the element pointed by tmp */
					tmp->nextCol = newel;
					/*we finally update the element following newel */
					newel->nextCol->prevCol = newel;
				}
			}	
		} 
	}
	return m; 
}	

Matrix* removeCol( Matrix* m, int index)
{
	cellElement* tmpEle= m->rows->row;
	rowElement* tmpRow = m->rows;
	cellElement* cellRemove = m->rows->row;
	while(tmpRow!=NULL)
	{
		tmpEle= tmpRow->row;
		cellRemove = tmpEle;
		while(tmpEle!=NULL || tmpEle->nextCol->colIndex <= index )
		{
			tmpEle = tmpEle->nextCol; 
		}
		if (tmpEle->nextCol->colIndex == index)
		{
			cellRemove= tmpEle->nextCol;
			tmpEle->nextCol = tmpEle->nextCol ->nextCol;
			free(cellRemove);
			m->colCount = m->colCount - 1;
			return m;
		}
	}

}



/* ----------------------------- ROWS ----------------------------- */

BOOL isRowEmpty(rowElement* row)
{
	return(row==NULL || row->row==NULL);
}

Matrix* insertRow(Matrix* m, int index)
{
	rowElement* newel = (rowElement*)malloc(sizeof(rowElement)); /* we define a new row element for add it to the matrix and a pointers to a row */
	rowElement* tmp = m->rows;

	if(tmp == NULL)
	{
		/*in this case, there are no element, the new element is the new first. */
		newel->rowN = index;

		/*the new first element of the list of cols is now the newel*/
		m->rows = newel;

		/*we make sure the previous element of the first is NULL*/
		newel->prevRow = NULL;

		/*we make sure the next element of the first is NULL*/
		newel->nextRow = NULL;


		/*we do the same for the col of the newel*/
		newel->row = NULL;

		}else{
		/* we search the position of the new row with 3 cases : the new element is the first, in the middle of the matrix or the last */
		if (tmp->rowN > index) 
		{
			/*in this case, the first element has an index greater than the index of the new element. The new element is the new first. */
		
			/* we assign the index to the new element*/
			newel->rowN = index;
			/* his next is the former first */
			newel->nextRow = tmp;
			/*the former first's previous is now the new first*/
			tmp->prevRow = newel;
			/*the new first element of the list of cols is now the newel*/
			m->rows = newel;
			/*we make sure the previous element of the first is NULL*/
			newel->prevRow = NULL;
			/*we do the same for the col of the newel*/
			newel->row = NULL;

		}
		else /* which means newel will not be the new first */
		{

			while(tmp->nextRow != NULL && index < tmp->rowN) /* while we are not at the end and we are sure we are still not after where the new element should be*/
			{
				tmp=tmp->nextRow; /* we advance to the next */
			}
			/* now, either we are at the end of the list or we have tmp pointing toward an element whose next have an index greater than the one we want to insert */
			if (index != tmp->rowN) /* if the element doesnt yet exist. If it does, we do nothing */
			{
				if (tmp->nextRow == NULL) /* if we are pointing toward the current last element*/
				{
					newel->rowN = index;
					newel->nextRow = NULL; /* since it's the new last element */
					newel->prevRow = tmp; /* same, new last. the old last become the penultimate element */
					newel->row = NULL; /* always better to initialise at NULL*/
					tmp->nextRow = newel; /* we update the formet last element*/
				}
				else /* this means we have to insert newel between 2 other elements */
				{
					
					/*we start by updating the newel*/
					newel->rowN= index;
					newel->nextRow = tmp->nextCol;
					newel->prevRow = tmp;
					newel->row = NULL;
					/*we now update the element pointed by tmp */
					tmp->nextRow = newel;
					/*we finally update the element following newel */
					newel->nextRow->prevRow = newel;
				}
			}
		}
	}	
	return m; 
}


Matrix* removeRow(Matrix* m, int index)
{
	cellElement* tmpEle= m->cols->col;
	colElement* tmpCol = m->cols;
	cellElement* cellRemove = m->cols->col;
	while(tmpCol!=NULL)
	{
		tmpEle = tmpCol->col;
		cellRemove = tmpEle;
		while(tmpEle!=NULL || tmpEle->nextRow->rowN <= index )
		{
			tmpEle = tmpEle->nextRow; 
		}
		if (tmpEle->nextRow->rowIndex == index)
		{
			cellRemove= tmpEle->nextRow;
			tmpEle->nextRow = tmpEle->nextRow ->nextRow;
			free(cellRemove);
			m->rowCount = m->rowCount -1; 
			return m;

		}
	}

}


/* ----------------------------- MATRIX ----------------------------- */

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

BOOL isMatrixSameSize(Matrix* a, Matrix* b)
{
	if (a==NULL || b==NULL)
	{
		return FALSE;
	}
	return (a->colCount == b->colCount &&  a->rowCount == b->rowCount );
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


Matrix* sumMatrix(Matrix* a, Matrix* b)
{
	if (isMatrixSameSize(a,b)!= TRUE)
	{
		return NULL;
	}else{
		rowElement* rowa = a->rows;
		cellElement* cella = a->rows->row;
		rowElement* rowb = b->rows;
		cellElement* cellb = b->rows->row;

		Points* newMat = (Points*)malloc(sizeof(Points));
		arrayMatrix* newel = (arrayMatrix*)malloc(sizeof(arrayMatrix));

		newel->n = a->rowCount; /* Definition to the size of the new matrix*/
		newel-> = b->colCount;
			
		while(rowa!= NULL && rowb != NULL)
			{
				if(rowa->rowN == rowb->rowN)
				{
				while(cella->nextCol != NULL && cellb->nextCol != NULL)
			{
				if (cella->colIndex >= cellb->colIndex)
				{
					newMat=insertTailPoints(cellb->colIndex, cellb->rowIndex, newMat);
					cellb = cellb->nextCol;
				} else{
					if (cella->colIndex >= cellb->colIndex)
					{
						newMat = insertTailPoints(cellb->colIndex, cellb->rowIndex, newMat);
						cellb = cellb->nextCol;
						cella = cella-> nextCol;
					} else{
						insertTailPoints(cella->colIndex, cella->rowIndex, newMat);
						cella = cella->nextCol;
					}
				}
			}
			rowa = rowa->nextRow;
			rowb = rowb->nextRow;
			}
			else{
				if(rowa->rowN < rowb->rowN)
				{
					rowa->nextRow;
				}else{
					rowb->nextRow;
				}

			}
		
		}

	}
	newel->list = newMat;
	return newMatrix(newel);
}


Matrix* mulMatrix(Matrix* A, Matrix* B)
{
	
	rowElement* row = A->rows;
	colElement* col = B->cols ;
	cellElement* rowCell = A->rows->row;
	cellElement* colCell = A->cols->col;

	Points* newMat = (Points*)malloc(sizeof(Points));
	arrayMatrix* newel = (arrayMatrix*)malloc(sizeof(arrayMatrix));
	if(A->colCount == B->rowCount )
	{
		newel->n = A->rowCount; /* Definition to the size of the new matrix*/
		newel-> = B->colCount;
		while(row!= NULL)
		{
			while(col!= NULL)
			{
				while( rowCell!=NULL && colCell!=NULL && rowCell->colIndex == colCell->rowIndex ) /* For 1 lines et 1 columm*/
				{
					if (rowCell->colIndex == colCell->rowIndex)
					{
						newMat = insertTailPoints(rowCell->colIndex,  colCell->rowIndex, newMat);
					}
					if (rowCell->rowIndex > colCell->colIndex)
					{
						colCell = colCell-> nextCol;
					} else {
						rowCell = rowCell-> nextRow;
					}
				}
			col = col->nextCol;	
			}
		}
		row = row->nextRow;
	}
	newel->list = newMat;
return newMatrix(newel);	

}

Matrix* newMatrix(arrayMatrix* m)
{
	Points* pt = m->list; /* the Points pointer toward the Points I am going to insert */
	colElement* currCol = NULL;
	rowElement* currRow = NULL;  

	Matrix* newMat = (Matrix*)malloc(sizeof(Matrix)); /* I malloc my new Matrix and initialize everything*/
	newMat->colCount = m->p; 
	newMat->rowCount = m->n;
	newMat->cols = NULL;
	newMat->rows = NULL;

	/*I insert the cell elements defined by ths listPoints in m*/

	if (pt == NULL) /* which means y list is empty. No one in the list. No ones in the Matrix*/
	{
		return newMat; /* no ones in this Matrix, then I return an empty Matrix. */
	}

	while(pt != NULL) /* I will then advance in the list */
	{

		/* my currCol and CurrRow initialized at the begining of the lists */
		currCol = newMat->cols;
		currRow = newMat->rows;
		/* I find the right column */
		while(currCol !=NULL && currCol->colN < pt->x)
		{
			currCol = currCol->nextCol;
		}
		/*now either currCol == x, and in this cas I'm happy, or the column x doesnt exist. 
		In this case, I will create it and update my currCol pointer */
		if(currCol == NULL || currCol->colN > pt->x)
		{
			newMat=insertCol(newMat, pt->x); /* I create the missing column */
			/* I point toward the said column */
			currCol = newMat->cols;
			while(currCol->colN != pt->x) /* if the column I'm looking for is the first, I will not do anything. */
			{
				currCol=currCol ->nextCol;
			} 
		}

		/*I now insert a new element in this list*/

		/* now that I have my new element in its column, I have to inser it in its row.
		I will first look for its row in the same way as the colunmn */
		while()


	}
}


Matrix* andColSequenceOnMatrix(Matrix* m)
{
	if (isMatrixEmpty(m)!= TRUE)
	 {
	 	colElement* fcol = m->cols;
	 	colElement* scol = m->cols->nextCol;
	 	cellElement* fcell = fcol->col;
	 	cellElement* scell = scol->col;

	 	while(scol->nextCol != NULL)
	 	{
	 		if (scol->colN == fcol->colN + 1)
	 		{
	 			fcell = fcol->col;
	 			scell =	scol->col;
	 			while(scell->nextRow != NULL && fcell->nextRow != NULL)
	 				
	 		}
	 	}
	 } 
}

/* ----------------------------- Points ----------------------------- */

Points* insertTailPoints(int x, int y, Points* newMat)
{
	Points* p = newMat;
	Points* newElement = (Points*)malloc(sizeof(Points));
	newElement->x = x;
	newElement->y = y;
	newElement->nextP = NULL;
	while(p->nextP != NULL )
	{
		p=p->nextP;
	}
	p->nextP = newElement;
	return newMat;
}
