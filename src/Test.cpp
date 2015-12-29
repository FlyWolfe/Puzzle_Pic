#include "Display.h"
#include "Player.h"
//#include "Game.cpp"


/*
    MAIN FUNCTION
*********************/

int main(int argc, char *argv[]){
    Display display = Display("Puzzle Pic",0,0,400,400,2);
    //Game game = new Game();

    std::cerr << std::endl << std::endl;
    std::cerr << "ARROW KEYS TO MOVE. SPACE TO TOGGLE SWAPPING COLOR OF TILES" << std::endl;

    display.printBoard();
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
                            player.setPos(player.getPosx(),player.getPosy()-display.getBheight());
                            if(display.checkCollision(player.getPosx(),player.getPosy())){
                                player.setPos(player.getPosx(),player.getPosy()+display.getBheight());
                            }else if(player.getSwap()){
                                //std::cerr << "SWAP COLORS : " << " x1: " << player.getPosx()/display.getBwidth() << " y1: " << player.getPosy()/display.getBheight() << " x2: " << player.getPosx()/display.getBwidth() << " y2: " << (player.getPosy()+display.getBheight())/display.getBheight() << std::endl;
                                display.swapColors(player.getPosx()/display.getBwidth(),player.getPosy()/display.getBheight(),player.getPosx()/display.getBwidth(),(player.getPosy()+display.getBheight())/display.getBheight());
                                player.switchSwap();
                                std::cerr << "MOVE TO SWAP WITH THAT COLOR" << std::endl;
                                //display.printBoard();

                            }
                            //display.getTileFromTiles(0,0)->setColor(BLACK);
                            display.render(player.getBox());
                        break;
                        case SDLK_DOWN: //Move Player Down
                            std::cerr << "KEY DOWN" << std::endl;
                            player.setPos(player.getPosx(),player.getPosy()+display.getBheight());
                            if(display.checkCollision(player.getPosx(),player.getPosy())){
                                player.setPos(player.getPosx(),player.getPosy()-display.getBheight());
                            }else if(player.getSwap()){
                                //std::cerr << "SWAP COLORS : " << " x1: " << player.getPosx()/display.getBwidth() << " y1: " << player.getPosy()/display.getBheight() << " x2: " << player.getPosx()/display.getBwidth() << " y2: " << (player.getPosy()-display.getBheight())/display.getBheight() << std::endl;
                                display.swapColors(player.getPosx()/display.getBwidth(),player.getPosy()/display.getBheight(),player.getPosx()/display.getBwidth(),(player.getPosy()-display.getBheight())/display.getBheight());
                                player.switchSwap();
                                std::cerr << "MOVE TO SWAP WITH THAT COLOR" << std::endl;
                                //display.printBoard();
                            }
                            //display.getTileFromTiles(0,0)->setColor(BLACK);
                            display.render(player.getBox());
                        break;
                        case SDLK_LEFT://Move Player Left
                            std::cerr << "KEY LEFT" << std::endl;
                            player.setPos(player.getPosx()-display.getBwidth(),player.getPosy());
                            if(display.checkCollision(player.getPosx(),player.getPosy())){
                                player.setPos(player.getPosx()+display.getBwidth(),player.getPosy());
                            }else if(player.getSwap()){
                                //std::cerr << "SWAP COLORS : " << " x1: " << player.getPosx()/display.getBwidth() << " y1: " << player.getPosy()/display.getBheight() << " x2: " << (player.getPosx()+display.getBwidth())/display.getBwidth() << " y2: " << (player.getPosy())/display.getBheight() << std::endl;
                                display.swapColors(player.getPosx()/display.getBwidth(),player.getPosy()/display.getBheight(),(player.getPosx()+display.getBwidth())/display.getBwidth(),(player.getPosy())/display.getBheight());
                                player.switchSwap();
                                std::cerr << "MOVE TO SWAP WITH THAT COLOR" << std::endl;
                                //display.printBoard();
                            }
                            //display.getTileFromTiles(0,0)->setColor(BLACK);
                            display.render(player.getBox());
                        break;
                        case SDLK_RIGHT: //Move Player Right
                            std::cerr << "KEY RIGHT" << std::endl;
                            player.setPos(player.getPosx()+display.getBwidth(),player.getPosy());
                            if(display.checkCollision(player.getPosx(),player.getPosy())){
                                player.setPos(player.getPosx()-display.getBwidth(),player.getPosy());
                            }else if(player.getSwap()){
                                //std::cerr << "SWAP COLORS : " << " x1: " << player.getPosx()/display.getBwidth() << " y1: " << player.getPosy()/display.getBheight() << " x2: " << (player.getPosx()-display.getBwidth())/display.getBwidth() << " y2: " << (player.getPosy())/display.getBheight() << std::endl;
                                display.swapColors(player.getPosx()/display.getBwidth(),player.getPosy()/display.getBheight(),(player.getPosx()-display.getBwidth())/display.getBwidth(),(player.getPosy())/display.getBheight());
                                player.switchSwap();
                                std::cerr << "MOVE TO SWAP WITH THAT COLOR" << std::endl;
                                //display.printBoard();
                            }
                            //display.getTileFromTiles(0,0)->setColor(BLACK);
                            display.render(player.getBox());
                        break;
                        case SDLK_SPACE://Toggle Swap
                            //std::cerr << "SPACE PRESSED: " << "PLayer swap: " << player.getSwap() << std::endl;
                            player.switchSwap();
                            //std::cerr << "SPACE PRESSED: " << "PLayer swap: " << player.getSwap() << std::endl;
                        break;
                        case SDLK_p:   //Print Board For Debugging Purposes
                            display.printBoard();
                        break;
                        default:
                            std::cerr << "NO VALID KEY PRESSES!" << std::endl;
                        break;
                    }
                default:
                //std::cerr << "NO VALID KEY PRESSES!" << std::endl;
                break;
            }
            //display.render(player.getBox());
        }
    }
    return 0;
}


