#ifndef BLOCK_H 
#define BLOCK_H

#include <SDL2/SDL.h>
#include <string>
#include "sdl_utils.h"

class Block{
    public:
        void setTexture(SDL_Texture*);
        SDL_Texture* getTexture();
        SDL_Rect* getBox();
        bool exists();

        void setX(int);
        void setY(int);
        
        void remove();
        void setColor(int);
        int getColor();
        Block();
        Block(int x, int y, int sizeOfBox, int COLORCONSTANT, SDL_Renderer* RenToInitTex);
        void setBox(int x, int y, int sizeOfBox, int COLORCONSTANT, SDL_Renderer* RenToInitTex);

        ~Block();
    private:
        int color;
        SDL_Texture* texture;
        SDL_Rect box;
};


#endif

