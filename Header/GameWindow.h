#pragma once

#include <iostream>
#include <SDL.h>
#include <string>

#include "GameException.h"
#include "SupportUtils.h"
#include "LogBase.h"

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

	LogBase &log;

protected:
	SDL_Surface* getWindowSurface();
	SDL_Surface* loadBMP(string);
	SDL_Surface* loadOtherImgTypes(string);

public:
	GameWindow(int, int, int, int, string, LogBase&);
	
	void fillWindowWithColor(int, int, int);
	void updateWindow();
	bool loadImageWithSurface(string, ImgTypes);
	bool loadImageWithTexture(string, ImgTypes);
	bool loadFromRenderedText(string text);
	GameEvents getEvent();
	void clearWindow();
	void drawRect(Rect rect, Color color);
	void drawLine(Line line, Color color);

	~GameWindow();
};

void pause(int);