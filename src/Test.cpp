#include "Display.h"
#include "Player.h"
//#include "Game.cpp"


/*
    MAIN FUNCTION
*********************/

int main(int argc, char *argv[]){
    Display display = Display("Puzzle Pic",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,400,400,2);
    //Game game = new Game();

    std::cerr << std::endl << std::endl;
    std::cerr << "ARROW KEYS TO MOVE. SPACE TO TOGGLE SWAPPING COLOR OF TILES" << std::endl;

    SDL_Rect r = {0,0,display.getBwidth(),display.getBheight()};
    Player player = Player(r);
    display.render(player.getBox());
    SDL_Event e;
    while(true){
        while(SDL_PollEvent(&e)!=0){
            switch( e.type ){
                case SDL_QUIT://Close Display
                    display.close();
                    return 0;
                break;
                case SDL_KEYDOWN:
                    switch( e.key.keysym.sym ){
                        case SDLK_ESCAPE://Close Display
                        case SDLK_DELETE:
                            display.close();
                            return 0;
                        break;
                        case SDLK_UP://Move Player Up
                            std::cerr << "KEY UP" << std::endl;
                            //display.deleteClickedTiles();
                            if(player.moveUP(0) && player.getSwap()){
                                display.swapColorsKeyboard(player.getPosx(),player.getPosy(),UP);
                                player.switchSwap();
                            }
                            display.render(player.getBox());
                        break;
                        case SDLK_DOWN: //Move Player Down
                            std::cerr << "KEY DOWN" << std::endl;
                            //display.deleteClickedTiles();
                            if(player.moveDOWN(display.getHeight()) && player.getSwap()){
                                display.swapColorsKeyboard(player.getPosx(),player.getPosy(),DOWN);
                                player.switchSwap();
                            }
                            display.render(player.getBox());
                        break;
                        case SDLK_LEFT://Move Player Left
                            std::cerr << "KEY LEFT" << std::endl;
                            //display.deleteClickedTiles();
                            if(player.moveLEFT(0) && player.getSwap()){
                                display.swapColorsKeyboard(player.getPosx(),player.getPosy(),LEFT);
                                player.switchSwap();
                            }
                            display.render(player.getBox());
                        break;
                        case SDLK_RIGHT: //Move Player Right
                            std::cerr << "KEY RIGHT" << std::endl;
                            if(player.moveRIGHT(display.getWidth()) && player.getSwap()){
                                display.swapColorsKeyboard(player.getPosx(),player.getPosy(),RIGHT);
                                player.switchSwap();
                            }
                            display.render(player.getBox());
                        break;
                        case SDLK_SPACE://Toggle Swap
                            //std::cerr << "SPACE PRESSED: " << "PLayer swap: " << player.getSwap() << std::endl;
                            std::cerr << "MOVE TO SWAP WITH THAT COLOR" << std::endl;
                            player.switchSwap();
                            //display.deleteClickedTiles();
                        break;
                        case SDLK_p:   //Print Board For Debugging Purposes
                            display.printBoard();
                        break;
                        default:
                            std::cerr << "NO VALID KEY PRESSES!" << std::endl;
                        break;
                    }
                break;
                case SDL_MOUSEMOTION:
                    
                break;
                case SDL_MOUSEBUTTONDOWN:
                    switch(e.button.button){
                        case SDL_BUTTON_LEFT:
                        case SDL_BUTTON_MIDDLE:
                        case SDL_BUTTON_RIGHT:
                            display.getClickedTile(e.button.x,e.button.y,player.getClicks());
                            player.click();
                            display.swapColorsMouse();
                        break;
                        default:
                            std::cerr << "NOT A VALID BUTTON!" << std::endl;
                        break;
                    }
                     display.render(player.getBox());
                break;
                case SDL_MOUSEBUTTONUP:
                    switch(e.button.button){
                        case SDL_BUTTON_LEFT:
                        case SDL_BUTTON_MIDDLE:
                        case SDL_BUTTON_RIGHT:
                            std::cerr << "Clicked: " << " x: " <<  e.button.x << " y: " << e.button.y << std::endl;
                        break;
                        default:
                            std::cerr << "NOT A VALID BUTTON!" << std::endl;
                        break;
                    }
                    display.render(player.getBox());
                break;
                default:
                //std::cerr << "NO VALID KEY PRESSES!" << std::endl;
                break;
            }
            //display.render(player.getBox());
        }
    }
    return 0;
}


