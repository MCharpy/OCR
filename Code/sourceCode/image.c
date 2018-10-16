#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>

Uint32 getpixel();
Uint32 putpixel();
void colortogris();
SDL_Surface* blacknwhite();
void segmentationh();
void segmentationl();
SDL_Surface* init_state();
SDL_Surface* copy();
void RLSA();

int main()
{
	int continuer = 1;
	if(SDL_Init(SDL_INIT_VIDEO))
		fprintf(stderr, "ERROR SDL : %s \n",SDL_GetError());
	//atexit(SDL_Quit);
	SDL_Surface *fenetre = NULL;

//	fenetre = SDL_SetVideoMode(700,700,32,SDL_HWSURFACE);
	SDL_Surface* image = SDL_LoadBMP("texte1.bmp");
//	SDL_Surface* clone = copy(image);
	fenetre = SDL_SetVideoMode(image->w,image->h,32,SDL_HWSURFACE);
	SDL_Surface* clone = copy("texte1.bmp");
//	SDL_Surface* clone = SDL_LoadBMP("test/image3.bmp");

	SDL_BlitSurface(clone, NULL,fenetre,NULL);
	SDL_Flip(fenetre);
	while(continuer)
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
						colortogris(fenetre);
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
						continuer=0;
						break;
					}
					case SDLK_a:
					{
						//segmentationl(fenetre);
						segmentationl(fenetre);
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
						RLSA(fenetre,"texte1.bmp");
					//	RLSA(fenetre,"texte1.bmp");
						SDL_Flip(fenetre);
					}
				    default:
						break;
				}
		}	
	}				
	//Uint8 r,g,b,a;
	//SDL_GetRGBA(getpixel(fenetre,0,0),fenetre->format,&r,&g,&b,&a);
	//printf("%d",r);*/


	SDL_FreeSurface(fenetre);	//SDL_GetRGBA(getpixel(surface,i,j),surface->format,&r,&g,&b,&a)

	SDL_FreeSurface(image);
	SDL_FreeSurface(clone);
	SDL_Quit();
	
	return 0;
}


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
void colortogris(SDL_Surface* surface)
{
	Uint8 r,g,b,a;
	for(int i=0;i< surface->w;i++)
	{
		for(int j=0;j< surface->h;j++)
			{
				SDL_GetRGBA(getpixel(surface,i,j),surface->format,&r,&g,&b,&a);
				Uint32 pixel = SDL_MapRGBA(surface->format,(r+g+b)/3,(r+g+b)/3,(r+g+b)/3,a);
				putpixel(surface,i,j,pixel);

			}
	}
	
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
				if (r<120 )
					pixel = SDL_MapRGBA(surface->format,0,0,0,a);
				else
					pixel = SDL_MapRGBA(surface->format,255,255,255,a);

				putpixel(surface,i,j,pixel);

			}
	}
	return surface;
	
}
void segmentationh(SDL_Surface* surface)
{
	int threash = 4;
	//int flag = 0;
	int zero = 0;
	Uint8 r,g,b,a;
	Uint32 pixel = SDL_MapRGBA(surface->format,0,0,0,0);
	for(int i=0 ;surface->w > i ; i++)
	{
		for(int j = 0; surface->h > j;j++)
		{
			SDL_GetRGBA(getpixel(surface,i,j),surface->format,&r,&g,&b,&a);
			//putpixel(surface,i,j,pixel);
			
			for(int k = j; r != 0 && k < surface->h;k++)
			{		
				SDL_GetRGBA(getpixel(surface,i,k),surface->format,&r,&g,&b,&a);
				zero++;
			}
			if(zero >= threash)
				j += zero ;
			else
			{
				for(int l = j - 1; l <= j + zero ;l++)
				{	
					putpixel(surface,i,l,pixel);
				}
				j = j + zero ;
			}
			zero = 0;
		}

		
	}
}
					
void segmentationl(SDL_Surface* surface)
{
	int threash = 15;
	//int flag = 0;
	int zero = 0;
	Uint8 r,g,b,a;
	Uint32 pixel = SDL_MapRGBA(surface->format,0,0,0,0);
	for(int i=0 ;surface->h > i ; i++)
	{
		for(int j = 0; surface->w > j; j++)
		{
			SDL_GetRGBA(getpixel(surface,j,i),surface->format,&r,&g,&b,&a);
			//putpixel(surface,i,j,pixel);
			
			for(int k = j; r != 0 && k < surface->w;k++)
			{		
				SDL_GetRGBA(getpixel(surface,k,i),surface->format,&r,&g,&b,&a);
				zero++;
			}
			if(zero >= threash)
				j += zero;
 			else
			{
				for(int l = j -1; l <= j + zero ;l++)
				{	
					putpixel(surface,l,i, pixel);
				}
				j = j + zero ;
			}
			zero = 0;
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

void RLSA(SDL_Surface* surface,char* image )
{
	SDL_Surface* cp1 = copy(image);
	SDL_Surface* cp2 = copy(image);
	cp1 = blacknwhite(cp1);
	cp2 = blacknwhite(cp2);
	segmentationl(cp2);
	segmentationh(cp1);
	//SDL_Surface toret = copy(copy(suface));
	Uint8 r1,r2,g,b,a,gg,bb,aa;
	for(int i = 0; i < surface->w; i++)
	{
		for(int j = 0; j < surface->h; j++)
		{
			SDL_GetRGBA(getpixel(cp1,i,j),surface->format,&r1,&g,&b,&a);
			SDL_GetRGBA(getpixel(cp2,i,j),surface->format,&r2,&gg,&bb,&aa);
			if(0 == r2 || r1 == 0)
			{
				putpixel(surface,i,j,SDL_MapRGBA(surface->format,0,0,0,0));
			}
			else
			{
				putpixel(surface,i,j,SDL_MapRGBA(surface->format,255,255,255,0));
			}
		}
	}
	SDL_FreeSurface(cp1);
	SDL_FreeSurface(cp2);

}

				



	
