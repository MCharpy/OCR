#ifndef NODES
#define NODES

#include <SDL.h>

typedef struct node node;
struct node  
{ 
    SDL_Surface* data; 
	int level;
    struct node *child; 
    struct node *sibling; 
}; 
 

node* newNode(int level);

#endif
