#pragma once

#include "GameWindow.h"

SDL_Surface* GameWindow::getWindowSurface() {
	return SDL_GetWindowSurface(window);
}

void GameWindow::fillWindowWithColor(int red, int green, int blue) {
	SDL_Surface* screenSurface = NULL;
	screenSurface = getWindowSurface();
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, red, green, blue));
}

void GameWindow::updateWindowSurface() {
	SDL_UpdateWindowSurface(window);
}

bool GameWindow::loadImage(string imagePath) {
	SDL_Surface* tSurface = SDL_LoadBMP(imagePath.c_str());
	if (tSurface == NULL) {
		cerr << "Unable to load image " << imagePath.c_str() << endl;
		return false;
	}
	SDL_Surface* surface = getWindowSurface();
	SDL_BlitSurface(tSurface, NULL, surface, NULL);
	return true;
}

void GameWindow::wait() {
	SDL_Event e;
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT)
				quit = true;
		}
	}
}

void pause(int delay) {
	SDL_Delay(delay);
}