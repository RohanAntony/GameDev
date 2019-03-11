#pragma once

#include <iostream>
#include <SDL.h>
#include <string>

#include "GameException.h"

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

	SDL_Window* window;

	SDL_Surface* getWindowSurface();
public:
	GameWindow(int top, int left, int width, int height, string title) :
		screenWidth(width), screenHeight(height), 
		positionLeft(left), positionTop(top),
		windowTitle(title) 
	{
		window = SDL_CreateWindow(title.c_str(), left, top, width, height, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			cerr << "Window could not be created" << SDL_GetError();
			throw GameExceptions{};
		}
		cout << "Window created with title " << title << endl;
	}

	void fillWindowWithColor(int, int, int);
	void updateWindowSurface();
	bool loadImage(string);
	void wait();

	~GameWindow() {
		SDL_DestroyWindow(window);
		window = NULL;
	}
};

void pause(int);