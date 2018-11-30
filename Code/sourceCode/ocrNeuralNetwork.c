#include <stdio.h>
#include "BigMatrix.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define WHITE "\x1B[37m"

Matrix weights1;
Matrix bias1;
Matrix weights2;
Matrix bias2;


char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,:;i\"'(){}[]!?@$%&-+=";
Matrix toEval;

Matrix intermediate;
Matrix lastLayer;

void backPropagate(Matrix *ErrorMatrix, float TotalError);
float CreationDeltaMatrix(float Error,float ActualOut,
        float PreviousOut,Matrix * DeltaMatrix, int j , float weight);
size_t maxValueIndex(Matrix *matrix);

//Evaluates the OCR on an image Matrix 
//If training == 0, it loads the Matrix otherwise they already are loaded
int eval(Matrix toEval, int training){
    
    if(!training)
    {
        weights1 = _LoadMatrix("OCRmat/weights1.mat");
        bias1 = _LoadMatrix("OCRmat/bias1.mat");
        weights2 = _LoadMatrix("OCRmat/weights2.mat");
        bias2 = _LoadMatrix("OCRmat/bias2.mat");
    }


      


    Matrix intermediatetmp = multMatrix(&weights1,&toEval);



    intermediate = addMatrix(&intermediatetmp,&bias1);
    free(intermediatetmp.values);

    sigmoidify(&intermediate);



    Matrix lastLayertmp = multMatrix(&weights2,&intermediate);
    lastLayer = addMatrix(&lastLayertmp,&bias2);
    free(lastLayertmp.values);
    sigmoidify(&lastLayer);


    int toReturn = maxValueIndex(&lastLayer);

    if(!training)
    {
        free(weights1.values);
        free(bias1.values);
        free(weights2.values);
        free(bias2.values);
        free(intermediate.values);
        free(toEval.values);
        free(lastLayer.values);
    }
    return toReturn; 
    
}

//Trains n times the neural network
void train(Matrix *toEvaluate, char trueResult)
{
    toEval = createMatrix(toEvaluate->x,toEvaluate->y);
    for(int i = 0 ; i<  toEval.x*toEval.y;i++)
    {
        toEval.values[i] = toEvaluate->values[i];
    }

    srand(time(NULL));
    //alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,:;i\"'(){}[]!?@$%&-+=";

    weights1 = _LoadMatrix("OCRmat/weights1.mat");
    bias1 = _LoadMatrix("OCRmat/bias1.mat");
    weights2 = _LoadMatrix("OCRmat/weights2.mat");
    bias2 = _LoadMatrix("OCRmat/bias2.mat");

    
    size_t trueResultIndex;
    for (trueResultIndex= 0; trueResultIndex< strlen(alphabet) && alphabet[trueResultIndex] != trueResult; trueResultIndex++)
    	continue;


    int result = eval(toEval,1);
    //printf("%i , result \n",result );
    //printf("%c %c\n",alphabet[result],trueResult);
	printf("%s %c %s pour %c\n",(alphabet[result] == trueResult)?GREEN:RED, alphabet[result],WHITE,trueResult);





    Matrix ErrorMatrix = createMatrix(lastLayer.x,1);
    float TotalError = 0;

    for( int i = 0; i< lastLayer.x*lastLayer.y ; i++)
    {
        float errori = -lastLayer.values[i];
		errori += i==(int)trueResultIndex;
        TotalError += (errori*errori)/2;
        ErrorMatrix.values[i]= errori;
    }

 	//printf("%f\n",	weights1.values[getCoordinates(0,1,&weights1)] );
    //printMatrix(ErrorMatrix);
	//printMatrix(intermediate);
    backPropagate(&ErrorMatrix,TotalError);

    //printMatrix(lastLayer);

    free(intermediate.values);
    free(toEval.values);
    free(lastLayer.values);

	    
    _SaveMatrix("OCRmat/weights1.mat",&weights1);
    _SaveMatrix("OCRmat/bias1.mat",&bias1);
    _SaveMatrix("OCRmat/weights2.mat",&weights2);
    _SaveMatrix("OCRmat/bias2.mat",&bias2);

    free(weights1.values);
    free(bias1.values);
    free(weights2.values);
    free(bias2.values);
    free(ErrorMatrix.values);

}


float DerivativeFormula(float delta, float out,float input)

{
	return -delta * out * (1 - out) * input * 0.5;
}



void backPropagate(Matrix *ErrorMatrix, float TotalError)
{
    TotalError+=1;
	Matrix DeltaMatrix = createMatrix(intermediate.x,1);
	
	for(int i = 0; i < DeltaMatrix.x; i++)
	{
		DeltaMatrix.values[getCoordinates(i,0,&DeltaMatrix)] = 0;
	}
    
    for(int i = 0; i < weights2.x; i++)
	{
		for(int j = 0; j < weights2.y;j++)
		{
			DeltaMatrix.values[getCoordinates(j,0,&DeltaMatrix)] += ErrorMatrix->values[getCoordinates(i,0,ErrorMatrix)] * 
																    weights2.values[getCoordinates(i,j,&weights2)];
		}
	}
	
	
	for(int i = 0; i < weights2.x ;i++)
	{
        bias2.values[getCoordinates(i,0,&bias2)] -= 
            DerivativeFormula(
                    ErrorMatrix->values[getCoordinates(i,0,ErrorMatrix)] ,
					lastLayer.values[getCoordinates(i,0,&lastLayer)],
                    1.0);

		for(int j = 0; j < weights2.y; j++)
		{

			weights2.values[getCoordinates(i,j,&weights2)] -= 
				DerivativeFormula(
					ErrorMatrix->values[getCoordinates(i,0,ErrorMatrix)] ,
					lastLayer.values[getCoordinates(i,0,&lastLayer)],
					intermediate.values[getCoordinates(j,0,&intermediate)]
					);
		}
	}

	for(int i = 0; i < weights1.x;i++)
	{
		bias1.values[getCoordinates(i,0,&bias1)] -= 
            DerivativeFormula(
                   DeltaMatrix.values[getCoordinates(i,0,&DeltaMatrix)] ,
                   intermediate.values[getCoordinates(i,0,&intermediate)] , 
                   1.0) ;		
        for(int j = 0; j < weights1.y; j++)
		{
		     weights1.values[getCoordinates(i,j,&weights1)] -= 
                DerivativeFormula(
                   DeltaMatrix.values[getCoordinates(i,0,&DeltaMatrix)] , 
                   intermediate.values[getCoordinates(i,0,&intermediate)],
                   toEval.values[getCoordinates(j,0,&toEval)]
                   );
		}
	}

 
    
    free(DeltaMatrix.values);
}


size_t maxValueIndex(Matrix *matrix)
{
    size_t maxIndex = 0;
    for(int i = 1; i < matrix->x*matrix->y ; i++)
    {
        if(matrix->values[i] > matrix->values[maxIndex])
            maxIndex = i;
    }

    return maxIndex;
}
