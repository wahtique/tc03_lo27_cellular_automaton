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

listPoints t = NULL;
listMatrix* tList = (listMatrix*)malloc(sizeof(listMatrix));
Matrix* test = NULL;
int r = 170;

printf("\n2d arrays initialised\n");

tList->n = 3;
tList->p = 4;
printf("dimensions ok \n");
t = insertTailPoints(1,3,t);
t = insertTailPoints(2,1,t);
t = insertTailPoints(2,2,t);
t = insertTailPoints(2,3,t);
t = insertTailPoints(3,1,t);
t = insertTailPoints(3,3,t);
t = insertTailPoints(3,4,t);
tList->list = t;

printf("t affected to tList\n");



/* Tested functions : */
test = newMatrix(tList);
printMatrix(test);


/*Result*/
r = 170;
test = applyRules(test,r,1);

printf("Applied rule %i \n", r);
printMatrix(test);
/*
testCell = applyRuleToCell(test,3,4,decomposeRule(170));
printf("test on cell 3 4 = %i", testCell);*/
/* Clean up */

freeMatrix(test);

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