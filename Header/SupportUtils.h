#pragma once


enum class ImgTypes {
	BMP,
	PNG,
	JPG
};

enum class GameEvents {
	QUIT,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE
};

enum class RenderingType {
	SURFACE,
	TEXTURE,
	RENDERER
};

struct Color {
	int red;
	int green;
	int blue;
	int alpha;
};

struct Rect {
	int left;
	int top;
	int width;
	int height;
};