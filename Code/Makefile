.RECIPEPREFIX = > 

all: OCR

OCR: OCR.o Matrix.o
>   gcc -Wall -Wextra -std=c99 OCR.o Matrix.o -o OCR.elf

OCR.o: ./sourceCode/OCR.c ./sourceCode/Matrix.h
>    gcc -c ./sourceCode/OCR.c

Matrix.o: ./sourceCode/Matrix.c
>    gcc -c ./sourceCode/Matrix.c
