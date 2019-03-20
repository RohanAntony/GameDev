#ifndef GALIB_INSTANCE_HEADER
#define GALIB_INSTANCE_HEADER

#include "GaLib/Sprite.h"
#include "SupportUtils.h"
#include "LogBase.h"

namespace GaLib {
	class SpriteInstance {
		Sprite *sprite;
		LogBase &log;
		Rect<float> destDim;	//define the dimensions of the destination
		bool visible;
	public:
		SpriteInstance(string imagePath, Rect<float> rect, bool isVisible, LogBase& log):
			sprite(NULL), log(log), destDim(rect), visible(isVisible)
		{
			sprite = new Sprite(imagePath, log);
		}

		void setNewDimensions(Rect<float> newDim) {
			destDim = newDim;
		}

		bool isVisible() {
			return visible;
		}

		bool hide() {
			visible = false;
		}

		bool show() {
			visible = true;
		}

		void updateDimensions(float top, float left, float width, float height) {
			destDim.top += top;
			destDim.left += left;
			destDim.width += width;
			destDim.height += height;
		}

		SDL_Rect getDimensions(int width, int height) {
			SDL_Rect dim;
			dim.x = destDim.left * width;
			dim.y = destDim.top * height;
			dim.w = destDim.width * width;
			dim.h = destDim.height * height;
			return dim;
		}

		SDL_Surface* getSurface() {
			return sprite->getSurface();
		}

		~SpriteInstance() {
			delete sprite;
		}
	};
}

#endif