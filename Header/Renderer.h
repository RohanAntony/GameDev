#ifndef GALIB_RENDERER_HEADER
#define GALIB_RENDERER_HEADER

#include <SDL.h>

#include "Exception.h"
#include "LogBase.h"
#include "SupportUtils.h"

namespace GaLib {
	class Renderer {
		LogBase &log;
		Color clearColor;
		SDL_Texture* texture;
		SDL_Renderer* renderer;
		SDL_Window* window;	//Get this set from the parent function
	public:
		Renderer(SDL_Window* window, LogBase &log) :
			log(log), window(window), 
			renderer(NULL), texture(NULL),
			clearColor({0, 0, 0, 0xFF})
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL) {
				log.error("Renderer could not be created! Error: " + string(SDL_GetError()));
				throw Exception{};
			}
		}

		Renderer(SDL_Window* window, LogBase &log, Color color) :
			log(log), window(window), 
			renderer(NULL), texture(NULL),
			clearColor(color)
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL) {
				log.error("Renderer could not be created! Error: " + string(SDL_GetError()));
				throw Exception{};
			}
		}

		inline void updateWindow() {
			SDL_RenderPresent(renderer);
		}

		inline void updateTexture(SDL_Texture* mTexture) {
			texture = mTexture;
			SDL_RenderCopy(renderer, texture, NULL, NULL);
			updateWindow();
		}

		inline void clearWindow() {
			Uint8 red, green, blue, alpha;
			SDL_GetRenderDrawColor(renderer, &red, &green, &blue, &alpha);
			SDL_SetRenderDrawColor(renderer, clearColor.red, clearColor.green, clearColor.blue, clearColor.alpha);
			SDL_RenderClear(renderer);
			SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
			updateWindow();
		}

		inline void setClearColor(Color color) {
			clearColor = color;
		}

		inline void drawRect(Rect rect, Color color) {
			SDL_Rect fillRect = { rect.top, rect.left, rect.width, rect.height };
			SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, color.alpha);
			SDL_RenderFillRect(renderer, &fillRect);
			updateWindow();
		}

		inline void drawLine(Line line, Color color) {
			SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, color.alpha);
			SDL_RenderDrawLine(renderer, line.startX, line.startY, line.endX, line.endY);
			updateWindow();
		}

		inline void setViewPort(int startX, int startY, int endX, int endY) {
			SDL_Rect viewPort;
			viewPort.x = startX;
			viewPort.y = startY;
			viewPort.w = endX - startX;
			viewPort.h = endY - startY;
			SDL_RenderSetViewport(renderer, &viewPort);
		}

		inline SDL_Renderer* getRenderer() {
			return renderer;
		}

		inline bool updateRendererWithSurface(SDL_Surface* surface) {
			SDL_Texture* mTexture = SDL_CreateTextureFromSurface(renderer, surface);
			if (!mTexture) {
				log.error("Error while loading texture! Error: " + string(SDL_GetError()));
				return false;
			}
			updateTexture(mTexture);
		}

		~Renderer() {
			SDL_DestroyRenderer(renderer);
		}
	};
}

#endif