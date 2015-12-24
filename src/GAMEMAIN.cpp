#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <vector>
#include <algorithm>
#include <iterator>

class Tiles;
class Display;
class Game;
class Player;

SDL_Color BLACK = {0,0,0,255};
SDL_Color WHITE = {255,255,255,255};

SDL_Rect square = {0,0,10,10};

class Display{

	private:
		SDL_Texture* texture;
		SDL_Renderer* renderer;
		SDL_Surface* surface;
		SDL_Window* windows;

		std::vector<SDL_Color> palette;

		int width;
		int height;

		int bwidth;
		int bheight;

		int boardSize;

		std::vector<std::vector<Tiles> > tiles;

	public:

		Display(std::string name,int initialPosX,int initialPosY,int newWidth,int newHeight,int size);

		void initSDL();
		void initTTF();

		void setPalette();
		std::vector<SDL_Color> getPalette();
		void printPalette();

		void loadTexture();

		void createTexttexture();

		void createTexture();
		void createSurface(std::string filename);
		void createWindow(std::string name,int initialPosX,int initialPosY,int width,int height);
		void createRenderer();

		void textureFromSurface();
		void createRGBSurface();
		void surfaceFromImage(std::string filename);

		void setupRenderer();

		void makeBoard();

		void printBoard();

		bool checkCollision(int posx,int posy);

		void render(SDL_Rect box);
		void renderPlayer(SDL_Rect box);
		void renderTile();

		void renderBoard();

		void renderPlayerScale(SDL_Rect* newBox);

		void close();


		int getWidth();
		int getHeight();

		int getBwidth();
		int getBheight();

		int getBoardSize();

		void swapColors(int x1,int y1,int x2,int y2);

		Tiles* getTileFromTiles(int i,int j);

};

class Tiles{

	private:
		SDL_Color color;
		SDL_Rect tile; 

	public:
		Tiles();
		Tiles(SDL_Color newColor, SDL_Rect newTile);
		//~Tiles();

		void setColor(SDL_Color newColor);
		SDL_Color getColor();

		void setTile(SDL_Rect newTile);
		SDL_Rect getTile();

		//void renderTile(SDL_Renderer renderer);

};

Tiles::Tiles(){
	this->color = WHITE;
}

Tiles::Tiles(SDL_Color newColor,SDL_Rect newTile){
	this->color = newColor;
	this->tile = newTile;
}

/*
Tiles::~Tiles(){
	std::cerr << "END OF TILE" << std::endl;
}
*/
void Tiles::setColor(SDL_Color newColor){
	std::cerr << "SET COLOR" << std::endl;
	this->color = newColor;
}

SDL_Color Tiles::getColor(){
	return this->color;
}

void Tiles::setTile(SDL_Rect newTile){
	this->tile = newTile;
}

SDL_Rect Tiles::getTile(){
	return this->tile;
}

std::random_device seeder;
std::mt19937 engine(seeder());


Display::Display(std::string name,int initialPosX,int initialPosY,int newWidth,int newHeight,int size):
	width(newWidth), height(newHeight),boardSize(size), bwidth(width/size), bheight(height/size){
	initSDL();
	initTTF();

	createWindow(name,initialPosX,initialPosY,width,height);
	createRenderer();
	setupRenderer();

	createRGBSurface();
	textureFromSurface();
	

	setPalette();

	makeBoard();

	printBoard();
}


void Display::initSDL(){
	if(SDL_Init(SDL_INIT_EVERYTHING) !=0 ) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        exit(1);
        //return false;
    }
    //return true;
}

void Display::initTTF(){
	if(TTF_Init() !=0){
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        exit(1);
        //return false;
    }
    //return true;
}

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

void Display::printPalette(){
	std::cerr << "PRINT PALETTE" << std::endl;
	for(int i=0;i<palette.size();i++){
		std::cerr << "Palette: " << " num: " << i << " r: " << (int)palette[i].r << " g: " << (int)palette[i].g << " b: " << (int)palette[i].b << " a: " << (int)palette[i].a << std::endl;
	}
}

std::vector<SDL_Color> Display::getPalette(){
	return this->palette;
}


void Display::createTexture(){
	
}

void Display::loadTexture(){

}

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

void Display::createTexttexture(){

}

void Display::createSurface(std::string filename){
	if(filename.empty()){
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
	}else{
		surface=IMG_Load(filename.c_str());
	}
	if(!surface){
        std::cerr << "Create Surface Error: " << SDL_GetError() << std::endl;
        exit(1);
        //return false;
    }
    //return true;
}

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

