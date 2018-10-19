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

void backPropagate(Matrix16 ErrorMatrix, float TotalError);
float BackP(float Error,float ActualOut,float PreviousOut,Matrix16 * DeltaMatrix, int j , float weight);


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

         //printf("%i %i -> %i\n",a,b,eval(a,b,1));
		 //for(int i = 0; i < n; i++)
		 //{
		 printf("%i %i -> %i\n",a,b,eval(a,b,1));

         //	error1 += (a != b) - lastLayer.values[0];
         //	error2 += (a == b) - lastLayer.values[1];
		 float error1 = (a != b) - lastLayer.values[0];
		 float error2 = (a == b) - lastLayer.values[1];
	
         //}
		 
	 	 ErrorMatrix.values[getCoordinates16(0,0,ErrorMatrix)] = (a != b) - lastLayer.values[0];
         ErrorMatrix.values[getCoordinates16(1,0,ErrorMatrix)] = (a == b) - lastLayer.values[1];
         float TotalError = (error1*error1)/2 + (error2*error2)/2;
		 //printf("%f",TotalError);
         backPropagate(ErrorMatrix,TotalError);
	 	 //printMatrix16(intermediate);
         //printMatrix16(secondWeights);
		
    }

		
    _SaveMatrix16("firstWeights.mat",firstWeights);
    _SaveMatrix16("firstBias.mat",firstBias);
    _SaveMatrix16("secondWeights.mat",secondWeights);
    _SaveMatrix16("secondBias.mat",secondBias);


}





float BackP(float Error,float ActualOut,float PreviousOut,Matrix16 * DeltaMatrix, int j , float weight)
{
	float delta = -Error * ActualOut * (1 - ActualOut);
	DeltaMatrix->values[getCoordinates16(j,0,*DeltaMatrix)] += delta * weight;
	return delta * PreviousOut * 0.5; 
}



float BackPFirstLayer(float delta, float hidden , float input)

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


		secondBias.values[getCoordinates16(i,0,secondBias)] -= BackPFirstLayer(ErrorMatrix.values[getCoordinates16(i,0,ErrorMatrix)] , lastLayer.values[getCoordinates16(i,0,lastLayer)] , 1.0) ;

 
		for(int j = 0; j < secondWeights.y; j++)
		{
			secondWeights.values[getCoordinates16(i,j,secondWeights)] -= BackP(ErrorMatrix.values[getCoordinates16(i,0,ErrorMatrix)] , lastLayer.values[getCoordinates16(i,0,lastLayer)], intermediate.values[getCoordinates16(j,0,intermediate)], &DeltaMatrix , j , secondWeights.values[getCoordinates16(i,j,secondWeights)] );

		}
	}
	//printMatrix16(DeltaMatrix);




	for(int i = 0; i < firstWeights.x;i++)
	{
		firstBias.values[getCoordinates16(i,0,firstBias)] -= BackPFirstLayer( DeltaMatrix.values[getCoordinates16(i,0,DeltaMatrix)] , intermediate.values[getCoordinates16(i,0,intermediate)] , 1.0) ;

	
		for(int j = 0; j < firstWeights.y; j++)
		{
			firstWeights.values[getCoordinates16(i,j,firstWeights)] -= BackPFirstLayer( DeltaMatrix.values[getCoordinates16(i,0,DeltaMatrix)] , intermediate.values[getCoordinates16(i,0,intermediate)] , toEval.values[getCoordinates16(j,0,toEval)]) ;

		}
	}





}
