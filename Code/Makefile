.RECIPEPREFIX = > 

all: OCR

OCR: OCR.o image.o
>   gcc -Wall -Wextra -std=c99 OCR.o image.o -o OCR.elf `sdl-config --cflags --libs`

OCR.o: ./sourceCode/OCR.c ./sourceCode/image.h
>    gcc -c ./sourceCode/OCR.c -Wall -Wextra -std=c99 `sdl-config --cflags --libs`

image.o: ./sourceCode/image.c
>   gcc -c ./sourceCode/image.c -Wall -Wextra -std=c99 `sdl-config --cflags --libs`
