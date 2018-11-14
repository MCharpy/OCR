#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <err.h>


//structure Matrix is a structure for matrix with a max of 784 number of values
//      x is the x size of the matrix
//      y is the y size of the matrix
//      values contains the values of the matrix
typedef struct Matrix Matrix;
struct Matrix {
    int x;
    int y;
    float *values;
};

Matrix createMatrix(int x,int y){
    Matrix mat;
    mat.x = x;
    mat.y = y;
    mat.values=NULL;
    mat.values = malloc(x*y*sizeof(float));
    if(mat.values== NULL)
        errx(42,"Memoire insuffisante");
    return mat;
}


//getCoordinates returns the index in value of the x,y value
//      x is the x coordinate you want
//      y is the y coordinate you want
//      matrix is the Matrix in wich you want a value
int getCoordinates(int x, int y, Matrix *matrix){
    return y + x*(matrix->y);
}

//multMatrix returns the product of 2 Matrix
//      matrix1 and matrix2 are the 2 Matrix to multiply
Matrix multMatrix(Matrix matrix1, Matrix matrix2){
    if(matrix1.y != matrix2.x){
        return createMatrix(0,0);
    }
    Matrix toReturn = createMatrix(matrix1.x,matrix2.y);
    
    for(int m = 0; m < matrix1.x; m++){
        for(int p=0; p<matrix2.y; p++){
            float sum = 0;
            for(int k= 0; k < matrix1.y; k++){
                float inMat1 = matrix1.values[getCoordinates(m,k,&matrix1)];
                float inMat2 = matrix2.values[getCoordinates(k,p,&matrix2)];
                sum += inMat1*inMat2;
            }
            toReturn.values[getCoordinates(m,p,&toReturn)] = sum;
        }
    }

    return toReturn;
}

//addMatrix returns the sum of 2 Matrix
//      matrix1 and matrix2 are the 2 Matrix to add
Matrix addMatrix(Matrix matrix1, Matrix matrix2){
    if(matrix1.x != matrix2.x || matrix1.y != matrix2.y){
        return createMatrix(0,0); 
    }
    Matrix toReturn = createMatrix(matrix1.x,matrix1.y);
    for (int i = 0; i< toReturn.x*toReturn.y ; i++){
        toReturn.values[i] = matrix1.values[i]+matrix2.values[i];
    }
    return toReturn;
}

//printMatrix prints a Matrix
//      matrix is the Matrix to print
void printMatrix(Matrix matrix){
    printf("\n");
    if(matrix.x<1||matrix.y<1)
    {
        printf("Cette matrice n'existe pas\n");
        return;
    }
    for(int i = 0; i< matrix.x * matrix.y ; i++){
        printf("%f ",matrix.values[i]);
        if((i+1)% matrix.y == 0)
            printf("\n");
    }
    printf("\n");
}

//sigmoidify apply the sigmoid function to the matrix
//      matrix is the Matrix to sigmoidify
void sigmoidify(Matrix *matrix)
{
    for (int i = 0; i< matrix->x*matrix->y; i++)
        matrix->values[i] = 1/(1 + exp(-matrix->values[i]));
}


//_SaveMatrix saves a Matrix to a file
//      p is the path where you want to save the Matrix
//      matrix is the Matrix to save
void _SaveMatrix(char p[], Matrix *matrix)
{
	FILE *fp;
	fp = fopen(p,"w");
	fprintf(fp,"%i%s%i%s",matrix->x,"\n",matrix->y,"\n");
	for(int i = 0 ; i < matrix->x*matrix->y;i++)
		fprintf(fp,"%f%s",matrix->values[i],"\n");
	fclose(fp);
}

//_LoadMatrix loads a Matrix from a file
//      p is the path of the file
//      dest is a pointer to a Matrix getting the file values
Matrix _LoadMatrix(char p[])
{
	char a[15];
	FILE *fp;
	fp = fopen(p,"r");
	fgets(a,15,fp);
	int c = strtol(a,NULL,10);
	fgets(a,15,fp);
	int d = strtol(a,NULL,10);
	char s[10] = "";
    Matrix dest = createMatrix(c,d);
    for(int i = 0; i < c*d;i++)
	{
		fgets(a,15,fp);
		dest.values[i] = atof(a);
	}
	fclose(fp);
    return dest;
}

void resetMatrix(char p[],int bias)
{
    Matrix toReset = _LoadMatrix(p);
    for (int i =0 ; i< toReset.x*toReset.y;i++)
    {
         toReset.values[i]=((float)rand()/RAND_MAX*(bias?1:2.0)-1); 
    }
    _SaveMatrix(p,&toReset);
    free(toReset.values);
}
