#include <stdlib.h>
#include <SDL.h>

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

