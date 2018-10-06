#include <stdio.h>
#include "Matrix.h"


int main(){
    Matrix16 patate;
    patate.x=2;
    patate.y=2;
    for ( int i = 1; i< 5; i++){
        patate.values[i-1]=i;
    }
    printMatrix16(MatrixMult16(patate,patate));

    return 0;
}
