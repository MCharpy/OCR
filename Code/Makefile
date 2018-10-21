.RECIPEPREFIX = > 

all: OCR

OCR: OCR.o image.o
>   gcc -Wall -Wextra -std=c99 OCR.o image.o -o OCR.elf `sdl-config --cflags --libs`

interface: ./sourceCode/interface.c
>	gcc -Wall -Wextra -std=c99 `pkg-config --cflags gtk+-3.0` ./sourceCode/interface.c -o interface.elf `pkg-config --libs gtk+-3.0`

OCR.o: ./sourceCode/OCR.c ./sourceCode/image.h
>    gcc -c ./sourceCode/OCR.c -Wall -Wextra -std=c99 `sdl-config --cflags --libs`

image.o: ./sourceCode/image.c
>    gcc -c ./sourceCode/image.c -Wall -Wextra -std=c99 `sdl-config --cflags --libs`

clean:
>	rm -rf *.o
>	rm -rf *.elf
>	rm -rf .*.swp
>	rm -rf .*.swo
>	rm -rf *.d
