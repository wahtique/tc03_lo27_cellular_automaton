/*
File containing all the functions manipulating a matrix
Author : William
Date : 09/12/16
*/

#ifndef MATRIXLIB_H_INCLUDED
#define MATRIXLIB_H_INCLUDED

#include <matrix.h>

/* ----------------------------- CELLS ----------------------------- */

/* ----------------------------- ROWS ----------------------------- */

/*
Function to test if a given Row is Empty
@arg row : the row element of the matrix
@return : a boolean true if the row is Empty.
*/

BOOL isRowEmpty(rowElement* row);

/*
Function to add a new row in a Matrix
@arg m : the matrix who receive the new row
@arg index: the index of the new row
@return : the mdodify matrix.
*/

Matrix* insertRow(Matrix* m, int index);

/*
Function to remove a given row in a Matrix
@arg m : the matrix who the row will be remove
@arg index: the index of the row
@return : the mdodify matrix.
*/

Matrix* removeRow( Matrix* m, int index);


/* ----------------------------- COLS ----------------------------- */

/*
Function to test if a given Columm is Empty
@arg col : the Columm element of the matrix
@return : a boolean, true if the columm is Empty.
*/
BOOL isColEmpty(colElement* col);

/*
Function to remove a given columm in a Matrix
@arg m : the matrix who the columm will be remove
@arg index: the index of the columm
@return : the mdodify matrix.
*/


Matrix* removeCol( Matrix* m, int index);

/*
Function to add a new columm in a Matrix
@arg m : the matrix who receive the new columm
@arg index: the index of the new columm
@return : the mdodify matrix.
*/

Matrix* insertCol(Matrix* m, int index);




/* ----------------------------- MATRIX ----------------------------- */

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
Function multiplaying two matrices. 
@arg A : pointer to the first matrix.
@arg B : pointer to the second matrix. Must have a number of rows equal to the number of columns of A.
@return : a pointer toward a new Matrix A x B. Have the same number of rows as A and the same number of columns as B.
*/
Matrix* mulMatrix(Matrix* A, Matrix* B);

/*
Function applying an AND operation on the columns of a Matrix, two by two
@arg m : a pointer to the Matrix we will transform, with p columns
@return : a pointer to the new Matrix created, with p-1 columns
*/
Matrix* andColSequenceOnMatrix(Matrix* m);

/*
Function applying an OR operation on the columns of a Matrix, two by two
@arg m : a pointer to the Matrix we will transform, with p columns
@return : a pointer to the new Matrix created, with p-1 columns
*/
Matrix* orColSequenceOnMatrix(Matrix* m);

/*
Function applying an AND operation on the rows of a Matrix, two by two
@arg m : a pointer to the Matrix we will transform, with n rows
@return : a pointer to the new Matrix created, with n-1 rows
*/
Matrix* andRowSequenceOnMatrix(Matrix* m);

/*
Function applying an AND operation on the rows of a Matrix, two by two
@arg m : a pointer to the Matrix we will transform, with n cols
@return : a pointer to the new Matrix created, with n-1 cols
*/
Matrix* orRowSequenceOnMatrix(Matrix* m);

/* ----------------------------- APPLYRULE ---------------------------- */

/*
THE function ( I heard they didnt have it in LO21. This is unfair. UNFAIR.)
Apply the rule(s) specified to the Matrix specified.
@arg M : a pointer toward the Matrix on which we want to operate
@arg rule : the rule we want to apply, must be between 1 ( do nothing ) and 511 ( every rules )
@arg times : the number of times we want to apply it
@return : a pointer toward the new Matrix obtained
*/
Matrix* applyRules(Matrix* m, int rule, int times);

/*
Translation of a Matrix to the right
@arg m : pointer toward the Matrix we want translate to the right
@return : nothing, m is modified during the iteration
*/
void transRight(Matrix* m);

/*
Translate the Matrix to the left
@arg m : pointer to the Matrix on which we operate
@return : nothing, m is modified during the iteration
*/
void transLeft(Matrix* m);

/*
Translate the Matrix upward
@arg m : pointer to the Matrix on which we operate
@return : nothing, m is modified during the iteration
*/
void transUp(Matrix* m);

/*
Translate the Matrix downward
@arg m : pointer to the Matrix on which we operate
@return : nothing, m is modified during the iteration
*/
void transDown(Matrix* m);

/*
Funtion saying if the cell specified is a 1 or not, ie if the cellElement exists in the Matrix
@arg m : pointer toward the Matrix in which we want to check a cell
@arg cellRow : rowIndex of the cell we want to know the existence of
@arg cellCol : colIndex of the cell we want to know the existence of
@return : TRUE if th cell exist, FALSE otherwise
*/
BOOL isCellTrue(Matrix* m, int cellRow, int cellCol);

/*
Function decomposing a complex rule into an array giving the elementary rules which compose it.
It gives us the cells we need to consider to to our XOR operations
@arg rule : the complex rule we will decompose
@return : a static array A of 9 Booleans, which tells us, for i from 0 to 8, if the cell identified as 2^i is to be considered for the XOR 
*/
BOOL* decomposeRule(int rule);

/*
Function saying if, given a Matrix, if the cell specified will gives a TRUE after applying the rule identified by the array toOperate
@arg m : pointer toward the Matrix in which we are operation
@arg cellRow : the rowIndex of the cell we are working with
@arg cellCol : the colIndex of the cell we are working with
@arg toOperate : a static array of 9 Booleans identifiying the rule we are using
@return : a boolean, TRUE if the use of the rule on the cell will give a TRUE, FALSE otherwise
*/
BOOL applyRuleToCell(Matrix* m, int cellRow, int cellCol, BOOL* toOperate);

/* ----------------------------- Points -----------------------------*/

/*
A function to add a new cell with a value of 1 to a array representation
@arg rowindex : the row index of the new cell
@arg colindex : the columm index of the new cell
@return : a array reprsentation of the new matrix
*/
Points* insertTailPoints( int rowindex,  int colIndex, Points* list);

#endif