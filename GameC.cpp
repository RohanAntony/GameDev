#include <iostream>
#include <SDL.h>
#include <cstdio>

#include "GameBase.h"
#include "GameWindow.h"
#include "StdLog.h"

int main(int argc, char*argv[])
{
	
	const int SCREEN_WIDTH = 300;
	const int SCREEN_HEIGHT = 300;

	StdLog log;
	GameBase gb = GameBase{log};

	{
		GameWindow gWindow(100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, "SDL Tutorial", log);
		for (int i = 0; i < 255; ++i) {
			gWindow.fillWindowWithColor(i, i, i);
			gWindow.updateWindow();
			//pause(100);
		}
		gWindow.getEvent();
		pause(1000);
	}

	{
		GameWindow gWindow2(200, 200, SCREEN_WIDTH, SCREEN_HEIGHT, "SDL image load", log);
		if (gWindow2.loadImageWithSurface(".\\Res\\hello_world.bmp", ImgTypes::BMP))
			log.debug("Successfully loaded the image on the window surface");
		gWindow2.updateWindow();
		pause(2000);
		if (gWindow2.loadImageWithTexture(".\\Res\\Axe-dota-2.jpg", ImgTypes::JPG))
			log.debug("Successfully loaded the image on the window surface");
		gWindow2.updateWindow();
		GameEvents e = gWindow2.getEvent();
		pause(3000);
	}

	{
		GameWindow gWindow3(400, 400, SCREEN_WIDTH, SCREEN_HEIGHT, "Render Rect", log);
		Rect rect = {20, 20, 260, 260};
		Line line = { 20, 20, 280, 280 };
		Color fill = { 0x22, 0x22, 0x22, 0xFF };
		Color lineFill = {0, 0, 0, 0xFF};
		gWindow3.clearWindow();
		gWindow3.drawRect(rect, fill);
		gWindow3.drawLine(line, lineFill);
		gWindow3.updateWindow();
		pause(2000);
	}

	{
		GameWindow gWindow4(100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, "Print text", log);
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
		GameEvents ev = GameEvents::NONE;
		while (ev != GameEvents::QUIT) {
			ev = gWindow4.getEvent();
		}
	}

	return 0;
}
