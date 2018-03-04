#include "game.h"
#include "math.h"
#include "globals.h"

void Game::printTilePositions(){
    for(int i = 0; i < NUMROWS; i++){
        for(int j = 0; j < NUMCOLS; j++){
           cout << "(" << j << ", " << i << ")(" << blocks[i][j].getBox()->x << ", " << blocks[i][j].getBox()->y << ")  ";
        }
        std::cout << std::endl;
    }
}

Game::Game(SDL_Renderer* ren, bool* q){
    renderer = ren;
    borderWidth = BORDER;
    quit = q;
    regulator = 0;
    //configure border
    border.x = screenWidth-BORDER;
    border.y = 0;
    border.w = BORDER;
    border.h = screenHeight;
    borderTex = loadTexture(ren, "border.bmp");
    moveCycle = 0;    
    size = screenHeight/NUMROWS;
    
    if((screenWidth-BORDER)/NUMCOLS != screenHeight/NUMROWS){
        std::cout << "MACROS ARE INCORRECT!!!!" << std::endl;
    }
    
    blocks = new Block*[NUMROWS];

    for(int i = 0; i < NUMROWS; i++){
        blocks[i] = new Block[NUMCOLS];
        for(int j = 0; j < NUMCOLS; j++)
            blocks[i][j] = Block(j*size,i*size, size, -1, ren);
    }
    speed = 16;
    tetrObj = new Tetromino(ren);
    tetromino = generateTetromino(tetrObj,ren);
    if(!tetromino){
        std::cout << "Error generating tetromino in constructor " << std::endl;
    }
    tetrominoMoving = true;

}

//takes in an screen coordinate and converts it into an index
int Game::normalizeX(int X){
    return (X/size);
}

//takes in an screen coordinate and converts it into an index
int Game::normalizeY(int Y){
    return (Y/size);

}

int Game::generateColor(){
    return rand()%NUM_COLORS;
}

void Game::integrateTetromino(){
    Block temp;
    int newX;
    int newY;
    //loop through the 4x4 tetromino
    for(int i = 0; i < 4; i++){
        newX = tetromino[i].getBox()->x;
        newY = tetromino[i].getBox()->y;
        blocks[normalizeY(newY)][normalizeX(newX)] = Block(newX, newY, size, tetromino[i].getColor(), renderer); // I think tileHeight is wrong
        //calling constructor like this is ineffecient 
    } 
}

void Game::stopTetromino(){
    tetrominoMoving = false;
    integrateTetromino();
}

void Game::moveTetromino(){
    for( int i = 0; i < 4; i ++){
        moveRectVerticalBy(-screenHeight/NUMROWS, tetromino[i].getBox());
    }
}
/*Moves tetromino in horizontal direction
 *  shift must be 1, or -1, indicating a positive or negative direction
 */
void Game::shiftTetromino(int shift){
    for(int i = 0; i < 4; i++){
        moveRectHorizontalBy(shift*(screenWidth-BORDER)/NUMCOLS, tetromino[i].getBox());
    }
}

/*
 *  allocates memory to a block array that is used 
 *  returns a pointer to the new block array
 *
 */
Block* Game::generateTetromino(Tetromino* tetr, SDL_Renderer* ren){
    int count = 0;
    Block* newBlocks = new Block[4];
    for(int i = 0; i < 4 && count < 4; i++){
        for(int j = 0; j < 4 && count < 4; j++){
            if(tetr->getBlocks()[i][j].exists()){

                //std::cout << "index " << i << "," << j << " of tetromino is not NULL" << std::endl;
                newBlocks[count].setBox(j*size, i*size, size, tetr->getBlocks()[i][j].getColor(), ren); //x,y,size, color, renderer
                count++;
            }
        }   
    }
    return newBlocks;
}

void Game::setSpeed(int x){
    speed = x;
}

int Game::getSpeed(){
    return speed;
}
/*
 *checks to see if a coordinate is inhabited by a block in the tetromino
 *
 */
bool Game::existsinTetromino(int x, int y){
    //if the tetromino is not null
    if(tetromino)
      for(int i = 0; i < 4; i++){
            if(tetromino[i].getBox()->x == x && tetromino[i].getBox()->y == y)
                return 1;
        }
    return 0;
}
/*
 *Params: x,y are coordinates of a block, pluaOrMinus is the direction that we are testing
 *
 */
