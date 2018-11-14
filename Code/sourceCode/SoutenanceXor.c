#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "image.h"
#include "Matrix.h"
#include "XoR.h"
#include "interface.h"

int main(){


    //Ask for choice of execution
    //Ask again if the choice is invalid
    int choice = 0;
    while ((choice < 1 || choice > 4) && choice != 9)
    {
        printf("What would you like to do ?i\n    1. Process an image\n");
        printf("    2. Evalutate XoRi\n    3. Train XoR\n");
        printf("    4. Preview Interface\n");
        printf("    9. Reset XoR values\n");
    
        scanf("%i",&choice);
    }
    int val1, val2;
    switch (choice){
        //Load text7.bmp image and execute process_image on it
        case 1:
            process_image("texte7.bmp");
            break;

        //Get values to XoR and prints the return value
        case 2:
            printf("XoR :\nFirst value\n");
            scanf("%i",&val1);
            printf("Second value\n");
            scanf("%i",&val2);
            int result = eval(val1==0?0:1,val2==0?0:1,0);
            printf("%i XoR %i -> %i",val1,val2,result);
            break;

        //Train n * 10 times the XoR neural network
        case 3:
            printf("How much training would you like to do?\n");
            scanf("%i",&val1);
            for (int i = 0; i < val1 ; i++)
            {
                train(10);
            }
            break;
        //Preview Interface
        case 4:
            interface(0, NULL);
        default : 
            break;
    }

    //Apply random values in the Matrix used in XoR
    if(choice == 9)
    {
        srand(time(NULL));


        Matrix16 firstWeights;
        Matrix16 firstBias;
        Matrix16 secondWeights;
        Matrix16 secondBias;
        _LoadMatrix16("XoRmat/firstWeights.mat",&firstWeights);
        _LoadMatrix16("XoRmat/firstBias.mat",&firstBias);
        _LoadMatrix16("XoRmat/secondWeights.mat",&secondWeights);
        _LoadMatrix16("XoRmat/secondBias.mat",&secondBias);

        for(int i = 0; i<8 ; i++)
        {
            firstWeights.values[i]=(float)rand()/RAND_MAX*2.0-1.0;
            firstBias.values[i]=(float)rand()/RAND_MAX-1.0;
            secondWeights.values[i]=(float)rand()/RAND_MAX*2.0-1.0;
            secondBias.values[i]=(float)rand()/RAND_MAX-1.0;

        }

        _SaveMatrix16("XoRmat/firstWeights.mat",firstWeights);
        _SaveMatrix16("XoRmat/firstBias.mat",firstBias);
        _SaveMatrix16("XoRmat/secondWeights.mat",secondWeights);
        _SaveMatrix16("XoRmat/secondBias.mat",secondBias);


    }
    return 0;
}
