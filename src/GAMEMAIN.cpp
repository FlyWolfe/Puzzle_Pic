#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
#elif defined __unix__ || defined __APPLE__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>
#endif

#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <vector>
#include <algorithm>
#include <iterator>

//Classes Used
class Tiles;

SDL_Color BLACK = {0,0,0,255};        //Color BLACK
SDL_Color WHITE = {255,255,255,255};  //Color WHITE

/*
	DISPLAY CLASS
*********************/ 
class Display{

	private:
		SDL_Texture* texture;			
		SDL_Renderer* renderer;
		SDL_Surface* surface;
		SDL_Window* windows;

		std::vector<SDL_Color> palette; //Colors in the Game

		int width;						//Width of Display Window
		int height;						//Height of Display Window

		int bwidth;						//Width of Tiles
		int bheight;					//Height of Tiles

		int boardSize;					//Number of a Row if 3X3 the boardsize is 3

		std::vector<std::vector<Tiles> > tiles; //Vector of vectors of Tiles

	public:
		//Contructor
		Display(std::string name, 				//Name of Window
				int initialPosX,				//intial X position of teh window
				int initialPosY,				//intial Y position of teh window
				int newWidth,					//Width of Window;
				int newHeight,					//Height of Window;
				int size						//Size of the Board;
				); 

		void initSDL();							//Initialize SDL  
		//void initTTF();							//Initialize TTF

		void setPalette();						//Create the Colors of the Display
		std::vector<SDL_Color> getPalette();	//Get the Colors of the Display
		void printPalette();					//Print the Colors for debbuging purposes

		void loadTexture();						//Load Textrues From file

		void createTexttexture();				//Create Textures from Text using TTF

		void createWindow(	std::string name,	//Name of Window
							int initialPosX,	//Initial X Position of Window
							int initialPosY,	//Initial Y Position of Window
							int width,			//Width of Window
							int height 			//Height of Window
							);
		void createRenderer();					//Creates the SDL Renderer 

		void textureFromSurface();				//Creates A Texture From A Surface
		void createRGBSurface();				//Creates a Surface from RGB Masks
		void surfaceFromImage(					//Creates Surface from Imaeg using SDL_Image
					std::string filename		//Filename of Image
					);

		void setupRenderer();					//Setup the renderer target and scale of Renderer

		void makeBoard();						//Make the game board

		void printBoard();						//Print Game Board in the terminal

		bool checkCollision(int posx,int posy);	//Check the Collision of the Player with the window boundaries

		void render(SDL_Rect box);				//Render Player and Board
		void renderPlayer(SDL_Rect box);		//Render The Player
		void renderTile(int x,int y);			//Render a Tile

		void renderBoard();						//Render the Board

		void renderPlayerScale(					//Change the Thickness of the Line for the Player
					SDL_Rect* newBox			//Players Box 
					);

		void close();							//Close the Display and SDL


		int getWidth();							//Get width of Display
		int getHeight();						//Get height of Display

		int getBwidth();						//Get tile width  
		int getBheight();						//Get tile height

		int getBoardSize();						//Get board size

		void swapColors(						//Swap Tile Colors
					int x1,int y1,				//The x and y position of tile one
					int x2,int y2				//The x and y position of tile two
					);

		Tiles* getTileFromTiles(int i,int j);	//Get the pointer a tile in the Board

};

/*
	TILES CLASS
*********************/ 

class Tiles{

	private:
		SDL_Color color;					//Color of a Tile
		SDL_Rect tile; 						//Rectange Box of a Tile

	public:
		Tiles();							//Empty Constructor of a Tile
		Tiles(								//Constructor of a Tile from a Color and Rectangle
				SDL_Color newColor, 		//Color using SDL_Color
				SDL_Rect newTile			//Rectangle Box using SDL_Rect
				);
		//~Tiles();

		void setColor(SDL_Color newColor);	//Set the Color of a Tile
		SDL_Color getColor();				//Get the Color of a Tile

		void setTile(SDL_Rect newTile);		//Set the Rectangle Box of a Tile 
		SDL_Rect getTile();					//Get the Rectangle Box of a Tile

		//void renderTile(SDL_Renderer renderer);

};

/*
	TILES CLASS FUNCTION DEFINITIONS
*********************/ 


//Empty Constructor 
Tiles::Tiles(){
	this->color = WHITE;
}


//Constructor for setting a Tile with a Color and Rectangle
Tiles::Tiles(SDL_Color newColor,SDL_Rect newTile){
	this->color = newColor;
	this->tile = newTile;
}

/*
Tiles::~Tiles(){
	std::cerr << "END OF TILE" << std::endl;
}
*/