bool Game::sideCollision(int x, int y, int plusOrMinus){
    if( (x+plusOrMinus >= screenWidth-BORDER || x+plusOrMinus < 0)  ){
        return 1;
    }
    if((!existsinTetromino(x+plusOrMinus, y) && blocks[normalizeY(y)][normalizeX(x+plusOrMinus)].exists()) ){
        return 1;
    }

    return 0;
}

bool Game::bottomCollision(int x, int y, int plusOrMinus){
    if(y+plusOrMinus >= screenHeight)
        return 1;
    if(!existsinTetromino(x, y+plusOrMinus) && blocks[normalizeY(y+plusOrMinus)][normalizeX(x)].exists()){
        return 1;
    }
    return 0;
}

bool Game::rotationCollision(int* x, int* y){
    int outsideBounds = 0, outsideBounds2 = screenWidth - BORDER - size;
    bool collide = false;
    for(int i = 0; i < 4; i++){
        if(x[i] < outsideBounds){
            outsideBounds = x[i];
        }
        if(x[i] > outsideBounds2){
            outsideBounds2 = x[i];;
        }
    }
    outsideBounds2 -= screenWidth-BORDER-size;

    cout << "OUTSIDE BOUNDS" << outsideBounds << ", " << outsideBounds2 << endl;
    if(outsideBounds < 0){
        for(int i = 0; i < 4; i++){
            if(bottomCollision(x[i]-outsideBounds, y[i], 0))
                collide = true;
        }
    }
    else{
        for(int i = 0; i < 4; i++){
            if(bottomCollision(x[i]-outsideBounds2, y[i], 0))
                collide = true;
        }
    }
    if(!collide && outsideBounds < 0){
        for(int i = 0; i < 4; i++){
            x[i] -= outsideBounds;
        }
    }
    else if(!collide && outsideBounds2 > 0){
        for(int i = 0; i < 4; i++){
            x[i] -= outsideBounds2;
        }
    }

    return collide;
}
/*
 *checks if all blocks on row index exist
 *
 */
bool Game::checkRow(int index){
    for(int i = 0; i < NUMCOLS; i++){
        if(!blocks[index][i].exists())
            return 0;
    }
    return 1;
}

void Game::deleteRow(int index){
    for(int i = 0; i < NUMCOLS; i++){
        blocks[index][i].remove();
    }
}

void Game::shiftRow(int index){
    for(int i = 0; i < NUMCOLS; i++){

        blocks[index][i].setColor(blocks[index-1][i].getColor());
        blocks[index][i].setTexture(blocks[index-1][i].getTexture());
    }
    deleteRow(index-1);
}

void Game::shiftRowsAbove(int index){
    for(int i = index; i > 0; i--){
       shiftRow(i); 
    } 
}

void Game::sortTetrominoX(){
    Block temp;
    for(int j =0; j < 3; j++){
        for(int i = 0; i < 3; i++){
            if(tetromino[i].getBox()->x > tetromino[i+1].getBox()->x){
                temp = tetromino[i];
                tetromino[i] = tetromino[i+1];
                tetromino[i+1] = temp;
            }
        }
    }   
}
void Game::sortTetrominoY(){
    Block temp;
    for(int j =0; j < 3; j++){
        for(int i = 0; i < 3; i++){
            if(tetromino[i].getBox()->y > tetromino[i+1].getBox()->y){
                temp = tetromino[i];
                tetromino[i] = tetromino[i+1];
                tetromino[i+1] = temp;
            }
        }
    }   
}

