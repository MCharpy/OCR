.RECIPEPREFIX = >

# Makefile

CC = gcc

CPPFLAGS = `pkg-config --cflags sdl` -MMD
CFLAGS = -Wall -Wextra -std=c99 -g #-O2
LDFLAGS =
LDLIBS = -lSDL_image -lSDL_gfx -lm `pkg-config --libs sdl`

SRC = sourceCode/main.c sourceCode/BigMatrix.c sourceCode/node.c sourceCode/ocrNeuralNetwork.c sourceCode/image.c

OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}


all: OCR

OCR: ${OBJ}
>   ${CC} ${OBJ} ${LDLIBS} -o OCR.elf 
.PHONY: clean

clean:
>   ${RM} ${OBJ}   # remove object files
>   ${RM} ${DEP}   # remove dependency files
>       ${RM} OCR.elf     # remove main program
>   ${RM} *.bmpi

-include ${DEP}

# END