void Display::surfaceFromImage(std::string filename){
	surface=IMG_Load(filename.c_str());
	if(!surface){
        std::cerr << "Create Surface from Image Error: " << SDL_GetError() << std::endl;
        exit(1);
        //return false;
    }
    //return true;
}



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

void Display::setupRenderer(){

	// Set size of renderer to the same as windows
	SDL_RenderSetLogicalSize(this->renderer, width, height);

	// Set color of renderer clear to black
	SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255 );
}

bool Display::checkCollision(int posx,int posy){

	if( (posx < 0) || (posx+bwidth > width) ){

		return true;
	}

	if( (posy < 0) || (posy+bheight > height) ){

		return true;
	}

	return false;
}

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

void Display::printBoard(){
	std::cerr << "PRINT BOARD" << std::endl;
	for(int i=0;i<boardSize;i++){
		std::cerr << "Tiles: " << "size: " << tiles[i].size() << std::endl;
		for(int j=0,h=0;j<boardSize;j++){
			std::cerr << "Tile Created :" << "i: " << i << " j: " << j << std::endl; 
			std::cerr << "Tile Position :" << "x: " << tiles[i][j].getTile().x << " y: " << tiles[i][j].getTile().y << " w: " << tiles[i][j].getTile().w << " h: " << tiles[i][j].getTile().h << std::endl; 
			std::cerr << "Tile Color :" << " r: " << (int)tiles[i][j].getColor().r << " g: " << (int)tiles[i][j].getColor().g << " b: " << (int)tiles[i][j].getColor().b << " a: " << (int)tiles[i][j].getColor().a << std::endl;
		}
	}
	//printPalette();
}

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

void Display::renderTile(){

	if(!SDL_SetRenderDrawColor(renderer,0,0,0,255)){
		std::cerr << "Drawing Tile Error: " <<  SDL_GetError() << std::endl;
	}
	SDL_Rect r = {0,0,width,height};
	if(!SDL_RenderFillRect(renderer,&r)){
		std::cerr << "Drawing Tile Error: " <<  SDL_GetError() << std::endl;
	}
}

void Display::renderPlayerScale(SDL_Rect* newBox){
	newBox->x/=boardSize;
	newBox->y/=boardSize;
	newBox->w/=boardSize;
	newBox->h/=boardSize;
}

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

void Display::close(){

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(windows);
	SDL_Quit();

}

int Display::getWidth(){
	return this->width;
}
int Display::getHeight(){
	return this->height;
}

int Display::getBwidth(){
	return this->bwidth;
}
int Display::getBheight(){
	return this->bheight;
}

int Display::getBoardSize(){
	return this->boardSize;
}

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

Tiles* Display::getTileFromTiles(int i,int j){
	return &this->tiles[i][j];
}

class Player{
	private:
		std::string name;
		SDL_Rect box;
		bool swap;

	public:
		Player();
		Player(SDL_Rect newBox);

		void setName(std::string newName);
		std::string getName();

		void setBox(SDL_Rect newBox);
		SDL_Rect getBox();

		void setPos(int x,int y);

		int getPosx();
		int getPosy();

		void switchSwap();
		bool getSwap();

		//void renderPlayer(SDL_Renderer renderer);
};

Player::Player(SDL_Rect newBox){
	name="DEATH";
	box = newBox;
	swap=false;
}

void Player::setName(std::string newName){
	name=newName;
}
std::string Player::getName(){
	return this->name;
}

void Player::setBox(SDL_Rect newBox){
	box=newBox;
}
SDL_Rect Player::getBox(){
	return this->box;
}

void Player::setPos(int x,int y){
	this->box.x=x;
	this->box.y=y;
}

int Player::getPosx(){
	return this->box.x;
}
int Player::getPosy(){
	return this->box.y;
}

void Player::switchSwap(){
	this->swap=!this->swap;
}
bool Player::getSwap(){
	return this->swap;
}

