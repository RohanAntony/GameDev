#ifndef GALIB_INSTANCE_HEADER
#define GALIB_INSTANCE_HEADER

#include "GaLib/Sprite.h"
#include "GaLib/SupportUtils.h"
#include "Logger/LogBase.h"

namespace GaLib {
	class SpriteInstance {
		Sprite *sprite;
		LogBase &log;
		bool absDim;
		Rect<double> destDim;	//define the dimensions of the destination
		Rect<int> destDimAbs;
		bool visible;
	public:
		SpriteInstance(string imagePath, Rect<double> rect, Color maskColor, bool isVisible, LogBase& log):
			sprite(NULL), log(log), destDim(rect), visible(isVisible)
		{
			sprite = new Sprite(imagePath, maskColor, log);
			absDim = false;
		}

		//set absolute dimensions
		SpriteInstance(string imagePath, Rect<int> rect, Color maskColor, bool isVisible, LogBase& log) :
			sprite(NULL), log(log), destDimAbs(rect), visible(isVisible)
		{
			sprite = new Sprite(imagePath, maskColor, log);
			absDim = true;
		}

		void setNewDimensions(Rect<double> newDim) {
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

		void updateDimensions(double top, double left, double width, double height) {
			destDim.top += top;
			destDim.left += left;
			destDim.width += width;
			destDim.height += height;
		}
		
		void updateDimensions(int top, int left, int width, int height) {
			destDimAbs.top += top;
			destDimAbs.left += left;
			destDimAbs.width += width;
			destDimAbs.height += height;
		}

		SDL_Rect getDimensions(int width, int height) {
			SDL_Rect dim;
			dim.x = static_cast<int>(destDim.left * width);
			dim.y = static_cast<int>(destDim.top * height);
			dim.w = static_cast<int>(destDim.width * width);
			dim.h = static_cast<int>(destDim.height * height);
			return dim;
		}

		SDL_Rect getDimensions() {
			SDL_Rect dim;
			dim.x = destDimAbs.left;
			dim.y = destDimAbs.top;
			dim.w = destDimAbs.width;
			dim.h = destDimAbs.height;
			return dim;
		}

		SDL_Surface* getSurface() {
			return sprite->getSurface();
		}

		bool isAbsDim() {
			return absDim;
		}

		~SpriteInstance() {
			delete sprite;
		}
	};
}

#endif