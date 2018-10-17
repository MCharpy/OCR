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

    printMatrix16(secondWeights);

    toEval.x=2;
    toEval.y=1;
    toEval.values[0]=(a==0?0:1);
    toEval.values[1]=(b==0?0:1);
    intermediate = multMatrix16(firstWeights,toEval);
    intermediate = (intermediate,firstBias);
    sigmoidify16(&intermediate);

    lastLayer = multMatrix16(secondWeights,intermediate);
    lastLayer = addMatrix16(lastLayer,secondBias);
    sigmoidify16(&lastLayer);

   /* printf("toEval");
    printMatrix16(toEval);
    printf("1s weight");
    printMatrix16(firstWeights);
    printf("1s bias");
    printMatrix16(firstBias);
    printf("intermediate");
    printMatrix16(intermediate);
    printf("2nd weight");
    printMatrix16(secondWeights);
    printf("secondBias");
    printMatrix16(secondBias);
    printf("lastLayer");
    printMatrix16(lastLayer);*/

    return lastLayer.values[0]>lastLayer.values[1];
    
}

void train(int n)
{
    srand(time(NULL));

    _LoadMatrix16("firstWeights.mat",&firstWeights);
    _LoadMatrix16("firstBias.mat",&firstBias);
    _LoadMatrix16("secondWeights.mat",&secondWeights);
    _LoadMatrix16("secondBias.mat",&secondBias);

    for (int i =0 ; i <n ; i++)
    {
         int a = rand()%2;
         int b = rand()%2;

         printf("%i %i -> %i\n",a,b,eval(a,b,1));
    }

    //backpropagate


    _SaveMatrix16("firstWeights.mat",firstWeights);
    _SaveMatrix16("firstBias.mat:",firstBias);
    _SaveMatrix16("secondWeights.mat",secondWeights);
    _SaveMatrix16("secondBias.mat",secondBias);


}

