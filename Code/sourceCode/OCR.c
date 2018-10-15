#include <stdio.h>
#include "Matrix.h"
#include "XoR.h"

int main(){
    Matrix16 patate;
    Matrix16 patate2;
    patate.x=2;
    patate.y=2;
    for ( int i = 1; i< 5; i++){
        patate.values[i-1]=i;
        patate2.values[i-1]=i;
    }
    patate2.x=2;
    patate2.y=1;

    printMatrix16(patate);
    printMatrix16(patate2);
    
    
    printMatrix16(addMatrix16(patate,patate2));

    return 0;
}
