//Aaron Hadley
//February 2018
//Various matrix-related functions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"

//Allocate memory for a new matrix, return pointer to the matrix.
Matrix *mXcreate(unsigned int rows, unsigned int columns)
{
	int i;
	char *ic;

	Matrix *matrix = (Matrix *) malloc(sizeof(Matrix*));

	if(!matrix)
		return (Matrix *) error("Allocation failure in mXcreate. (*matrix)");

	matrix->numRows    = rows;
	matrix->numColumns = columns;
	matrix->values     = (double **) calloc(rows, sizeof(double*));

	if(!matrix->values)
	{
		free(matrix);
		return 	(Matrix *) error("Allocation failure in mXcreate. (matrix->values");
	}

	for(i = 0; i < rows; i++)
	{
		matrix->values[i] = (double *) calloc(columns , sizeof(double));

		if(!matrix->values[i])
		{
			for(; i >= 0; free(matrix->values[i--]));

			free(matrix->values);
			free(matrix);

			return (Matrix *) error("Allocation error in mXcreate. (matrix->values[i])");
		}
	}

	return matrix;
}

Matrix *mXclone(Matrix *A)
{
	Matrix *imposter;
	int i, j;

	if(!A) 
		return (Matrix *) error("NULL pointer in mXclone. (A)");

	imposter = mXcreate(A->numRows, A->numColumns);

	if(!imposter) 
		return (Matrix *) error("Returning from mXclone due to allocation failure.");

	for(i = 0; i < A->numRows; i++)
		for(j = 0; j < A->numColumns; j++)
			imposter->values[i][j] = A->values[i][j];
}

void *mXfreeAll(Matrix *matrix)
{
	int i;

	if(!matrix)	
		return NULL;

	for(i = 0; i < matrix->numRows; i++)
		free(matrix->values[i]);

	free(matrix->values);
	free(matrix);

	return NULL;
}

//Create a matrix transpose given a matrix
Matrix *mXtranspose(Matrix *matrix)
{
	int i,j;
	Matrix *transpose;

	//Don't call the error function in this case, because the transpose of a 0 x 0 matrix is indeed itself.
	if(!matrix)	
		return NULL;

	transpose = mXcreate(matrix->numColumns , matrix->numRows);

	if(!transpose) 
		return (Matrix *) error("Returning from mXtranspose due to allocation failure.");

	transpose->numRows    = matrix->numColumns;
	transpose->numColumns = matrix->numRows;

	for(i = 0; i < transpose->numRows; i++)
		for(j = 0; j < transpose->numColumns; j++)
			transpose->values[i][j] = matrix->values[j][i];

	return transpose;
}

//Dot product. Naive solution.
//Faster algorithms exist, but are impractical for matrices smaller than 1M elements.
Matrix *mXdot(Matrix *A, Matrix *B)
{
	int i, j, k;
	double hold;
	Matrix *dotProduct;

	if(!A && !B)	return NULL;
	if(!A) 			return (Matrix *) error("NULL pointer passed to mXdot. (A)");
	if(!B) 			return (Matrix *) error("NULL pointer passed to mXdot. (B)");

	if(A->numColumns != B->numRows)	
		return (Matrix *) error("Row-column mismatch in mXdot.");	// This isn't a pointer error, but the return value is the same.


	dotProduct = mXcreate(A->numColumns, B->numRows);

	if(!dotProduct)						return (Matrix *) error("Returning from mXdot due to allocation failure.");

	for(i = 0; i < A->numColumns; i++)
		for(j = 0; j < A->numRows; j++)
			for(k = 0; k < B->numRows; k++)
				dotProduct->values[i][j] += A->values[i][k] * B->values[k][j];

	return dotProduct;
}

//Add two matrices together
Matrix *mXadd(Matrix *A, Matrix *B)
{
	int i,j;
	Matrix *sum;

	if(!A && !B)	return NULL;
	if(!A)			return (Matrix *) error("NULL pointer passed to mXdot. (A)");
	if(!B)			return (Matrix *) error("NULL pointer passed to mXdot. (B)");

	if(A->numRows != B->numRows || A->numColumns != B->numColumns)	
		return (Matrix *) error("Row-column mismatch in mXadd.");	// This isn't a pointer error, but the return value is the same.

	sum = mXcreate(A->numRows, B->numColumns);

	if(!sum) 
		return error("Returning from mXsum due to pointer error.");

	for(i =  0; i < A->numColumns; i++)
	{
		for(j = 0; j < A->numRows; j++)
		{
			sum->values[i][j] += A->values[i][j];
			sum->values[i][j] += B->values[i][j];
		}
	}

	return sum;
}

//Multiply a matrix by a scalar.
void mXscale(Matrix *matrix, double scalar)
{
	int i, j;

	if(!matrix)	return;

	for(i = 0; i < matrix->numRows; i++)
		for(j = 0; j < matrix->numColumns; j++)
			matrix->values[i][j] *= scalar;
		
	return;
}

//Print a matrix.
void *mXprint(Matrix *matrix)
{
	int i, j;

	if(!matrix)	
		return "[NULL]";

	for(i = 0; i < matrix->numRows; i++)
	{
		if(!matrix->values)
		{
			mXfreeAll(matrix);
			return	error("NULL pointer found in mXprint. (matrix->values)");	
		}

		printf("\t");
		for(j = 0; j < matrix->numColumns; j++)
		{	
			
			if(!matrix->values[i])
			{
				mXfreeAll(matrix);
				return	error("NULL pointer found in mXprint. (matrix->values)");	
			}

			if(j == 0)
				printf("[");

			printf("%.1lf", matrix->values[i][j]);

			if(j < matrix->numColumns - 1)
				printf("\t");

			else
				printf("]");
		}
			printf("\n");
	}
	printf("\n\n");
	return matrix;
}

//Fill matrix with random values.
//It currently generates ints cast to doubles, but can be easily modified.
void *mXfillRand(Matrix *matrix , int seed, int mod)
{
	int i,j;
	double *p;
	srand(seed);

	if(!matrix)		
		return error("NULL pointer passed to mXfillRand. (matrix)");

	for(i = 0; i < matrix->numRows; i++)
		for(j = 0; j < matrix->numColumns; j++)
			matrix->values[i][j] = (double) (rand() % mod);

	return matrix;
}

//Determine if a given matrix is square
int trueSquare(Matrix *matrix)
{
	if(!matrix || matrix->numRows != matrix->numColumns)
		return FALSE;

	else
		return TRUE;
}

void *error(char *message)
{
	fprintf(stderr, "Error: %s", message);
	return NULL;
}
