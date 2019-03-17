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

namespace GaLib {
	class Window {
		int screenWidth;
		int screenHeight;
		int positionLeft;
		int positionTop;
		string windowTitle;

		SDL_Window* window;

		LogBase &log;

	protected:
		SDL_Surface* getWindowSurface();
		SDL_Surface* loadBMP(string);
		SDL_Surface* loadOtherImgTypes(string);

	public:
		Window(int, int, int, int, string, LogBase&);

		void fillWindowWithColor(int, int, int); //make private function and use it in .clear function
		void updateWindow();
		bool loadImageWithSurface(string, ImgTypes);
		bool loadImageWithTexture(string, ImgTypes);
		bool loadFromRenderedText(string text);
		GameEvents getEvent();
		void clearWindow();

		~Window();
	};
}

void pause(int);

//create a font class which has the renderText method, pass this object to Window object