/*
File containing all the functions manipulating a matrix
Author : William
Date : 09/12/16
*/

#ifndef MATRIXLIB_H_INCLUDED
#define MATRIXLIB_H_INCLUDED

#include <matrix.h>

/* CELLS */

/* ROWS */

/*
Function to test if a given Row is Empty
@arg row : the row element of the matrix
@return : a boolean true if the row is Empty.
*/

BOOL isRowEmpty(rowElement* row);

/*
Function to add a new row
@arg m : the matrix who receive the new row
@arg index: the index of the new row
@return : the mdodify matrix.
*/

Matrix* insertRow(Matrix* m, int index);

/*
Function to remove a given row
@arg m : the matrix who the row will be remove
@arg index: the index of the row
@return : the mdodify matrix.
*/

Matrix* removeRow( Matrix* m, int index);


/* COLS */

/*
Function to test if a given Columm is Empty
@arg col : the Columm element of the matrix
@return : a boolean, true if the columm is Empty.
*/
BOOL isColEmpty(colElement* col);

/*
Function to remove a given columm
@arg m : the matrix who the columm will be remove
@arg index: the index of the columm
@return : the mdodify matrix.
*/

Matrix* removeCol( Matrix* m, int index)

/*
Function to add a new columm
@arg m : the matrix who receive the new columm
@arg index: the index of the new columm
@return : the mdodify matrix.
*/

Matrix* insertCol(Matrix* m, int index)




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
@arg a : pointer to the first Matrix
@arg b : pointer to the second Matrix
@return : a pointer to a new Matrix
*/
Matrix* sumMatrix(Matrix* a, Matrix* b);

/*
THE function ( I heard they didnt have it in LO21. This is unfair. UNFAIR.)
Apply the rule(s) specified to the Matrix specified.
@arg M : a pointer toward the Matrix on whoch we want to operate
@arg rule : the rule we want to apply, must be between 1 ( do nothing ) and 511 ( every rules )
@arg times : the number of times we want to apply it
@return : a pointer toward a the new Matrix created.
*/
void applyRules(Matrix* m, int rule, int times);



/*
A function to add a new cell with a value of 1 to a array representation
@arg rowindex : the row index of the new cell
@arg colindex : the columm index of the new cell
@return : a array reprsentation of the new matrix
*/
Points* insertTailPoints( int rowindex,  int colIndex, Points* list);

#endif