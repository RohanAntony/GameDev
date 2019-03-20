#ifndef GALIB_WINDOW_HEADER
#define GALIB_WINDOW_HEADER

#include <iostream>
#include <SDL.h>
#include <string>

#include "Exception.h"
#include "SupportUtils.h"
#include "LogBase.h"

using std::string;
using std::endl;
using std::cerr;
using std::cout;

namespace GaLib {


	class Window {
		Rect windowDimensions;
		string windowTitle;
		SDL_Window* window;
		Color clearColor;
		LogBase &log;

	protected:
		SDL_Window* getWindow() {
			return window;
		}

		SDL_Surface* getWindowSurface() {
			return SDL_GetWindowSurface(window);
		}

		SDL_Surface* loadBMP(string imagePath) {
			SDL_Surface* loadedSurface = SDL_LoadBMP(imagePath.c_str());
			SDL_Surface* surface = getWindowSurface();
			if (loadedSurface == NULL) {
				log.error("Unable to load image " + imagePath);
				return NULL;
			}
			return loadedSurface;
		}

		SDL_Surface* loadOtherImgTypes(string imagePath) {
			SDL_Surface* optimizedSurface = NULL;
			SDL_Surface* loadedSurface = IMG_Load(imagePath.c_str());
			SDL_Surface* surface = getWindowSurface();
			if (loadedSurface == NULL) {
				log.error("Error while loading image: " + imagePath);
				return NULL;
			}
/*			else {
				optimizedSurface = SDL_ConvertSurface(loadedSurface, surface->format, NULL);
				if (optimizedSurface == NULL) {
					log.error("Unable to optimize image, Error: " + string(SDL_GetError()));
					SDL_FreeSurface(loadedSurface);
					return NULL;
				}
				return optimizedSurface;
			}*/
			return loadedSurface;
		}

	public:
		Window(Rect dim, string title, LogBase& logger) :
			windowDimensions(dim), windowTitle(title),
			log(logger), clearColor({0, 0, 0, 0xFF}), window(NULL)
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

		virtual bool loadImage(string imagePath, ImgTypes type) {
			SDL_Surface* loadedSurface;
			SDL_Surface* surface = getWindowSurface();
			if (type == ImgTypes::BMP)
				loadedSurface = loadBMP(imagePath);
			else
				loadedSurface = loadOtherImgTypes(imagePath);
			if (loadedSurface == NULL)
				return false;
			/*SDL_Rect dest;
			dest.x = 150;
			dest.y = 150;
			dest.w = 150;
			dest.h = 150;*/
			SDL_BlitScaled(loadedSurface, NULL, surface, NULL);
			updateWindow();
			SDL_FreeSurface(loadedSurface);
			return true;
		}

		virtual void updateWindow() {
			SDL_UpdateWindowSurface(window);
		}

		virtual void clearWindow() {
			SDL_Surface* screenSurface = getWindowSurface();
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, clearColor.red, clearColor.green, clearColor.blue));
			updateWindow();
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