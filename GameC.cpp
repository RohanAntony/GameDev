#include <iostream>
#include <SDL.h>
#include <cstdio>

#include "GaLib/Base.h"
#include "GaLib/Window.h"
#include "Logger/StdLog.h"

#define UNIT_SIZE 48

using namespace GaLib;

int main(int argc, char*argv[])
{
	
	const int SCREEN_WIDTH = UNIT_SIZE * 39;
	const int SCREEN_HEIGHT = UNIT_SIZE * 20;

	StdLog log;
	Base gb = Base{log};

	/*
		1. Create a window with size and int array

		3. Define objects in the window such as 
	*/

	{
		Window window1(Rect<int>{ 10, UNIT_SIZE + 10, SCREEN_WIDTH, SCREEN_HEIGHT }, "SDL Software based rendering", log);
		/*if (window1.loadImage(".\\Res\\hello_world.bmp"))
			log.debug("Successfully loaded the image hello world bmp to window surface");
		pause(2000);*/
		Color maskColor{ 0x30, 0x34, 0x6D, 0xFF }, noMask{0, 0, 0, 0};
		for (int i = 0; i < 59; i++) {
			for (int j = 0; j < 30; j++) {
				window1.addSprite(".\\Res\\props\\background\\wall1.bmp", Rect<int>{i*UNIT_SIZE, j*UNIT_SIZE, UNIT_SIZE, UNIT_SIZE}, noMask, true);
			}
		}
		int potion = window1.addSprite(".\\Res\\props\\items\\emptyBottle.bmp", 
			Rect<int>{ (UNIT_SIZE * 29) + UNIT_SIZE / 4, (UNIT_SIZE * 10) + UNIT_SIZE / 4, UNIT_SIZE / 2, UNIT_SIZE / 2}, 
			maskColor, true);
		int greenDude = window1.addSprite(".\\Res\\props\\items\\greenDude.bmp", Rect<int>{(UNIT_SIZE * 20) + 3, (UNIT_SIZE * 5) + 3, UNIT_SIZE * 2, UNIT_SIZE * 2}, maskColor, true);
		Events ev = Events::NONE;
		while (ev != Events::QUIT) {
			ev = window1.getEvent();
			if (ev == Events::LEFT)
				window1.modifySpriteDim(greenDude, 0, -UNIT_SIZE, 0, 0);
			else if (ev == Events::RIGHT)
				window1.modifySpriteDim(greenDude, 0, +UNIT_SIZE, 0, 0);
			else if (ev == Events::DOWN)
				window1.modifySpriteDim(greenDude, +UNIT_SIZE, 0, 0, 0);
			else if (ev == Events::UP)
				window1.modifySpriteDim(greenDude, -UNIT_SIZE, 0, 0, 0);
			window1.updateWindow();
		}
		//log.debug("Successfully loaded the image axe-dota2.jpg on the window surface");
		//pause(2000);
	}

	/*{
		WindowHW window2(Rect{ 500, 500, SCREEN_WIDTH, SCREEN_HEIGHT }, "SDL Hardware based rendering", log);
		window2.setClearColor(Color{ 0xFF, 0xFF, 0xFF });
		window2.clearWindow();
		window2.displayText("Hello", "C:\\Users\\Rohan Antony\\source\\repos\\GameC\\GameC\\Fonts\\Roboto\\Roboto-Regular.ttf", 100);
		//window2.drawRect(Rect{ 20, 20, 260, 260 }, Color{ 0xFF, 0xAB, 0xAD });
		//window2.drawLine(Line{ 20, 20, 280, 280 }, Color{ 0xAA, 0xBC, 0xDC });
		pause(2000);
		pause(2000);
		if (window2.loadImage("C:\\Users\\Rohan Antony\\source\\repos\\GameC\\GameC\\Res\\hello_world.bmp", ImgTypes::BMP))
			log.debug("Successfully loaded the image hello world bmp to window surface");
		pause(2000);
		if (window2.loadImage("C:\\Users\\Rohan Antony\\source\\repos\\GameC\\GameC\\Res\\Axe-dota-2.jpg", ImgTypes::JPG))
			log.debug("Successfully loaded the image axe-dota2.jpg on the window surface");
		pause(2000);
		pause(2000);
		pause(2000);
	}*/

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
