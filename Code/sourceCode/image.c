#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>

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

int process_image(char * path)
{
	int continu = 1;
	if(SDL_Init(SDL_INIT_VIDEO))
		fprintf(stderr, "ERROR SDL : %s \n",SDL_GetError());
	SDL_Surface *fenetre = NULL;
	SDL_Surface* image = SDL_LoadBMP(path);
	fenetre = SDL_SetVideoMode(image->w,image->h,32,SDL_HWSURFACE);
	SDL_Surface* clone = copy(path);
	SDL_BlitSurface(image, NULL,fenetre,NULL);
	SDL_Flip(fenetre);
	while(continu)
	{
		SDL_Event event;
		SDL_WaitEvent(&event);
		if(event.type == SDL_QUIT)
			break;
		switch(event.type)
		{
			case SDL_QUIT:
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_AMPERSAND:
					{
						colortogray(fenetre);
						SDL_Flip(fenetre);
						break;
					}
					case SDLK_QUOTE:
					{
						blacknwhite(fenetre);
						SDL_Flip(fenetre);
						break;
					}

					case SDLK_ESCAPE:
					{
						continu=0;
						break;
					}
					case SDLK_a:
					{
						RLSA_width(fenetre,10);
						SDL_Flip(fenetre);
						break;
					}
					case SDLK_b:
					{
						init_state(fenetre,clone);
						SDL_Flip(fenetre);
						break;
					}
					case SDLK_z:
					{
						RLSA(fenetre,path,10,5);
						SDL_Flip(fenetre);
						break;
					}
					case SDLK_e:
					{
						Segment_line(RLSA(image,path,1,5),fenetre);
						SDL_Flip(fenetre);
						break;
					}
					case SDLK_r:
					{
						Segment_line(RLSA(image,path,10,5),fenetre);
						SDL_Flip(fenetre);
						break;
					
					}
					case SDLK_t:
					{
						Segment_line(RLSA(image,path,25,5),fenetre);
						SDL_Flip(fenetre);
						break;
					}

					case SDLK_y:
					{
						Segment_line(RLSA(image,path,25,20),fenetre);
						SDL_Flip(fenetre);
						break;
					}


				    default:
						break;
				}
		}	
	}				


	SDL_FreeSurface(fenetre);	
	SDL_FreeSurface(image);
	SDL_FreeSurface(clone);
	SDL_Quit();
	
	return 0;
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
			for(int k = j; r != 0 && k < surface->h;k++)
			{		
				SDL_GetRGB(getpixel(surface,i,k),surface->format,&r,&g,&b);
				Nth_Zero++;
			}
			if(Nth_Zero >= threash)
				j += Nth_Zero ;
			else
			{
				for(int l = j - 1; l <= j + Nth_Zero ;l++)
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
			for(int k = j; r != 0 && k < surface->w;k++)
			{		
				SDL_GetRGB(getpixel(surface,k,i),surface->format,&r,&g,&b);
				Nth_Zero++;
			}
			if(Nth_Zero >= threash)
				j += Nth_Zero;
 			else
			{
				for(int l = j -1; l <= j + Nth_Zero ;l++)
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

SDL_Surface* copy(char* surface)
{
	SDL_Surface* c  = SDL_LoadBMP(surface);
	return c;
}

SDL_Surface* RLSA(SDL_Surface* surface,char* image, int threash1, int threash2)
{
	SDL_Surface* cp1 = copy(image);
	SDL_Surface* cp2 = copy(image);
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

				
SDL_Surface *Segment_line(SDL_Surface* RLSA_surface, SDL_Surface* surface)
{
	Uint8 r1,g1,b1;
	int* tab = NULL;
	for(int i = 0; i <surface->w; i++)
	{
		for(int j = 0; j < surface->h; j++)
		{
			SDL_GetRGB(getpixel(RLSA_surface,i,j),
					RLSA_surface->format,&r1,&g1,&b1);
			if(r1 == 0)
			{
				tab = calloc(sizeof(int),4);
				tab[2] = j;
				tab[0] = i;
				extremum(tab,RLSA_surface,i,j);
				DrawRect(tab[0], tab[1], tab[2] - 1,tab[2] - 1,surface);
				DrawRect(tab[0], tab[1], tab[3] + 1,tab[3] + 1,surface);
				DrawRect(tab[0] - 1 , tab[0] - 1, tab[2] ,tab[3] ,surface);
				DrawRect(tab[1] + 1, tab[1] + 1,tab[2] ,tab[3] ,surface);
				free(tab);
			}

		}
	}
	return surface;
}

void extremum(int* tab, SDL_Surface * surface,int i,int j)
{
	Uint8 r,g,b;
	SDL_GetRGB(getpixel(surface,i,j),surface->format,&r,&g,&b);
	if(r != 255)
	{
		tab[0] = i	< tab[0] ? i : tab[0];
		tab[1] = i >= tab[1] ? i : tab[1];
		tab[2] = j < tab[2] ? j : tab[2];
		tab[3] = j >= tab[3] ? j : tab[3];

		putpixel(surface,i,j,SDL_MapRGB(surface->format,255,255,255));
		if(i+1<surface->w)
			extremum(tab, surface,i+1,j);
		extremum(tab, surface,i-1,j);
		if(j+1 < surface->h)
			extremum(tab, surface,i,j+1);
		extremum(tab, surface,i,j-1);
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

