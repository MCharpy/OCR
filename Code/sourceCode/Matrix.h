#ifndef Matrix_H
#define Matrix_H


typedef struct Matrix16 Matrix16;
struct Matrix16{
  int x;
  int y;
  float values[16];
    
};

void printMatrix16(Matrix16 matrix);
Matrix16 MatrixMult16(Matrix16 matrix1, Matrix16 matrix2);
int GetCoordinates16(int x, int y, Matrix16 matrix);

typedef struct Matrix Matrix;
struct Matrix{
  int x;
  int y;
  float values[784];
    
};

void printMatrix(Matrix matrix);
Matrix MatrixMult(Matrix matrix1, Matrix matrix2);
int GetCoordinates(int x, int y, Matrix matrix);


#endif
