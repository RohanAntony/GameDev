#include <SDL.h>
#include <SDL_image.h>
#include <algorithm>
#include <string>

#include "LogBase.h"
#include "SupportUtils.h"

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

		bool loadImage(string imagePath, ImgTypes type) {
			SDL_Surface* loadedSurface;
			if (type == ImgTypes::BMP)
				loadedSurface = loadBMP(imagePath);
			else
				loadedSurface = loadOtherImgTypes(imagePath);
			if (loadedSurface == NULL)
				return false;
			SDL_BlitScaled(loadedSurface, NULL, surface, NULL);
			SDL_FreeSurface(loadedSurface);
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
		Sprite(string imagePath, LogBase& log) :
			log(log), surface(NULL)
		{
			loadImage(imagePath, getExtensionOfFile(imagePath));
		}

		~Sprite() {
			SDL_FreeSurface(surface);
		}
	};
}