Block** Game::generateMatrix(int leftmostX, int topmostY, int matrixSize){
    Block** matrix;
    int count;
    cout << "topmostY: " << topmostY <<" leftmostX: " << leftmostX << endl;
    matrix = new Block*[matrixSize];
    for(int i = 0; i < matrixSize; i++){
        matrix[i] = new Block[matrixSize];      //allocate matrix and making sure no block exists
        for(int j = 0; j < matrixSize; j++)
            matrix[i][j].remove();
    }
    for(int i = 0; i < 4; i++){
        std::cout << "row " << (tetromino[i].getBox()->y-topmostY)/size;
        std::cout << ", col " << (tetromino[i].getBox()->x-leftmostX)/size << std::endl;
        matrix[(tetromino[i].getBox()->y-topmostY)/size][(tetromino[i].getBox()->x - leftmostX)/size] = tetromino[i]; //use coordinates to generate relative index
    }                                                                                                                 //set that index to the corresponding tetr
    for(int i = 0; i < matrixSize; i++){
        for(int j = 0; j < matrixSize; j++){
            if(matrix[i][j].exists())
                std::cout << "X";
            else{
                std::cout << "-";
            }
        }
        std::cout << std::endl;
     
    }
    if(matrixSize == 4 && matrix[2][0].exists()){
        for(int i = 0; i < 4; i++){
            matrix[i][1] = matrix[i][0];
            matrix[i][0].remove();
        }
    }
    else if(matrixSize ==4){
        for(int i = 0; i < 4; i++){
            matrix[2][i] = matrix[3][i];
            matrix[3][i].remove();
        }
    }
    return matrix;
}

void Game::rotateMatrix(Block** matrix, int leftmostX, int topmostY, int matrixSize){
    if(matrixSize == 2)//if piece is O, do nothing
        return;
    int additive = size, count = 0;
    int* newXValues = new int[4], *newYValues = new int[4];
    bool collide = false;
    Block** newMatrix = new Block*[matrixSize]; //matrix that we copy to
    Block* tempRow = new Block[matrixSize];     //array that we use to capture an entire row of a matrix
    
    if(++regulator && regulator%2) //regulator prevents blocks from shifting in one direction for every rotation
        additive = -size;

    for(int i = 0; i < matrixSize; i++){
        newMatrix[i] = new Block[matrixSize]; //create new matrix
    }   

    //rotate old matrix into new matrix
        for(int numTimesDone = 0; numTimesDone < matrixSize; numTimesDone++){
            for(int i = 0; i < matrixSize; i++){
                    tempRow[i] = matrix[numTimesDone][i] ;
            }
            for(int k = matrixSize-1; k >=0; k--){
                   newMatrix[k][numTimesDone] = tempRow[abs(k-matrixSize + 1)];
            }
        }
#ifdef DEBUG

    for(int i = 0; i < matrixSize; i++){
        for(int j = 0; j < matrixSize; j++){
            if(newMatrix[i][j].exists()){
                cout << "X";

            }
            else{
                cout << "-";
            }
        }
        cout << endl;
    }
#endif
    /* Check for wall kicks and adjust
     * Check for collisions and cancel if any are found.
     */
    for(int i = 0; i < matrixSize; i++){
        for(int j = 0; j < matrixSize; j++){
            if(newMatrix[i][j].exists()){
                newXValues[count] = j*size + leftmostX +additive;
                newYValues[count] = i*size + topmostY;
    
                count++;
                    
             }
         }

    }
    if(rotationCollision(newXValues, newYValues)){
                cout << "COLLISION" <<endl;
                collide = true;
    }

    count = 0;
    /* if no collisions would occur, then rotate
     *
     */
    if(!collide){
        for(int i = 0; i < matrixSize; i++){
            for(int j = 0; j < matrixSize; j++){
                if(newMatrix[i][j].exists()){
                    newMatrix[i][j].setX(j*size + leftmostX +additive);
                    newMatrix[i][j].setY(i*size + topmostY);
                    tetromino[count] = newMatrix[i][j];
                    tetromino[count].setX(newXValues[count]);
                    count++;
                        
                 }
             }
    
        }    

    }  
}

/*
 * takes in pointer to block array, changes coordinates to rotate
 */
void Game::rotateTetromino(){
    int tetrSize = 0, count = screenHeight, leftX, topY;
    Block** matrix;

    sortTetrominoX();       //sort blocks by ascending x coordinate
    leftX = tetromino[0].getBox()->x; //grab lowest x value
    tetrSize = (tetromino[3].getBox()->x - tetromino[0].getBox()->x)/size + 1; //grab domain of x and divide by piece size

    sortTetrominoY();      //sort blocks by ascending y coordinate
    topY = tetromino[0].getBox()->y;
    if((tetromino[3].getBox()->y - tetromino[0].getBox()->y)/size+1 > tetrSize){ //grab domain of y and divide by piece size
                                                                               //if that size of greater than previous, reset the size
        tetrSize = (tetromino[3].getBox()->y - tetromino[0].getBox()->y)/size + 1; 
    }
#ifdef DEBUG 
    cout << "SIZEOF MATRIX " << tetrSize << endl;
#endif 
                                     //xIndex holds index of leftmost block
                                     //yIndex holds lowest y value
    //generate a 2d matrix
    matrix = generateMatrix(leftX, topY, tetrSize);
    //rotate matrixx
    rotateMatrix(matrix, leftX, topY, tetrSize);
}

