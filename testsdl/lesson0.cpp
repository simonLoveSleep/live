
#include <QtCore/QCoreApplication>

#include <SDL.h>
#include <iostream>
#include "res_path.h"
int main(int argc, char *argv[])
{
	//QCoreApplication a(argc, argv);

	//return a.exec();
	if (SDL_Init(SDL_INIT_EVERYTHING)!=0)
	{
		std::cout<<"sdl_init error"<<SDL_GetError()<<std::endl;
		return 1;
	}
	SDL_Window *tWin=SDL_CreateWindow("hello world!",100,100,640,480,SDL_WINDOW_SHOWN);
	if (tWin==NULL)
	{
		std::cout<<"sdl_createwindow error:"<<SDL_GetError()<<std::endl;
		SDL_Quit();
		return 1;
	}
	SDL_Renderer *tRen=SDL_CreateRenderer(tWin,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
	if (NULL==tRen)
	{
		SDL_DestroyWindow(tWin);
		std::cout<<"sdl_createrender error:"<<SDL_GetError()<<std::endl;
		SDL_Quit();
		return 1;
	}
	std::string tImagePath=getResourcePath("lessonl")+"hello.bmp";
	SDL_Surface *tBmp=SDL_LoadBMP(tImagePath.c_str());
	if (NULL==tBmp)
	{
		SDL_DestroyRenderer(tRen);
		SDL_DestroyWindow(tWin);
		std::cout<<"sdl_loadbmp error:"<<SDL_GetError()<<std::endl;
		SDL_Quit();
		return 1;
	}
	SDL_Texture *tTex=SDL_CreateTextureFromSurface(tRen,tBmp);
	SDL_FreeSurface(tBmp);
	if (NULL==tTex)
	{
		SDL_DestroyRenderer(tRen);
		SDL_DestroyWindow(tWin);
		std::cout<<"sdl_createtextfromsurface error:"<<SDL_GetError()<<std::endl;
		SDL_Quit();
		return 1;
	}
	SDL_RenderClear(tRen);
	SDL_RenderCopy(tRen, tTex, NULL, NULL);
	SDL_RenderPresent(tRen);
	SDL_Delay(2000);
	SDL_DestroyTexture(tTex);
	SDL_DestroyRenderer(tRen);
	SDL_DestroyWindow(tWin);
	SDL_Quit();
	return 0;
}