#ifndef GALIB_FONT_HEADER
#define GALIB_FONT_HEADER

#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "GaLib/Exception.h"
#include "LogBase.h"
#include "GaLib/SupportUtils.h"
#include "Experimental/Renderer.h"

using std::string;

namespace GaLib {

	const string fontsPath = "";
	const int DEFAULT_FONT_SIZE = 28;
	const Color DEFAULT_COLOR = { 0, 0, 0, 0xFF };

	class Font {
		Renderer* renderer;
		LogBase &log;
		TTF_Font* gFont;
		Color color;
		int fontSize;

	public:
		Font(string font, int size, Color color, Renderer *renderer, LogBase &log) : 
			fontSize(size), color(color),
			log(log), renderer(renderer)
		{
			log.debug("Creating a font object");
			string path = fontsPath + font;
			gFont = TTF_OpenFont(path.c_str(), size);
			if (gFont == NULL) {
				log.error("Error while initializing font! ");
				throw Exception{};
			}
		}

		inline void setColor(Color color) {
			this->color = color;
		}

		inline void setFontSize(int size) {
			this->fontSize = size;
		}

		inline bool displayText(string text) {
			SDL_Texture* mTexture = NULL;
			SDL_Color textColor = { color.red, color.green, color.blue };
			SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, text.c_str(), textColor);
			if (textSurface == NULL) {
				log.error("Unable to render text surface! SDL_Error" + string(TTF_GetError()));
				return false;
			}
			else {
				log.debug("Displaying text:" + text);
				renderer->updateRendererWithSurface(textSurface);
				SDL_FreeSurface(textSurface);
				return true;
			}
		}

		~Font() {
		}
	};
}

#endif