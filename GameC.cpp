#include <iostream>
#include <SDL.h>
#include <cstdio>

#include "GameBase.h"
#include "GameWindow.h"
#include "StdLog.h"

int main(int argc, char*argv[])
{
	
	int width = 300;
	int height = 100;

	StdLog log;
	GameBase gb = GameBase{log};

	/*{
		GameWindow gWindow(100, 100, width, height, "SDL Tutorial", log);
		for (int i = 0; i < 255; ++i) {
			gWindow.fillWindowWithColor(i, i, i);
			gWindow.updateWindow();
			//pause(100);
		}
		gWindow.getEvent();
		pause(1000);
	}

	{
		GameWindow gWindow2(200, 200, width, height, "SDL image load", log);
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
		GameWindow gWindow3(400, 400, width, height, "Render Rect", log);
		Rect rect = {20, 20, 260, 260};
		Line line = { 20, 20, 280, 280 };
		Color fill = { 0x22, 0x22, 0x22, 0xFF };
		Color lineFill = {0, 0, 0, 0xFF};
		gWindow3.clearWindow();
		gWindow3.drawRect(rect, fill);
		gWindow3.drawLine(line, lineFill);
		gWindow3.updateWindow();
		pause(2000);
	}*/

	{
		GameWindow gWindow4(400, 400, width, height, "Print text", log);
		gWindow4.loadFromRenderedText("Hello world!");
		gWindow4.updateWindow();
		pause(2000);
	}

	return 0;
}
