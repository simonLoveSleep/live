#ifndef RES_PATH_H
#define RES_PATH_H

#include <iostream>
#include <string>
#include <SDL.h>

/*
 * Get the resource path for resources located in res/subDir
 * It's assumed the project directory is structured like:
 * bin/
 *  the executable
 * res/
 *  Lesson1/
 *  Lesson2/
 *
 * Paths returned will be Lessons/res/subDir
 */
std::string getResourcePath(const std::string &subDir = ""){
	//We need to choose the path separator properly based on which
	//platform we're running on, since Windows uses a different
	//separator than most systems
#ifdef _WIN32
	const char PATH_SEP = '\\';
#else
	const char PATH_SEP = '/';
#endif
	//This will hold the base resource path: Lessons/res/
	//We give it static lifetime so that we'll only need to call
	//SDL_GetBasePath once to get the executable path
	static std::string baseRes;
	if (baseRes.empty()){
		//SDL_GetBasePath will return NULL if something went wrong in retrieving the path
		char *basePath = SDL_GetBasePath();
		if (basePath){
			baseRes = basePath;
			SDL_free(basePath);
		}
		else {
			std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
			return "";
		}
		//We replace the last bin/ with res/ to get the the resource path
		size_t pos = baseRes.rfind("bin");
		baseRes = baseRes.substr(0, pos) + "res" + PATH_SEP;
	}
	//If we want a specific subdirectory path in the resource directory
	//append it to the base path. This would be something like Lessons/res/Lesson0
	return subDir.empty() ? baseRes : baseRes + subDir + PATH_SEP;
}
const int SCREEN_WIDTH=640;
const int SCREEN_HEIGHT=480;
const int TILE_SIZE=40;
void logSDLError(std::ostream &os,const std::string &msg){
	os<<msg<<"error:"<<SDL_GetError()<<std::endl;
}
SDL_Texture *loadTexture(const std::string &file,SDL_Renderer *ren){
	SDL_Texture *texture=nullptr;
	SDL_Surface *loadedImage=SDL_LoadBMP(file.c_str());
	if (nullptr!=loadedImage)
	{
		texture=SDL_CreateTextureFromSurface(ren,loadedImage);
		SDL_FreeSurface(loadedImage);
		if (nullptr==texture)
		{
			logSDLError(std::cout,"createtexturefromsurface");
		}
	}else{
		logSDLError(std::cout,"loadbmp");
	}
	return texture;
}
void renderTexTure(SDL_Texture *tex,SDL_Renderer *ren,int x,int y){
	SDL_Rect dst;
	dst.x=x;
	dst.y=y;
	SDL_Rect sst;
	SDL_QueryTexture(tex,NULL,NULL,&dst.w,&dst.h);
	SDL_RenderCopy(ren,tex,NULL,&dst);
}

#endif