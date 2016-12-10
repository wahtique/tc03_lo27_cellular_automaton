/*
File containing all the functions manipulating a matrix
Author : William
Date : 09/12/16
*/

#ifndef MATRIXLIB_H_INCLUDED
#define MATRIXLIB_H_INCLUDED

#include <matrix.h>
/* CELL */

/* ROWS */



/* COLS */


BOOL isColEmpty(colElement* col);


/* MATRIX */

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

Points* insertTailPoints( int rowindex,  int colIndex, Points* list);

#endif