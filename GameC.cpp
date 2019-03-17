#include <iostream>
#include <SDL.h>
#include <cstdio>

#include "Base.h"
#include "Window.h"
#include "WindowHW.h"
#include "StdLog.h"

using namespace GaLib;

int main(int argc, char*argv[])
{
	
	const int SCREEN_WIDTH = 300;
	const int SCREEN_HEIGHT = 300;

	StdLog log;
	Base gb = Base{log};

	/*{
		Window window1(Rect{ 200, 200, SCREEN_WIDTH, SCREEN_HEIGHT }, "SDL Software based rendering", log);
		if (window1.loadImage(".\\Res\\hello_world.bmp", ImgTypes::BMP))
			log.debug("Successfully loaded the image hello world bmp to window surface");
		pause(2000);
		if (window1.loadImage(".\\Res\\Axe-dota-2.jpg", ImgTypes::JPG))
			log.debug("Successfully loaded the image axe-dota2.jpg on the window surface");
		pause(2000);
	}*/

	{
		WindowHW window2(Rect{ 500, 500, SCREEN_WIDTH, SCREEN_HEIGHT }, "SDL Hardware based rendering", log);
		window2.setClearColor(Color{ 0xFF, 0xFF, 0xFF });
		window2.clearWindow();

		pause(2000);
		if (window2.loadImage(".\\Res\\hello_world.bmp", ImgTypes::BMP))
			log.debug("Successfully loaded the image hello world bmp to window surface");
		pause(2000);
		if (window2.loadImage(".\\Res\\Axe-dota-2.jpg", ImgTypes::JPG))
			log.debug("Successfully loaded the image axe-dota2.jpg on the window surface");
		pause(2000);
		window2.displayText("Hello", "Roboto\\Roboto-Regular.ttf", 100);
		window2.drawRect(Rect{ 20, 20, 260, 260 }, Color{0xFF, 0xAB, 0xAD});
		window2.drawLine(Line{ 20, 20, 280, 280 }, Color{0xAA, 0xBC, 0xDC});
		pause(2000);
	}

	/*{
		Window gWindow4(100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, "Print text", log);
		gWindow4.clearWindow();
		gWindow4.loadImageWithTexture(".\\Res\\Axe-dota-2.jpg", ImgTypes::JPG);
		gWindow4.updateWindow();
		gWindow4.setViewPort(0, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, SCREEN_HEIGHT);
		gWindow4.loadFromRenderedText("xN|");
		gWindow4.updateWindow();
		gWindow4.setViewPort(0, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		gWindow4.loadFromRenderedText("Axe|");
		gWindow4.updateWindow();
		gWindow4.setViewPort(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2 + SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 4);
		gWindow4.loadFromRenderedText("qW|");
		gWindow4.updateWindow();
		gWindow4.setViewPort(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2 + SCREEN_WIDTH / 4, SCREEN_HEIGHT);
		gWindow4.loadFromRenderedText("Ty|");
		gWindow4.updateWindow();
		Events ev = Events::NONE;
		while (ev != Events::QUIT) {
			ev = gWindow4.getEvent();
		}
	}*/

	return 0;
}
