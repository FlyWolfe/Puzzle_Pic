#include "Display.h"


/*
	DISPLAY CLASS FUNCTION DEFINITIONS
*********************/
/*
//Used to generate Random Number
#ifdef _WIN32
std::mt19937 engine(std::chrono::system_clock::now().time_since_epoch().count());
#elif defined __unix__ || defined __APPLE__
std::random_device seeder;
std::mt19937 engine(seeder());
#endif
*/
//Constructor of Display Class
Display::Display(){}

Display::Display(std::string name,int initialPosX,int initialPosY,int width,int height,int size){
	initSDL();													//Initialize SDL for Display
	//initTTF();													//Initialize TTF for Fonts and Displaying Words

	createWindow(name,initialPosX,initialPosY,width,height);	//Create window
	createRenderer();											//Create Renderer
	setupRenderer(width,height);											//Setup Renderer

	this->board = Board(width,height,size);

}


//Initialize SDL for Display
void Display::initSDL(){
	if(SDL_Init(SDL_INIT_EVERYTHING) !=0 ) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        exit(1);
        //return false;
    }
    //return true;
}


//Create a Window
void Display::createWindow(std::string name,int initialPosX,int initialPosY,int width,int height){

	// Create an application window with the following settings:
    window = SDL_CreateWindow(
        name.c_str(),                  							// window title
        initialPosX,           							// initial x position
        initialPosY,           							// initial y position
        width,                              			// width, in pixels
        height,                             			// height, in pixels
        SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI	 	// flags
    );
    if(!window){
    	std::cerr << "Create Window Error: " << name << " " << SDL_GetError() << std::endl;
    	exit(1);
    	//return false;
    }
    //return true;

}

//Create a Renderer
void Display::createRenderer(){

	renderer = SDL_CreateRenderer(
		window, 						//the window where rendering is displayed
		-1, 							//the index of the rendering driver to initialize, or -1 to initialize the first one supporting the requested flags
		SDL_RENDERER_ACCELERATED		//flags
		);

	if(!renderer){
    	std::cerr << "Create Renderer Error: " << SDL_GetError() << std::endl;
    	exit(1);
    	//return false;
    }
    //return true;
}

//Setup a Renderer
void Display::setupRenderer(int width,int height){

	// Set size of renderer to the same as window
	SDL_RenderSetLogicalSize(this->renderer,width, height);

	// Set color of renderer clear to black
	SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255 );
}


//Render Board
void Display::renderBoard(int boardSize){
	for(int i=0;i<boardSize;i++){
		for(int j=0;j<boardSize;j++){
			if(SDL_SetRenderDrawColor(this->renderer,board.tiles[i][j].color.r,board.tiles[i][j].color.g,board.tiles[i][j].color.b,board.tiles[i][j].color.a) != 0){
				std::cerr << "Drawing Board Color Tile Error: " <<  SDL_GetError() << std::endl;
			}
			SDL_Rect r = board.getTileBox(i,j);
			if(SDL_RenderFillRect(this->renderer,&r) != 0 ){
				std::cerr << "Drawing Board Fill Tile Error: " <<  SDL_GetError() << std::endl;
			}
		}
	}
}

//Render a Tile
void Display::renderTile(int x,int y){

	if(SDL_SetRenderDrawColor(this->renderer,board.tiles[x][y].color.r,board.tiles[x][y].color.g,board.tiles[x][y].color.b,board.tiles[x][y].color.a) != 0){
		std::cerr << "Drawing Color Tile Error: " <<  SDL_GetError() << std::endl;
	}
	SDL_Rect r = board.tiles[x][y].box;
	if(SDL_RenderFillRect(this->renderer,&r) != 0 ){
		std::cerr << "Drawing Fill Tile Error: " <<  SDL_GetError() << std::endl;
	}
}

//Change Line thickness of Player
void Display::renderPlayerScale(SDL_Rect* newBox,int boardSize){
	newBox->x/=boardSize;
	newBox->y/=boardSize;
	newBox->w/=boardSize;
	newBox->h/=boardSize;
}

//Render Player
void Display::renderPlayer(SDL_Rect box, int boardSize){

	//std::cerr << "Player: " << " x: " << box.x << " y: " << box.y << " w: " << box.w << " h: " << box.h << std::endl;

	/*if(SDL_RenderSetScale(renderer,boardSize,boardSize) != 0){
		std::cerr << "Drawing Player Error: " <<  SDL_GetError() << std::endl;
	}*/

	if(SDL_SetRenderDrawColor(renderer,0,0,0,255) != 0){
		std::cerr << "Drawing Player Error: " <<  SDL_GetError() << std::endl;
	}

	//renderPlayerScale(&box,boardSize);

	//std::cerr << "Player scaled: " << " x: " << box.x << " y: " << box.y << " w: " << box.w << " h: " << box.h << std::endl;
	if(SDL_RenderDrawRect(renderer,&box) != 0 ){
		std::cerr << "Drawing Player Error: " <<  SDL_GetError() << std::endl;
	}

	/*if(SDL_RenderSetScale(renderer,1,1) != 0){
		std::cerr << "Drawing Player Error: " <<  SDL_GetError() << std::endl;
	}*/
}

//Render all Objects
void Display::render(SDL_Rect box){
	//std::cerr << "RENDER"  << "\n";
	// Change color to black
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	//clear screen
	SDL_RenderClear(renderer);

	// Render the tiles
	renderBoard(this->board.boardSize);

	// Render the Player
	renderPlayer(box,this->board.boardSize);

	// Render the changes above
	SDL_RenderPresent(renderer);
}

//Close Display
void Display::close(){

	//SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
	SDL_Quit();
}

//Get Width of Display
int Display::getWidth(){
	int w,h;
	SDL_GetRendererOutputSize(this->renderer,&w,&h);
	return w;
}

//Get Heigth of Display
int Display::getHeight(){
	int w,h;
	SDL_GetRendererOutputSize(this->renderer,&w,&h);
	return h;
}
