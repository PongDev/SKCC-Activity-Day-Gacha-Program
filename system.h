#include<bits/stdc++.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

using namespace std;

SDL_Window *window=NULL;
SDL_Surface *screen=NULL;
SDL_Renderer *render=NULL;
SDL_Event e;

bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO)<0)
	{
	 printf("[System/SDL] Initialize Error %s\n",SDL_GetError());
	 return false;
	}
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1"))printf("[System/SDL] Warning Linear texture filtering not eanbled\n");
	Uint32 flags=SDL_WINDOW_SHOWN;
	if (FULLSCREEN)flags|=SDL_WINDOW_FULLSCREEN_DESKTOP;
	window=SDL_CreateWindow("SKCC: Activity Day",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1000,1000,flags);
	if (window==NULL)
	{
	 printf("[System/SDL] CreateWindow(); Error %s\n",SDL_GetError());
	 return false;
	}
	render=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
	if (render==NULL)
	{
	 printf("[System/SDL] CreateRender(); Error %s\n",SDL_GetError());
	 return false;
	}
	SDL_SetRenderDrawColor(render,0xFF,0xFF,0xFF,0xFF);
	int imgFlags=IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags)&imgFlags))
	{
	 printf("[System/SDL] SDL_image Initialize Error %s\n",IMG_GetError());
	 return false;
	}
	screen=SDL_GetWindowSurface(window);
	return true;
}

void renderImage(int x,int y,int w,int h,double angle,SDL_Texture* texture)
{
	SDL_Rect pos={x,y,w,h};
	SDL_RenderCopyEx(render,texture,NULL,&pos,angle,NULL,SDL_FLIP_NONE);
}

SDL_Texture* loadImage(string loc)
{
	SDL_Texture *tmp=NULL;
	SDL_Surface* load=IMG_Load(loc.c_str());
	if (load==NULL)
	{
	 printf("[System/SDL] IMG_Load(); Error %s\n",IMG_GetError());
	 return NULL;
	}
	SDL_SetColorKey(load,SDL_TRUE,SDL_MapRGB(load->format,0,0xFF,0xFF));
	tmp=SDL_CreateTextureFromSurface(render,load);
	if (tmp==NULL)
	{
	 printf("[System/SDL] SDL_CreateTextureFromSurface(); Error %s\n",IMG_GetError());
	 return NULL;
	}
	SDL_FreeSurface(load);
	return tmp;
}

void renderShow()
{
	SDL_RenderPresent(render);
}

void renderClear()
{
	SDL_RenderClear(render);
}
