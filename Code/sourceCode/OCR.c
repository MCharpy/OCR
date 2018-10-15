#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"
#include "XoR.h"

int main(int argc, char** argv){

    int val1 = 0;
    int val2 = 0;
    if(argc > 1)
        val1 = strtol(argv[1],NULL,10);
    if (argc > 2)
        val2 = strtol(argv[2],NULL,10);
    printf("%s",eval(val1,val2,0)?"true":"false");
    return 0;
}
