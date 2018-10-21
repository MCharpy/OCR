.RECIPEPREFIX = > 

all: OCR

OCR: OCR.o image.o Matrix.o XoR.o interface.o
>   gcc -Wall -Wextra -std=c99 -lm `pkg-config --cflags gtk+-3.0` OCR.o image.o Matrix.o XoR.o interface.o -o OCR.elf  `pkg-config --libs gtk+-3.0` `sdl-config --cflags --libs`

OCR.o: ./sourceCode/OCR.c ./sourceCode/image.h ./sourceCode/Matrix.h ./sourceCode/XoR.h ./sourceCode/interface.h
>    gcc -c `pkg-config --cflags gtk+-3.0` ./sourceCode/OCR.c -Wall -Wextra -std=c99 `pkg-config --libs gtk+-3.0` `sdl-config --cflags --libs`

image.o: ./sourceCode/image.c
>   gcc -c ./sourceCode/image.c -Wall -Wextra -std=c99 `sdl-config --cflags --libs`

Matrix.o: ./sourceCode/Matrix.c
>    gcc -c ./sourceCode/Matrix.c

XoR.o: ./sourceCode/XoR.c
>   gcc -c ./sourceCode/XoR.c


interface.o: ./sourceCode/interface.c
>	gcc -std=c99 `pkg-config --cflags gtk+-3.0` ./sourceCode/interface.c -c `pkg-config --libs gtk+-3.0`


clean:
>	rm -rf *.o
>	rm -rf *.elf
>	rm -rf .*.swp
>	rm -rf .*.swo
>	rm -rf *.d
