.RECIPEPREFIX = > 

all: OCR ; ./OCR.elf

OCR: OCR.o BigMatrix.o ocrNeuralNetwork.o
>   gcc -g -Wall -Wextra -std=c99 `pkg-config --cflags gtk+-3.0` OCR.o BigMatrix.o ocrNeuralNetwork.o -o OCR.elf  `pkg-config --libs gtk+-3.0` `sdl-config --cflags --libs` -lm -g

OCR.o: ./sourceCode/OCR.c ./sourceCode/BigMatrix.h ./sourceCode/ocrNeuralNetwork.h
>    gcc -c `pkg-config --cflags gtk+-3.0` ./sourceCode/OCR.c -Wall -Wextra -std=c99 `pkg-config --libs gtk+-3.0` `sdl-config --cflags --libs` 

image.o: ./sourceCode/image.c
>   gcc -c ./sourceCode/image.c -Wall -Wextra -std=c99 `sdl-config --cflags --libs` 

Matrix.o: ./sourceCode/Matrix.c
>    gcc -c -c -Wall -Wextra -std=c99 ./sourceCode/Matrix.c 

XoR.o: ./sourceCode/XoR.c
>   gcc -c -c -Wall -Wextra -std=c99 ./sourceCode/XoR.c 


interface.o: ./sourceCode/interface.c ./sourceCode/image.h
>	gcc -std=c99 `pkg-config --cflags gtk+-3.0` ./sourceCode/interface.c -c `pkg-config --libs gtk+-3.0` `sdl-config --cflags --libs` 


ocrNeuralNetwork.o: ./sourceCode/ocrNeuralNetwork.c
>   gcc -c -Wall -Wextra -std=c99 ./sourceCode/ocrNeuralNetwork.c 

BigMatrix.o: ./sourceCode/BigMatrix.c
>    gcc -c -Wall -Wextra -std=c99 ./sourceCode/BigMatrix.c


clean:
>	rm -rf *.o
>	rm -rf *.elf
>	rm -rf .*.swp
>	rm -rf .*.swo
>	rm -rf *.d
