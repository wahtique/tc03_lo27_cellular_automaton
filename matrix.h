/*
File containing the prototypes of the functions pertaining to the matrix data type
Author : William 
Creation date : 11/23/16
*/

#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

/* May be useless. Maybe not.*/
#define TRUE 1
#define FALSE 0

typedef int BOOL;

/*
a cell element of a Matrix. We got rid of the value, since the existence of an element is equivalent to a TRUE
	colIndex : the index of the column containing the element
	rowIndex : the index of the row in which the element is contained
	nextCol : pointer to the next element in the column
	nextRow : pointer to the next element in the row
*/
typedef struct cellEl
{
	int colIndex;
	int rowIndex;
	struct cellEl* nextCol;
	struct cellEl* nextRow;
}cellElement;


/*
A point element in a list of points. It correspond to the TRUEs in an array representation of a boolean matrix.
	x : the column index
	y : the row index
	nextP : a pointer toward the next points in the list of points
*/
typedef struct pls
{
	int x,y;
	struct pls* nextP;
}Points;

/*
a list if points, defined as a pointer toward the first element
*/
typedef Points* listPoints;

/*
A doubly chained list containing the rows of a Matrix
	rowN : an integer, the index of the row represented by this rowElement
	nextRow : a pointer toward the next rowElement, or NULL if last row, in the Matrix
	prevRow : a pointer toward the previous rowElement in the Matrix, or NULL if it's the first row
	row : a pointer toward the first cellElement of the row
*/
typedef struct rowEl
{
	int rowN;
	struct rowEl* nextRow;
	struct rowEl* prevRow;
	cellElement* row;
}rowElement;

/*
A doubly chained list containing the columns of a Matrix
	colN : an integer, the index of the column represented by this colElement
	nextCol : a pointer toward the next colElement in the Matrix, or NULL if it's the last column
	prevCol : a pointer toward the previous colElement in the Matrix, or NULL if it's the first column
	col : a pointer toward the first cellElement of the column
*/
typedef struct colEl
{
	int colN;
	struct colEl* nextCol;
	struct colEl* prevCol;
	cellElement* col;
}colElement;

/*
Our array based matrix representation.
	list : a linked list ( pointer toward the first element ) of the coordinates of the ones in our matrix
	n : number of rows in the matrix
	p : number of columns in the matrix
*/
typedef struct 
{
	listPoints list;
	int n,p;
}arrayMatrix;

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

#endif