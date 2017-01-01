/*
File containing the C code for the project
Author : William Veal Phan (william.veal@utbm.fr) & Yann Le Chevanton (yann.le-chevanton@utbm.fr)
Creation date : 11/23/16
*/

/* ------------------ INCLUDES ------------------ */

#include <matrixLib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ------------------ PROTOTYPES ------------------  */

/*
print a matrix
@arg matrix : pointer to the Matrix we want to print
@result : nothing
*/
void printMatrix(Matrix* matrix);

/*
print a listMatrix
@arg m : pointer to the listMatrix we want to print
@result : nothing
*/
void printListMatrix(listMatrix* m);

/*
print the coordinates of the cells of a Matrix
@arg matrix : pointer to the Matrix we want to print
@result : nothing
*/
void printMatrixCoordinates(Matrix* m);
/* ------------------ MAIN ------------------ */


int main(int argc, char* argv[])
{
	if(argc==2 && strcmp(argv[1],"demo")==0)
	{
		/* declaration of our variables */

		listMatrix* lexp1 = (listMatrix*)malloc(sizeof(listMatrix));
		/*
		listMatrix* lexp2 = (listMatrix*)malloc(sizeof(lisMatrix));
		listMatrix* lexp3 = (listMatrix*)malloc(sizeof(lisMatrix));
		*/
		Matrix* exp1 = NULL;
		/*
		Matrix* exp2 = NULL;
		Matrix* exp3 = NULL;
		*/
		printf("\nThis is a demo : we will use our library to compute the examples of applyRule shown in the project descriptive :\n");
		/* first example */
		lexp1->list = NULL;
		lexp1->n = 3;
		lexp1->p = 4;
		lexp1->list = insertTailPoints(1,2,lexp1->list);
		lexp1->list = insertTailPoints(1,4,lexp1->list);
		lexp1->list = insertTailPoints(2,1,lexp1->list);
		lexp1->list = insertTailPoints(2,3,lexp1->list);
		lexp1->list = insertTailPoints(3,2,lexp1->list);
		exp1 = newMatrix(lexp1);
		printf("\nFirst example : \n");
		printMatrix(exp1);
		printf("\n We apply the rule 128 once:\n");
		exp1 = applyRules(exp1,128,1);
		printMatrix(exp1);
		return 0;

	}

	/* help display */
	if(argc==2 && strcmp(argv[1],"help")==0)
	{
		printf("\nhello\n");
		return 0;
	}
	printf("\nWRONG ARGUMENT : try \"help\" argument\n");
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