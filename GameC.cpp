#include <iostream>
#include <SDL.h>
#include <cstdio>

#include "GameBase.h"
#include "GameWindow.h"

int main(int argc, char*argv[])
{
	
	int width = 640;
	int height = 480;

	GameBase gb;

	{
		GameWindow gWindow(100, 100, width, height, "SDL Tutorial");
		for (int i = 0; i < 255; ++i) {
			gWindow.fillWindowWithColor(i, i, i);
			gWindow.updateWindowSurface();
			pause(100);
		}
		gWindow.wait();
	}

	{
		GameWindow gWindow2(200, 200, width, height, "SDL image load");
		if (gWindow2.loadImage("C:\\Users\\Rohan Antony\\Desktop\\Learning\\SDL\\hello_world.bmp"))
			cout << "Successfully loaded the image on the window surface" << endl;
		gWindow2.updateWindowSurface();
		gWindow2.wait();
	}

	return 0;
}
