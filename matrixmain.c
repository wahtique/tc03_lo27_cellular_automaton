/*
File containing the C code for the project
Author : William Veal Phan (william.veal@utbm.fr) & Yann Le Chevanton (yann.le-chevanton@utbm.fr)
Creation date : 11/23/16
*/

/* ------------------ INCLUDES ------------------ */

#include <matrixLib.h>
#include <stdio.h>
#include <stdlib.h>


/* ------------------ PROTOTYPES ------------------  */

void printMatrix(Matrix* matrix);
void printListMatrix(listMatrix* m);
void printMatrixCoordinates(Matrix* m);
/* ------------------ MAIN ------------------ */


int main()
{
/* definition of variables*/
listMatrix* m = (listMatrix*)malloc(sizeof(listMatrix));
listMatrix* id = (listMatrix*)malloc(sizeof(listMatrix));
Matrix* matrix = (Matrix*)malloc(sizeof(listMatrix));
Matrix* identite = (Matrix*)malloc(sizeof(listMatrix));
Matrix* summ = (Matrix*)malloc(sizeof(listMatrix));

/*initialisation of the matrix*/

m->n = 5;
m->p = 5;
m->list = insertTailPoints(1, 1 , m->list);
m->list = insertTailPoints(1, 4 , m->list);
m->list = insertTailPoints(2, 1 , m->list);
m->list = insertTailPoints(3, 5 , m->list);
m->list = insertTailPoints(5, 2 , m->list);
m->list = insertTailPoints(4, 2 , m->list);
m->list = insertTailPoints(4, 3 , m->list);
m->list = insertTailPoints(2, 3 , m->list);
m->list = insertTailPoints(4, 1 , m->list);
m->list = insertTailPoints(3, 2 , m->list);
m->list = insertTailPoints(2, 2 , m->list);
m->list = insertTailPoints(1, 5 , m->list);

id->n = 5;
id->p = 5;
id->list = insertTailPoints(1, 1 , id->list);
id->list = insertTailPoints(2, 2 , id->list);
id->list = insertTailPoints(3, 3 , id->list);
id->list = insertTailPoints(4, 4 , id->list);
id->list = insertTailPoints(5, 5 , id->list);
printf("Matrix Initialised\n");

/* definition of variables*/
matrix = newMatrix(m);
identite = newMatrix(id);
printMatrix(matrix);
printMatrix(identite);
summ = mulMatrix(matrix , identite);	


printMatrix(summ);


/* Clean up */

freeMatrix(matrix);
printf("matrix freed \n");
freeMatrix(identite);
printf("identite freed \n");
freeMatrix(summ);
printf("summ freed \n");
printf("Done\n");
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
		cellElement* tmpcell = NULL;	
		printf("\nPrinting a Matrix of %i rows and %i columns : \n ", matrix->rowCount , matrix->colCount);
		for(i = 1;i<=matrix->rowCount;++i)
		{
			printf("-");
		}
		printf("\n");
		for(i = 1; i <= matrix->rowCount; ++i)
		{
			printf("|");
			if(tmprow != NULL && i == tmprow->rowN)/* if the row we want to print isnt empty */
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
						printf(" ");
					}
				}
				tmprow = tmprow->nextRow; /* if we printed this row then we can move the pointer to the next nonempty row */
			}
			else
			{
				for (j =1; j <= matrix->colCount; ++j)
				{
					printf(" ");
				}
			}
			printf("|\n");
		}
		printf(" ");
		for(i = 1;i<=matrix->rowCount;++i)
		{
			printf("-");
		}
		printf("\n");
	}
	else
	{
		printf("Error : Empty Matrix\n");
	}
printf("\n");
}

void printLisMatrix(listMatrix* m)
{
	if(m->list !=NULL)
	{
		Points* plist = m->list; 
		printf("\nPrinting a listMatrix of %i rows and %i columns :  \n", m->n, m->p);
		while(plist!=NULL)
		{
			printf("[%i,%i]\n",plist->y,plist->x);
			plist =plist->nextP;
		}
	}
	else
	{
		printf("Error : empty listMatrix");
	}
}

void printMatrixCoordinates(Matrix* m)
{
	rowElement* currRow =m->rows;
	cellElement* currCell =NULL;
	while(currRow != NULL)
	{
		currCell = currRow->row;
		while(currCell != NULL)
		{
			printf("(%i,%i) ", currCell->rowIndex, currCell->colIndex);
			currCell = currCell->nextRow;
		}
		printf("\n");
		currRow = currRow->nextRow;
	}
}