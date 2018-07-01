#include <stdio.h>
#include "matrix.h"

int main(void)
{
	int i, seed;

	printf("calling create A\n");
	Matrix *A = mXcreate(3, 3);

	printf("calling create B\n");
	Matrix *B = mXcreate(3, 3);

	Matrix *C;

	Matrix *D;

	printf("calling fillrand\n");
	seed = time(NULL);
	mXfillRand(A, seed, 10);
	mXscale(A, 2);

	printf("scaled A\n");

	mXfillRand(B, 69, 10);
	mXscale(B, 3);

	printf("printing A:\n\n");
	mXprint(A);

	printf("printing B:\n\n");
	mXprint(B);

	//printf("Printing B transpose:\n\n");
	//mXprint(mXtranspose(B));

	printf("getting product\n");
	C = mXdot(A, B);

	printf("printing product:\n\n");
	mXprint(C);

	D = mXadd(A , B);
	printf("printing sum\n");
	mXprint(D);

	printf("getting product\n");
	C = mXdot(A , B);

	printf("printing product:\n\n");
	mXprint(C);

	printf("\n");

	mXfreeAll(A);
	mXfreeAll(B);
	mXfreeAll(C);

	return 0;
}