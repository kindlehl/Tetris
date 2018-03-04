#include "/usr/include/sdl_utils.h"
void moveRectHorizontalBy(int plusOrMinus, SDL_Rect* rect){
    rect->x += plusOrMinus;
}

void moveRectVerticalBy(int plusOrMinus, SDL_Rect* rect){
    rect->y -= plusOrMinus;
}

int testMoveVerticalBy(int plusorMinus, SDL_Rect* rect){
    return rect->y + plusorMinus;
}

int testMoveHorizontalBy(int plusorMinus, SDL_Rect* rect){
    return rect->x + plusorMinus;
}

//loads bmp at *path*, checks for errors, loads a texture to renderer, returns texture
SDL_Texture* loadTexture(SDL_Renderer* renderer, string path ){
    SDL_Surface* tempSurf = SDL_LoadBMP(path.c_str());
    if(!tempSurf){
        cout << "Error loading image at: " << path.c_str() << endl;
        return NULL;
    }
    
    SDL_Texture* tempTex = SDL_CreateTextureFromSurface(renderer, tempSurf);
    if(!tempTex){
        cout << "Error loading surface into texture";
        return NULL;
    }

    return tempTex;

}


