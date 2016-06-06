
#include "Game.h"

Game::Game(){}

Game::Game(std::string name,int width,int height,int size){
	display = Display(name,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,width,height,size);
	SDL_Rect box = {0,0,display.board.bwidth,display.board.bheight};
	player = Player(box,size);
	this->playGame = true;
	this->numOfSwaps=0;
}

void Game::incrementNumSwaps(){
	this->numOfSwaps++;
}

int Game::getIncrementNumSwaps(){
	return this->numOfSwaps;
}

void Game::updateDisplay(){
	display.render(player.getBox());
}

void Game::controls(){
	SDL_Event e;
        while(SDL_PollEvent(&e)!=0){
            switch( e.type ){
                case SDL_QUIT://Close Display
                    display.close();
					playGame=false;
                break;
                case SDL_KEYDOWN:
                    switch( e.key.keysym.sym ){
                        case SDLK_ESCAPE://Close Display
                        case SDLK_DELETE:
                            display.close();
							playGame=false;
                        break;
                        case SDLK_UP://Move Player Up
                            std::cerr << "KEY UP" << std::endl;
                            //display.deleteClickedTiles();
                            if(player.moveUP() && player.getSwap()){
                                display.board.swapColorsKeyboard(player.getPosx(),player.getPosy(),UP);
                                player.switchSwap();
                            }
                        break;
                        case SDLK_DOWN: //Move Player Down
                            std::cerr << "KEY DOWN" << std::endl;
                            //display.deleteClickedTiles();
                            if(player.moveDOWN() && player.getSwap()){
                                display.board.swapColorsKeyboard(player.getPosx(),player.getPosy(),DOWN);
                                player.switchSwap();
                            }
                        break;
                        case SDLK_LEFT://Move Player Left
                            std::cerr << "KEY LEFT" << std::endl;
                            //display.deleteClickedTiles();
                            if(player.moveLEFT() && player.getSwap()){
                                display.board.swapColorsKeyboard(player.getPosx(),player.getPosy(),LEFT);
                                player.switchSwap();
                            }
                        break;
                        case SDLK_RIGHT: //Move Player Right
                            std::cerr << "KEY RIGHT" << std::endl;
                            if(player.moveRIGHT() && player.getSwap()){
                                display.board.swapColorsKeyboard(player.getPosx(),player.getPosy(),RIGHT);
                                player.switchSwap();
                            }
                        break;
                        case SDLK_SPACE://Toggle Swap
                            //std::cerr << "SPACE PRESSED: " << "PLayer swap: " << player.getSwap() << std::endl;
                            std::cerr << "MOVE TO SWAP WITH THAT COLOR" << std::endl;
                            player.switchSwap();
                            //display.board.deleteClickedTiles();
                        break;
                        case SDLK_p:   //Print Board For Debugging Purposes
                            display.board.printBoard();
                            std::cerr << std::endl;
                            player.printBox();
                        break;
                        default:
                            std::cerr << "NO VALID KEY PRESSES!" << std::endl;
                        break;
                    }
                break;
			/*case SDL_MOUSEMOTION:

                break;
                case SDL_MOUSEBUTTONDOWN:
                    switch(e.button.button){
                        case SDL_BUTTON_LEFT:
                        case SDL_BUTTON_MIDDLE:
                        case SDL_BUTTON_RIGHT:
                            display.board.getClickedTile(e.button.x,e.button.y,player.getClicks());
                            player.click();
                            display.board.swapColorsMouse();
                        break;
                        default:
                            std::cerr << "NOT A VALID BUTTON!" << std::endl;
                        break;
                    }
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
                break;*/
                default:
                //std::cerr << "NO VALID KEY PRESSES!" << std::endl;
                break;
            }
            //display.render(player.getBox());
        }
}


bool Game::getPlayGame(){
	return this->playGame;
}
