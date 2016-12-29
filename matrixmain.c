/*
File containing the C code for the project
Author : William 
Creation date : 11/23/16
*/

/* INCLUDES */

#include <matrixLib.h>
#include <stdio.h>
#include <stdlib.h>


/* PROTOTYPES OF FUNCTIONS PERTAINING TO GRAPHICAL INTERFACE */

void printMatrix(Matrix* matrix);
void printArray(arrayMatrix* m);

int main()
{
/* definition of variables*/
arrayMatrix* m = (arrayMatrix*)malloc(sizeof(arrayMatrix));
Matrix* matrix = (Matrix*)malloc(sizeof(Matrix));


/*initialisation of the matrix*/

m->n = 5;
m->p = 5;
m->list = insertTailPoints(2, 1 , m->list);
m->list = insertTailPoints(3, 1 , m->list);
m->list = insertTailPoints(4, 2 , m->list);
m->list = insertTailPoints(5, 4 , m->list);
printf("Matrix Initialiser\n");
printArray(m);

/*Fonction tested:*/

matrix = newMatrix(m);

/*Result*/
printMatrix(matrix);
return 0;
}

void printMatrix(Matrix* matrix)
{
	int i;
	int j;
	if (isMatrixEmpty(matrix) != TRUE)
	{
		rowElement* tmprow = matrix->rows;
		cellElement* tmpcell = matrix->rows->row;	
		printf("Matrix [%i, %i]: \n", matrix->rowCount , matrix->colCount);
		for (i = 0; i < matrix->rowCount; ++i)
		{
			printf(" |");
			if (i == tmprow->rowN)
			{
				for (j = 0; j < matrix->colCount; ++j)
				{
					if(j==tmpcell->colIndex)
					{
						printf("X");
						if(tmpcell->nextRow != NULL)
						{
							tmpcell = tmpcell->nextRow;
						}
					}else{
						printf("_");
					}
				}
			}else{
				for (j = 0; j < matrix->colCount; ++j)
				{
					printf("_");
				}
			}
			printf("|\n");
			if (tmprow->nextRow != NULL)
			{
				tmprow = tmprow->nextRow;
			}
		}
	}else{
		printf("Matrix Vide\n");
	}
printf("Fin Matrix\n");
}

void printArray(arrayMatrix* m)
{
	if(m->list !=NULL)
	{
		Points* plist = m->list; 
		printf("Size matrix = [%i, %i] \n", m->n, m->p);
		while(plist!=NULL)
		{
			printf("[%i,%i]\n",m->n,m->p);
			plist =plist->nextP;
		}
	}
}