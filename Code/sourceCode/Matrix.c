#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct Matrix16 Matrix16;
struct Matrix16 {
    int x;
    int y;
    float values[16];
};

int getCoordinates16(int x, int y, Matrix16 matrix){
    return y + x*((matrix.y));
}

Matrix16 multMatrix16(Matrix16 matrix1, Matrix16 matrix2){
    Matrix16 toReturn;
    if(matrix1.y != matrix2.x){
        toReturn.x = 0;
        toReturn.y = 0;
        return toReturn;
    }
    toReturn.x = matrix1.x;
    toReturn.y = matrix2.y;

    for(int m = 0; m < matrix1.x; m++){
        for(int p=0; p<matrix2.y; p++){
            float sum = 0;
            for(int k= 0; k < matrix1.y; k++){
                float inMat1 = matrix1.values[getCoordinates16(m,k,matrix1)];
                float inMat2 = matrix2.values[getCoordinates16(k,p,matrix2)];
                sum += inMat1*inMat2;
            }
            toReturn.values[getCoordinates16(m,p,toReturn)] = sum;
        }
    }

    return toReturn;
}


Matrix16 addMatrix16(Matrix16 matrix1, Matrix16 matrix2){
    Matrix16 toReturn;
    if(matrix1.x != matrix2.x || matrix1.y != matrix2.y){
        toReturn.x = 0;
        toReturn.y = 0;
        return toReturn;
    }
    toReturn.x = matrix1.x;
    toReturn.y = matrix1.y;
    for (int i = 0; i< toReturn.x*toReturn.y ; i++){
        toReturn.values[i] = matrix1.values[i]+matrix2.values[i];
    }
    return toReturn;
}

void printMatrix16(Matrix16 matrix){
    printf("\n");
    if(matrix.x<1||matrix.y<1)
    {
        printf("Cette matrice n'existe pas\n");
        return;
    }
    for(int i = 0; i< matrix.x * matrix.y ; i++){
        printf("%f ",matrix.values[i]);
        if((i-1)% matrix.y == 0)
            printf("\n");
    }
    printf("\n");
}

void sigmoidify16(Matrix16 *matrix)
{
    for (int i = 0; i< matrix->x*matrix->y; i++)
        matrix->values[i] = 1/(1 + exp(-matrix->values[i]));
}



void _SaveMatrix16(Matrix16 matrix, char p[])
{
	FILE *fp;
	fp = fopen(p,"w");
	fprintf(fp,"%i%s%i%s",matrix.x,"\n",matrix.y,"\n");
	for(int i = 0 ; i < matrix.x*matrix.y;i++)
		fprintf(fp,"%f%s",matrix.values[i],"\n");
	fclose(fp);
}

void _Load(char p[],Matrix16 *dest)
{
	float tab[16];
	char a[15];
	FILE *fp;
	fp = fopen(p,"r");
	fgets(a,5,fp);
	int c = strtol(a,NULL,10);
	fgets(a,5,fp);
	int d = strtol(a,NULL,10);
	char s[10] = "";
    float rtab[16];
	for(int i = 0; i < c*d;i++)
	{
		fgets(a,15,fp);
		rtab[i] = atof(a);
	}
	fclose(fp);	
    dest->x = c;
    dest->y = d;
    for (int i = 0 ; i< c*d; i++)
        dest->values[i] = rtab[i];
}

