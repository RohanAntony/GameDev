#ifndef GALIB_SPRITE_HEADER
#define GALIB_SPRITE_HEADER

#include <SDL.h>
#include <SDL_image.h>
#include <algorithm>
#include <string>

#include "Logger/LogBase.h"
#include "GaLib/SupportUtils.h"

using std::string;

namespace GaLib {
	class Sprite {
		LogBase &log;
		SDL_Surface* surface;

		SDL_Surface* loadBMP(string imagePath) {
			SDL_Surface* loadedSurface = SDL_LoadBMP(imagePath.c_str());
			if (loadedSurface == NULL) {
				log.error("Unable to load BMP image " + imagePath);
				return NULL;
			}
			return loadedSurface;
		}

		SDL_Surface* loadOtherImgTypes(string imagePath) {
			SDL_Surface* optimizedSurface = NULL;
			SDL_Surface* loadedSurface = IMG_Load(imagePath.c_str());
			if (loadedSurface == NULL) {
				log.error("Umable to load image: " + imagePath);
				return NULL;
			}
			return loadedSurface;
		}

		bool loadImage(string imagePath, ImgTypes type, Color maskColor) {
			SDL_Surface* loadedSurface;
			if (type == ImgTypes::BMP)
				loadedSurface = loadBMP(imagePath);
			else
				loadedSurface = loadOtherImgTypes(imagePath);
			if (loadedSurface == NULL)
				return false;
			SDL_bool enableMasking = SDL_FALSE;
			if (maskColor.alpha == 0xFF)
				enableMasking = SDL_TRUE;
			SDL_SetColorKey(loadedSurface, enableMasking, 
				SDL_MapRGB(loadedSurface->format, maskColor.red, maskColor.green, maskColor.blue)
			);
			surface = loadedSurface;
			return true;
		}

		ImgTypes getExtensionOfFile(string filename) {
			string::size_type idx = filename.rfind('.');
			ImgTypes type = ImgTypes::NONE;
			if (idx != string::npos)
			{
				string extension = filename.substr(idx + 1);
				std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
				if (extension == "bmp")
					type = ImgTypes::BMP;
				else if (extension == "jpg")
					type = ImgTypes::JPG;
				else if (extension == "png")
					type = ImgTypes::PNG;
			}
			return type;
		}

	public:
		Sprite(string imagePath, Color maskColor, LogBase& log) :
			log(log), surface(NULL)
		{
			//add code to loadImage with color key set
			loadImage(imagePath, getExtensionOfFile(imagePath), maskColor);
		}

		SDL_Surface* getSurface() {
			return surface;
		}

		~Sprite() {
			SDL_FreeSurface(surface);
		}
	};
}

#endif