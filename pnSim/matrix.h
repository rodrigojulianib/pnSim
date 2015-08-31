/************************
 ** Author: Luiz Leite **
 *************************/

#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <stdbool.h>
#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>


//to function findInMatrix
#define ZERO 0
#define EQUAL 0
#define EQUALS_GREATER 1
#define EQUALS_LESS 2
#define GREATER 3
#define LESS 4

//Matrix definition
typedef struct{
    unsigned int row, col;
    int **m;
} Matrix;


//initialize the matrix with specified dimension
void initializeMatrix(Matrix* m, unsigned int row, unsigned int col);

//(load Matrix actualy set matrix, but will be changed for load);
void setMatrix(Matrix *m);

//Show matrix
void showMatrix(Matrix *m);

//Sum matrix A with B and save the value in C
void sumMatrix(Matrix* a, Matrix* b, Matrix* c);

//Subtract matrix B from A and save the value in C
void subMatrix(Matrix* a, Matrix* b, Matrix* c);

//Find if exist a value in a matrix
int findInMatrix(Matrix* a, int val);

//Change a col of matrix to a vector
void colToVector(Matrix* a, int col, Matrix* vecta);

//Compare array line
void equalGreaterMatrix(Matrix* a, Matrix* b, Matrix* result);

//Load matrix from xml
void loadMatrix(Matrix *m, char* path);

//save vector of index of value determined;
void findInMatrixId(Matrix *a, int value, Matrix *b);
#endif // MATRIX_H_INCLUDED
