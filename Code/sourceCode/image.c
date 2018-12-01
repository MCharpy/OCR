#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include<err.h>
#include "ocrNeuralNetwork.h"
#include "node.h"
#include "BigMatrix.h"
#include <stddef.h> 


char alpha[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,:;i\"'(){}[]!?@$%&-+=";

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
char * dfs();
SDL_Surface * contour();
Matrix Surface_to_Matrix();

char *text;

void trainImage(char* path, char* texxt)
{
	text = texxt;
    SDL_Surface* image = SDL_LoadBMP(path);
    node *T = newNode(0);
    T->data = copy(image);
    node *t1 = T;
    Segment_line(RLSA(copy(image),20,20),copy(image),T,0);
    dfs(t1,16,1);
	//SDL_FreeSurface(image);
    
}

char *str;

char *evalImage(char *path)
{

    SDL_Surface* image = SDL_LoadBMP(path);
    node *T = newNode(0);
    T->data = copy(image);
    node *t1 = T;
    Segment_line(RLSA(copy(image),25,5),copy(image),T,0);
	text = "\0";
    str = malloc(sizeof(char));
    *str = 0;
	dfs(t1,16,0);
    return str;

}

/**
 * \fn Uint32 putpixel(SDL_Surface *surface,int x,int y,Uint32 pixel)
 * \brief put the pixel on the suface which is in (x,y).
 * \param surface Your image.
 * \param (x,y) the position can't be negative.
 * \param pixel The pixel to put in Uint32 and can't be null.
 */


Uint32 putpixel(SDL_Surface *surface,int x,int y,Uint32 pixel)
{
	int bpp= surface->format->BytesPerPixel;
	Uint8 *p = (Uint8*)surface ->pixels +y*surface->pitch +x *bpp;
	switch(bpp)
	{
		case 1:
			*p = pixel;
			 break;
		case 2:
			*(Uint16*)p=pixel;
			break;
		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
			{
				 p[0] = (pixel >> 16) & 0xff;
				 p[1] = (pixel >> 8) & 0xff;
				 p[2] =  pixel  & 0xff;
			}

			else
			{
				 p[2] = (pixel >> 16) & 0xff;
				 p[1] = (pixel >> 8) & 0xff;
				 p[0] =  pixel  & 0xff;
			}
			break;
				
		case 4:
			 *(Uint32*)p = pixel;
			 break;
	}
	return 0;
}

Uint32 getpixel(SDL_Surface*surface, int x, int  y)
{
	int bpp= surface->format->BytesPerPixel;
	Uint8 *p = (Uint8*)surface ->pixels +y*surface->pitch +x *bpp;
	switch(bpp)
	{
		case 1 : 
			return *p;
		case 2:
			return *(Uint16 *) p;
		case 3:
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
				return p[0] << 16 | p[1] << 8 | p[2];
			else
				return p[0] | p[1] << 8 | p[2] <<16;
		case 4:
			return *(Uint32 *)p;

		default : 
			return 0;
	}
}
SDL_Surface* colortogray(SDL_Surface* surface)
{
	Uint8 r,g,b;
	int gray;
	for(int i=0;i< surface->w;i++)
	{
		for(int j=0;j< surface->h;j++)
			{
				SDL_GetRGB(getpixel(surface,i,j),surface->format,&r,&g,&b);
				gray = (r + g + b)/3;
				Uint32 pixel = SDL_MapRGB(surface->format,gray,gray,gray);
				putpixel(surface,i,j,pixel);

			}
	}
	return surface;
	
}
SDL_Surface* blacknwhite(SDL_Surface* surface)
{
	Uint8 r,g,b,a;
	Uint32 pixel;
	for(int i=0;i< surface->w;i++)
	{
		for(int j=0;j< surface->h;j++)
			{
				SDL_GetRGBA(getpixel(surface,i,j),surface->format,&r,&g,&b,&a);
				if (r<126 )
					pixel = SDL_MapRGBA(surface->format,0,0,0,a);
				else
					pixel = SDL_MapRGBA(surface->format,255,255,255,a);

				putpixel(surface,i,j,pixel);

			}
	}
	return surface;
	
}
void RLSA_height(SDL_Surface* surface,int threash)
{
	int Nth_Zero = 0;
	Uint8 r,g,b;
	Uint32 pixel = SDL_MapRGB(surface->format,0,0,0);
	for(int i=0 ;surface->w > i ; i++)
	{
		for(int j = 0; surface->h > j;j++)
		{
			SDL_GetRGB(getpixel(surface,i,j),surface->format,&r,&g,&b);
			for(int k = j; r != 0 && k < surface->h-1;k++)
			{		
				SDL_GetRGB(getpixel(surface,i,k),surface->format,&r,&g,&b);
				Nth_Zero++;
			}
			if(Nth_Zero >= threash)
				j += Nth_Zero ;
			else
			{
				for(int l = j-1<0?0:j-1 ; l <= j + Nth_Zero && l< surface->h-1;l++)
				{
					putpixel(surface,i,l,pixel);
				}
				j = j + Nth_Zero ;
			}
			Nth_Zero = 0;
		}

		
	}
}
					
void RLSA_width(SDL_Surface* surface, int threash)
{
	int Nth_Zero = 0;
	Uint8 r,g,b;
	Uint32 pixel = SDL_MapRGB(surface->format,0,0,0);
	for(int i=0 ;surface->h > i ; i++)
	{
		for(int j = 0; surface->w > j; j++)
		{
			SDL_GetRGB(getpixel(surface,j,i),surface->format,&r,&g,&b);
			for(int k = j; r != 0 && k < surface->w-1;k++)
			{		
				SDL_GetRGB(getpixel(surface,k,i),surface->format,&r,&g,&b);
				Nth_Zero++;
			}
			if(Nth_Zero >= threash)
				j += Nth_Zero;
 			else
			{
				for(int l = j-1<0?0:j-1; l <= j + Nth_Zero && l < surface->w-1;l++)
				{	
					putpixel(surface,l,i, pixel);
				}
				j = j + Nth_Zero ;
			}
			Nth_Zero = 0;
		}		
	}
}
					
					

SDL_Surface* init_state( SDL_Surface* old_surface, SDL_Surface* new)
{
	for(int i = 0; old_surface->w > i ; i++)
	{
		for(int j = 0; old_surface->h > j ; j++)
		{
			putpixel(old_surface,i,j,getpixel(new,i,j));
		}
	}
	return old_surface;
}

SDL_Surface* copy(SDL_Surface* surface)
{
	SDL_Surface* new =   SDL_CreateRGBSurface(0,surface->w, surface->h,32, 0, 0, 0, 0);
	for(int i = 0;i<surface->w;i++)
	{
		for(int j = 0; j<surface->h;j++)
		{
			putpixel(new, i , j ,getpixel(surface,i,j));
		}
	}
//	SDL_FreeSurface(surface);
	return new;
}

SDL_Surface* RLSA(SDL_Surface* surface, int threash1, int threash2)
{
	SDL_Surface* cp1 =  copy(surface);
	SDL_Surface* cp2 = copy(surface);
	RLSA_width(blacknwhite(colortogray(cp1)), threash1);
	RLSA_height(blacknwhite(colortogray(cp2)), threash2);
	Uint8 r1,r2,g,b,gg,bb;
	for(int i = 0; i < surface->w; i++)
	{
		for(int j = 0; j < surface->h; j++)
		{
			SDL_GetRGB(getpixel(cp1,i,j),surface->format,&r1,&g,&b);
			SDL_GetRGB(getpixel(cp2,i,j),surface->format,&r2,&gg,&bb);
			if(0 == r2 || r1 == 0)
			{
				putpixel(surface,i,j,SDL_MapRGB(surface->format,0,0,0));
			}
			else
			{
				putpixel(surface,i,j,
						SDL_MapRGB(surface->format,255,255,255));
			}
		}
	}
	SDL_FreeSurface(cp1);
	SDL_FreeSurface(cp2);
	return surface;

}

				
void Segment_line(SDL_Surface* RLSA_surface, SDL_Surface* surface,node* T,
		int level)
{	Uint8 r1,g1,b1;
	int tab[4]={0,0,0,0};
	level = level+1;
	T->child = newNode(level);
	T =T->child;
	for(int i = 0; i <surface->w; i++)
	{
		for(int j = 0; j < surface->h; j++)
		{
			SDL_GetRGB(getpixel(RLSA_surface,i,j),
					RLSA_surface->format,&r1,&g1,&b1);
			if(r1 == 0)
			{
				tab[3] = 0;
				tab[1] = 0;
				tab[2] = j;
				tab[0] = i;
				extremum(tab,RLSA_surface,i,j);
				SDL_Surface *a = extracall(copy(surface) , tab[0],tab[1],tab[2],tab[3]);
				if(a != NULL)
				{
					if(T->data == NULL)
						T->data = a;
					if(level ==1)
					{
						if(T->data)
							Segment_line(RLSA(copy(T->data),25,5),copy(T->data),T,level);
					}
					if(level ==2)
					{
						if(T->data)
							Segment_line(RLSA(copy(T->data),25,5),copy(T->data),T,level);
					}
					if(level ==3)
					{
						if(T->data)
							Segment_line(RLSA(copy(T->data),0,5),copy(T->data),T,level);
					}
					T->sibling = newNode(level);
					T=T->sibling;
				}

			}
		}
	}
	SDL_FreeSurface(RLSA_surface);
	SDL_FreeSurface(surface);
}

void extremum(int* tab, SDL_Surface * surface,int i,int j)
{
	Uint8 r,g,b;
	SDL_GetRGB(getpixel(surface,i,j),surface->format,&r,&g,&b);
	if(r != 255)
	{
		tab[0] = i	< tab[0] ? i : tab[0];
		tab[1] = i >= tab[1] ? i : tab[1];
		tab[2] = j < tab[2] ? j  : tab[2];
		tab[3] = j >= tab[3] ? j : tab[3];

		putpixel(surface,i,j,SDL_MapRGB(surface->format,255,255,255));
		if(i+1<surface->w)
			extremum(tab, surface,i+1,j);
		if(i>0)
			extremum(tab, surface,i-1,j);
		if(j+1 < surface->h)
			extremum(tab, surface,i,j+1);
		if(j>0)
			extremum(tab, surface,i,j-1);
		if(j>0 && i+1<surface->w)
			extremum(tab, surface,i+1,j-1);
		if(i>0 && j+1<surface->h)
			extremum(tab, surface,i-1,j+1);
		if(j+1<surface->h && i+1<surface->w)
			extremum(tab, surface,i+1,j+1);
		if(j>0 && i>0)
			extremum(tab, surface,i-1,j-1);




	}
}

void DrawRect(int x1,int x2,int y1,int y2, SDL_Surface *surface)
{
	for(int i = x1; i <= x2; i++)
	{
		for(int j = y1;  j<= y2; j++)
			{
				putpixel(surface,i,j,SDL_MapRGB(surface->format,254,0,0));
			}
	}
}

SDL_Surface* extracall(SDL_Surface* surface,int x1,int x2,int y1, int y2)
{
	if(x2-x1 > 0 || y2 - y1 >0)
	{
		SDL_Surface* surface2 =  SDL_CreateRGBSurface(0,x2-x1+1, y2-y1+1, 32, 0, 0, 0, 0);
		for(int i = 0; i <=x2-x1; i++)
		{
			for(int j = 0;  j<=y2-y1; j++)
			{
				if(i+x1 < surface->w && surface->h> j+y1)
					putpixel(surface2,i,j,getpixel(surface,i+x1,j+y1));
				else
					putpixel(surface2,i,j,SDL_MapRGB(surface->format,255,255,255));

			}
		}
		SDL_FreeSurface(surface);
		return surface2;
	}
	SDL_FreeSurface(surface);
	return NULL;
}

SDL_Surface* contour(SDL_Surface * surface)
{
	SDL_Surface *s = SDL_CreateRGBSurface(0,surface->w+2, surface->h+2, 32, 0, 0, 0, 0);
	for(int i = 0; i<s->w;i++)
	{
		putpixel(s,i,0,SDL_MapRGB(surface->format,255,255,255));
		putpixel(s,i,s->h-1,SDL_MapRGB(surface->format,255,255,255));

	}
	for(int i = 0; i<s->h;i++)
	{
		putpixel(s,0,i,SDL_MapRGB(surface->format,255,255,255));
		putpixel(s,s->w-1,i,SDL_MapRGB(surface->format,255,255,255));
	}
	for(int i = 0;i<surface->w;i++)
	{
		for(int j = 0; j<surface->h;j++)
		{
			putpixel(s, i+1 , j+1 ,getpixel(surface,i,j));
		}
	}
	return s;
}


size_t strlen(const char *s) {
    size_t i;
    for (i = 0; s[i] != '\0'; i++) ;
    return i;
}

char* concat(char *str1,char * str2)
{
	size_t size1 = strlen(str1);
	size_t size = size1 + strlen(str2) +1;
	char *str = realloc(str1,size * sizeof(char));
	char *p = str + size1;
	while(*str2 != 0)
		*(p++) = *(str2++);
	*p = 0;
	return str;
}
int name = 0;

char * dfs(node* T,int size, int training)
{
//	char* str = malloc(sizeof(char));
//    *str = ' ';
	if(T != NULL)
	{
		if(training)
		{
			dfs(T->child,size,training);
			char str[12];
			sprintf(str,"%d.bmpi",name);

			if(T->data)
			{

			//if(T->level != 4)
			//	SDL_SaveBMP(blacknwhite(colortogray(T->data)),str);
			//else
				if(T->level == 4 && *text!=0 )
				{
					SDL_Surface *s = SDL_CreateRGBSurface(0,size, size, 32, 0, 0, 0, 0);
					SDL_Surface * a = contour(blacknwhite(colortogray(T->data)));
					SDL_SoftStretch(a,NULL,s,NULL);
					SDL_SaveBMP(s,str);
					Matrix toTrain = Surface_to_Matrix(a,size);
					train(&toTrain,*text);
					text++;
					SDL_FreeSurface(a);
					SDL_FreeSurface(s);
					name++;
					free(toTrain.values);

			
				}
			}
			if(T->sibling != NULL)
				dfs(T->sibling,size,training);
			if(T->data)
				SDL_FreeSurface(T->data);
			free(T);
		}

		else
		{
			dfs(T->child,size,training);
			if(T->data)
			{
				if(T->level ==1)
					str = concat(str,"\n\t");
				if(T->level ==2)
					str = concat(str,"\n");
				if(T->level ==3)
					str = concat(str," ");
				if(T->level ==4)
				{
					SDL_Surface *s = SDL_CreateRGBSurface(0,size, size, 32, 0, 0, 0, 0);
					SDL_Surface * a = contour(blacknwhite(colortogray(T->data)));
					SDL_SoftStretch(a,NULL,s,NULL);
					Matrix m = Surface_to_Matrix(a,size);
					char toConcat[2] = "\0";
					toConcat[0] = alpha[eval(m,0)];
					str = concat(str,toConcat);
					SDL_FreeSurface(a);
					SDL_FreeSurface(s);
					//free(m.values);
				}
			}


			if(T->sibling)
				dfs(T->sibling,size,training);
			SDL_FreeSurface(T->data);
			free(T);
		}
	}

	return str;
}

Matrix Surface_to_Matrix(SDL_Surface* surface,int size)
{
	Uint8 r,g,b;
	Matrix m = createMatrix(size*size,1);
	for(int i=0; i< size;i++)
	{
		for(int j=0; j<size;j++)
		{
			SDL_GetRGB(getpixel(surface,i,j),surface->format,&r,&g,&b);

			if(r == 0)
				m.values[j+i*size] = 0;
			else
				m.values[j+i*size] = 1;
		}
	}
	return m;
}




