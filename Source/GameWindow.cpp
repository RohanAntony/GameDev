#pragma once

#include <string>

#include <SDL_image.h>
#include "GameWindow.h"

using std::string;

GameWindow::GameWindow(int top, int left, int width, int height, string title, LogBase& log) :
	screenWidth(width), screenHeight(height),
	positionLeft(left), positionTop(top),
	windowTitle(title), lastUsedRenderingType(RenderingType::SURFACE),
	log(log)
{
	window = SDL_CreateWindow(title.c_str(), left, top, width, height, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		log.error("Window could not be created" + string(SDL_GetError()));
		throw GameExceptions{};
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		log.error("Renderer could not be created! Error: " + string(SDL_GetError()));
		throw GameExceptions{};
	}
	SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0, 0xFF);
	log.debug("Window created with title " + title);
}


SDL_Surface* GameWindow::getWindowSurface() {
	return SDL_GetWindowSurface(window);
}

void GameWindow::fillWindowWithColor(int red, int green, int blue) {
	SDL_Surface* screenSurface = NULL;
	screenSurface = getWindowSurface();
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, red, green, blue));
}

void GameWindow::updateWindow() {
	if (lastUsedRenderingType == RenderingType::SURFACE)
		SDL_UpdateWindowSurface(window);
	else if (lastUsedRenderingType == RenderingType::TEXTURE) {
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}
	else if (lastUsedRenderingType == RenderingType::RENDERER) {
		SDL_RenderPresent(renderer);
	}
}

SDL_Surface* GameWindow::loadBMP(string imagePath) {
	SDL_Surface* tSurface = SDL_LoadBMP(imagePath.c_str());
	if (tSurface == NULL) {
		log.error("Unable to load image " + imagePath);
		return NULL;
	}
	return tSurface;
}

SDL_Surface* GameWindow::loadOtherImgTypes(string imagePath) {
	SDL_Surface* optimizedSurface = NULL;
	SDL_Surface* loadedSurface = IMG_Load(imagePath.c_str());
	SDL_Surface* surface = getWindowSurface();
	if (loadedSurface == NULL) {
		log.error("Error while loading image: " + imagePath);
		return NULL;
	}
	else {
		optimizedSurface = SDL_ConvertSurface(loadedSurface, surface->format, NULL);
		if (optimizedSurface == NULL) {
			log.error("Unable to optimize image, Error: " + string(SDL_GetError()));
			return NULL;
		}
		SDL_FreeSurface(loadedSurface);
		return optimizedSurface;
	}
	return false;
}

bool GameWindow::loadImageWithSurface(string imagePath, ImgTypes type) {
	SDL_Surface* tSurface = NULL;
	SDL_Surface* surface = getWindowSurface();
	if (type == ImgTypes::BMP)
		tSurface = loadBMP(imagePath);
	else if (type == ImgTypes::PNG || type == ImgTypes::JPG)
		tSurface = loadOtherImgTypes(imagePath.c_str());
	if (!tSurface)
		return false;
	SDL_BlitSurface(tSurface, NULL, surface, NULL);
	SDL_FreeSurface(tSurface);
	lastUsedRenderingType = RenderingType::SURFACE;
	return true;
}

bool GameWindow::loadImageWithTexture(string imagePath, ImgTypes type) {
	SDL_Surface* tSurface = NULL;
	if (type == ImgTypes::BMP)
		tSurface = loadBMP(imagePath);
	else if (type == ImgTypes::PNG || type == ImgTypes::JPG)
		tSurface = loadOtherImgTypes(imagePath.c_str());
	if (!tSurface)
		return false;
	texture = SDL_CreateTextureFromSurface(renderer, tSurface);
	if (!texture) {
		log.error("Error while loading texture! Error: " + string(SDL_GetError()));
		return false;
	}
	SDL_FreeSurface(tSurface);
	lastUsedRenderingType = RenderingType::TEXTURE;
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

void GameWindow::clearWindow() {
	Color clearColor = { 0xFF, 0xFF, 0xFF, 0xFF };
	SDL_SetRenderDrawColor(renderer, clearColor.red, clearColor.green, clearColor.blue, clearColor.alpha);
	SDL_RenderClear(renderer);
}

void GameWindow::drawRect(Rect rect, Color color) {
	SDL_Rect fillRect = { rect.top, rect.left, rect.width, rect.height };
	SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, color.alpha);
	SDL_RenderFillRect(renderer, &fillRect);
	lastUsedRenderingType = RenderingType::RENDERER;
}

void GameWindow::drawLine(Line line, Color color) {
	SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, color.alpha);
	SDL_RenderDrawLine(renderer, line.startX, line.startY, line.endX, line.endY);
	lastUsedRenderingType = RenderingType::RENDERER;
}

GameWindow::~GameWindow() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;
}

void pause(int delay) {
	SDL_Delay(delay);
}