#pragma once

#include <iostream>
#include <SDL.h>
#include <string>

#include "GameException.h"

using std::string;
using std::endl;
using std::cerr;
using std::cout;

enum class ImgTypes {
	BMP,
	PNG,
	JPG
};

enum class GameEvents {
	QUIT,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE
};

enum class RenderingType {
	SURFACE,
	TEXTURE
};

class GameWindow {
	int screenWidth;
	int screenHeight;
	int positionLeft; 
	int positionTop;
	string windowTitle;
	RenderingType lastUsedRenderingType;

	SDL_Window* window;
	SDL_Texture* texture;
	SDL_Renderer* renderer;

protected:
	SDL_Surface* getWindowSurface();
	SDL_Surface* loadBMP(string);
	SDL_Surface* loadOtherImgTypes(string);

public:
	GameWindow(int, int, int, int, string);
	
	void fillWindowWithColor(int, int, int);
	void updateWindow();
	bool loadImageWithSurface(string, ImgTypes);
	bool loadImageWithTexture(string, ImgTypes);
	GameEvents getEvent();

	~GameWindow();
};

void pause(int);