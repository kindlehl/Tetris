#include "block.h"
#include "globals.h"
/* gives box arbitrary values. sets color to -1 which is what we use to determine if that block actually exists
 *
 */
Block::Block(){
    box.x = screenWidth/2;
    box.y = screenHeight/2;
    box.h = screenHeight/10;
    box.w = screenWidth/10;
    color = -1;
}

void Block::setX(int x){
    box.x = x;
    
}

void Block::setY(int y){
    box.y = y;
}

void Block::remove(){
    color = -1;
}

void Block::setColor(int c){
    color = c;
}

Block::~Block(){

}

/*
 * checks the blocks color. a color value of -1 indicates that the box is not being used.
 */
bool Block::exists(){
    if(color == -1){
        return 0;
    }
    return 1;
}

/*
 * specific constructor. Sets coordinates size, as well as color
 * Also creates a texture for the box using our error-checking texture-loading
 * function
 */
Block::Block(int x, int y, int size, int tetrColor, SDL_Renderer* ren){
   box.x = x;
   box.y = y;
   box.h = size;
   box.w = size;
   color  = tetrColor;
   string path;

  if(tetrColor == RED)
        path = "red.bmp";
  else if(tetrColor == GREEN)
      path = "green.bmp";
  else if(tetrColor == BLUE)
      path = "blue.bmp";
  else if(tetrColor == PURPLE)
      path = "purple.bmp";
  else if(tetrColor == YELLOW)
      path = "yellow.bmp";
  else
      path = "grey.bmp";
    texture = loadTexture(ren, path);  
}

/*
 *  invoked usually after a block is initialized using the default constructor
 *  Does exact same as the secondary constructor, but we can't use that 
 *  constructor to initialize an array of blocks _       _
 *                                                \(^~^)/
 */
void Block::setBox(int x, int y, int size, int tetrColor, SDL_Renderer* ren){
   box.x = x;
   box.y = y;
   box.h = size;
   box.w = size;
   color  = tetrColor;
   string path;
  
  if(tetrColor == RED)
        path = "red.bmp";
  else if(tetrColor == GREEN)
      path = "green.bmp";
  else if(tetrColor == BLUE)
      path = "blue.bmp";
  else if(tetrColor == PURPLE)
      path = "purple.bmp";
  else if(tetrColor == YELLOW)
      path = "yellow.bmp";
  else
      return;
   


   texture = loadTexture(ren, path);  
}

int Block::getColor(){
    return color;
}

SDL_Rect* Block::getBox(){
    return &box;
}
void Block::setTexture(SDL_Texture* tex){
    texture = tex;
}

SDL_Texture* Block::getTexture(){
    return texture;
}
