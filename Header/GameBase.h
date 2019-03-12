#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "GameException.h"

using std::endl;
using std::cerr;
using std::cout;

namespace InitParam{
	enum Param {
		SDL_INIT = 1,
		IMG_INIT = 2
		//Next library initiliazation must be set to 4 , use as bitwise AND
	};
}


class GameBase {
	int init;
public:
	GameBase(int t = InitParam::SDL_INIT) {
		init = t;
		if ((t & InitParam::SDL_INIT) && SDL_Init(SDL_INIT_VIDEO) < 0) {
			cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
			throw GameExceptions{};
		}
		cout << "Initializing SDL success" << endl;
		int imgFlags = IMG_INIT_PNG;
		if ((t & InitParam::SDL_INIT) && (t & InitParam::IMG_INIT)) {
			if (!(IMG_Init(imgFlags) & imgFlags)) {
				cerr << "Image load library could not initialize! Error: " << IMG_GetError();
				throw GameExceptions{};
			}
		}
	}
	~GameBase() {
		if (init & InitParam::IMG_INIT)
			IMG_Quit();
		SDL_Quit();
	}
};