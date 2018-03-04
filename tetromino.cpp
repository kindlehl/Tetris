#include "tetromino.h"
#include "globals.h"

/*
 *populate 4 of the blocks based on RNG
 *
 *
 */
void populateTetr(Block** tetr, int COLORCONSTANT, SDL_Renderer* ren){
    int type = rand()%7; //scalar number is number of possible pieces
    switch(type){
        case 0: //if long piece
            for(int i = 0; i < 4; i++)
                //populate bottom row of our block array
                tetr[i][3] = Block(30, i, 1000, COLORCONSTANT, ren); //first three params are arbitrary 
                break;
        case 1:
            tetr[1][2] = Block(30, 1 ,1000, COLORCONSTANT, ren);
            tetr[0][1] = Block(30, 1 ,1000, COLORCONSTANT, ren); //T
            tetr[0][2] = Block(30, 1 ,1000, COLORCONSTANT, ren);
            tetr[0][3] = Block(30, 1 ,1000, COLORCONSTANT, ren);
            break;
        case 2:
            tetr[0][2] = Block(30, 1 ,1000, COLORCONSTANT, ren);
            tetr[0][3] = Block(30, 1 ,1000, COLORCONSTANT, ren);
            tetr[1][2] = Block(30, 1 ,1000, COLORCONSTANT, ren); //S
            tetr[1][1] = Block(30, 1 ,1000, COLORCONSTANT, ren);
            break;
        case 3:
            tetr[0][2] = Block(30, 1 ,1000, COLORCONSTANT, ren);
            tetr[0][1] = Block(30, 1 ,1000, COLORCONSTANT, ren);
            tetr[1][2] = Block(30, 1 ,1000, COLORCONSTANT, ren);//Z
            tetr[1][3] = Block(30, 1 ,1000, COLORCONSTANT, ren);
            break;
             
        case 4:
            tetr[0][2] = Block(30, 1 ,1000, COLORCONSTANT, ren);
            tetr[0][1] = Block(30, 1 ,1000, COLORCONSTANT, ren); //O
            tetr[1][2] = Block(30, 1 ,1000, COLORCONSTANT, ren);
            tetr[1][1] = Block(30, 1 ,1000, COLORCONSTANT, ren);
            break;

        case 5:
            tetr[0][1] = Block(30, 1 ,1000, COLORCONSTANT, ren);
            tetr[1][1] = Block(30, 1 ,1000, COLORCONSTANT, ren);
            tetr[2][1] = Block(30, 1 ,1000, COLORCONSTANT, ren); //L
            tetr[2][2] = Block(30, 1 ,1000, COLORCONSTANT, ren);
            break;
        case 6:
            tetr[0][2] = Block(30, 1 ,1000, COLORCONSTANT, ren);
            tetr[1][2] = Block(30, 1 ,1000, COLORCONSTANT, ren);//J
            tetr[2][2] = Block(30, 1 ,1000, COLORCONSTANT, ren);
            tetr[2][1] = Block(30, 1 ,1000, COLORCONSTANT, ren);
            break;
    }
}

Block** Tetromino::getBlocks(){
    return blocks;
}

Tetromino::Tetromino(SDL_Renderer* ren){
    srand(time(NULL));
    //assign block** to four block*
    blocks = new Block*[4];
    //assign those four block* the actual blocks of 4
    for( int i = 0; i < 4; i++ ){
        blocks[i] = new Block[4];
        for(int j = 0; j < 4; j++){
            //give those blocks -1 color value to indicate passive population
            blocks[i][j] = Block(200, 200, 200, -1, ren);
        }
    }

    int tetrColor = rand()%NUM_COLORS;
    //populate 4 of the blocks
    populateTetr(blocks, tetrColor, ren);

 
}

