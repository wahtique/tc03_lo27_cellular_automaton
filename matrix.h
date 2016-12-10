/*
File containing the prototypes of the functions pertaining to the matrix data type
Author : William 
Creation date : 11/23/16
*/

#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
/*
THE Matrix structure
	colcount : integer indicating the number of columns the Matrix contains
	rowCount : integer indicating the number of rows the Matrix contains
	cols : a pointer toward the first element of the list of colElement representing the columns of the Matrix
	rows : a pointer toward the first element of the list of rowElement representing the rows of the Matrix
*/
typedef struct
{
	int colCount;
	int rowCount;
	colElement* cols;
	rowElement* rows;
}Matrix;

/*
Our array based matrix representation.
	list : a linked list ( pointer toward the first element ) of the coordinates of the ones in our matrix
	n : number of rows in the mqtrix
	p : number of columns in the matrix
*/
typedef struct 
{
	listPoints list;
	int n,p;
}arrayMatrix;

/*
Function creating a new Matrix from its arrayMatrix representation
@arg m : the arrayMatrix representation of our Matrix
@return : a pointer to the new Matrix
*/
Matrix* newMatrix(arrayMatrix* m);

/*
Function displaying a Matrix given as argument
@arg m : pointer to the matrix de display
@return : nothing
*/
void printMatrix(Matrix* m);

/*
Function verifying if a matrix is empty, which means the Matrix is NULL or it has no rows and no columns
Having sparse matrices, any Matrix with more than zero columns and zero rows isnt empty
@arg m : pointer to the matrix we want to check
@return : a boolean, TRUE if it is and FALSE if not
*/
BOOL isMatrixEmpty(Matrix* m);

/*
Function sayin if a matrix is square
@arg m : pointer to the Matrix we want to check
@return : a boolean
*/
BOOL isMatrixSquare(Matrix* m);

/*
Function saying if two matrices are equals
@arg A : pointer to the first Matrix
@arg B : pointer to the second Matrix
@return : a boolean
*/
BOOL equalsMatrix(Matrix* A, Matrix* B);

/*
A function computing the sum of two Matrix
@arg A : pointer to the first Matrix
@arg B : pointer to the second Matrix
@return : a pointer to a new Matrix
*/
Matrix* sumMatrix(Matrix A, Matrix B);

/*
THE function ( I heard they didnt have it in LO21. This is unfair. UNFAIR.)
Apply the rule(s) specified to the Matrix specified.
@arg M : a pointer toward the Matrix on whoch we want to operate
@arg rule : the rule we want to apply, must be between 1 ( do nothing ) and 511 ( every rules )
@arg times : the number of times we want to apply it
@return : a pointer toward a the new Matrix created.
*/
Matrix* applyRules(Matrix* m, int rule, int times);

#endif