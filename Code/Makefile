.RECIPEPREFIX = > 

all: OCR

OCR: OCR.o Matrix.o XoR.o
>   gcc -Wall -Wextra -std=c99 -lm OCR.o Matrix.o XoR.o -o OCR.elf

OCR.o: ./sourceCode/OCR.c ./sourceCode/Matrix.h ./sourceCode/XoR.h
>    gcc -c ./sourceCode/OCR.c

Matrix.o: ./sourceCode/Matrix.c
>    gcc -c ./sourceCode/Matrix.c

XoR.o: ./sourceCode/XoR.c
>   gcc -c ./sourceCode/XoR.c
