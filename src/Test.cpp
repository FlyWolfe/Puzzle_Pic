#include "Game.h"
//#include "Game.cpp"


/*
    MAIN FUNCTION
*********************/

int main(int argc, char *argv[]){
    //Display display = Display("Puzzle Pic",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,400,400,2);
    //Game game = new Game();
    Game game = Game("Puzzle Pic",400,400,2);

    std::cerr << std::endl << std::endl;
    std::cerr << "ARROW KEYS TO MOVE. SPACE TO TOGGLE SWAPPING COLOR OF TILES" << std::endl;

    while(game.getPlayGame()){
        game.updateDisplay();
        game.controls();
    }

    return 0;
}
