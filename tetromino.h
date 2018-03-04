#ifndef TETROMINO_H
#define TETROMINO_H

#include "block.h"
#include <time.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
/*
 *
 *  0,0 1,0 2,0 3,0
 *
 *  0,1 1,1 2,1 3,1
 *
 *  0,2 1,2 2,2 3,2
 *
 *  0,3 1,3 2,3 3,3
 *
 */

class Tetromino{
    public:
        Tetromino(SDL_Renderer*);
        ~Tetromino();
        Block** getBlocks();
    private:
        Block** blocks;      //

};

#endif