//Set Color 
void Tiles::setColor(SDL_Color newColor){
	//std::cerr << "SET COLOR" << std::endl;
	this->color = newColor;
}

//Get Color
SDL_Color Tiles::getColor(){
	return this->color;
}

//Set Tile Box
void Tiles::setTile(SDL_Rect newTile){
	this->tile = newTile;
}

//Get Tile Box
SDL_Rect Tiles::getTile(){
	return this->tile;
}

/*
	DISPLAY CLASS FUNCTION DEFINITIONS
*********************/ 

//Used to generate Random Number
std::random_device seeder;
std::mt19937 engine(seeder());

//Constructor of Display Class 
Display::Display(std::string name,int initialPosX,int initialPosY,int newWidth,int newHeight,int size):
	width(newWidth), height(newHeight),boardSize(size), bwidth(width/size), bheight(height/size){ //Integer Constructors
	initSDL();													//Initialize SDL for Display
	//initTTF();													//Initialize TTF for Fonts and Displaying Words

	createWindow(name,initialPosX,initialPosY,width,height);	//Create Windows
	createRenderer();											//Create Renderer
	setupRenderer();											//Setup Renderer

	createRGBSurface();											//Create Surface from RGB pixel Encoding
	textureFromSurface();										//Create Texture from Surface
	

	setPalette();												//Set the Palette of the Game Board

	makeBoard();												//Make Game Board

	printBoard();												//Print Board for Debugging Purposes
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

//Initialize TTF for Fonts and Displaying Words
/*void Display::initTTF(){
	if(TTF_Init() !=0){
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        exit(1);
        //return false;
    }
    //return true;
}*/

//Set the Palette of the Game Board
void Display::setPalette(){

	SDL_Color colors[] = {
		{0,128,0,255}, //green
		{255,165,0,255}, //orange
		{0,0,255,255}, //blue
		{255,0,0,255}, //red
		{255,255,0,255}, //yellow
		{238,130,238,255}, //violet
		{255,255,255,255}, //white
		{128,0,128,255}, //purple
		{255,192,203,255} //pink
	};

	std::vector<SDL_Color> temp(colors, colors + sizeof(colors) / sizeof(SDL_Color) );

	this->palette = temp;

}

//Print the Colors for debbuging purposes
void Display::printPalette(){
	std::cerr << "PRINT PALETTE" << std::endl;
	for(int i=0;i<palette.size();i++){
		std::cerr << "Palette: " << " num: " << i << " r: " << (int)palette[i].r << " g: " << (int)palette[i].g << " b: " << (int)palette[i].b << " a: " << (int)palette[i].a << std::endl;
	}
}

//Get Palette of a Display
std::vector<SDL_Color> Display::getPalette(){
	return this->palette;
}

//Load Texture From Image
void Display::loadTexture(){
	std::cerr << "NOT IMPLEMENTED" << std::endl;
}

//Create a Texture from a Surface
void Display::textureFromSurface(){
	texture=SDL_CreateTextureFromSurface(renderer,surface);
	if(!texture){
    	std::cerr << "Texture from Surface Error: " << SDL_GetError() << std::endl;
    	exit(1);
    	//return false;
	}
	SDL_FreeSurface(surface);
	//return true;

}


//Create a Texture of Text
void Display::createTexttexture(){

}

//Create a Surface using RGB pixel Encoding
void Display::createRGBSurface(){
	Uint32 rmask, gmask, bmask, amask;
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
	#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
	#endif
	surface=SDL_CreateRGBSurface(0,width,height,32,rmask, gmask, bmask, amask);
	if(!surface){
        std::cerr << "Create RGB Surface Error: " << SDL_GetError() << std::endl;
        exit(1);
        //return false;
    }
}

//Create a Surface from a Image
void Display::surfaceFromImage(std::string filename){
	surface=IMG_Load(filename.c_str());
	if(!surface){
        std::cerr << "Create Surface from Image Error: " << SDL_GetError() << std::endl;
        exit(1);
        //return false;
    }
    //return true;
}


//Create a Window
void Display::createWindow(std::string name,int initialPosX,int initialPosY,int width,int height){

	// Create an application windows with the following settings:
    windows = SDL_CreateWindow(
        name.c_str(),                  							// windows title
        initialPosX,           							// initial x position
        initialPosY,           							// initial y position
        width,                              			// width, in pixels
        height,                             			// height, in pixels
        SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI	 	// flags 
    );
    if(!windows){
    	std::cerr << "Create windows Error: " << name << " " << SDL_GetError() << std::endl;
    	exit(1);
    	//return false;
    }
    //return true;

}

//Create a Renderer
void Display::createRenderer(){

	renderer = SDL_CreateRenderer(
		windows, 						//the windows where rendering is displayed
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
void Display::setupRenderer(){

	// Set size of renderer to the same as windows
	SDL_RenderSetLogicalSize(this->renderer, width, height);

	// Set color of renderer clear to black
	SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255 );
}


//Check Collision of the Player and Window 
bool Display::checkCollision(int posx,int posy){

	if( (posx < 0) || (posx+bwidth > width) ){

		return true;
	}

	if( (posy < 0) || (posy+bheight > height) ){

		return true;
	}

	return false;
}

//Make Board
void Display::makeBoard(){
	std::uniform_int_distribution<int> dist(0,palette.size()-1);
	int num;
	//tiles.resize(boardSize,std::vector<Tiles>(boardSize));

	//std::cerr << "TILES: " << "size: " << tiles.size() << std::endl;
 	SDL_Rect temp;
	temp.w=bwidth;
	temp.h=bheight;
	for(int i=0, w=0;i<boardSize;i++,w+=bwidth){
		tiles.push_back(std::vector<Tiles>());
		temp.x=w;
		//std::cerr << "Tiles: " << "size: " << tiles[i].size() << std::endl;
		for(int j=0,h=0;j<boardSize;j++,h+=bheight){
			//std::cerr << "Tile Created :" << "i: " << i << " j: " << j << std::endl; 
			temp.y=h;
			num=dist(engine);
			//std::cerr << "Tile Color :" << "num: " << num << " r: " << (int)this->palette[num].r << " g: " << (int)palette[num].g << " b: " << (int)palette[num].b << " a: " << (int)palette[num].a << std::endl;
			tiles[i].push_back(Tiles(this->palette[num],temp));
		}
	}
}

//Print a Board
void Display::printBoard(){
	std::cerr << "PRINT BOARD" << std::endl;
	for(int i=0;i<boardSize;i++){
		std::cerr << "Tiles: " << "size: " << tiles[i].size() << std::endl;
		for(int j=0;j<boardSize;j++){
			std::cerr << "Tile Created :" << "i: " << i << " j: " << j << std::endl; 
			std::cerr << "Tile Position :" << "x: " << tiles[i][j].getTile().x << " y: " << tiles[i][j].getTile().y << " w: " << tiles[i][j].getTile().w << " h: " << tiles[i][j].getTile().h << std::endl; 
			std::cerr << "Tile Color :" << " r: " << (int)tiles[i][j].getColor().r << " g: " << (int)tiles[i][j].getColor().g << " b: " << (int)tiles[i][j].getColor().b << " a: " << (int)tiles[i][j].getColor().a << std::endl;
		}
	}
	//printPalette();
}

//Render Board
void Display::renderBoard(){
	for(int i=0;i<boardSize;i++){
		for(int j=0;j<boardSize;j++){
			if(SDL_SetRenderDrawColor(this->renderer,tiles[i][j].getColor().r,tiles[i][j].getColor().g,tiles[i][j].getColor().b,tiles[i][j].getColor().a) != 0){
				std::cerr << "Drawing Board Color Tile Error: " <<  SDL_GetError() << std::endl;
			}
			SDL_Rect r = tiles[i][j].getTile();
			if(SDL_RenderFillRect(this->renderer,&r) != 0 ){
				std::cerr << "Drawing Board Fill Tile Error: " <<  SDL_GetError() << std::endl;
			}
		}
	}
} 

//Render a Tile
void Display::renderTile(int x,int y){

	if(SDL_SetRenderDrawColor(this->renderer,tiles[x][y].getColor().r,tiles[x][y].getColor().g,tiles[x][y].getColor().b,tiles[x][y].getColor().a) != 0){
		std::cerr << "Drawing Color Tile Error: " <<  SDL_GetError() << std::endl;
	}
	SDL_Rect r = tiles[x][y].getTile();
	if(SDL_RenderFillRect(this->renderer,&r) != 0 ){
		std::cerr << "Drawing Fill Tile Error: " <<  SDL_GetError() << std::endl;
	}
}

//Change Line thickness of Player
void Display::renderPlayerScale(SDL_Rect* newBox){
	newBox->x/=boardSize;
	newBox->y/=boardSize;
	newBox->w/=boardSize;
	newBox->h/=boardSize;
}

//Render Player
void Display::renderPlayer(SDL_Rect box){

	//std::cerr << "Player: " << " x: " << box.x << " y: " << box.y << " w: " << box.w << " h: " << box.h << std::endl;


	if(SDL_RenderSetScale(renderer,boardSize,boardSize) != 0){
		std::cerr << "Drawing Player Error: " <<  SDL_GetError() << std::endl;
	}

	if(SDL_SetRenderDrawColor(renderer,0,0,0,255) != 0){
		std::cerr << "Drawing Player Error: " <<  SDL_GetError() << std::endl;
	}

	//renderPlayerScale(&box);

	//std::cerr << "Player scaled: " << " x: " << box.x << " y: " << box.y << " w: " << box.w << " h: " << box.h << std::endl;
	if(SDL_RenderDrawRect(renderer,&box) != 0 ){
		std::cerr << "Drawing Player Error: " <<  SDL_GetError() << std::endl;
	}

	if(SDL_RenderSetScale(renderer,1,1) != 0){
		std::cerr << "Drawing Player Error: " <<  SDL_GetError() << std::endl;
	}
}

//Render all Objects
void Display::render(SDL_Rect box){
	std::cerr << "RENDER" << std::endl;
	// Change color to black
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	//clear screen
	SDL_RenderClear(renderer);

	// Render the tiles
	renderBoard();

	// Render the Player
	renderPlayer(box);
	
	// Render the changes above
	SDL_RenderPresent(renderer);
}

//Close Display
void Display::close(){

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(windows);
	SDL_Quit();

}

//Get Width of Display
int Display::getWidth(){
	return this->width;
}

//Get Heigth of Display
int Display::getHeight(){
	return this->height;
}

//Get Width of Tiles
int Display::getBwidth(){
	return this->bwidth;
}

//Get Height of Tiles
int Display::getBheight(){
	return this->bheight;
}

//Get board Size if 3X3 board size is 3
int Display::getBoardSize(){
	return this->boardSize;
}

//Swap Colors of Two Tiles
void Display::swapColors(int x1,int y1,int x2,int y2){
	//std::cerr << "SWAP COLORS : " << " x1: " << x1 << " y1: " << y1 << " x2: " << x2 << " y2: " << y2 << std::endl;
	//std::cerr <<"BEFORE: " << std::endl;
	//printBoard();
	Tiles temp = Tiles(tiles[x1][y1].getColor(),tiles[x1][y1].getTile());
	tiles[x1][y1].setColor(tiles[x2][y2].getColor());
	tiles[x2][y2].setColor(temp.getColor());
	//std::cerr <<"AFTER: " << std::endl;
	//printBoard();
	//std::cerr <<"DONE SWAP COLORS: " << std::endl;
}

//Get Pointer to a tile on a board
Tiles* Display::getTileFromTiles(int i,int j){
	return &this->tiles[i][j];
}

/*
	PLAYER CLASS
*********************/ 

class Player{
	private:
		std::string name;			//Name Of Player
		SDL_Rect box;				//Box of Player
		bool swap;					//Bool fo knowing When to Swap tiles

	public:
		Player();					//Empty Constructor
		Player(SDL_Rect newBox);	//Constructor Player from SDL_Rect box

		void setName(				//Set Name of Player
				std::string newName	//Name of Player
				);
		std::string getName();		//Get Name of Player

		void setBox(				//Set Box of the Player
				SDL_Rect newBox		//Box of the Player
				);
		SDL_Rect getBox();			//Get Box of the Player

		void setPos(int x,int y);	//Set Position of the Player

		int getPosx();				//Get X Position of the Player
		int getPosy();				//Get Y Position of the Player

		void switchSwap();			//Toggle the Boolean for swapping Tiles
		bool getSwap();				//Get Swap Boolean

		//void renderPlayer(SDL_Renderer renderer);
};

/*
	PLAYER CLASS FUNCTION DEFINITIONS
*********************/ 

//Constructor of Player CLass
Player::Player(SDL_Rect newBox){
	name="DEATH";
	box = newBox;
	swap=false;
}

//Set Player Name
void Player::setName(std::string newName){
	name=newName;
}

//Get Player Name
std::string Player::getName(){
	return this->name;
}

//Set Player Box
void Player::setBox(SDL_Rect newBox){
	box=newBox;
}

//Get Player Box
SDL_Rect Player::getBox(){
	return this->box;
}

//Set Player Position
void Player::setPos(int x,int y){
	this->box.x=x;
	this->box.y=y;
}

//Get the X Position
int Player::getPosx(){
	return this->box.x;
}

//Get the Y Position
int Player::getPosy(){
	return this->box.y;
}

//Toggle the swap Boolean
void Player::switchSwap(){
	this->swap=!this->swap;
}

//Get Swap Boolean
bool Player::getSwap(){
	return this->swap;
}

/*
	MAIN FUNCTION
*********************/ 

int main(int argc, char const *argv[]){
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


