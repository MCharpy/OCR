#ifndef IMAGE_H
#define IMAGE_H

#include <SDL.h>

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
SDL_Surface* Segment_line();
void extremum();
void DrawRect();


#endif
