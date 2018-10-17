#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"
#include "XoR.h"

int main(int argc, char** argv){

    //printf("%i",eval(1,0,0));
    train(10);
    /*
    Matrix16 mat;
    mat.x = 2;
    mat.y = 2;

    Matrix16 b;

    for (int i = 0; i < 4; i++)
        mat.values[i]=i;

    printMatrix16(mat);
    printMatrix16(b);
    _SaveMatrix16("test.mat",mat);
    _LoadMatrix16("test.mat",&b);

*    printMatrix16(mat);
    printMatrix16(b);

    
      int val1 = 0;
      int val2 = 0;
      if(argc > 1)
        val1 = strtol(argv[1],NULL,10);
      if (argc > 2)
        val2 = strtol(argv[2],NULL,10);
      printf("%s",eval(val1,val2,0)?"true":"false");
     */
    return 0;
}
