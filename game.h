#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "globals.h"
#include <SDL2/SDL.h>
#include "block.h"
#include "sdl_utils.h"
#include "tetromino.h"

class Block;

class Game{
    public:
        void printTilePositions();
        float borderWidth;
        Block* generateTetromino( Tetromino*, SDL_Renderer*);
        int regulator;
        bool rotationCollision(int*, int*);
        void input();
        void drawBlocks();
        void draw();
        void update();
        void rotateTetromino();
        void rotateMatrix(Block**, int, int, int);
        void sortTetrominoX();
        void sortTetrominoY();
        Block** generateMatrix(int, int, int);
        void moveTetromino();               //moves tetromino vertically
        void shiftTetromino(int );          //moves tetromino horizontally
        void stopTetromino();
        void integrateTetromino();
        bool checkRow(int);
        void deleteRow(int);
        void shiftRow(int);
        void shiftRowsAbove(int);
        bool existsinTetromino(int, int);
        int normalizeX(int);
        int normalizeY(int);
        Game(SDL_Renderer* theRenderer, bool*);
        ~Game();
        int getSpeed();
        int generateColor();
        void setSpeed(int);
        bool sideCollision(int, int, int);
        bool bottomCollision(int, int, int);
    private:
        int moveCycle;
        int size;
        bool* quit;
        Tetromino* tetrObj;         //object to store tetromino before it is put into game
        SDL_Texture* borderTex;
        SDL_Rect border;
        int nextTetrominoColor;
        Block* tetromino;           //actualy tetromino as it moves down board
        bool tetrominoMoving;
        float speed;
        SDL_Renderer* renderer;
        //a block in this array is NULL if the color value is -1
        Block** blocks;         //game board
        
};


#endif
