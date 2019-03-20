#ifndef GALIB_WINDOWHW_HEADER
#define GALIB_WINDOWHW_HEADER

#include "Renderer.h"
#include "Font.h"
#include "Window.h"
#include "LogBase.h"

using GaLib::Font;

namespace GaLib {
	class WindowHW : public Window{
		Renderer* renderer;
		SDL_Window* window;
		LogBase &logger;
		Color clearColor;

	public:
		WindowHW(Rect<int> dim, string title, LogBase& log) :
			Window(dim, title, log),
			logger(log), clearColor({0, 0, 0, 0xFF})
		{
			window = getWindow();
			renderer = new Renderer(window, log);
		}

		/*virtual bool loadImage(string imagePath, ImgTypes type) {
			SDL_Surface* loadedSurface;
			SDL_Surface* surface = getWindowSurface();
			SDL_Texture* texture = NULL;
			if (type == ImgTypes::BMP)
				loadedSurface = loadBMP(imagePath);
			else
				loadedSurface = loadOtherImgTypes(imagePath);
			if (loadedSurface == NULL)
				return false;
			renderer->updateRendererWithSurface(loadedSurface);
			updateWindow();
			SDL_FreeSurface(loadedSurface);
			return true;
		}*/

		virtual void updateWindow() {
			renderer->updateWindow();
		}

		virtual void clearWindow() {
			renderer->clearWindow();
		}

		void setClearColor(Color clear) {
			renderer->setClearColor(clear);
		}

		void displayText(string text, string font, int size = 100, Color color = { 0xFF, 0xAD, 0, 0xFF }) {
			Font robotoRegular{ font, size, color, renderer, logger };
			robotoRegular.displayText(text);
			updateWindow();
		}

		void drawRect(Rect<int> rect, Color color = { 0, 0, 0, 0xFF }) {
			renderer->drawRect(rect, color);
		}

		void drawLine(Line line, Color color = { 0, 0, 0, 0xFF }) {
			renderer->drawLine(line, color);
		}

		~WindowHW() {
			delete renderer;
		}
	};
}

#endif