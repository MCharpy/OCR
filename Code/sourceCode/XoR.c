#include <stdio.h>
#include "BigMatrix.h"
#include <time.h>
#include <stdlib.h>

#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define WHITE "\x1B[37m"

Matrix weights1;
Matrix bias1;
Matrix weights2;
Matrix bias2;

Matrix toEval;

Matrix intermediate;
Matrix lastLayer;

void backPropagate(Matrix ErrorMatrix, float TotalError);
float CreationDeltaMatrix(float Error,float ActualOut,
        float PreviousOut,Matrix * DeltaMatrix, int j , float weight);

//Evaluates XoR on a and b.
//If training == 0, it loads the Matrix otherwise they already are loaded
int eval(int a, int b , int training){
    
    if(!training)
    {
        weights1 = _LoadMatrix("OCRmat/weights1.mat");
        bias1 = _LoadMatrix("OCRmat/bias1.mat");
        weights2 = _LoadMatrix("OCRmat/weights2.mat");
        bias2 = _LoadMatrix("OCRmat/bias2.mat");
    }


    toEval = createMatrix(2,1);

    toEval.values[0]=(a==0?0:1);
    toEval.values[1]=(b==0?0:1);

    Matrix intermediatetmp = multMatrix(weights1,toEval);
    intermediate = addMatrix(intermediatetmp,bias1);
    free(intermediatetmp.values);

    sigmoidify(&intermediate);

    Matrix lastLayertmp = multMatrix(weights2,intermediate);
    lastLayer = addMatrix(lastLayertmp,bias2);
    free(lastLayertmp.values);
    sigmoidify(&lastLayer);

    int toReturn = lastLayer.values[0]>lastLayer.values[1];

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
void train(int n)
{
    srand(time(NULL));
    weights1 = _LoadMatrix("OCRmat/weights1.mat");
    bias1 = _LoadMatrix("OCRmat/bias1.mat");
    weights2 = _LoadMatrix("OCRmat/weights2.mat");
    bias2 = _LoadMatrix("OCRmat/bias2.mat");

    
    Matrix ErrorMatrix = createMatrix(2,1);
    ErrorMatrix.values[0] = 0.0;
    ErrorMatrix.values[1] = 0.0;
    


    for (int i =0 ; i <n ; i++)
    {
         int a = rand()%2;
         int b = rand()%2;
         int c = rand()%2;

         int result = eval(a,b,1);
		 printf("%i %i -> %s%i%s\n",a,b,a^b==result?GREEN:RED, result,WHITE);

		 float error1 = (a != b) - lastLayer.values[0];
		 float error2 = (a == b) - lastLayer.values[1];
		 float TotalError = (error1*error1)/2 + (error2*error2)/2;
		 
		 
	 	 ErrorMatrix.values[getCoordinates(0,0,&ErrorMatrix)] = 
             (a != b) - lastLayer.values[0];
         ErrorMatrix.values[getCoordinates(1,0,&ErrorMatrix)] = 
             (a == b) - lastLayer.values[1];
		 
         backPropagate(ErrorMatrix,TotalError);
         free(intermediate.values);
         free(toEval.values);
         free(lastLayer.values);

    }
	    
    _SaveMatrix("OCRmat/weights1.mat",weights1);
    _SaveMatrix("OCRmat/bias1.mat",bias1);
    _SaveMatrix("OCRmat/weights2.mat",weights2);
    _SaveMatrix("OCRmat/bias2.mat",bias2);

    free(weights1.values);
    free(bias1.values);
    free(weights2.values);
    free(bias2.values);
    //free(intermediate.values);
    //free(toEval.values);
    //free(lastLayer.values);
    free(ErrorMatrix.values);

}





float CreationDeltaMatrix(float Error,float ActualOut,
        float PreviousOut,Matrix * DeltaMatrix, int j , float weight)
{
	float delta = -Error * ActualOut * (1 - ActualOut);
	DeltaMatrix->values[getCoordinates(j,0,DeltaMatrix)] += delta * weight;
	return delta * PreviousOut * 0.5; 
}



float DerivativeFormula(float delta, float hidden , float input)

{
	return delta * hidden * (1- hidden) * input * 0.5;
}



void backPropagate(Matrix ErrorMatrix, float TotalError)
{

	Matrix DeltaMatrix = createMatrix(4,1);
	for(int i = 0; i < DeltaMatrix.x; i++)
	{
		for(int j = 0; j < DeltaMatrix.y;j++)
		{
			DeltaMatrix.values[getCoordinates(i,j,&DeltaMatrix)] = 0.0;
		}
	}


	for(int i = 0; i < weights2.x ;i++)
	{


		bias2.values[getCoordinates(i,0,&bias2)] -= 
            DerivativeFormula(
                    ErrorMatrix.values[getCoordinates(i,0,&ErrorMatrix)] , 
                    lastLayer.values[getCoordinates(i,0,&lastLayer)] , 
                    1.0) ;

 
		for(int j = 0; j < weights2.y; j++)
		{
			weights2.values[getCoordinates(i,j,&weights2)] -= 
                CreationDeltaMatrix(
                   ErrorMatrix.values[getCoordinates(i,0,&ErrorMatrix)] , 
                   lastLayer.values[getCoordinates(i,0,&lastLayer)], 
                   intermediate.values[getCoordinates(j,0,&intermediate)], 
                   &DeltaMatrix , 
                   j , 
                   weights2.values[getCoordinates(i,j,&weights2)] );

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
		/*	weights1.values[getCoordinates(i,j,&weights1)] -= 
                DerivativeFormula(
                   DeltaMatrix.values[getCoordinates(i,0,&DeltaMatrix)] , 
                   intermediate.values[getCoordinates(i,0,&intermediate)],
                   toEval.values[getCoordinates(j%2,0,&toEval)]
                   ) ;**/
            
		}
	}


    free(DeltaMatrix.values);


}
