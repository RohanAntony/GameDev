#pragma once

#include <iostream>
#include <SDL.h>

#include "GameException.h"

using std::endl;
using std::cerr;
using std::cout;

class GameBase {
public:
	GameBase() {
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
			throw GameExceptions{};
		}
		cout << "Initializing SDL success" << endl;
	}
	~GameBase() {
		SDL_Quit();
	}
};