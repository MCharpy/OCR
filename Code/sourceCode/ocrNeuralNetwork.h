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
int eval(Matrix toEval , int training);
void train(Matrix toEval, char trueResult);
float CreationDeltaMatrix(float Error,float ActualOut,
        float PreviousOut,Matrix * DeltaMatrix, int j , float weight);
float DerivativeFormula(float delta, float hidden , float input);
void backPropagate(Matrix ErrorMatrix, float TotalError);
