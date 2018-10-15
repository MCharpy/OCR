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
        //Load firstWeight firstBias secondWeights secondBiasi
        firstWeights.x=4;
        firstWeights.y=2;
        secondWeights.x=2;
        secondWeights.y=4;

        firstBias.x=4;
        firstBias.y=1;
        secondBias.x=2;
        secondBias.y=1;

        for (int i = 0; i<8 ; i++)
        {
            firstWeights.values[i]=i/8.0;
            secondWeights.values[i]=i/8.0;
            firstBias.values[i]=i/8.0;
            secondBias.values[i]=i/8.0;
        }
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

