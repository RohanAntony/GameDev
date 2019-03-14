#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "GameException.h"
#include "LogBase.h"

using std::endl;
using std::cerr;
using std::cout;

class GameBase {
	int init;
	LogBase &log;
public:
	GameBase(LogBase &log) : log(log) {
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			log.error("SDL could not initialize! SDL_Error: " + string(SDL_GetError()));
			throw GameExceptions{};
		}
		log.debug("Initializing SDL success");
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags)) {
			log.error("Image load library could not initialize! Error: " + string(IMG_GetError()));
			throw GameExceptions{};
		}
	}
	~GameBase() {
		IMG_Quit();
		SDL_Quit();
	}
};