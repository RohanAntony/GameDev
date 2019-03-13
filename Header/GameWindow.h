#pragma once

#include <iostream>
#include <SDL.h>
#include <string>

#include "GameException.h"
#include "SupportUtils.h"

using std::string;
using std::endl;
using std::cerr;
using std::cout;

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
	void drawRect(Rect rect, Color color, Color clearColor);

	~GameWindow();
};

void pause(int);