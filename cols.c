/*
File containing the function and procedures for the manipulation of colElement.
Author : Yann
Creation date : 12/09/2016
*/


#include <stdlib.h>
#include <stdio.h>
#include <cols.h>


Bool isColumnEmpty(colElement* column) {
	return(column==NULL || column->col==NULL);
}

colElement* insertCol(colElement* col, int index);
{
	colElement* newel = (colElement*)malloc(sizeof(colElement));
	colElement* tmp= col;
	if (tmp>index)
	{
		newel->colN= index;
		newel->nextCol = tmp;
		tmp->prevCol = newel;
	}else{

		while(index<tmp)
		{
			tmp=col->nextCol;
		}
		if (index=!tmp)
		{
			newel->colN= index;
			tmp->nextCol->prevCol = newel;
			newel->nextCol = tmp->nextCol;
			newel->prevCol = tmp;
			tmp->nextCol =	newel;
		}
	} 
return col;
}

colElement* removeColHead( colElement* col)
{
	colElement* tmp= col;

}

