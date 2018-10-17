#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"
#include "XoR.h"

int main(int argc, char** argv){

    //printf("%i",eval(1,0,0));
    train(100);

   
    /*
    Matrix16 mat1;
    Matrix16 mat2;
    mat1.x = 4;
    mat1.y = 2;
    
    mat2.x = 4;
    mat2.y = 2;


    for (int i = 0; i < 8; i++)
    {
        mat1.values[i]=i;
        mat2.values[i]=i-0.2;
    }


    printMatrix16(mat1);
    printMatrix16(mat2);

    Matrix16 a = addMatrix16(mat1,mat2);
    printMatrix16(a);
    a = addMatrix16(a,mat1);
    printMatrix16(a);
    sigmoidify16(&a);
    printMatrix16(a);
    
      int val1 = 0;
      int val2 = 0;
      if(argc > 1)
        val1 = strtol(argv[1],NULL,10);
      if (argc > 2)
        val2 = strtol(argv[2],NULL,10);
      printf("%s",eval(val1,val2,0)?"true":"false");*/
     
    return 0;
}
