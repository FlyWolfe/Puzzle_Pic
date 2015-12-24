#include "Display.cpp"
//#include "Game.cpp"


int main(int argc, char const *argv[]){
	Display display = Display("Puzzle Pic",0,0,900,900,3);
    //Game game = new Game();

    SDL_Event e;
    while(true){
    while(SDL_PollEvent(&e)!=0){
                    switch( e.type ){
                        case SDL_QUIT:
                            //display.close();
                            break;
                        case SDL_KEYDOWN:
                            switch( e.key.keysym.sym ){
                                case SDLK_ESCAPE:
                                case SDLK_DELETE:
                                   // display.close();
                                break;
                                default:
                                    std::cerr << "NO VALID KEY PRESSES!" << std::endl;
                                break;
                        }
                        default:
                             std::cerr << "NO VALID KEY PRESSES!" << std::endl;
                        break;
                    }
                }
            }
            

	/*while(true){
	    while(SDL_PollEvent(&e)!=0){
                    switch( e.type == SDL_QUIT ){
                    	case SDL_QUIT:
                    		this.close();
                    	case SDL_KEYDOWN:
                    		switch( e.key.keysym.sym ){
                    			case SDLK_ESCAPE:
                    			case SDLK_DELETE:
                    				this.close();
                    			break;
                            	case SDLK_UP:
                            		if(!this.checkCollision(int posx,int posy)){
                            			posy+=this.bheight; 
                            			std::cerr << "SWAP COLORS : " << " x: " << posx/this.width << " y: " << posy/this.height << std::endl;
                            			this.swapColors(this.tiles[posx/this.width][posy/this.height]);
                            			this.player.switchSwap();
                            		}
	                            break;

                            	case SDLK_DOWN:
                            		if(!this.checkCollision(int posx,int posy)){
                            			posy-=this.bheight;
                            			std::cerr << "SWAP COLORS : " << " x: " << posx/this.width << " y: " << posy/this.height << std::endl;
                            			this.swapColors(this.tiles[posx/this.width][posy/this.height]);
                            			this.player.switchSwap();
                            		}
                            	break;

                            	case SDLK_LEFT:
                            		if(!this.checkCollision(int posx,int posy)){
                            			posx-=this.bwidth;
                            			std::cerr << "SWAP COLORS : " << " x: " << posx/this.width << " y: " << posy/this.height << std::endl;
                            			this.swapColors(this.tiles[posx/this.width][posy/this.height]);
                            			this.player.switchSwap();
                            		}
                            	break;

                            	case SDLK_RIGHT:
                            		if(!this.checkCollision(int posx,int posy)){
                            			posx+=this.bwidth;
                            			std::cerr << "SWAP COLORS : " << " x: " << posx/this.width << " y: " << posy/this.height << std::endl;
                            			this.swapColors(this.tiles[posx/this.width][posy/this.height]);
                            			this.player.switchSwap();
                            		}
                            	break;

                            	case SDLK_SPACE:
                            		this.player.switchSwap();
                            	break;
                            	default:
                            		std::cerr << "NO VALID KEY PRESSES!" << std::endl;
                            	break;
                        }
                    }
                }*/

	return 0;
}