#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "image.h"
#include "Matrix.h"
#include "XoR.h"

int main(){


    int choice = 0;

    while ((choice < 1 || choice > 3) && choice != 9)
    {
        printf("What would you like to do ?i\n     1. Process an image\n");
        printf("     2. Evalutate XoRi\n     3. Train XoR\n");
        printf("     9. Reset XoR values\n");
    
        scanf("%i",&choice);
    }
    char path[25];
    int val1, val2;
    switch (choice){
        case 1:
            printf("What is the path to your image ?\n");
            scanf("%20s",path);
            process_image(path);
            break;
        case 2:
            printf("XoR :\nFirst value\n");
            scanf("%i",&val1);
            printf("Second value\n");
            scanf("%i",&val2);
            int result = eval(val1==0?0:1,val2==0?0:1,0);
            printf("%i XoR %i -> %i",val1,val2,result);
            break;
        case 3:
            printf("How much training would you like to do?\n");
            scanf("%i",&val1);
            for (int i = 0; i < val1 ; i++)
            {
                train(10);
            }
            break;
        default : 
            break;
}
    if(choice == 9)
    {
        srand(time(NULL));


        Matrix16 firstWeights;
        Matrix16 firstBias;
        Matrix16 secondWeights;
        Matrix16 secondBias;
        _LoadMatrix16("firstWeights.mat",&firstWeights);
        _LoadMatrix16("firstBias.mat",&firstBias);
        _LoadMatrix16("secondWeights.mat",&secondWeights);
        _LoadMatrix16("secondBias.mat",&secondBias);

        for(int i = 0; i<8 ; i++)
        {
            firstWeights.values[i]=(float)rand()/RAND_MAX*2.0-1;
            firstBias.values[i]=(float)rand()/RAND_MAX*2.0-1;
            secondWeights.values[i]=(float)rand()/RAND_MAX*2.0-1;
            secondBias.values[i]=(float)rand()/RAND_MAX*2.0-1;

        }

        _SaveMatrix16("firstWeights.mat",firstWeights);
        _SaveMatrix16("firstBias.mat",firstBias);
        _SaveMatrix16("secondWeights.mat",secondWeights);
        _SaveMatrix16("secondBias.mat",secondBias);


    }


    //printf("%i",eval(1,0,0));
   
    /*
Matr:ix16 mat1;
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
