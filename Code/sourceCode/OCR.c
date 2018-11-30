#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "ocrNeuralNetwork.h"
#include "BigMatrix.h"

int main(int argc,char **argv){
    //train(1000);
   

    //char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,:;i\"'(){}[]!?@$%&-+=";
    //printf("%s %lu",alphabet,strlen(alphabet));
  

    
   /*  Matrix weights1 = createMatrix(355,784);
    Matrix bias1 = createMatrix(355,1);
  Matrix weights2 = createMatrix(84,355,84);
    Matrix bias2 = createMatrix(84,1);


    _SaveMatrix("OCRmat/weights1.mat",&weights1);
    _SaveMatrix("OCRmat/bias1.mat",&bias1);
    _SaveMatrix("OCRmat/weights2.mat",&weights2);
    _SaveMatrix("OCRmat/bias2.mat",&bias2);*/
    

    /*Matrix toTest = _LoadMatrix("testmat.mat");
        for(int i = 0 ; i< toTest.x*toTest.y; i++)
        {
            toTest.values[i] = 1;
        }
        _SaveMatrix("testmat.mat",&toTest);
*/
    if(argc == 1)
    {
        Matrix toTest = _LoadMatrix("testmat.mat");
        train(&toTest,'+');
    }
    else
    {
    printf("%s\n",argv[0]);
    resetMatrix("OCRmat/weights1.mat",0);
    resetMatrix("OCRmat/bias1.mat",1);
    resetMatrix("OCRmat/weights2.mat",0);
    resetMatrix("OCRmat/bias2.mat",1);
    }
   
}

