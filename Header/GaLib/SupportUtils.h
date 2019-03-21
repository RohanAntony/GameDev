#ifndef GALIB_SUPPORT_UTILS_HEADER
#define GALIB_SUPPORT_UTILS_HEADER

namespace GaLib {
	enum class ImgTypes {
		BMP,
		PNG,
		JPG,
		NONE
	};

	enum class Events {
		QUIT,
		UP,
		DOWN,
		LEFT,
		RIGHT,
		NONE
	};

	struct Color {
		Uint8 red;
		Uint8 green;
		Uint8 blue;
		Uint8 alpha;
	};

	template <class T>
	struct Rect {
		T left;
		T top;
		T width;
		T height;
	};

	struct Line {
		int startX, startY, endX, endY;
	};
}

#endif