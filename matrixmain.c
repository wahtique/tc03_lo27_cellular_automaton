/*
File containing the C code for the project
Author : William 
Creation date : 11/23/16
*/

/* ------------------ INCLUDES ------------------ */

#include <matrixLib.h>
#include <stdio.h>
#include <stdlib.h>


/* ------------------ PROTOTYPES ------------------  */

void printMatrix(Matrix* matrix);
void printArrayMatrix(arrayMatrix* m);

/* ------------------ MAIN ------------------ */


int main()
{
/* definition of variables*/
arrayMatrix* m = (arrayMatrix*)malloc(sizeof(arrayMatrix));
Matrix* matrix = (Matrix*)malloc(sizeof(Matrix));
Matrix* andmatrix = (Matrix*)malloc(sizeof(Matrix));

/*initialisation of the matrix*/

m->n = 5;
m->p = 5;
m->list = insertTailPoints(1, 1 , m->list);
m->list = insertTailPoints(2, 1 , m->list);
m->list = insertTailPoints(2, 2 , m->list);
m->list = insertTailPoints(5, 5 , m->list);
printf("Matrix Initialised\n");
printArrayMatrix(m);

/* Tested functions : */

matrix = newMatrix(m);

andmatrix = orRowSequenceOnMatrix(matrix);

/* Result */

printf("The cell 2,4 is %i",isCellTrue(matrix,2,4));
printMatrix(matrix);
printf("Test And col Sequence:\n");
printMatrix(andmatrix);
return 0;
}


/* ------------------ INTERFACE FUNCTIONS ------------------ */


void printMatrix(Matrix* matrix)
{
	int i;
	int j;
	if (isMatrixEmpty(matrix) != TRUE)
	{
		rowElement* tmprow = matrix->rows;
		cellElement* tmpcell = matrix->rows->row;	
		printf("\nPrinting a Matrix of %i rows and %i columns : \n", matrix->rowCount , matrix->colCount);
		for (i = 1; i <= matrix->rowCount; ++i)
		{
			printf(" |");
			if (tmprow != NULL && i == tmprow->rowN)/* if the row we want to print isnt empty */
			{
				tmpcell = tmprow->row;
				for (j = 1; j <=  matrix->colCount; ++j)
				{
					if(tmpcell != NULL && j==tmpcell->colIndex)
					{
						printf("X");
						tmpcell = tmpcell->nextRow;
					}
					else
					{
						printf(".");
					}
				}
				tmprow = tmprow->nextRow; /* if we printed this row then we can move the pointer to the next nonempty row */
			}
			else
			{
				for (j =1; j <= matrix->colCount; ++j)
				{
					printf(".");
				}
			}
			printf("|\n");
		}
	}
	else
	{
		printf("Error : Empty Matrix\n");
	}
printf("\n");
}

void printArrayMatrix(arrayMatrix* m)
{
	if(m->list !=NULL)
	{
		Points* plist = m->list; 
		printf("\nPrinting an arrayMatrix of %i rows and %i columns :  \n", m->n, m->p);
		while(plist!=NULL)
		{
			printf("[%i,%i]\n",plist->y,plist->x);
			plist =plist->nextP;
		}
	}
	else
	{
		printf("Error : empty arrayMatrix");
	}
}