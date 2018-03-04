#ifndef SDL_UTILS_H
#define SDL_UTILS_H

#include <SDL2/SDL.h>
#include <string>
#include <iostream>

using namespace std;

int testMoveHorizontalBy(int, SDL_Rect*);
int testMoveVerticalBy(int, SDL_Rect*);
void moveRectVerticalBy(int, SDL_Rect* );
void moveRectHorizontalBy(int, SDL_Rect* );
SDL_Texture* loadTexture(SDL_Renderer* renderer, string path);

#endif
