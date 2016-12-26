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
	}
	else
	{
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

			while(tmp->nextCol != NULL && index > tmp->colN) /* while we are not at the end and we are sure we are still not after where the new element should be*/
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


/*a refaire
Matrix* removeCol(Matrix* m, int index)
{
	cellElement* tmpEle= m->rows->row; 
	rowElement* tmpRow = m->rows;
	cellElement* cellRemove = m->rows->row;
	while(tmpRow!=NULL)
	{
		tmpEle= tmpRow->row;
		cellRemove = tmpEle;
		while(tmpEle!=NULL || tmpEle->nextCol->colIndex < index )
		{
			tmpEle = tmpEle->nextCol; 
		}
		if (tmpEle->nextCol->colIndex == index)
		{
			cellRemove= tmpEle->nextCol;
			tmpEle->nextCol = tmpEle->nextCol ->nextCol;
			free(cellRemove);
			m->colCount = m->colCount - 1;
		}
	}
	return m;

}*/



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

			while(tmp->nextRow != NULL && index > tmp->rowN) /* while we are not at the end and we are sure we are still not after where the new element should be*/
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
	if (isMatrixEmpty(m)!= TRUE && index < m->rowCount) /* we test if the row can be remove */
	{
		rowElement* rrow = m->rows;
		while(rrow->rowN <=index)
		{
			rrow = rrow->nextRow;
		}
		if (rrow->nextRow == index) /* test if the row exist*/
		{
			if(isRowEmpty(rrow)=! TRUE)
			{
				cellElement* tmpEle= m->cols->col;	
				colElement* tmpCol = m->cols;
				cellElement* cellRemove = m->cols->col;
				while(tmpCol!=NULL) /* we free each case of the row without break the structure*/
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
					}
				}
			}
			if (rrow->prevRow == NULL)
			{
				rrow->nextRow->prevRow = NULL;
				m->rows = rrow->nextRow;
			}else{
				if (rrow->nextRow == NULL)
				{
					rrow->prevRow->nextRow = NULL;
				}else{
						/* bricoler les ponts gerer si on remove toute la colonne, gerer si 1er de la liste*/
				}
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
	if (isMatrixSameSize(a,b) != TRUE)
	{
		return NULL; /* error, we cant operate on the matrices */
	}
	else
	{
		rowElement* rowa = a->rows;
		cellElement* cella = a->rows->row;
		rowElement* rowb = b->rows;
		cellElement* cellb = b->rows->row;

		Points* newMat = (Points*)malloc(sizeof(Points));
		arrayMatrix* newel = (arrayMatrix*)malloc(sizeof(arrayMatrix));

		newel->n = a->rowCount; /* Definition of the size of the new matrix*/
		newel->p = b->colCount;
			
		while(rowa!= NULL || rowb != NULL)
		{
			if(rowa->rowN == rowb->rowN)
			{
				while(cella->nextCol != NULL && cellb->nextCol != NULL)
				{
					if (cella->colIndex >= cellb->colIndex)
					{
						newMat=insertTailPoints(cellb->colIndex, cellb->rowIndex, newMat);
						cellb = cellb->nextCol;
					}
					else
					{
						if (cella->colIndex >= cellb->colIndex)
						{
							newMat = insertTailPoints(cellb->colIndex, cellb->rowIndex, newMat);
							cellb = cellb->nextCol;
							cella = cella-> nextCol;
						} 
						else
						{
							insertTailPoints(cella->colIndex, cella->rowIndex, newMat);
							cella = cella->nextCol;
						}
					}
				}	
				rowa = rowa->nextRow;
				rowb = rowb->nextRow;
			}
			else
			{
				if(rowa->rowN < rowb->rowN)
				{
					rowa = rowa->nextRow;
				}
				else
				{
					rowb = rowb->nextRow;
				}

			}
	
		}
		newel->list = newMat;
	return newMatrix(newel);
	}
	
}


Matrix* mulMatrix(Matrix* A, Matrix* B)
{
	
	rowElement* row = A->rows;
	colElement* col = B->cols ;
	cellElement* rowCell = A->rows->row;
	cellElement* colCell = B->cols->col;

	Points* newMat = (Points*)malloc(sizeof(Points));
	arrayMatrix* newel = (arrayMatrix*)malloc(sizeof(arrayMatrix));
	if(A->colCount == B->rowCount )
	{
		newel->n = A->rowCount; /* Definition of the size of the new Matrix*/
		newel->p = B->colCount;
		while(row!= NULL)
		{
			while(col!= NULL)
			{
				while( rowCell!=NULL && colCell!=NULL && rowCell->colIndex == colCell->rowIndex ) /* For 1 row and 1 columm*/
				{
					if (rowCell->colIndex == colCell->rowIndex)
					{
						newMat = insertTailPoints(rowCell->colIndex,  colCell->rowIndex, newMat);
					}
					if (rowCell->rowIndex > colCell->colIndex)
					{
						colCell = colCell-> nextCol;
					} 
					else 
					{
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
				currCol=currCol->nextCol;
			} 
		}

		/*I now insert a new element in this list*/
		newCell = (cellElement*)malloc(sizeof(cellElement)); /* I create a new element and I assign newCell (the pointer) to this cell */
		newCell->colIndex = pt->x;
		newCell->rowIndex = pt->y;

		/* either the col is empty, or it's not */
		if(currCol->col == NULL) /* then my newCell will be the only cell */
		{
			currCol->col = newCell;
			newCell->nextCol = NULL;
		}
		else /* not empty then */
		{
			/* either first, last, or in between */
			currCell = currCol->col;
			if(currCell->rowIndex > newCell->colIndex) /* my newCell is the first */
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
					newCell->nextCol = NULL;
					currCell->nextCol = newCell;
				}
				else
				{
					newCell->nextCol = currCell->nextCol;
					currCell->nextCol = newCell; 
				}
			}
		}

		/* now that I have my new element in its column, I have to inser it in its row.
		I will first look for its row in the same way as the colunmn */
		while(currRow != NULL && currRow->rowN < newCell->rowIndex)
		{
			currRow=currRow->nextRow;
		}
		/* If the row doesnt exist, I create it */
		if(currRow == NULL || currRow->rowN > newCell->rowIndex)
		{
			newMat =insertRow(newMat, newCell->rowIndex);
			currRow=newMat->rows;
			while(currRow->rowN != newCell->rowIndex)
			{
				currRow=currRow->nextRow;
			}
		}
		/* now currRow is pointing toward my the right row, and newCell is pointing toward the cellElement I want to insert in this row */
		currCell = currRow->row;
		if(currCell == NULL) /* if the row is empty */
		{
			currRow->row = newCell;
			newCell->nextRow = NULL;
		}
		else/* if the row isnt empty, I will have currCell pointing toward the cell right before the newCell  */
		{
			if(currCell->rowIndex > newCell->colIndex) /* this means my newCell is the new first element on the row*/
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
					newCell->nextRow = NULL;
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
	return newMat;
}


Matrix* andColSequenceOnMatrix(Matrix* m)
{
	arrayMatrix* newMat = (arrayMatrix*)malloc(sizeof(arrayMatrix)); /* we initialize a new arrayMatrix */
	if (isMatrixEmpty(m) != TRUE) /* If the matrix is Empty we do nothing*/
	{
	 	
		if(m->cols != NULL && m->cols->nextCol != NULL) /* if there are at least 2 columns in our Matrix */
		{
			colElement* fcol = m->cols; /*we initialize a pointer to the first columm*/
		 	colElement* scol = m->cols->nextCol; /*we initialize a pointer to the second columm*/
		 	cellElement* fcell = fcol->col; /*we initialize a pointer to the first cell of the first columm*/
		 	cellElement* scell = scol->col; /*we initialize a pointer to the first cell of the second columm*/
		 	newMat->n = m->rowCount;
		 	newMat->p = m->colCount -1; 
		 	while(scol != NULL) /* we iterate until the last column*/
		 	{
		 		if (scol->colN == fcol->colN + 1) /* if scol and fcol are neighbours = if all our AND wont give us zeros*/
		 		{
		 			fcell = fcol->col; /* we set fcell as the first cell of fcol*/ 
		 			scell =	scol->col; /* we set scell as the fist element of scol*/

		 			while(scell != NULL && fcell != NULL) /* for each cell of the two columm we apply the boolean operation*/ 
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
		 			fcol = scol; /* we increment the two columms */
		 			scol = scol->nextCol; /* and now, if scol is NULL then we stop */
		 		}
		 	}	 
		}
		else /* if my Matrix isnt empty but theres only at most one column containing TRUEs*/
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
	arrayMatrix* newMat = (arrayMatrix*)malloc(sizeof(arrayMatrix)); /* we initialize a array of the new matrix*/
	if (isMatrixEmpty(m)!= TRUE) /* If the matrix is Empty we do nothing*/
	{
	 	colElement* fcol = m->cols; /*we initialize a pointeur to the first columm*/
	 	colElement* scol = m->cols->nextCol; /*we initialize a pointeur to the second columm*/
	 	cellElement* fcell = fcol->col; /*we initialize a pointeur to the first cell of the first columm*/
	 	cellElement* scell = scol->col; /*we initialize a pointeur to the first cell of the second columm*/
	 	newMat->n = m->rowCount;
	 	newMat->p = m->colCount -1; 
	 	while(scol != NULL) /* we test all of the columm*/
	 	{
	 		if (scol->colN == fcol->colN + 1) /* we test if the columm n+1 exist*/
	 		{
	 			fcell = fcol->col; /* we give the value of the first cell of the first columm*/ 
	 			scell =	scol->col; /* we give the value of the first cell of the second columm*/ 
	 			while(scell != NULL || fcell != NULL) /* for each cell of the two columm we apply the bolean operation*/ 
	 			{
	 				if (fcell->rowIndex == scell->rowIndex) /* we the if the condition is true*/
	 				{
	 					newMat->list = insertTailPoints(fcell->rowIndex, fcell->colIndex , newMat->list); /* we add this coordanate to the new matrix*/
	 					fcell = fcell->nextCol; /* we incremante the two case*/
	 					scell =	scell->nextCol;
	 				}else{	
	 					if(fcell->rowIndex < scell->rowIndex) /* if the the condition is not true we add and incremante the most little between the two columm*/
	 					{
	 						newMat->list = insertTailPoints(fcell->rowIndex, fcell->colIndex , newMat->list);
	 						fcell = fcell->nextCol;
	 					}else{
	 						if(fcell->rowIndex > scell->rowIndex)
	 						{
	 							newMat->list = insertTailPoints(scell->rowIndex, scell->colIndex , newMat->list);
	 							scell =	scell->nextCol;
	 						}
	 					}
	 				}
	 			}
	 			while(fcell != NULL) /* in the case where the first columm is longer to the second we continue to incrementa all of thier case*/
	 			{
	 				newMat->list = insertTailPoints(fcell->rowIndex, fcell->colIndex , newMat->list);
	 				fcell = fcell->nextCol;
	 			}
	 			while(scell != NULL) /* if the second is longer to the first*/
	 			{
	 				newMat->list = insertTailPoints(scell->rowIndex, scell->colIndex , newMat->list);
	 				scell = scell->nextCol;
	 			}
	 		}else{
	 				while(fcell != NULL ) /* if the second columm is not the next of the first wa add at the new matrix all the case of this columm*/
	 				{
	 					newMat->list = insertTailPoints(fcell->rowIndex, fcell->colIndex , newMat->list);
	 					fcell = fcell->nextCol;
	 				}
	 			}
	 		fcol = scol; /* we incremante the two columm */
	 		scol = scol->nextCol;	
	 	}
	}
	else
	{
	 	newMat-> n = 0;
	 	newMat-> p = 0;
	 	newMat-> list =NULL;
	}
	return newMatrix(newMat); 
}

Matrix* andRowSequenceOnMatrix(Matrix* m)
{
	arrayMatrix* newMat = (arrayMatrix*)malloc(sizeof(arrayMatrix)); /* we initialize a array of the new matrix*/
	if (isMatrixEmpty(m)!= TRUE) /* If the matrix is Empty we do nothing*/
	{
	 	rowElement* frow = m->rows; /*we initialize a pointeur to the first columm*/
	 	rowElement* srow = m->rows->nextRow; /*we initialize a pointeur to the second columm*/
	 	cellElement* fcell = frow->row; /*we initialize a pointeur to the first cell of the first columm*/
	 	cellElement* scell = srow->row; /*we initialize a pointeur to the first cell of the second columm*/
	 	newMat->n = m->rowCount -1;
	 	newMat->p = m->colCount; 
	 	while(srow->nextRow != NULL) /* we test all of the columm*/
	 	{
	 		if (srow->rowN == frow->rowN + 1) /* we test if the columm n+1 exist*/
	 		{
	 			fcell = frow->row; /* we give the value of the first cell of the first columm*/ 
	 			scell =	srow->row; /* we give the value of the first cell of the second columm*/ 
	 			while(scell->nextCol != NULL || fcell->nextCol != NULL) /* for each cell of the two columm we apply the bolean operation*/ 
	 			{
	 				while(fcell->colIndex == scell->colIndex) /* we the if the condition is true*/
	 				{
	 					newMat->list = insertTailPoints(fcell->rowIndex, fcell->colIndex , newMat->list); /* we add this coordanate to the new matrix*/
	 					fcell = fcell->nextCol; /* we incremante the two case*/
	 					scell =	scell->nextCol;
	 				}
	 				while(fcell->colIndex < scell->colIndex)
	 				{
	 					fcell = fcell->nextCol;
	 				}
	 				while(fcell->colIndex > scell->colIndex)
	 				{
	 					scell =	scell->nextCol;
	 				}
	 			}
	 		frow = srow; /* we incremante the two columm */
	 		srow = srow->nextRow;	
	 		}
		} 
	}
	else
	{
	 	newMat-> n = 0;
	 	newMat-> p = 0;
	 	newMat-> list =NULL;
	}
	return newMatrix(newMat); 
}

Matrix* orRowSequenceOnMatrix(Matrix* m)
{
	arrayMatrix* newMat = (arrayMatrix*)malloc(sizeof(arrayMatrix)); /* we initialize a array of the new matrix*/
	if (isMatrixEmpty(m)!= TRUE) /* If the matrix is Empty we do nothing*/
	{
	 	rowElement* frow = m->rows; /*we initialize a pointeur to the first rowumm*/
	 	rowElement* srow = m->rows->nextRow; /*we initialize a pointeur to the second rowumm*/
	 	cellElement* fcell = frow->row; /*we initialize a pointeur to the first cell of the first rowumm*/
	 	cellElement* scell = srow->row; /*we initialize a pointeur to the first cell of the second rowumm*/
	 	newMat->n = m->rowCount;
	 	newMat->p = m->rowCount -1; 
	 	while(srow->nextRow != NULL) /* we test all of the rowumm*/
	 	{
	 		if (srow->rowN == frow->rowN + 1) /* we test if the rowumm n+1 exist*/
	 		{
	 			fcell = frow->row; /* we give the value of the first cell of the first rowumm*/ 
	 			scell =	srow->row; /* we give the value of the first cell of the second rowumm*/ 
	 			while(scell != NULL && fcell != NULL) /* for each cell of the two rowumm we apply the bolean operation*/ 
	 			{
	 				while(fcell->rowIndex == scell->rowIndex) /* we the if the condition is true*/
	 				{
	 					newMat->list = insertTailPoints(fcell->rowIndex, fcell->colIndex , newMat->list); /* we add this coordanate to the new matrix*/
	 					fcell = fcell->nextRow; /* we incremante the two case*/
	 					scell =	scell->nextRow;
	 				}
	 				while(fcell->rowIndex < scell->rowIndex)
	 				{
	 					newMat->list = insertTailPoints(fcell->rowIndex, fcell->colIndex , newMat->list);
	 					fcell = fcell->nextRow;
	 				}
	 				while(fcell->rowIndex > scell->rowIndex)
	 				{
	 					newMat->list = insertTailPoints(fcell->rowIndex, fcell->colIndex , newMat->list);
	 					scell =	scell->nextRow;
	 				}
	 			}
	 			while(fcell != NULL )
	 			{
	 				newMat->list = insertTailPoints(fcell->rowIndex, fcell->colIndex , newMat->list);
	 				fcell = fcell->nextRow;
	 			}
	 			while(fcell != NULL )
	 			{
	 				newMat->list = insertTailPoints(scell->rowIndex, scell->colIndex-1 , newMat->list);
	 				scell = scell->nextRow;
	 			}
	 		}
	 		frow = srow; /* we incremante the two columm */
	 		srow = srow->nextRow;	
	 	}
	}
	else
	{
	 	newMat-> n = 0;
	 	newMat-> p = 0;
	 	newMat-> list =NULL;
	}
	return newMatrix(newMat); 
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
