Aaron Hadley
Spring, 2018
matrix.c
A library containing various matrix-related functions.

The header file, matrix.h contains the matrix type definition,
and function headers.

Function Descriptions:

	Matrix *mXcreate(unsigned int rows, unsigned int columns)

		Allocate memory for a new matrix.
		Initialize all elements to 0, or NULL.
		Returns NULL upon allocation failure.


	void mXfreeAll(Matrix *matrix)

		Free all dynamically allocated memory associated with a given matrix.
		Returns NULL upon allocation failure.


	Matrix *mXclone(Matrix *A)

		Create a copy of a given matrix.


	Matrix *mXtranspose(Matrix *matrix)

		Return the matrix transpose of a given matrix,
		Return NULL upon failure.

		We define the transpose T of a given matrix A as 
			the matrix whose element at the ith row, jth column corresponds to the element at the jth row, ith column of A.


	Matrix *mXdot(Matrix *A, Matrix *B)

		Return the inner product (dot product) of two given matrices, A and B.
		Return NULL upon failure.
