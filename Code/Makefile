.RECIPEPREFIX = > 
 

interface.o: ./sourceCode/interface.c
>	gcc -Wall -Wextra -std=c99 `pkg-config --cflags gtk+-3.0` ./sourceCode/interface.c -o interface.elf `sdl-config --cflags --libs` `pkg-config --libs gtk+-3.0`

image.o: ./sourceCode/image.c
>    gcc -c ./sourceCode/image.c -Wall -Wextra -std=c99 `sdl-config --cflags --libs`

clean:
>	rm -rf *.o
>	rm -rf *.elf
>	rm -rf .*.swp
>	rm -rf .*.swo
>	rm -rf *.d
