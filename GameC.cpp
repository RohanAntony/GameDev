#include <iostream>
#include <SDL.h>
#include <cstdio>

#include "GameBase.h"
#include "GameWindow.h"

int main(int argc, char*argv[])
{
	
	int width = 640;
	int height = 480;

	GameBase gb = GameBase{ InitParam::SDL_INIT & InitParam::IMG_INIT };

	{
		GameWindow gWindow(100, 100, width, height, "SDL Tutorial");
		for (int i = 0; i < 255; ++i) {
			gWindow.fillWindowWithColor(i, i, i);
			gWindow.updateWindow();
			//pause(100);
		}
		gWindow.getEvent();
		pause(1000);
	}

	{
		GameWindow gWindow2(200, 200, width, height, "SDL image load");
		if (gWindow2.loadImageWithSurface(".\\Res\\hello_world.bmp", ImgTypes::BMP))
			cout << "Successfully loaded the image on the window surface" << endl;
		gWindow2.updateWindow();
		pause(2000);
		if (gWindow2.loadImageWithTexture(".\\Res\\Axe-dota-2.jpg", ImgTypes::JPG))
			cout << "Successfully loaded the image on the window surface" << endl;
		gWindow2.updateWindow();
		GameEvents e = gWindow2.getEvent();
		while(e != GameEvents::QUIT)
			e = gWindow2.getEvent();
	}

	return 0;
}
