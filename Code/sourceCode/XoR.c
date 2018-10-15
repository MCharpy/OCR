#include <stdio.h>
#include "Matrix.h"

Matrix16 firstWeights;
Matrix16 firstBias;
Matrix16 secondWeights;
Matrix16 secondBias;

Matrix16 intermediate;
Matrix16 lastLayer;


int eval(int a, int b , int training){
    
    if(!training)
    {
        _LoadMatrix16("firstWeights.mat",&firstWeights);
        _LoadMatrix16("firstBias.mat:",&firstBias);
        _LoadMatrix16("secondWeights.mat",&firstWeights);
        _LoadMatrix16("secondBias.mat",&firstWeights);


    }

    Matrix16 toEval;
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

    return lastLayer.values[0]>lastLayer.values[1];
}

