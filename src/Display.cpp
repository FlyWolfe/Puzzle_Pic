#include "Display.h"
#include <chrono>
#include <cmath>
#include <random>

/*
	DISPLAY CLASS FUNCTION DEFINITIONS
*********************/

//Used to generate Random Number
#ifdef _WIN32
std::mt19937 engine(std::chrono::system_clock::now().time_since_epoch().count());
#elif defined __unix__ || defined __APPLE__
std::random_device seeder;
std::mt19937 engine(seeder());
#endif

//Constructor of Display Class
Display::Display(std::string name,int initialPosX,int initialPosY,int newWidth,int newHeight,int size):
	width(newWidth), height(newHeight), bwidth(width/size), bheight(height/size), boardSize(size){ //Integer Constructors
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
	for(int i=0;(unsigned)i<palette.size();i++){
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

void Display::getClickedTile(int posx,int posy,int num){
	int x, y;

	x=(posx/bwidth)%boardSize;
	y=(posy/bheight)%boardSize;

	std::cerr << "CLICKED TILE: " << " x: " << x << " y: " << y <<  " posx: " <<  posx   << " posy: " << posy << std::endl; 
	
	(num%2==0)?clickedTiles[0]=&tiles[x][y]:clickedTiles[1]=&tiles[x][y];
}

void Display::deleteClickedTiles(){
	clickedTiles[0]=NULL;
	clickedTiles[1]=NULL;
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
			std::cerr << "Tile Position :" << "x: " << tiles[i][j].getBox().x << " y: " << tiles[i][j].getBox().y << " w: " << tiles[i][j].getBox().w << " h: " << tiles[i][j].getBox().h << std::endl;
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
			SDL_Rect r = tiles[i][j].getBox();
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
	SDL_Rect r = tiles[x][y].getBox();
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

	renderPlayerScale(&box);

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

	free(clickedTiles[0]);
	free(clickedTiles[1]);

	deleteClickedTiles();

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
void Display::swapColorsKeyboard(int x,int y,int num){

	int x1=x/bwidth,y1=y/bheight,x2=0,y2=0;

	switch(num){
		case UP://UP
			x2=x/bwidth;
			y2=(y+bheight)/bheight;
		break;
		case DOWN://DOWN
			x2=x/bwidth;
			y2=(y-bheight)/bheight;
		break;
		case LEFT://LEFT
			x2=(x+bwidth)/bwidth;
			y2=y/bheight;
		break;
		case RIGHT://RIGHT
			x2=(x-bwidth)/bwidth;
			y2=y/bheight;
		break;
		default:
			std::cerr << "INVALID DIRECTION FOR COLOR SWAP!" << std::endl;
		break;
	}

	/*std::cerr << "TILES: " << std::endl;
	tiles[x1][y1].printTile();
	tiles[x2][y2].printTile();*/
	
	Tiles temp = Tiles(tiles[x1][y1].getColor(),tiles[x1][y1].getBox());
	tiles[x1][y1].setColor(tiles[x2][y2].getColor());
	tiles[x2][y2].setColor(temp.getColor());
}

void Display::swapColorsMouse(){
	if(clickedTiles[0]!=NULL && clickedTiles[1]!=NULL){
		Tiles temp = Tiles(clickedTiles[0]->getColor(),clickedTiles[0]->getBox());
		clickedTiles[0]->setColor(clickedTiles[1]->getColor());
		clickedTiles[1]->setColor(temp.getColor());
		clickedTiles[0]=NULL;
		clickedTiles[1]=NULL;
	}
}

//Get Pointer to a tile on a board
Tiles* Display::getTileFromTiles(int i,int j){
	return &this->tiles[i][j];
}
