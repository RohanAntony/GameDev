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

GameEvents GameWindow::getEvent() {
	SDL_Event e;
	GameEvents gEv = GameEvents::NONE;
	if (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT) {
			cout << "Quit!" << endl;
			gEv = GameEvents::QUIT;
		}
		else if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
				case SDLK_UP:
					cout << "Up!" << endl;
					gEv = GameEvents::UP;
					break;
				case SDLK_DOWN:
					cout << "Down!" << endl;
					gEv = GameEvents::DOWN;
					break;
				case SDLK_LEFT:
					cout << "Left!" << endl;
					gEv = GameEvents::LEFT;
					break;
				case SDLK_RIGHT:
					cout << "Right!" << endl;
					gEv = GameEvents::RIGHT;
					break;

			}
		}
	}
	return gEv;
}

void pause(int delay) {
	SDL_Delay(delay);
}