int main(int argc, char const *argv[]){
	Display display = Display("Puzzle Pic",0,0,400,400,2);
    //Game game = new Game();

    display.printBoard();
    SDL_Rect r = {0,0,display.getBwidth(),display.getBheight()};
    Player player = Player(r);
    display.render(player.getBox());
    SDL_Event e;
    while(true){
    	while(SDL_PollEvent(&e)!=0){
            switch( e.type ){
                case SDL_QUIT:
                    display.close();
                	return 0;
                break;
                case SDL_KEYDOWN:
                    switch( e.key.keysym.sym ){
                        case SDLK_ESCAPE:
                        case SDLK_DELETE:
                            display.close();
                            return 0;
                        break;
                        case SDLK_UP:
                            std::cerr << "KEY UP" << std::endl;
                          	player.setPos(player.getPosx(),player.getPosy()-display.getBheight());
                       		if(display.checkCollision(player.getPosx(),player.getPosy())){
                       			player.setPos(player.getPosx(),player.getPosy()+display.getBheight());
                       		}else if(player.getSwap()){
                       			//std::cerr << "SWAP COLORS : " << " x1: " << player.getPosx()/display.getBwidth() << " y1: " << player.getPosy()/display.getBheight() << " x2: " << player.getPosx()/display.getBwidth() << " y2: " << (player.getPosy()+display.getBheight())/display.getBheight() << std::endl;
                       			display.swapColors(player.getPosx()/display.getBwidth(),player.getPosy()/display.getBheight(),player.getPosx()/display.getBwidth(),(player.getPosy()+display.getBheight())/display.getBheight());
                       			player.switchSwap();
                       			display.printBoard();
                       			
                       		}
                       		//display.getTileFromTiles(0,0)->setColor(BLACK);
                       		display.render(player.getBox());
	                    break;
                        case SDLK_DOWN:
                          	std::cerr << "KEY DOWN" << std::endl;
                        	player.setPos(player.getPosx(),player.getPosy()+display.getBheight());
                       		if(display.checkCollision(player.getPosx(),player.getPosy())){
                       			player.setPos(player.getPosx(),player.getPosy()-display.getBheight());
                            }else if(player.getSwap()){
                            	//std::cerr << "SWAP COLORS : " << " x1: " << player.getPosx()/display.getBwidth() << " y1: " << player.getPosy()/display.getBheight() << " x2: " << player.getPosx()/display.getBwidth() << " y2: " << (player.getPosy()-display.getBheight())/display.getBheight() << std::endl;
                            	display.swapColors(player.getPosx()/display.getBwidth(),player.getPosy()/display.getBheight(),player.getPosx()/display.getBwidth(),(player.getPosy()-display.getBheight())/display.getBheight());
                            	player.switchSwap();
                            	display.printBoard();
                            }
                            //display.getTileFromTiles(0,0)->setColor(BLACK);
                            display.render(player.getBox());
                        break;
                        case SDLK_LEFT:
                            std::cerr << "KEY LEFT" << std::endl;
                            player.setPos(player.getPosx()-display.getBwidth(),player.getPosy());
                            if(display.checkCollision(player.getPosx(),player.getPosy())){
                            	player.setPos(player.getPosx()+display.getBwidth(),player.getPosy());
                            }else if(player.getSwap()){
                            	//std::cerr << "SWAP COLORS : " << " x1: " << player.getPosx()/display.getBwidth() << " y1: " << player.getPosy()/display.getBheight() << " x2: " << (player.getPosx()+display.getBwidth())/display.getBwidth() << " y2: " << (player.getPosy())/display.getBheight() << std::endl;
                            	display.swapColors(player.getPosx()/display.getBwidth(),player.getPosy()/display.getBheight(),(player.getPosx()+display.getBwidth())/display.getBwidth(),(player.getPosy())/display.getBheight());
                            	player.switchSwap();
                            	display.printBoard();
                            }
                            //display.getTileFromTiles(0,0)->setColor(BLACK);
                            display.render(player.getBox());
                        break;
                        case SDLK_RIGHT:
                            std::cerr << "KEY RIGHT" << std::endl;
                            player.setPos(player.getPosx()+display.getBwidth(),player.getPosy());
                            if(display.checkCollision(player.getPosx(),player.getPosy())){
                           		player.setPos(player.getPosx()-display.getBwidth(),player.getPosy());
                           	}else if(player.getSwap()){
                           		//std::cerr << "SWAP COLORS : " << " x1: " << player.getPosx()/display.getBwidth() << " y1: " << player.getPosy()/display.getBheight() << " x2: " << (player.getPosx()-display.getBwidth())/display.getBwidth() << " y2: " << (player.getPosy())/display.getBheight() << std::endl;
                            	display.swapColors(player.getPosx()/display.getBwidth(),player.getPosy()/display.getBheight(),(player.getPosx()-display.getBwidth())/display.getBwidth(),(player.getPosy())/display.getBheight());
                            	player.switchSwap();
                            	display.printBoard();
                            }
                            //display.getTileFromTiles(0,0)->setColor(BLACK);
                            display.render(player.getBox());
                        break;
                        case SDLK_SPACE:
                          	//std::cerr << "SPACE PRESSED: " << "PLayer swap: " << player.getSwap() << std::endl;
                           	player.switchSwap();
                           	//std::cerr << "SPACE PRESSED: " << "PLayer swap: " << player.getSwap() << std::endl;
                        break;
                        case SDLK_p:
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


