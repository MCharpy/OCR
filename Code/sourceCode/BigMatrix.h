#ifndef Matrix_H
#define Matrix_H


typedef struct Matrix Matrix;
struct Matrix{
  int x;
  int y;
  float *values;
};

int getCoordinates(int x, int y, Matrix *matrix);
Matrix addMatrix(Matrix matrix1, Matrix matrix2);
void sigmoidify(Matrix *matrix);
void printMatrix(Matrix matrix);
void _SaveMatrix(char p[], Matrix *matrix);
Matrix _LoadMatrix(char p[]);
Matrix multMatrix(Matrix matrix1, Matrix matrix2);
Matrix createMatrix(int x,int y);
Matrix resetMatrix(char p[],int bias);
#endif
