#ifndef IMAGE
#define IMAGE

#include <SDL.h>
#include "BigMatrix.h"
#include "node.h"
#include "ocrNeuralNetwork.h"

void trainImage();
int process_image(char * path);
Uint32 getpixel();
Uint32 putpixel();
SDL_Surface* colortogray();
SDL_Surface* blacknwhite();
void RLSA_height();
void RLSA_width();
SDL_Surface* init_state();
SDL_Surface* copy();
SDL_Surface* RLSA();
void extremum();
void DrawRect();
void Segment_line();

void treesation();
SDL_Surface* extracall();
void dfs();
SDL_Surface * contour();
Matrix Surface_to_Matrix();

#endif
