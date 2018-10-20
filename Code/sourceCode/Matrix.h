#ifndef Matrix_H
#define Matrix_H


typedef struct Matrix16 Matrix16;
struct Matrix16{
  int x;
  int y;
  float values[16];
    
};

void printMatrix16(Matrix16 matrix);
Matrix16 multMatrix16(Matrix16 matrix1, Matrix16 matrix2);
int getCoordinates16(int x, int y, Matrix16 matrix);
Matrix16 addMatrix16(Matrix16 matrix1, Matrix16 matrix2);
void sigmoidify16(Matrix16 *matrix);
void _SaveMatrix16(char p[], Matrix16 matrix);
void _LoadMatrix16(char p[], Matrix16 *dest);


#endif
