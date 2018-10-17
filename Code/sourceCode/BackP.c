#include <stdio.h>



float BackP(float Error,float ActualOut,float PreviousOut)
{
	float lambda = (-Error) * ActualOut * (1 - ActualOut);
	return lambda * PreviousOut * 0.5; 
}


void Train()
{
	float TotalError = 0;
	for(int x = 0; x < 2;x++)
	{
		TotalError += ErrorMatrix[x,0];
	}

	for(int i = 0; i < 4;i++)
	{
		FirstBias[i,0] += BackP(TotalError , Intermediate[i,0] , Input[i,0]);
		for(int j = 0; j < 2; j++)
		{
			FirstMatrix[i,j] += BackP(TotalError , Inter;ediate[i,0] ,Input[i,0]);
		}
	}


	for(int i = 0; i < 2;i++)
	{
		SecondBias[i,0] += BackP(Error[i,0] , Last[i,0] , Intermediate[i,0]); 
		for(int j = 0; j < 4; j++)
		{
			SecondMatrix[i,j] += BackP(Error[i,0] , Last[i,0] , Intermediate[i,0]);
		}
	}
}
