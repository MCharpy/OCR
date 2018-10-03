.RECIPEPREFIX = > 

all: OCR

OCR: OCR.o colorRemoval.o
>   gcc -Wall -Wextra -std=c99 OCR.o colorRemoval.o -o OCR.elf

OCR.o: ./sourceCode/OCR.c ./sourceCode/colorRemoval.h
>    gcc -c ./sourceCode/OCR.c

colorRemoval.o: ./sourceCode/colorRemoval.c
>    gcc -c ./sourceCode/colorRemoval.c
