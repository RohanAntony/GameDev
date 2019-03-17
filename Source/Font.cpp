#include "Font.h"

using GaLib::Font;

void Font::setColor(Color color) {
	this->color = color;
}

void Font::setFontSize(int size) {
	this->fontSize = size;
}

bool Font::displayText(string message) {
	SDL_Texture* mTexture = NULL;
	SDL_Color textColor = { color.red, color.green, color.blue};
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, message.c_str(), textColor);
	if (textSurface == NULL) {
		log.error("Unable to render text surface! SDL_Error" + string(TTF_GetError()));
		return false;
	}
	else {

	}
}