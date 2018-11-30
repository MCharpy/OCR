#ifndef IMAGE
#define IMAGE

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
void extremum();
void DrawRect();
void Segment_line();

void treesation();
SDL_Surface* extracall();
void dfs();
SDL_Surface * contour();
Matrix Surface_to_Matrix();
char* imagePath = "test/1.bmp";

typedef struct node node;
struct node  
{ 
    SDL_Surface* data; 
	int level;
    struct node *child; 
    struct node *sibling; 
}; 
 
struct node* newNode(int level) 
{ 
	struct node* node = malloc(sizeof(struct node)); 
	node->data = NULL;
	node->level = level;
	node->child = NULL; 
	node->sibling = NULL; 
	return node; 
} 
#endif
