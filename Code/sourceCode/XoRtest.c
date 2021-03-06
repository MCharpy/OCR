#include <stdio.h>
#include "Matrix.h"
#include <time.h>
#include <stdlib.h>

#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define WHITE "\x1B[37m"

Matrix16 firstWeights;
Matrix16 firstBias;
Matrix16 secondWeights;
Matrix16 secondBias;

Matrix16 toEval;

Matrix16 intermediate;
Matrix16 lastLayer;

void backPropagate(Matrix16 ErrorMatrix, float TotalError);
float CreationDeltaMatrix(float Error,float ActualOut,
        float PreviousOut,Matrix16 * DeltaMatrix, int j , float weight);

//Evaluates XoR on a and b.
//If training == 0, it loads the Matrix otherwise they already are loaded
int eval(int a, int b , int training){
    
    if(!training)
    {
        _LoadMatrix16("XoRmat/firstWeights.mat",&firstWeights);
        _LoadMatrix16("XoRmat/firstBias.mat",&firstBias);
        _LoadMatrix16("XoRmat/secondWeights.mat",&secondWeights);
        _LoadMatrix16("XoRmat/secondBias.mat",&secondBias);
    }


    toEval.x=2;
    toEval.y=1;
    toEval.values[0]=(a==0?0:1);
    toEval.values[1]=(b==0?0:1);
    intermediate = multMatrix16(firstWeights,toEval);
    intermediate = addMatrix16(intermediate,firstBias);
    sigmoidify16(&intermediate);

    lastLayer = multMatrix16(secondWeights,intermediate);
    lastLayer = addMatrix16(lastLayer,secondBias);
    sigmoidify16(&lastLayer);

  

    return lastLayer.values[0]>lastLayer.values[1];
    
}

//Trains n times the neural network
void train(int n)
{
    srand(time(NULL));

    _LoadMatrix16("XoRmat/firstWeights.mat",&firstWeights);
    _LoadMatrix16("XoRmat/firstBias.mat",&firstBias);
    _LoadMatrix16("XoRmat/secondWeights.mat",&secondWeights);
    _LoadMatrix16("XoRmat/secondBias.mat",&secondBias);
    
    
    Matrix16 ErrorMatrix;
    ErrorMatrix.x = 2;
    ErrorMatrix.y = 1;
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
		 
		 
	 	 ErrorMatrix.values[getCoordinates16(0,0,ErrorMatrix)] = 
             (a != b) - lastLayer.values[0];
         ErrorMatrix.values[getCoordinates16(1,0,ErrorMatrix)] = 
             (a == b) - lastLayer.values[1];
		 
         backPropagate(ErrorMatrix,TotalError);	
    }

		
    _SaveMatrix16("XoRmat/firstWeights.mat",firstWeights);
    _SaveMatrix16("XoRmat/firstBias.mat",firstBias);
    _SaveMatrix16("XoRmat/secondWeights.mat",secondWeights);
    _SaveMatrix16("XoRmat/secondBias.mat",secondBias);


}





float CreationDeltaMatrix(float Error,float ActualOut,
        float PreviousOut,Matrix16 * DeltaMatrix, int j , float weight)
{
	float delta = -Error * ActualOut * (1 - ActualOut);
	DeltaMatrix->values[getCoordinates16(j,0,*DeltaMatrix)] += delta * weight;
	return delta * PreviousOut * 0.5; 
}



float DerivativeFormula(float delta, float hidden , float input)

{
	return delta * hidden * (1- hidden) * input * 0.5;
}



void backPropagate(Matrix16 ErrorMatrix, float TotalError)
{

	Matrix16 DeltaMatrix;
	DeltaMatrix.x = 4;
	DeltaMatrix.y = 1;
	for(int i = 0; i < DeltaMatrix.x; i++)
	{
		for(int j = 0; j < DeltaMatrix.y;j++)
		{
			DeltaMatrix.values[getCoordinates16(i,j,DeltaMatrix)] = 0.0;
		}
	}


	for(int i = 0; i < secondWeights.x ;i++)
	{


		secondBias.values[getCoordinates16(i,0,secondBias)] -= 
            DerivativeFormula(
                    ErrorMatrix.values[getCoordinates16(i,0,ErrorMatrix)] , 
                    lastLayer.values[getCoordinates16(i,0,lastLayer)] , 
                    1.0) ;

 
		for(int j = 0; j < secondWeights.y; j++)
		{
			secondWeights.values[getCoordinates16(i,j,secondWeights)] -= 
                CreationDeltaMatrix(
                   ErrorMatrix.values[getCoordinates16(i,0,ErrorMatrix)] , 
                   lastLayer.values[getCoordinates16(i,0,lastLayer)], 
                   intermediate.values[getCoordinates16(j,0,intermediate)], 
                   &DeltaMatrix , 
                   j , 
                   secondWeights.values[getCoordinates16(i,j,secondWeights)] );

		}
	}


	for(int i = 0; i < firstWeights.x;i++)
	{
		firstBias.values[getCoordinates16(i,0,firstBias)] -= 
            DerivativeFormula(
                   DeltaMatrix.values[getCoordinates16(i,0,DeltaMatrix)] ,
                   intermediate.values[getCoordinates16(i,0,intermediate)] , 
                   1.0) ;

		for(int j = 0; j < firstWeights.y; j++)
		{
			firstWeights.values[getCoordinates16(i,j,firstWeights)] -= 
                DerivativeFormula(
                   DeltaMatrix.values[getCoordinates16(i,0,DeltaMatrix)] , 
                   intermediate.values[getCoordinates16(i,0,intermediate)],
                   toEval.values[getCoordinates16(j,0,toEval)]) ;

		}
	}





}
