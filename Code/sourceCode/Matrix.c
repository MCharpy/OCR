#include <stdio.h>

typedef struct Matrix16 Matrix16;
struct Matrix16 {
    int x;
    int y;
    float values[16];
};

int GetCoordinates16(int x, int y, Matrix16 matrix){
    if(x < 0 || y<0 || x>= matrix.x || y >= matrix.y)
        return -1;
    return y*matrix.y + x;
}

Matrix16 MatrixMult16(Matrix16 matrix1, Matrix16 matrix2){
   Matrix16 toReturn;
   if (matrix1.y != matrix2.x){
        toReturn.x =-1;
        toReturn.y =-1;
        return toReturn;
    }
    toReturn.x = matrix1.x;
    toReturn.y = matrix2.y;
    
    for (int m = 0 ; m < matrix1.x ; m++)
    {
        for (int p = 0 ; p < matrix2.y ; p++)
        {
            int sum = 0;
            for (int k= 0 ; k< matrix1.y ; k++)
            {
                sum += matrix1.values[GetCoordinates16(m,k,matrix1)]*matrix2.values[GetCoordinates16(k,p,matrix2)];
            }
            toReturn.values[m+toReturn.y*p]=sum;
        }
    }
    return toReturn;
}

void printMatrix16(Matrix16 matrix){
    for (int i = 0; i< matrix.x*matrix.y; i++){
        printf("%f ",matrix.values[i]);
        if((i-1)%matrix.x == 0)
            printf("\n");

    }
}

typedef struct Matrix Matrix;
struct Matrix {
    int x;
    int y;
    float values[784];
};


int GetCoordinates(int x, int y, Matrix matrix){
    if(x < 0 || y<0 || x>= matrix.x || y >= matrix.y)
        return -1;
    return y*matrix.y + x;
}

Matrix MatrixMult(Matrix matrix1, Matrix matrix2){
   Matrix toReturn;
   if (matrix1.y != matrix2.x){
        toReturn.x =-1;
        toReturn.y =-1;
        return toReturn;
    }
    toReturn.x = matrix1.x;
    toReturn.y = matrix2.y;
    
    for (int m = 0 ; m < matrix1.x ; m++)
    {
        for (int p = 0 ; p < matrix2.y ; p++)
        {
            int sum = 0;
            for (int k= 0 ; k< matrix1.y ; k++)
            {
                sum += matrix1.values[GetCoordinates(m,k,matrix1)]*matrix2.values[GetCoordinates(k,p,matrix2)];
            }
            toReturn.values[m+toReturn.y*p]=sum;
        }
    }
    return toReturn;
}

void printMatrix(Matrix matrix){
    for (int i = 0; i< matrix.x*matrix.y; i++){
        printf("%f ",matrix.values[i]);
        if((i-1)%matrix.x == 0)
            printf("\n");

    }
}

