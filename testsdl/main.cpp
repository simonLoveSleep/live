
#include <QtCore/QCoreApplication>

#include <SDL.h>
#include <iostream>
int main(int argc, char *argv[])
{
	//QCoreApplication a(argc, argv);

	//return a.exec();
	if (SDL_Init(SDL_INIT_EVERYTHING)!=0)
	{
		std::cout<<"sdl_init error"<<SDL_GetError()<<std::endl;
		return 1;
	}
	SDL_Quit();
	return 0;
}
