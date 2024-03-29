/*
File containing all the functions manipulating a matrix
Author : William Veal Phan (william.veal@utbm.fr) & Yann Le Chevanton (yann.le-chevanton@utbm.fr)
Date : 09/12/16
*/

/* ----------------------------- INCLUDES ----------------------------- */
#include <stdio.h>
#include <stdlib.h> 
#include <matrixLib.h>
#include <math.h>
#include <time.h>

/* ----------------------------- CELLS ----------------------------- */

/* ----------------------------- COLS ----------------------------- */

BOOL isColEmpty(colElement* column) 
{
	return(column == NULL || column->col == NULL);
}

Matrix* insertCol(Matrix* m, int index)
{
	colElement* newel = NULL;
	colElement* tmp = m->cols;

	if(tmp == NULL) /* we are adding the first column */
	{
		newel = (colElement*)malloc(sizeof(colElement));
		/*in this case, there are no elements, the new element is the new first. */
		newel->colN = index;
		/*the new first element of the list of cols is now the newel*/
		m->cols = newel;
		/*we make sure the previous element of the first is NULL*/
		newel->prevCol = NULL;
		/*we make sure the next element of the first is NULL*/
		newel->nextCol = NULL;
		/*we do the same for the col of the newel*/
		newel->col = NULL;
	}
	else
	{
		/* we search the position of the new columm with 3 cases : the new element is the first, in the middle of the matrix or the last */
		if (tmp->colN > index) 
		{
			newel = (colElement*)malloc(sizeof(colElement));
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
			while(tmp->nextCol != NULL && index > tmp->nextCol->colN) /* while we are not at the end and we are sure we are still not after where the new element should be*/
			{
				tmp=tmp->nextCol; /* we advance to the next */
			}
			/* now, either we are at the end of the list or we have tmp pointing toward an element whose next have an index greater than the one we want to insert */
			if (index != tmp->colN) /* if the element doesnt yet exist. If it does, we do nothing */
			{
				if (tmp->nextCol == NULL) /* if we are pointing toward the current last element*/
				{
					newel = (colElement*)malloc(sizeof(colElement));
					newel->colN = index;
					newel->nextCol = NULL; /* since it's the new last element */
					newel->prevCol = tmp; /* same, new last. the old last become the penultimate element */
					newel->col = NULL; /* always better to initialise at NULL*/
					tmp->nextCol = newel; /* we update the formet last element*/
				}
				else /* this means we have to insert newel between 2 other elements */
				{
					/*we start by updating the newel*/
					newel = (colElement*)malloc(sizeof(colElement));
					newel->colN = index;
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


Matrix* removeCol(Matrix* m, int index)
{
	if(isMatrixEmpty(m) != TRUE && index <= m->colCount && index > 0)
	{
		colElement* rcol = m->cols;

		while(rcol != NULL && rcol->colN < index)
		{
			rcol = rcol->nextCol;
		}
		if(rcol->colN == index)
		{
			/* rcol is on the col we need to remove */
			rowElement* currRow = m->rows;
			cellElement* currCell = NULL;
			cellElement* cellToRemove  = NULL;
			/* we found a col which is linked to other cols. We will update the links*/
			if(rcol == m->cols)
			{
				m->cols = rcol->nextCol;	
			}
			else
			{
				rcol->prevCol->nextCol = rcol->nextCol;
			}
			if(rcol->nextCol !=NULL)
			{
				rcol->nextCol->prevCol = rcol->prevCol;
			}
			while(currRow != NULL)
			{
				if(currRow->row->colIndex == index && (currRow->row->nextRow == NULL || currRow->row->colIndex == m->colCount))
				{
					/* which means the only element is in the col to remove */
					if(currRow == m->rows && currRow->nextRow == NULL)/* the only row in the Matrix */ 
					{
						free(currRow);
						currRow = NULL;
					}
					else
					{
						if(currRow == m->rows) /* if it's the first row*/
						{
							m->rows = currRow->nextRow;
							currRow=currRow->nextRow;
							free(currRow->prevRow);
							currRow->prevRow = NULL;
						}
						else
						{
							if(currRow->nextRow == NULL) /* last and not first */
							{	
								currRow->prevRow->nextRow = NULL;
								free(currRow);
								currRow = NULL;
							}
							else /* neither last nor first */
							{
								currRow->nextRow->prevRow = currRow->prevRow;
								currRow=currRow->nextRow;
								free(currRow->prevRow->nextRow);
								currRow->prevRow->nextRow = currRow;
							}
						}						
					}
				}
				else /* the row is still here after, we only need to update the pointers */
				{
					currCell = currRow->row;
					if(currCell->colIndex == index) /* first but not last */
					{
						currRow->row = currCell->nextRow;
						currRow = currRow->nextRow;
					}
					else
					{
						if(currCell->colIndex < index)
						{
							while(currCell->nextRow != NULL && currCell->nextRow->colIndex < index)
							{
								currCell = currCell->nextRow;
							}
							if(currCell->nextRow != NULL && currCell->nextRow->colIndex == index )
							{
								currCell->nextRow = currCell->nextRow->nextRow; 
							}							
						}
						currRow = currRow->nextRow;
					}
				}	
			}
			/* we have updated our rows. we now delete the col */
			currCell = rcol->col;
			while(currCell != NULL)
			{
				cellToRemove = currCell;
				currCell = currCell->nextCol;
				free(cellToRemove);
			}
			free(rcol);
		}
	}
	return m;
}

/* ----------------------------- ROWS ----------------------------- */

BOOL isRowEmpty(rowElement* row)
{
	return(row==NULL || row->row==NULL);
}

Matrix* insertRow(Matrix* m, int index)
{
	rowElement* newel = NULL; /* we define a new row element for add it to the matrix and a pointers to a row */
	rowElement* tmp = m->rows;

	if(tmp == NULL)
	{
		newel = (rowElement*)malloc(sizeof(rowElement));
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
	}
	else
	{
		/* we search the position of the new row with 3 cases : the new element is the first, in the middle of the matrix or the last */
		if (tmp->rowN > index) 
		{
			newel = (rowElement*)malloc(sizeof(rowElement));
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

			while(tmp->nextRow != NULL && index > tmp->nextRow->rowN) /* while we are not at the end and we are sure we are still not after where the new element should be*/
			{
				tmp=tmp->nextRow; /* we advance to the next */
			}
			/* now, either we are at the end of the list or we have tmp pointing toward an element whose next have an index greater than the one we want to insert */
			if (index != tmp->rowN) /* if the element doesnt yet exist. If it does, we do nothing */
			{
				if (tmp->nextRow == NULL) /* if we are pointing toward the current last element*/
				{
					newel = (rowElement*)malloc(sizeof(rowElement));
					newel->rowN = index;
					newel->nextRow = NULL; /* since it's the new last element */
					newel->prevRow = tmp; /* same, new last. the old last become the penultimate element */
					newel->row = NULL; /* always better to initialise at NULL*/
					tmp->nextRow = newel; /* we update the former last element*/
				}
				else /* this means we have to insert newel between 2 other elements */
				{
					
					/*we start by updating the newel*/
					newel = (rowElement*)malloc(sizeof(rowElement));
					newel->rowN= index;
					newel->nextRow = tmp->nextRow;
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
	if(isMatrixEmpty(m) != TRUE && index <= m->rowCount && index > 0)
	{
		rowElement* rrow = m->rows;

		while(rrow != NULL && rrow->rowN < index)
		{
			rrow = rrow->nextRow;
		}
		if(rrow->rowN == index)
		{
			/* rrow is on the row we need to remove */
			colElement* currCol = m->cols;
			cellElement* currCell = NULL;
			cellElement* cellToRemove  = NULL;
			/* we found a row which is linked to other rows. We will update the links*/
			if(rrow == m->rows)
			{
				m->rows = rrow->nextRow;	
			}
			else
			{
				rrow->prevRow->nextRow = rrow->nextRow;
			}
			if(rrow->nextRow != NULL)
			{
				rrow->nextRow->prevRow = rrow->prevRow;
			}
			/* we start by updating the columns */
			while(currCol != NULL)
			{
				if(currCol->col->rowIndex == index && (currCol->col->nextCol == NULL || currCol->col->rowIndex == m->rowCount))
				{
					/* which means the only element is in the row to remove */
					if(currCol == m->cols && currCol->nextCol == NULL)/* the only col in the Matrix */ 
					{
						free(m->cols);
						currCol = NULL;
					}
					else
					{
						if(currCol == m->cols) /* if it's the first col*/
						{
							m->cols = currCol->nextCol;
							currCol=currCol->nextCol;
							free(currCol->prevCol);
							currCol->prevCol = NULL;
						}
						else
						{
							if(currCol->nextCol == NULL) /* last and not first */
							{	
								currCol->prevCol->nextCol = NULL;
								currCol = currCol->prevCol;
								free(currCol->nextCol);
								currCol = NULL;
							}
							else /* neither last nor first */
							{
								currCol->nextCol->prevCol = currCol->prevCol;
								currCol=currCol->nextCol;
								free(currCol->prevCol->nextCol);
								currCol->prevCol->nextCol = currCol;
							}
						}						
					}
				}
				else /* the col is still here after, we only need to update the pointers */
				{
					currCell = currCol->col;
					if(currCell->rowIndex == index) /* first but not last */
					{
						currCol->col = currCell->nextCol;
						currCol = currCol->nextCol;
					}
					else
					{
						if(currCell->rowIndex < index)
						{
							while(currCell->nextCol != NULL && currCell->nextCol->rowIndex < index)
							{
								currCell = currCell->nextCol;
							}
							if(currCell->nextCol != NULL && currCell->nextCol->rowIndex == index )
							{
								currCell->nextCol = currCell->nextCol->nextCol; 
							}							
						}
						currCol = currCol->nextCol;
					}
				}	
			}
			/* we have updated our columns. we now delete the row */
			currCell = rrow->row;
			while(currCell != NULL)
			{
				cellToRemove = currCell;
				currCell = currCell->nextRow;
				free(cellToRemove);
			}
			free(rrow);
		}
	}
	return m;
}



/* ----------------------------- MATRIX ----------------------------- */

BOOL isMatrixEmpty(Matrix* m)
{
	if (m == NULL)
	{
		return TRUE;
	}

	return (m->colCount < 1 || m->rowCount < 1 );
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
	if(a==NULL && b==NULL)
	{
		return TRUE; /* two empty matrices have the same size */
	}
	if (a==NULL || b==NULL)
	{
		return FALSE; /* I am sure both of them arent null at the same time */
	}
	return (a->colCount == b->colCount &&  a->rowCount == b->rowCount );
}

BOOL equalsMatrix(Matrix* A, Matrix* B)
{
	colElement* colA=NULL;
	colElement* colB=NULL;
	cellElement* cellA=NULL; 
	cellElement* cellB=NULL;

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

	while (colA != NULL &&  colB != NULL) 
	{
		if (colA->colN != colB->colN)
		{
			return FALSE;
		}
		/*else we have the same columns and we check the cells of the columns*/
		cellA = colA->col;
		cellB = colB->col;
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

	if (isMatrixSameSize(a,b) == FALSE || isMatrixEmpty(a) || isMatrixEmpty(b))
	{
		printf("ERROR : wrong size\n");
		return NULL; /* error, we cant operate on the matrices */
	}
	else
	{
		rowElement* rowa = a->rows;
		cellElement* cella = NULL;
		rowElement* rowb = b->rows;
		cellElement* cellb = NULL;
		
		listMatrix* newel = (listMatrix*)malloc(sizeof(listMatrix));
		newel->n = a->rowCount; /* Definition of the size of the new matrix*/
		newel->p = b->colCount;
		newel->list = NULL;
			
		while(rowa!= NULL && rowb != NULL) /* until we reach the end of all the TRUES in a Matrix */
		{
			cella = rowa->row;
			cellb = rowb->row;

			if(rowa->rowN == rowb->rowN) /* if the two rows have the same index */
			{
				while(cella != NULL && cellb != NULL)
				{
					if (cella->colIndex > cellb->colIndex)
					{
						newel->list=insertTailPoints(cellb->rowIndex, cellb->colIndex, newel->list);
						cellb = cellb->nextRow;
					}
					else
					{
						if (cella->colIndex == cellb->colIndex)
						{
							newel->list=insertTailPoints(cellb->rowIndex, cellb->colIndex, newel->list);
							cellb = cellb->nextRow;
							cella = cella->nextRow;
						} 
						else /* cellb is ahead of cella */
						{
							newel->list=insertTailPoints(cella->rowIndex, cella->colIndex, newel->list);
							cella = cella->nextRow;
						}
					}
				}
				while(cella != NULL) /* rowb shorter than rowa */
				{
					newel->list=insertTailPoints(cella->rowIndex, cella->colIndex, newel->list);
					cella = cella->nextRow;
				}
				while(cellb != NULL)
				{
					newel->list=insertTailPoints(cellb->rowIndex, cellb->colIndex, newel->list);
					cellb = cellb->nextRow;
				}
				
				rowa = rowa->nextRow;	
				rowb = rowb->nextRow;
			}
			else /* the two rows arent corresponding */
			{
				if(rowa->rowN < rowb->rowN) /* rowb is ahead of rowa */
				{
					while(cella != NULL)
					{
						newel->list=insertTailPoints(cella->rowIndex, cella->colIndex, newel->list);
						cella = cella->nextRow;
					}
				rowa = rowa->nextRow;
				}
				else
				{
					while(cellb != NULL)
					{
						newel->list=insertTailPoints(cellb->rowIndex, cellb->colIndex, newel->list);
						cellb = cellb->nextRow;
					}
				rowb = rowb->nextRow;
				}
			}
		}

		while(rowa != NULL) /* now we've gone through every non zero cells of b */
		{
			cella = rowa->row;
			while(cella != NULL)
			{
				newel->list=insertTailPoints(cella->rowIndex, cella->colIndex, newel->list);
				cella = cella->nextRow;
			}
		rowa = rowa->nextRow;
		}
		while(rowb != NULL)
		{
			
			cellb = rowb->row;
			while(cellb != NULL)
			{
				newel->list=insertTailPoints(cellb->rowIndex, cellb->colIndex, newel->list);
				cellb = cellb->nextRow;
			}
		rowb = rowb->nextRow;
		}
		return newMatrix(newel);
	}
	
}


Matrix* mulMatrix(Matrix* A, Matrix* B)
{
	
	rowElement* row = A->rows;
	colElement* col = B->cols ;
	cellElement* rowCell = A->rows->row;
	cellElement* colCell = B->cols->col;
	listMatrix* newel = (listMatrix*)malloc(sizeof(listMatrix));

	newel->list = NULL; 
	if(A->colCount == B->rowCount )
	{
		newel->n = A->rowCount; /* Definition of the size of the new Matrix*/
		newel->p = B->colCount;
		
		while(row!= NULL) /* for each row of the matrix A*/
		{
			while(col!= NULL) /* For each columm*/
			{
				rowCell = row->row;
				colCell = col->col;
				while( rowCell != NULL && colCell != NULL) /* For 1 row and 1 columm*/
				{
					if (rowCell->colIndex == colCell->rowIndex)
					{
						newel->list = insertTailPoints(row->rowN,  col->colN, newel->list);
						colCell = NULL;
						rowCell = NULL;

					}else
					{
						if (rowCell->colIndex > colCell->rowIndex)
						{
							colCell = colCell-> nextCol;
						} 
						else 
						{
							rowCell = rowCell-> nextRow;
						}
					}
				}
			col = col->nextCol;	
			}
			row = row->nextRow;
			col = B->cols;
		}
	}else{
		printf("Error Matrix no compatible\n");
		newel->n = 0; /* Definition of the size of the new Matrix*/
		newel->p = 0;
		newel->list = NULL;
	}
	return newMatrix(newel);	
}

Matrix* newMatrix(listMatrix* m)
{
	Points* pt = m->list; /* the Points pointer toward the Points I am going to insert */
	Points* ptToFree = NULL; /* a pointer I use to free my Points list element by element */
	colElement* currCol = NULL; /* a pointer used to identify the current column I am working on, ie the one in which I am inserting a new cell */
	rowElement* currRow = NULL;  /* same but with row */
	cellElement* newCell = NULL; /* pointer to the new cell I am inserting in the Matrix */
	cellElement* currCell = NULL; /* a pointer I use to move in the Matrix */

	Matrix* newMat = (Matrix*)malloc(sizeof(Matrix)); /* I malloc my new Matrix and initialize everything*/
	newMat->colCount = m->p; 
	newMat->rowCount = m->n;
	newMat->cols = NULL;
	newMat->rows = NULL;

	/* I insert the cell elements defined by ths listPoints in m */

	if (pt == NULL) /* which means my list is empty. No one in the list. No ones in the Matrix*/
	{
		return newMat; /* no ones in this Matrix, then I return an empty Matrix. */
	}

	while(pt != NULL) /* If I have at least one element in m->list, I will start the traversal of the list */
	{
		/* my currCol and currRow initialized at the begining of the lists */
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
				currCol=currCol->nextCol;
			} 
		}

		/*I now insert a new element in this list*/
		newCell = (cellElement*)malloc(sizeof(cellElement)); /* I create a new element and I assign newCell (the pointer) to this cell */
		newCell->colIndex = pt->x;
		newCell->rowIndex = pt->y;
		newCell->nextRow = NULL;
		newCell->nextCol = NULL;

		/* either the col is empty, or it's not */
		if(currCol->col == NULL) /* then my newCell will be the only cell */
		{
			currCol->col = newCell;
		}
		else /* not empty */
		{
			/* either first, last, or in between */
			currCell = currCol->col;
			if(currCell->rowIndex > newCell->rowIndex) /* my newCell is the first */
			{
				newCell->nextCol = currCell;
				currCol->col = newCell;
			}
			else
			{
				while(currCell->nextCol != NULL && currCell->nextCol->rowIndex < newCell->rowIndex) /* I get the one right before newCell in the col */
				{
					currCell=currCell->nextCol;
				}
				/* currCell is right before newCell */
				if(currCell->nextCol == NULL) /* last element in the col */
				{
					currCell->nextCol = newCell;
				}
				else
				{
					newCell->nextCol = currCell->nextCol;
					currCell->nextCol = newCell; 
				}
			}
		}

		/* now that I have my new element in its column, I have to insert it in its row.
		I will first look for its row in the same way as the colunmn */
		while(currRow != NULL && currRow->rowN < newCell->rowIndex)
		{
			currRow=currRow->nextRow;
		}
		/* If the row doesnt exist, I create it */
		if(currRow == NULL || currRow->rowN > newCell->rowIndex)
		{
			newMat = insertRow(newMat, newCell->rowIndex);
			currRow=newMat->rows;
			while(currRow->rowN != newCell->rowIndex)
			{
				currRow=currRow->nextRow;
			}
		}
		/* now currRow is pointing toward the right row, and newCell is pointing toward the cellElement I want to insert in this row */
		currCell = currRow->row;
		if(currCell == NULL) /* if the row is empty */
		{
			currRow->row = newCell;
		}
		else/* if the row isnt empty, I will have currCell pointing toward the cell right before the newCell  */
		{
			if(currCell->colIndex > newCell->colIndex) /* this means my newCell is the new first element on the row*/
			{
				newCell->nextRow = currCell;
				currRow->row = newCell;
			}
			else /* either the last or in the middle */
			{
				while(currCell->nextRow != NULL && currCell->nextRow->colIndex < newCell->colIndex)
				/* this way we stop at the one right before where I should have my newCell */
				{
					currCell=currCell->nextRow;
				}
				/* currCell is now pointing toward the cell right before newCell */
				if(currCell->nextRow == NULL) /* if I stopped at the last cell in the row*/
				{
					currCell->nextRow = newCell;
				}
				else /* now I'm sure I will have to deal with having my newCell between two cells */
				{
					newCell->nextRow = currCell->nextRow;
					currCell->nextRow = newCell;
				}
			}

		}
		/* here my newCell is well included in the newMat 
		I can now advance to the next one and free the Points I just used*/
		ptToFree = pt;
		pt = pt->nextP;
		free(ptToFree);
	}	
	/* I now have included all the Points in my list in newMat */
	m->list = NULL;
	free(m);
	return newMat;
}


Matrix* andColSequenceOnMatrix(Matrix* m)
{
	listMatrix* newMat = (listMatrix*)malloc(sizeof(listMatrix)); /* we initialize a new listMatrix */
	if (isMatrixEmpty(m) != TRUE) /* If the matrix is Empty we do nothing*/
	{
		if(m->cols != NULL && m->cols->nextCol != NULL) /* if there are at least 2 columns in our Matrix */
		{
			
			colElement* fcol = m->cols; /*we initialize a pointer to the first columm*/
		 	colElement* scol = m->cols->nextCol; /*we initialize a pointer to the second columm*/
		 	cellElement* fcell = fcol->col; /*we initialize a pointer to the first cell of the first columm*/
		 	cellElement* scell = scol->col; /*we initialize a pointer to the first cell of the second columm*/
		 	newMat->list = NULL;
		 	newMat->n = m->rowCount;
		 	newMat->p = m->colCount -1;
		 	while(scol != NULL) /* we iterate until the last column*/
		 	{
		 		if (scol->colN == fcol->colN + 1) /* if scol and fcol are neighbours = if all our AND wont give us zeros*/
		 		{
		 			fcell = fcol->col; /* we set fcell as the first cell of fcol*/ 
		 			scell =	scol->col; /* we set scell as the fist element of scol*/
		 			while(scell != NULL && fcell != NULL) /* for each cell of the two columms we apply the boolean operation*/ 
		 			{
		 				if(fcell->rowIndex == scell->rowIndex) /* if AND gives us a TRUE*/
		 				{
		 					newMat->list = insertTailPoints(fcell->rowIndex, fcell->colIndex , newMat->list); /* we add this coordanate to the new matrix*/
		 					fcell = fcell->nextCol; /* we increment both of them */
		 					scell =	scell->nextCol;
		 				}
		 				else /* if theyre not equals then we have to increment the one which is most behind */
		 				{
		 					/* if fcell is the one most behind or if scell is already at the end of the column */
		 					if(fcell->rowIndex < scell->rowIndex)
		 					{
		 						fcell = fcell->nextCol; 
		 					}
		 					else
		 					{
		 						if(scell->rowIndex < fcell->rowIndex) /* not sure if this condition is necessary */
		 						{
		 							scell = scell->nextCol;
		 						}
		 					}
		 				}
		 			}/* if one of the cells is pointing to NULL then we know we are done with the columns anyway */
				}
		 		fcol = fcol->nextCol; /* we increment the two columms */
		 		scol = scol->nextCol; /* and now, if scol is NULL then we stop */
		 	}	
		}
		else /* if my Matrix isnt empty but theres only at most one column or less containing TRUEs*/
		{
			newMat->n = m->rowCount;
			newMat->p = m->colCount;
			newMat->list = NULL;
		}
	}
	else /* if the matrix is empty */
	{
	 	newMat->n = 0;
	 	newMat->p = 0;
	 	newMat->list = NULL;
	}
	return newMatrix(newMat); 
}

Matrix* orColSequenceOnMatrix(Matrix* m)
{
	listMatrix* newMat = (listMatrix*)malloc(sizeof(listMatrix)); /* we initialize a new listMatrix*/
	if (isMatrixEmpty(m)!= TRUE) /* If the matrix is Empty we do nothing*/
	{
		if(m->cols != NULL && m->cols->nextCol != NULL) /* if there are at least 2 columns in our Matrix */
		{
			colElement* fcol = m->cols; /*we initialize a pointer to the first columm*/
		 	colElement* scol = m->cols->nextCol; /*we initialize a pointer to the second columm*/
		 	cellElement* fcell = fcol->col; /*we initialize a pointer to the first cell of the first columm*/
		 	cellElement* scell = scol->col; /*we initialize a pointer to the first cell of the second columm*/
		 	newMat->n = m->rowCount;
		 	newMat->p = m->colCount -1;
		 	newMat->list = NULL;
		 	while(scol != NULL) /* we iterate until the last column*/
		 	{
		 		if (scol->colN == fcol->colN + 1) /* we test if the columm n+1 exist*/
	 			{
	 				fcell = fcol->col; /* we give the value of the first cell of the first columm*/ 
	 				scell =	scol->col; /* we give the value of the first cell of the second columm*/ 
	 				while(scell != NULL && fcell != NULL) /* for each cell of the two columms we apply the boolean operation*/ 
	 				{
	 					if (fcell->rowIndex == scell->rowIndex)
	 					{
	 						newMat->list = insertTailPoints(fcell->rowIndex, fcell->colIndex , newMat->list); /* we add this coordanate to the new matrix*/
	 						fcell = fcell->nextCol; /* we incremant both pointers */
	 						scell =	scell->nextCol;
	 					}
	 					else
	 					{	
	 						if(fcell->rowIndex < scell->rowIndex) /* if the the condition is not true we add the "latest" element pointed and we incremant the corresponding pointer */
	 						{
	 							newMat->list = insertTailPoints(fcell->rowIndex, fcell->colIndex , newMat->list);
	 							fcell = fcell->nextCol;
	 						}
	 						else
	 						{
								if(fcell->rowIndex > scell->rowIndex)
	 							{
	 								newMat->list = insertTailPoints(scell->rowIndex, scell->colIndex-1 , newMat->list);
	 								scell =	scell->nextCol;
	 							}
	 						}
	 					}
	 				}
		 			while(fcell != NULL) /* in the case where the first columm is longer than the second */
		 			{
		 				newMat->list = insertTailPoints(fcell->rowIndex, fcell->colIndex , newMat->list);
		 				fcell = fcell->nextCol;
		 			}
		 			while(scell != NULL) /* if the second is longer than the first*/
		 			{
		 				newMat->list = insertTailPoints(scell->rowIndex, scell->colIndex-1 , newMat->list);
		 				scell = scell->nextCol;
		 			}
		 		}
		 		else
		 		{
	 				while(fcell != NULL ) /* if the second columm is not the next of the first wa add at the new matrix all the cells of the first*/
	 				{
	 					newMat->list = insertTailPoints(fcell->rowIndex, fcell->colIndex , newMat->list);
	 					fcell = fcell->nextCol;
	 				}
	 			}
	 			fcol = scol; /* we incremant the two columm */
	 			scol = scol->nextCol;	
		 	}
		}
		else
		{
			if (m->cols != NULL)
			{
				cellElement* tmp = m->cols->col;
				newMat->n = m->rowCount;
		 		newMat->p = m->colCount -1;
				while( tmp != NULL)
				{
					newMat->list = insertTailPoints(tmp->rowIndex, tmp->colIndex , newMat->list);
	 				tmp = tmp->nextCol;
				}
			}
		}
	}
	else
	{
		newMat->n = 0;
		newMat->p = 0;
		newMat->list = NULL;
	}
	return newMatrix(newMat);
}

Matrix* andRowSequenceOnMatrix(Matrix* m)
{
	listMatrix* newMat = (listMatrix*)malloc(sizeof(listMatrix)); /* we initialize a new listMatrix */
	if (isMatrixEmpty(m) != TRUE) /* If the matrix is Empty we do nothing*/
	{
		if(m->rows != NULL && m->rows->nextRow != NULL) /* if there are at least 2 row in our Matrix */
		{

			rowElement* frow = m->rows; /*we initialize a pointer to the first col*/
		 	rowElement* srow = m->rows->nextRow; /*we initialize a pointer to the second col*/
		 	cellElement* fcell = frow->row; /*we initialize a pointer to the first cell of the first col*/
		 	cellElement* scell = srow->row; /*we initialize a pointer to the first cell of the second col*/
		 	newMat->n = m->rowCount-1;
		 	newMat->p = m->rowCount; 
		 	newMat->list = NULL;
		 	while(srow != NULL) /* we iterate until the last rowumn*/
		 	{
		 		if (srow->rowN == frow->rowN + 1) /* if srow and frow are neighbours = if all our AND wont give us zeros*/
		 		{
		 			fcell = frow->row; /* we set fcell as the first cell of frow*/ 
		 			scell =	srow->row; /* we set scell as the fist element of srow*/

		 			while(scell != NULL && fcell != NULL) /* for each cell of the two col we apply the boolean operation*/ 
		 			{
		 				if(fcell->colIndex == scell->colIndex) /* if AND gives us a TRUE*/
		 				{
		 					newMat->list = insertTailPoints(fcell->rowIndex, fcell->colIndex , newMat->list); /* we add this coordanate to the new matrix*/
		 					fcell = fcell->nextRow; /* we increment both of them */
		 					scell =	scell->nextRow;
		 				}
		 				else /* if theyre not equals then we have to increment the one which is most behind */
		 				{
		 					/* if fcell is the one most behind or if scell is already at the end of the rowumn */
		 					if(fcell->colIndex < scell->colIndex)
		 					{
		 						fcell = fcell->nextRow; 
		 					}
		 					else
		 					{
		 						if(scell->colIndex < fcell->colIndex) /* not sure if this condition is necessary */
		 						{
		 							scell = scell->nextRow;
		 						}
		 					}
		 				}
		 			}
		 		}
		 		/* if one of the cells is pointing to NULL then we know we are done with the rowumns anyway */
		 		frow = srow; /* we increment the two cols */
		 		srow = srow->nextRow; /* and now, if srow is NULL then we stop */
		 	}	 
		}
		else /* if my Matrix isnt empty but theres only at most one rowumn containing TRUEs*/
		{
			newMat->n = m->rowCount;
			newMat->p = m->colCount;
			newMat->list = NULL;
		}
	}
	else /* if the matrix is empty */
	{
	 	newMat->n = 0;
	 	newMat->p = 0;
	 	newMat->list = NULL;
	}
	return newMatrix(newMat); 
}


Matrix* orRowSequenceOnMatrix(Matrix* m)
{
	listMatrix* newMat = (listMatrix*)malloc(sizeof(listMatrix)); /* we initialize a array of the new matrix*/
	if (isMatrixEmpty(m)!= TRUE) /* If the matrix is Empty we do nothing*/
	{
		if(m->rows != NULL && m->rows->nextRow != NULL) /* if there are at least 2 rowumns in our Matrix */
		{
			rowElement* frow = m->rows; /*we initialize a pointer to the first col*/
		 	rowElement* srow = m->rows->nextRow; /*we initialize a pointer to the second col*/
		 	cellElement* fcell = frow->row; /*we initialize a pointer to the first cell of the first col*/
		 	cellElement* scell = srow->row; /*we initialize a pointer to the first cell of the second col*/
		 	newMat->n = m->rowCount-1;
		 	newMat->p = m->colCount;
		 	newMat->list = NULL; 
		 	while(srow != NULL) /* we iterate until the last rowumn*/
		 	{
		 		if (srow->rowN == frow->rowN + 1) /* we test if the col n+1 exist*/
	 			{

	 				fcell = frow->row; /* we give the value of the first cell of the first col*/ 
	 				scell =	srow->row; /* we give the value of the first cell of the second col*/ 
	 				while(scell != NULL && fcell != NULL) /* for each cell of the two col we apply the bolean operation*/ 
	 				{
	 					if (fcell->colIndex == scell->colIndex) /* we the if the condition is true*/
	 					{
	 						newMat->list = insertTailPoints(fcell->rowIndex, fcell->colIndex , newMat->list); /* we add this coordanate to the new matrix*/
	 						fcell = fcell->nextRow; /* we incremante the two case*/
	 						scell =	scell->nextRow;
	 					}else{	
	 						if(fcell->colIndex < scell->colIndex) /* if the the condition is not true we add and incremante the most little between the two col*/
	 						{
	 							newMat->list = insertTailPoints(fcell->rowIndex, fcell->colIndex , newMat->list);
	 							fcell = fcell->nextRow;
	 						}else{
								if(fcell->colIndex > scell->colIndex)
	 							{
	 								newMat->list = insertTailPoints(scell->rowIndex-1, scell->colIndex , newMat->list);
	 								scell =	scell->nextRow;
	 							}
	 						}
	 					}
	 				}
	 			while(fcell != NULL) /* in the case where the first col is longer to the second we continue to incrementa all of thier case*/
	 			{
	 				newMat->list = insertTailPoints(fcell->rowIndex, fcell->colIndex , newMat->list);
	 				fcell = fcell->nextRow;
	 			}
	 			while(scell != NULL) /* if the second is longer to the first*/
	 			{
	 				newMat->list = insertTailPoints(scell->rowIndex-1, scell->colIndex , newMat->list);
	 				scell = scell->nextRow;
	 			}
	 		}else{
	 				while(fcell != NULL ) /* if the second col is not the next of the first wa add at the new matrix all the case of this col*/
	 				{
	 					newMat->list = insertTailPoints(fcell->rowIndex, fcell->colIndex , newMat->list);
	 					fcell = fcell->nextRow;
	 				}
	 			}
	 		frow = srow; /* we incremante the two col */
	 		srow = srow->nextRow;	
		 	}
		}else{
			if (m->rows != NULL)
			{
				cellElement* tmp = m->rows->row;
				while( tmp != NULL)
				{
					newMat->list = insertTailPoints(tmp->rowIndex, tmp->colIndex , newMat->list);
	 				tmp = tmp->nextRow;
				}
			}
		}
	}else{
		newMat->n = 0;
		newMat->p = 0;
		newMat->list = NULL;
	}

	return newMatrix(newMat);
}

void freeMatrix(Matrix* m)
{
	if(isMatrixEmpty(m) != TRUE)
	{
		int i;
		for (i = 1; i <= m->rowCount; ++i)
		{
			m = removeRow(m, i);
		}			
	}
	free(m);
	m = NULL;
}

Matrix* randMatrix(int rowc, int colc, int seed)
{
	if(rowc > 0 && colc > 0 && seed >= 0)
	{
		listMatrix* lm = (listMatrix*)malloc(sizeof(listMatrix));
		Matrix* m = NULL;
		int i,j,r;
		r = 0;
		srand(seed);
		lm->n = rowc;
		lm->p = colc;
		lm->list = NULL;

		for(i=1;i<=rowc;++i)
		{
			for(j=1;j<=colc;++j)
			{

				r = rand()%2;
				if(r == 1)
				{
					lm->list = insertTailPoints(i,j,lm->list);
				}
			}
		}

		m = newMatrix(lm);

		return m;
	}
	 return NULL;
}

/* ----------------------------- applyrule ----------------------------- */


void transRight(Matrix* m)
{
	colElement* currCol = m->cols;
	cellElement* currCell = NULL;
	if(isMatrixEmpty(m) == FALSE)
	{
		while(currCol != NULL)
		{
			if(currCol->colN == m->colCount) /* if we are pointing to the last column (the rightest) which is also the rightest possible */
			{
				currCol = NULL;
				m = removeCol(m, m->colCount);
			}
			else
			{
				currCol = currCol->nextCol;
			}			
		}
		currCol = m->cols;
		while(currCol != NULL)
		{
			currCol->colN += 1;
			currCell = currCol->col;
			while(currCell != NULL)
			{
				currCell->colIndex += 1; 
				currCell = currCell->nextCol;
			}
			currCol = currCol->nextCol;
		}
	}
}


void transLeft(Matrix* m)
{
	colElement* currCol = m->cols;
	cellElement* currCell = NULL;
	if(isMatrixEmpty(m) == FALSE)
	{
		while(currCol != NULL)
		{
			if(currCol->colN == 1)
			{
				currCol = currCol->nextCol;
				m = removeCol(m, 1);
			}
			else
			{
				currCol->colN += -1;
				currCell = currCol->col;
				while(currCell !=NULL)
				{
					currCell->colIndex += -1;
					currCell = currCell->nextCol;
				}
				currCol = currCol->nextCol;
			}
		}
	}
}

void transUp(Matrix* m)
{
	rowElement* currRow = m->rows;
	cellElement* currCell = NULL;
	if(isMatrixEmpty(m) == FALSE)
	{
		while(currRow != NULL)
		{
			if(currRow->rowN == 1)
			{
				currRow = currRow->nextRow;
				m = removeRow(m, 1);
			}
			else
			{
				currRow->rowN += -1;
				currCell = currRow->row;
				while(currCell !=NULL)
				{
					currCell->rowIndex += -1;
					currCell = currCell->nextRow;
				}
				currRow = currRow->nextRow;
			}
		}
	}
}

void transDown(Matrix* m)
{
	rowElement* currRow = m->rows;
	cellElement* currCell = NULL;
	if(isMatrixEmpty(m) == FALSE)
	{
		/* we start by removing the last row */
		while(currRow != NULL)
		{
			if(currRow->rowN == m->rowCount)
			{
				m = removeRow(m, m->rowCount);
				currRow = NULL;
				
			}
			else
			{
				currRow = currRow->nextRow;
			}
		}
		currRow = m->rows;
		while(currRow != NULL)
		{
			currRow->rowN += 1;
			currCell = currRow->row;
			while(currCell != NULL)
			{
				currCell->rowIndex += 1; 
				currCell = currCell->nextRow;
			}
			currRow = currRow->nextRow;
		}
	}
}

BOOL isCellTrue(Matrix* m, int cellRow, int cellCol)
{
	colElement* currCol = NULL;
	cellElement* currCell = NULL;

	if(isMatrixEmpty(m))
	{
		return FALSE;
	}
	if(cellRow > m->rowCount || cellRow > m->colCount || cellRow < 1 || cellCol < 1) /* if the cell is outside the Matrix */
	{
		return FALSE; /* it's ok since we consider that extreme cells ar connected with logic-0 states */
	}
	currCol = m->cols;
	while(currCol != NULL && currCol->colN < cellCol)
	{
		currCol = currCol->nextCol;
	}
	if(currCol == NULL || currCol->colN > cellCol) /* if the column in which the cell should be doesnt exits */
	{
		return FALSE;
	}
	currCell = currCol->col;
	while(currCell != NULL && currCell->rowIndex < cellRow) 
	{
		currCell = currCell->nextCol;
	}
	if(currCell == NULL || currCell->rowIndex > cellRow) /* if the cell doesnt exist */
	{
		return FALSE;
	}
	return TRUE; /* here we are sure currCell has the same colIndex and rowIndex that the one we are looking for */
}

BOOL* decomposeRule(int rule)
{
	static BOOL decompose[9];
	int i;

	for(i=8;i>=0;--i)
	{
		decompose[i] = rule / (int)pow(2,i);
		rule = rule % (int)pow(2,i); 
	}

	return decompose;
}

BOOL xor(BOOL a, BOOL b)
{
	return((a == TRUE && b == FALSE) || (a == FALSE && b == TRUE));
}

BOOL applyRuleToCell(Matrix* m, int cellRow, int cellCol, BOOL* dRule)
{
	BOOL result = FALSE;

	/* if I try to apply a rule to a cell outside the bound of the Matrix */
	if(cellRow < 1 || cellCol < 1 || cellCol > m->colCount || cellRow > m->rowCount)
	{
		return result;
	}

	/* If my cell does exist, I will hard code every cases */
	/* reminder : if the cell given to isCellTrue is outside th Matrix, it will return FALSE. */
	if(dRule[0] == TRUE)
	{
		result = xor(result,isCellTrue(m,cellRow,cellCol));
	}

	if(dRule[1] == TRUE)
	{
		result = xor(result,isCellTrue(m,cellRow,cellCol+1));
	}
	if(dRule[2] == TRUE)
	{
		result = xor(result,isCellTrue(m,cellRow+1,cellCol+1));
	}
	
	if(dRule[3] == TRUE)
	{
		result = xor(result,isCellTrue(m,cellRow+1,cellCol));
	}
	
	if(dRule[4] == TRUE)
	{
		result = xor(result,isCellTrue(m,cellRow+1,cellCol-1));
	}
	
	if(dRule[5] == TRUE)
	{
		result = xor(result,isCellTrue(m,cellRow,cellCol-1));
	}
	
	if(dRule[6] == TRUE)
	{
		result = xor(result,isCellTrue(m,cellRow-1,cellCol-1));
	}
	
	if(dRule[7] == TRUE)
	{
		result = xor(result,isCellTrue(m,cellRow-1,cellCol));
	}
	
	if(dRule[8] == TRUE)
	{
		result = xor(result,isCellTrue(m,cellRow-1,cellCol+1));
	}
	
	return result;
}

Matrix* applyRules(Matrix* m, int rule, int times)
{
	if(isMatrixEmpty(m) == FALSE && rule >= 2 && rule <= 511) /* if it's empty we do nothing. if the rule doesnt exist we do nothing either. Rule 1 do nothing.*/
	{
		int i,k,l;
		BOOL* dRule;
		rowElement* currRow = NULL;
		cellElement* currCell = NULL; /* the pointer we will use to travel in the Matrix */
		listMatrix* newMat = NULL;
		listPoints listTrues = NULL;
		Matrix* tempMat = NULL;
		for(i=1;i<=times;++i) /* we apply the rule times times */
		{
			switch(rule)
			{	
				/* we start with cases corresponding to elementary rules */
				case 2 :
					transLeft(m);
					break;
				case 4 :
					transUp(m);
					transLeft(m);
					break;
				case 8 :
					transUp(m);
					break;
				case 16:
					transRight(m);
					transUp(m);
					break;
				case 32 :
					transRight(m);
					break;
				case 64 :
					transDown(m);
					transRight(m);
					break;
				case 128 :
					transDown(m);
					break;
				case 256 :
					transLeft(m);
					transDown(m);
					break;			
				/* the default case means we are using a complex rule */
				default :
					newMat = (listMatrix*)malloc(sizeof(listMatrix));
					listTrues = NULL;	
					dRule = decomposeRule(rule); /* we decompose our complex rule */
					currRow = m->rows; /* initiate a row pointer to the first row */
					newMat->n = m->rowCount;
					newMat->p = m->colCount;
					tempMat = m; /* to be on the safe side of things */
					while(currRow != NULL)
					{
						currCell = currRow->row; /* we begin our traversal of the row */
						while(currCell != NULL)
						{
							/* we now apply the rule to each and everycell of the row */
							/* if the rule return TRUE then we add the point to the list */
							if(applyRuleToCell(m,currCell->rowIndex, currCell->colIndex,dRule))
							{
								listTrues = insertTailPoints(currCell->rowIndex, currCell->colIndex, listTrues);
							}
							/* now comes the tricky part : 
							we know : a TRUE in a cell in the output iff there was at least one TRUE in the vicinity of this cell in the input.
							Thus, we will check every 8 cells in the vicinity of our current cell.
							If it's a TRUE, we wont test it since it will be done later with currCell.
							If it's a FALSE, then we can test it. */
							for(k=-1;k<2;++k) /* for the row before thru right after */
							{
								for(l=-1;l<2;++l) /* column -1 to column +1 */
								{
									if(isCellTrue(m,currCell->rowIndex + k,currCell->colIndex + l) == FALSE)
									{
										if(applyRuleToCell(m,currCell->rowIndex + k,currCell->colIndex + l, dRule))
										{
											/* if the rule check on this cell gives us TRUE we check if the list already contains this cell before adding it */
											if(containsPoints(currCell->colIndex + l, currCell->rowIndex + k, listTrues) == FALSE)
											{
												/* if it doesnt contains it we add it */
												listTrues = insertTailPoints(currCell->rowIndex + k, currCell->colIndex + l, listTrues);
											}
										}
									}
								}
							}
							/* now that we have tested this cell and its vicinity, we can now move to the next */
							currCell = currCell->nextRow;
						}
						/* and once at the end of the row we go to the next */
						currRow = currRow->nextRow;
					}
					/* now that we have a coplete list, we will complet our new listMatrix */
					newMat->list = listTrues;
					/* and to be homogenous with the behaviour of the reste of the function, we will update the input Matrix
					by freeing it and creating a new one */
					freeMatrix(tempMat);
					m = newMatrix(newMat);
					newMat = NULL;
			}/* end of the switch */
		}/* end of the for on times */
	}
	return m;
}
/* ----------------------------- Points ----------------------------- */

Points* insertTailPoints(int rowindex, int colindex, Points* newMat)
{
	Points* p = newMat;
	/*  we create the new element we will insert at the end*/ 
	Points* newElement = (Points*)malloc(sizeof(Points));
	newElement->x = colindex;
	newElement->y = rowindex;
	newElement->nextP = NULL;

	if(p == NULL) /* if we are going to insert the first element*/
	{
		return newElement;
	}

	while(p->nextP != NULL )
	{
		p=p->nextP;
	}

	p->nextP = newElement;
	return newMat;
}


BOOL containsPoints(int xval, int yval, Points* list)
{
	if(list == NULL)
	{
		return FALSE;
	}
	else
	{
		Points* currP = list;
		while(currP != NULL && (currP->x != xval || currP->y != yval))
		{
			currP = currP->nextP;
		}
		if(currP == NULL)
		{
			return FALSE;
		}
		else
		{
			return TRUE;
		}
	}
}

/*

listMatrix* listMatrixFrom2DArray(int nval, int pval,BOOL array[][pval])
{
	int nval, pval, i, j;
	listMatrix* newMat = NULL;
	Points* newlist = NULL; my list of points 
	newMat = (listMatrix*)malloc(sizeof(listMatrix));
	newMat->n = nval;
	newMat->p = pval;

	for(i = 0;i < nval;++i)
	{
		for(j=0;j<pval;++j)
		{
			if(array[i][j] == TRUE)
			{
				newlist = insertTailPoints(i+1,j+1,newlist);
			}
		}
	}

	newMat->list = newlist;

	return newMat;
}
*/