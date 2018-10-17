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

void backPropagate(Matrix16 ErrorMatrix);

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
    ErrorMatrix.values[0] = 0.0;
    ErrorMatrix.values[1] = 0.0;
    


    for (int i =0 ; i <n ; i++)
    {
         int a = rand()%2;
         int b = rand()%2;

         printf("%i %i -> %i\n",a,b,eval(a,b,1));

         ErrorMatrix.values[getCoordinates16(0,0,ErrorMatrix)] = (a != b) - lastLayer.values[0];
         ErrorMatrix.values[getCoordinates16(1,0,ErrorMatrix)] = (a == b) - lastLayer.values[1];
         	
	 //printf("%f",firstWeights.values[getCoordinates16(1,0,firstWeights)]);
         
         backPropagate(ErrorMatrix);
	 printMatrix16(firstWeights);
         //printMatrix16(secondWeights);
    }
    



    _SaveMatrix16("firstWeights.mat",firstWeights);
    _SaveMatrix16("firstBias.mat:",firstBias);
    _SaveMatrix16("secondWeights.mat",secondWeights);
    _SaveMatrix16("secondBias.mat",secondBias);


}



float BackP(float Error,float ActualOut,float PreviousOut)
{
	float lambda = Error * ActualOut * (1 - ActualOut);
	return lambda * PreviousOut * 0.5; 
}

void backPropagate(Matrix16 ErrorMatrix)
{
	float TotalError = 0;


	for(int x = 0; x < 2;x++)
	{
		TotalError += ErrorMatrix.values[getCoordinates16(x,0,ErrorMatrix)];
          
	}


	for(int i = 0; i < firstWeights.y;i++)
	{
		firstBias.values[getCoordinates16(i,0,firstBias)] += BackP(TotalError , intermediate.values[getCoordinates16(i,0,intermediate)] , toEval.values[getCoordinates16(i,0,toEval)]);
		for(int j = 0; j < firstWeights.x; j++)
		{
			firstWeights.values[getCoordinates16(i,j,firstWeights)] += BackP(TotalError , intermediate.values[getCoordinates16(i,0,intermediate)] ,toEval.values[getCoordinates16(i,0,toEval)]);
		}
	}


	for(int i = 0; i < 2;i++)
	{
		secondBias.values[getCoordinates16(i,0,secondBias)] += BackP(ErrorMatrix.values[getCoordinates16(i,0,ErrorMatrix)] , lastLayer.values[getCoordinates16(i,0,lastLayer)] , intermediate.values[getCoordinates16(i,0,intermediate)]); 
		for(int j = 0; j < 4; j++)
		{
			secondWeights.values[getCoordinates16(i,j,secondWeights)] += BackP(ErrorMatrix.values[getCoordinates16(i,0,ErrorMatrix)] , lastLayer.values[getCoordinates16(i,0,lastLayer)]  , intermediate.values[getCoordinates16(i,0,intermediate)] );
		}
	}
}
