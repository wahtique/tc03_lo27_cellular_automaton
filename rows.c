/*
File containing the function and procedures for the manipulation of rowElement.
Author : Yann
Creation date : 12/10/2016
*/


#include <stdlib.h>
#include <stdio.h>
#include <rows.h>


Bool isRowEmpty(rowElement* row) {
	return(row==NULL || row->Row==NULL);
}

rowElement* insertRow(rowElement* row, int index);
{
	rowElement* newel = (rowElement*)malloc(sizeof(rowElement));
	rowElement* tmp= row;
	if (tmp>index)
	{
		newel->RowN= index;
		newel->nextRow = tmp;
		tmp->prevRow = newel;
	}else{

		while(index<tmp)
		{
			tmp=row->nextRow;
		}
		if (index=!tmp)
		{
			newel->RowN= index;
			tmp->nextRow->prevRow = newel;
			newel->nextRow = tmp->nextRow;
			newel->prevRow = tmp;
			tmp->nextRow =	newel;
		}
	} 
return row;
}
