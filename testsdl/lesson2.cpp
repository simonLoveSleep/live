#include <QtCore/QCoreApplication>

#include <SDL.h>
#include <iostream>
#include "res_path.h"
#include "SDL_image.h"
int main(int argc, char *argv[]){
	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		return 1;
	}
	SDL_Window *window=SDL_CreateWindow("lesson 2",100,100,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
	if (nullptr==window)
	{
		SDL_Quit();
		return 1;
	}
	SDL_Renderer *renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
	if (nullptr==renderer)
	{
		SDL_Quit();
		return 1;
	}
	const std::string resPath=getResourcePath("lesson2");
	SDL_Texture *background=loadTexture(resPath+"background.bmp",renderer);
	SDL_Texture *image=loadTexture(resPath+"image.bmp",renderer);
	if (nullptr==background||nullptr==image)
	{
		SDL_Quit();
		return 1;
	}
	SDL_RenderClear(renderer);
	int bw,bh;
	SDL_QueryTexture(background,NULL,NULL,&bw,&bh);
	renderTexTure(background,renderer,0,0);
	renderTexTure(background,renderer,bw,0);
	renderTexTure(background,renderer,0,bh);
	renderTexTure(background,renderer,bw,bh);
	int iw,ih;
	SDL_QueryTexture(image,NULL,NULL,&iw,&ih);
	int x=SCREEN_WIDTH/2-iw/2;
	int y=SCREEN_HEIGHT/2-ih/2;
	renderTexTure(image,renderer,x,y);
	SDL_RenderPresent(renderer);
	SDL_Event e;
	bool quit=false;
	while (!quit)
	{
		while(SDL_PollEvent(&e)){
			if (e.type==SDL_QUIT)
			{
				quit=true;
			}
			if (e.type==SDL_KEYDOWN)
			{
				quit=true;
			}
		}
		SDL_Delay(100);
	}
	SDL_Delay(2000);
	SDL_Quit();
	return 0;
}