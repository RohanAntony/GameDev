#ifndef GALIB_BASE_HEADER
#define GALIB_BASE_HEADER

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "GaLib/Exception.h"
#include "Logger/LogBase.h"

using std::endl;
using std::cerr;
using std::cout;

namespace GaLib {
	class Base {
		int init;
		LogBase &log;
	public:
		Base(LogBase &log) : log(log) {
			if (SDL_Init(SDL_INIT_VIDEO) < 0) {
				log.error("SDL could not initialize! SDL_Error: " + string(SDL_GetError()));
				throw Exception{};
			}
			log.debug("Initializing SDL success");
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags)) {
				log.error("Image load library could not initialize! Error: " + string(IMG_GetError()));
				throw Exception{};
			}
			if (TTF_Init() == -1) {
				log.error("SDL_ttf could not initialize! Error: " + string(SDL_GetError()));
				throw Exception{};
			}
		}
		~Base() {
			TTF_Quit();
			IMG_Quit();
			SDL_Quit();
		}
	};
}

#endif