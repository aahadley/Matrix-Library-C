#include <time.h>
#include <stdio.h>

#define TRUE  1
#define FALSE 0

typedef struct matrix
{
	unsigned int numRows;
	unsigned int numColumns;
	double **values;
}Matrix;


//Function Prototypes
Matrix *mXcreate(unsigned int rows, unsigned int columns);
Matrix *mXtranspose(Matrix *matrix);
Matrix *mXadd(Matrix *A, Matrix *B);
Matrix *mXdot(Matrix *A, Matrix *B);
Matrix *mXclone(Matrix *A);
void   *mXfreeAll(Matrix *matrix);
void   *mXprint(Matrix *A);
void 	mXscale(Matrix *matrix, double scalar);
//diuble     mXdet(Matrix *A);
void   _deleteRow(Matrix *A, int row);
void   _deleteColumn(Matrix *A, int column);
void    *mXfillRand(Matrix *matrix , int seed, int mod);
int     falsePass(Matrix *matrix);
int     trueSquare(Matrix *matrix);
void 	*error(char *message);
