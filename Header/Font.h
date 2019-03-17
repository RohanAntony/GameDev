
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "GameException.h"
#include "LogBase.h"
#include "SupportUtils.h"

using std::string;

namespace GaLib {

	const string fontsPath = "Fonts";
	const int DEFAULT_FONT_SIZE = 28;
	const Color DEFAULT_COLOR = { 0, 0, 0, 0xFF };

	class Font {
		LogBase &log;
		TTF_Font* gFont;
		Color color;
		int fontSize;
	public:
		Font(string font, LogBase &log) : 
			fontSize(DEFAULT_FONT_SIZE), color(DEFAULT_COLOR),
			log(log)
		{
			GaLib::Font(font, DEFAULT_FONT_SIZE, DEFAULT_COLOR, log);
		}
		Font(string font, int fontSize, LogBase &log) : 
			fontSize(fontSize), color(DEFAULT_COLOR),
			log(log)
		{
			GaLib::Font(font, fontSize, DEFAULT_COLOR, log);
		}
		Font(string font, Color color, LogBase& log) : 
			fontSize(DEFAULT_FONT_SIZE), color(color),
			log(log)
		{
			GaLib::Font(font, DEFAULT_FONT_SIZE, color, log);	
		}
		Font(string font, int size, Color color, LogBase &log) : 
			fontSize(size), color(color),
			log(log)
		{
			string path = fontsPath + font;
			gFont = TTF_OpenFont(path.c_str(), size);
			if (gFont == NULL) {
				log.error("Error while initializing font! ");
				throw GameExceptions{};
			}
		}

		inline void setColor(Color color);
		inline void setFontSize(int size);

		inline bool displayText(string text);

		~Font() {
		}
	};
}