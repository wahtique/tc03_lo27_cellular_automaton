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
m->list = insertTailPoints(5, 5 , m->list);

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
	rowElement* tmprow = matrix->rows;
	cellElement* tmpcell = matrix->rows->row;	
	printf("Matrix: \n");
	for (i = 0; i < matrix->rowCount; ++i)
	{
		for (j = 0; j < matrix->colCount; ++i)
		{
			if(i==tmpcell->colIndex)
			{
				printf("X");
				tmpcell = tmpcell->nextRow;
			}else{
				printf("_");
			}
		}
		printf("|\n");
		tmprow = tmprow->nextRow;
	}
printf("Fin Matrix\n");
}