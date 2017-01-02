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
		listMatrix* lexp2 = (listMatrix*)malloc(sizeof(listMatrix));
		listMatrix* lexp3 = (listMatrix*)malloc(sizeof(listMatrix));
		Matrix* exp1 = NULL;
		Matrix* exp2 = NULL;
		Matrix* exp3 = NULL;

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
		printf("First example :");
		printMatrix(exp1);
		printf("We apply the rule 128 once:\n");
		exp1 = applyRules(exp1,128,1);
		printMatrix(exp1);

		/*second example*/
		lexp2->list = NULL;
		lexp2->n = 3;
		lexp2->p = 4;
		lexp2->list = insertTailPoints(1,4,lexp2->list);
		lexp2->list = insertTailPoints(2,3,lexp2->list);
		lexp2->list = insertTailPoints(2,4,lexp2->list);
		lexp2->list = insertTailPoints(3,4,lexp2->list);
		exp2 = newMatrix(lexp2);
		printf("Second example\n");
		printMatrix(exp2);
		printf("We apply the rule 3 once :\n");
		exp2 = applyRules(exp2,3,1);
		printMatrix(exp2);

		/* third example */

		lexp3->list = NULL;
		lexp3->n = 3;
		lexp3->p = 4;
		lexp3->list = insertTailPoints(1,3,lexp3->list);
		lexp3->list = insertTailPoints(2,1,lexp3->list);
		lexp3->list = insertTailPoints(2,2,lexp3->list);
		lexp3->list = insertTailPoints(2,3,lexp3->list);
		lexp3->list = insertTailPoints(3,1,lexp3->list);
		lexp3->list = insertTailPoints(3,3,lexp3->list);
		lexp3->list = insertTailPoints(3,4,lexp3->list);

		exp3 = newMatrix(lexp3);
		printf("Second example\n");
		printMatrix(exp3);
		printf("We apply the rule 170 once :\n");
		exp3 = applyRules(exp3,170,1);
		printMatrix(exp3);
		return 0;
	}

	if(argc > 5 && strcmp(argv[1],"rd")==0 && atoi(argv[2])>0 && atoi(argv[3])>0 && atoi(argv[4])>=0)
	{
		/* we will generate a random matrix and keep going. Else, we have nothing on which we can operate*/
		int row1,col1,seed;
		Matrix* rd1 = NULL;
		Matrix* disp = NULL;

		sscanf(argv[2],"%d",&row1);
		sscanf(argv[3],"%d",&col1);
		sscanf(argv[4],"%d",&seed);

		rd1 = randMatrix(row1,col1,seed);

		printMatrix(rd1);

		if(strcmp(argv[5],"acol")==0)
		{
			disp = andColSequenceOnMatrix(rd1);
			freeMatrix(rd1);
			printf("Applying andColSequenceOnMatrix on this Matrix:\n");
			printMatrix(disp);
		}
		if(strcmp(argv[5],"ocol")==0)
		{
			disp = orColSequenceOnMatrix(rd1);
			freeMatrix(rd1);
			printf("Applying orColSequenceOnMatrix on this Matrix:\n");
			printMatrix(disp);
		}
		if(strcmp(argv[5],"arow")==0)
		{
			disp = andRowSequenceOnMatrix(rd1);
			freeMatrix(rd1);
			printf("Applying andRowSequenceOnMatrix on this Matrix:\n");
			printMatrix(disp);		
		}
		if(strcmp(argv[5],"orow")==0)
		{
			disp = orRowSequenceOnMatrix(rd1);
			freeMatrix(rd1);
			printf("Applying orRowSequenceOnMatrix on this Matrix:\n");
			printMatrix(disp);			
		}
		if(strcmp(argv[5],"rule")==0)
		{
			if(argc > 6 && atoi(argv[6])>0 && atoi(argv[6])<=511 && atoi(argv[7]) >= 1)
			{
				rd1 = applyRules(rd1,atoi(argv[6]),atoi(argv[7]));
				printf("Aplying %s time(s) the rule %s:\n",argv[7],argv[6]);
				printMatrix(rd1);
				freeMatrix(rd1);
			}
			else
			{
				printf("WRONG ARGUMENT : <times> parameter must be >= 1\n");
			}
		}
		else
		{
			/* We will need another Matrix with its size constrained by the first one*/
			if(strcmp(argv[5],"sum")==0)
			{
				if(atoi(argv[6]) >= 0)
				{
					Matrix* rd2 = NULL;
					rd2 = randMatrix(row1,col1,atoi(argv[6]));
					printf("Second Matrix generated:\n");
					printMatrix(rd2);
					disp = sumMatrix(rd1,rd2);
					printf("Sum of these two Matrices :\n");
					printMatrix(disp);
					freeMatrix(rd1);
					freeMatrix(rd2);
					freeMatrix(disp);
				}
			}
			if(strcmp(argv[5],"mul")==0)
			{
				if(argc >= 9 && strcmp(argv[6],"rd")==0 && atoi(argv[7]) == col1 && atoi(argv[8])>0 && atoi(argv[9])>=0)
				{
					Matrix* rd2 = NULL;
					rd2 = randMatrix(atoi(argv[7]),atoi(argv[8]),atoi(argv[9]));
					printf("Second Matrix generated :\n");
					printMatrix(rd2);
					disp = mulMatrix(rd1,rd2);
					printf("Computing rd1 x rd2 :\n");
					printMatrix(disp);
					freeMatrix(disp);
					freeMatrix(rd1);
					freeMatrix(rd2);
				}
				else
				{
					printf("WRONG ARGUMENT : the second Matrix must have as many rows as the first has columns.\n");
				}
			}
		}				
		return 0;
	}

	/* help display */
	if(argc==2 && strcmp(argv[1],"help")==0)
	{
		printf("\nMatrix and cellular automata, UTBM, LO27, A16,\nby Yann Le CHevanton & William Veal Phan\n\n");
		printf("First argument must be\n\tdemo\n\t\tcompute some examples shown in the project descriptive\n\trd <rc> <cc> <seed>\n\t\tgenerates a Matrix with rc rows and cc columns from the seed\n");
		printf("After generating a random Matrix :\n\tacol | arow | ocol | orow \n\t\tcomputes andColSequenceOnMatrix, andRowSequenceOnMatrix,...\n\tsum <seed>\n\t\t computes the sum with another random Matrix of same size generated by its seed\n");
		printf("\tmul rd <rc> <cc> <seed>\n\t\tcomputes the multiplication with another randomely generated Matrix\n\trule <r> <t>\n\t\tapply t times the rule r to the Matrix previously declared\n");	
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
		printf("Size : %i rows, %i columns\n ", matrix->rowCount , matrix->colCount);
		for(i = 1;i<=matrix->colCount;++i)
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
		for(i = 1;i<=matrix->colCount;++i)
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