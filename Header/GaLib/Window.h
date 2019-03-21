#ifndef GALIB_WINDOW_HEADER
#define GALIB_WINDOW_HEADER

#include <iostream>
#include <SDL.h>
#include <string>

#include "GaLib/Exception.h"
#include "GaLib/SupportUtils.h"
#include "Logger/LogBase.h"
#include "GaLib/Sprite.h"
#include "GaLib/SpriteInstance.h"
#include <map>

using std::string;
using std::endl;
using std::cerr;
using std::cout;
using std::map;

namespace GaLib {


	class Window {
		Rect<int> windowDimensions;
		string windowTitle;
		SDL_Window* window;
		LogBase &log;
		map<int, SpriteInstance*> sprites;
		int spriteCount;
	protected:
		SDL_Window* getWindow() {
			return window;
		}

		SDL_Surface* getWindowSurface() {
			return SDL_GetWindowSurface(window);
		}

		inline int getXPos(float val) {
			if (val > 1 || val < 0)
				val = 0;
			return static_cast<int>(windowDimensions.width * val);
		}

		inline int getYPos(float val) {
			if (val > 1 || val < 0)
				val = 0;
			return static_cast<int>(windowDimensions.height * val);
		}

	public:
		Window(Rect<int> dim, string title, LogBase& logger) :
			windowDimensions(dim), windowTitle(title),
			log(logger), window(NULL), spriteCount(0)
		{
			window = SDL_CreateWindow(title.c_str(), dim.left, dim.top, dim.width, dim.height, SDL_WINDOW_SHOWN);
			if (window == NULL) {
				log.error("Window could not be created" + string(SDL_GetError()));
				throw Exception{};
			}
			log.debug("Window created with title " + title);
		}

		Events getEvent() {
			SDL_Event e;
			Events gEv = Events::NONE;
			if (SDL_PollEvent(&e) != 0) {
				if (e.type == SDL_QUIT) {
					cout << "Quit!" << endl;
					gEv = Events::QUIT;
				}
				else if (e.type == SDL_KEYDOWN) {
					switch (e.key.keysym.sym) {
					case SDLK_UP:
						cout << "Up!" << endl;
						gEv = Events::UP;
						break;
					case SDLK_DOWN:
						cout << "Down!" << endl;
						gEv = Events::DOWN;
						break;
					case SDLK_LEFT:
						cout << "Left!" << endl;
						gEv = Events::LEFT;
						break;
					case SDLK_RIGHT:
						cout << "Right!" << endl;
						gEv = Events::RIGHT;
						break;

					}
				}
			}
			return gEv;
		}

		/*int addSprite(string imagePath,
			Rect<double> dim = {0, 0, 1.0, 1.0}, 
			Color maskColor = { 0x00, 0x00, 0x00, 0x00}, 
			bool visibility = true) {
			sprites.insert(std::pair<int, SpriteInstance*>(spriteCount,new SpriteInstance(imagePath, dim, maskColor, visibility, log)));
			return spriteCount++;
		}*/

		int addSprite(string imagePath,
			Rect<int> dim = { 0, 0, 0, 0 },
			Color maskColor = { 0x00, 0x00, 0x00, 0x00 },
			bool visibility = true) {
			sprites.insert(std::pair<int, SpriteInstance*>(spriteCount, new SpriteInstance(imagePath, dim, maskColor, visibility, log)));
			return spriteCount++;
		}

		void modifySpriteDim(int id, double top, double left, double width, double height) {
			SpriteInstance* s = sprites.at(id);
			s->updateDimensions(top, left, width, height);
		}

		void modifySpriteDim(int id, int top, int left, int width, int height) {
			SpriteInstance* s = sprites.at(id);
			s->updateDimensions(top, left, width, height);
		}

		void hideSprite(int id) {
			sprites.at(id)->hide();
		}

		void showSprite(int id) {
			sprites.at(id)->show();
		}

		virtual void updateWindow() {
			for (auto &s : sprites) {
				SpriteInstance *sprite = s.second;
				SDL_Rect dim;
				if (sprite->isAbsDim())
					dim = sprite->getDimensions();
				else
					dim = sprite->getDimensions(windowDimensions.width, windowDimensions.height);
				SDL_BlitScaled(sprite->getSurface(), NULL, getWindowSurface(), &dim);
			}
			SDL_UpdateWindowSurface(window);
		}

		virtual bool loadImage(string imagePath, Color maskColor = { 0x00, 0x00, 0x00, 0x00 }) {
			Sprite *image = new Sprite(imagePath, maskColor, log);
			SDL_Surface *tempSurface = image->getSurface();
			if (tempSurface == NULL)
				return false;
			SDL_BlitScaled(tempSurface, NULL, getWindowSurface(), NULL);
			delete image;
			return true;
		}

		~Window() {
			SDL_DestroyWindow(window);
		}
	};


	void pause(int delay) {
		SDL_Delay(delay);
	}

}

#endif