void Game::input(){
    bool willHit = false;
    bool alreadyMovedRight = false;
    bool alreadyMovedLeft = false;

    SDL_Event e;
    while(SDL_PollEvent(&e)){
        if(e.type == SDL_KEYDOWN){
    
            switch(e.key.keysym.sym){
                case SDLK_ESCAPE: 
                    *quit = true;
                    break;
                case SDLK_a:
                    willHit = false;
                    //detect if any part of tetris piece would go out of bounds if moved left
                    for(int i = 0; i < 4; i++){
                        if(sideCollision(tetromino[i].getBox()->x, tetromino[i].getBox()->y, -size)){
                            willHit = true;
                        }
                        
                    }
                    //if the piece wont collide, move left
                    if(!willHit && !alreadyMovedLeft){
                        alreadyMovedLeft = true;
                        shiftTetromino(-1);
                    }
                    break;
                case SDLK_d:
                    willHit = false;
                    //detect if any part of tetris piecce would hit wall if moved right
                    for(int i = 0; i < 4; i++){
                        if(sideCollision(tetromino[i].getBox()->x,tetromino[i].getBox()->y, size)){
                            willHit = true;
                        }
                        
                    } 
                    //if there would be no collision
                    if(!willHit && !alreadyMovedRight){
                        alreadyMovedRight = true;
                        shiftTetromino(1);
                    }
                    break;
                case SDLK_SPACE:
                    stopTetromino();
                    break;
                case SDLK_f:
                    speed = 400;
                    break;
                case SDLK_w:
                    rotateTetromino();
            }       
         }
        else if(e.type == SDL_KEYUP){
            switch(e.key.keysym.sym){
                case SDLK_f:
                    speed = 16;
                    break;
            }           
        }
    

    }

}

void Game::update(){
    bool willHit = false;
    //checks for collision with floor
    for(int i = 0; i < 4; i++){
        if(bottomCollision(tetromino[i].getBox()->x, tetromino[i].getBox()->y, size)){
            willHit = true;
            tetrominoMoving = false;
            integrateTetromino();
            break;
        }
    }
//if tetromino isnt null, is moving, and is ready to move(only moves once every NUMCYCLES call to update())
    if(tetromino && tetrominoMoving && moveCycle > NUMCYCLES){
        //move tetromino if it hasn't collided with a block or border
        moveTetromino();
        moveCycle = 0;
    }
    else if(!tetrominoMoving){
        //tetromino has stopped, create a new one and start moving it
        tetrObj = new Tetromino(renderer);
        tetromino = generateTetromino(tetrObj, renderer);
        tetrominoMoving = !tetrominoMoving;
    }
    //check the rows for fullness
    for(int i = 1; i < NUMROWS; i++){
        if( checkRow(i) ){
//            deleteRow(i);
            shiftRowsAbove(i);
        }
    }
    moveCycle++;
}

void Game::drawBlocks(){
    for(int i = 0; i < NUMROWS; i++){
        for(int j = 0; j < NUMCOLS; j++){ 
            if(blocks[i][j].exists()){
                SDL_RenderCopy(renderer, blocks[i][j].getTexture(), NULL, blocks[i][j].getBox() );

            }   
        }
    }
}

void Game::draw(){
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderClear(renderer);
   // printTilePositions(); 
    //draw tetromino
    for(int i = 0; i < 4; i++){
        //std::cout << "Tetromino at i: " << tetromino << std::endl;
        SDL_RenderCopy(renderer, tetromino[i].getTexture(), NULL, tetromino[i].getBox() );
    }
    // draw all blocks
    drawBlocks();
    
    
    //draw right part of screen i.e. border
    //std::cout << "value of boarder texture " << borderTex << std::endl;
    SDL_RenderCopy(renderer, borderTex, NULL, &border);

    SDL_RenderPresent(renderer);
    SDL_Delay(1000/speed);
}

Game::~Game(){

}
