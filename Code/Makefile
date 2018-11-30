.RECIPEPREFIX = > 

all: OCR ; ./OCR.elf

OCR: OCR.o BigMatrix.o ocrNeuralNetwork.o image.o node.o
>   gcc -g -Wall -Wextra -std=c99 `pkg-config --cflags gtk+-3.0` OCR.o BigMatrix.o ocrNeuralNetwork.o image.o -o OCR.elf  `pkg-config --libs gtk+-3.0` `pkg-config --libs sdl` -lSDL_image -lSDL_gfx -lm -g

OCR.o: ./sourceCode/OCR.c ./sourceCode/BigMatrix.h ./sourceCode/image.h
>    gcc -c `pkg-config --cflags gtk+-3.0` ./sourceCode/OCR.c -Wall -Wextra -std=c99 `pkg-config --libs gtk+-3.0` `sdl-config --cflags --libs` 

node.o: ./sourceCode/node.c
>   gcc -c ./sourceCode/node.c -Wall -Wextra -std=c99 `pkg-config --cflags sdl` -MMD

image.o: ./sourceCode/image.c ./sourceCode/BigMatrix.h ./sourceCode/ocrNeuralNetwork.h ./sourceCode/node.h
>   gcc -c ./sourceCode/image.c -Wall -Wextra -std=c99 `pkg-config --cflags sdl` -MMD

Matrix.o: ./sourceCode/Matrix.c
>    gcc -c -c -Wall -Wextra -std=c99 ./sourceCode/Matrix.c 

XoR.o: ./sourceCode/XoR.c
>   gcc -c -c -Wall -Wextra -std=c99 ./sourceCode/XoR.c 


interface.o: ./sourceCode/interface.c 
>	gcc -std=c99 `pkg-config --cflags gtk+-3.0` ./sourceCode/interface.c -c `pkg-config --libs gtk+-3.0` `sdl-config --cflags --libs` 


ocrNeuralNetwork.o: ./sourceCode/ocrNeuralNetwork.c ./sourceCode/BigMatrix.h
>   gcc -c -Wall -Wextra -std=c99 ./sourceCode/ocrNeuralNetwork.c `pkg-config --cflags sdl` -MMD

BigMatrix.o: ./sourceCode/BigMatrix.c
>    gcc -c -Wall -Wextra -std=c99 ./sourceCode/BigMatrix.c


clean:
>	rm -rf *.o
>	rm -rf *.elf
>	rm -rf .*.swp
>	rm -rf .*.swo
>	rm -rf *.d
