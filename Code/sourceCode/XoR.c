#include <stdio.h>
#include "Matrix.h"
#include <time.h>
#include <stdlib.h>


Matrix16 firstWeights;
Matrix16 firstBias;
Matrix16 secondWeights;
Matrix16 secondBias;

Matrix16 toEval;

Matrix16 intermediate;
Matrix16 lastLayer;


int eval(int a, int b , int training){
    
    if(!training)
    {
        _LoadMatrix16("firstWeights.mat",&firstWeights);
        _LoadMatrix16("firstBias.mat",&firstBias);
        _LoadMatrix16("secondWeights.mat",&secondWeights);
        _LoadMatrix16("secondBias.mat",&secondBias);
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

void train(int n)
{
    srand(time(NULL));

    _LoadMatrix16("firstWeights.mat",&firstWeights);
    _LoadMatrix16("firstBias.mat",&firstBias);
    _LoadMatrix16("secondWeights.mat",&secondWeights);
    _LoadMatrix16("secondBias.mat",&secondBias);
    
    
    Matrix16 ErrorMatrix;
    ErrorMatrix.x = 2;
    ErrorMatrix.y = 1;
    ErrorMatrix.values[0] = 0;
    ErrorMatrix.values[1] = 0;


    for (int i =0 ; i <n ; i++)
    {
         int a = rand()%2;
         int b = rand()%2;

         printf("%i %i -> %i\n",a,b,eval(a,b,1));
         Matrix16 localError;
         localError.x = 2;
         localError.y = 1;

         localError.values[0] =toEval.values[0] a != b;
         localError.values[1] =a == b;
         ErrorMatrix = addMatrix16(ErrorMatrix,localError);

    }
    
    //multMatrixValue
    ErrorMatrix.values[0] = ErrorMatrix.values[0]/(long)n;
    ErrorMatrix.values[1] = ErrorMatrix.values[1]/(long)n;

    backPropagate();


    _SaveMatrix16("firstWeights.mat",firstWeights);
    _SaveMatrix16("firstBias.mat:",firstBias);
    _SaveMatrix16("secondWeights.mat",secondWeights);
    _SaveMatrix16("secondBias.mat",secondBias);


}



float BackP(float Error,float ActualOut,float PreviousOut)
{
	float lambda = (-Error) * ActualOut * (1 - ActualOut);
	return lambda * PreviousOut * 0.5; 
}

void backPropagate( )
{
	float TotalError = 0;

    Matrix16 ErrorMatrix;

	for(int x = 0; x < 2;x++)
	{
		TotalError += ErrorMatrix.values[GetCoordinates16(x,0,ErrorMatrix)];
          
	}

	for(int i = 0; i < 4;i++)
	{
		firstBias.values[GetCoordinates16(i,0,firstBias)] += BackP(TotalError , intermediate.values[GetCoordinates16(i,0,intermediate)] , toEval.values[GetCoordinates16(i,0,toEval)]);
		for(int j = 0; j < 2; j++)
		{
			firstWeights.values[GetCoordinates16(i,j,firstWeights)] += BackP(TotalError , intermediate.values[GetCoordinates16(i,0,intermediate)] ,toEval.values[GetCoordinates16(i,0,toEval)]);
		}
	}


	for(int i = 0; i < 2;i++)
	{
		secondBias.values[GetCoordinates16(i,0,secondBias)] += BackP(ErrorMatrix.values[GetCoordinates16(i,0,ErrorMatrix)] , lastLayer.values[GetCoordinates16(i,0,lastLayer)] , intermediate.values[GetCoordinates16(i,0,intermediate)]); 
		for(int j = 0; j < 4; j++)
		{
			secondWeights.values[GetCoordinates16(i,j,secondWeights)] += BackP(ErrorMatrix.values[GetCoordinates16(i,0,ErrorMatrix)] , lastLayer.values[GetCoordinates16(i,0,lastLayer)]  , intermediate.values[GetCoordinates16(i,0,intermediate)] );
		}
	}
}
