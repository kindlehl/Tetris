#include "globals.h"
#include <math.h>
#include <iostream>
#include "test.h"
#include <SDL2/SDL.h>
#include "game.h"

using namespace std;



void SDL_initialize(SDL_Window** window, SDL_Renderer** renderer){
    SDL_Init(SDL_INIT_EVERYTHING);
    *window = SDL_CreateWindow("Tetris: The Game", 200, 0, screenWidth, screenHeight, 0);
    *renderer = SDL_CreateRenderer(*window, -1, 0);
    if(!*window || !*renderer){
        cout << "Error initalizing window/renderer" << endl;
    }
    
    SDL_RenderClear(*renderer);
}

int main(){
    //containers for window rendering
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool quit = false;
    SDL_initialize(&window, &renderer);

    Game game(renderer, &quit);
    

    while(!quit){
        game.input();
        game.update();
        game.draw();
    }
    
    cout << "Hi! " << endl;
}
