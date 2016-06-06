#include "Board.h"
#include <chrono>
#include <cmath>
#include <random>

//Used to generate Random Number
#ifdef _WIN32
std::mt19937 engine(std::chrono::system_clock::now().time_since_epoch().count());
#elif defined __unix__ || defined __APPLE__
std::random_device seeder;
std::mt19937 engine(seeder());
#endif
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
Board::Board(){}


Board::Board(int width, int height, int size):bwidth(width/size),bheight(height/size),width(width),height(height),boardSize(size){

	std::vector<std::pair<int,int > > vec;
	vec.push_back(std::make_pair(0,1));
	vec.push_back(std::make_pair(1,1));
	vec.push_back(std::make_pair(2,2));

	setPalette(vec);											//Set the Palette of the Game Board
	printPalette();

	makeBoard();												//Make Game Board

	printBoard();												//Print Board for Debugging Purposes
}


//Set the Palette of the Game Board
void Board::setPalette(std::vector<std::pair<int ,int > > newpalette){

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

	std::string name;

	std::vector<PaletteColors> palette;

	for(int i=0; i < newpalette.size(); i++){
		switch(newpalette[i].first){
			case 0:
				name="Green";
			break;
			case 1:
				name="Orange";
			break;
			case 2:
				name="Blue";
			break;
			case 3:
				name="Red";
			break;
			case 4:
				name="Yellow";
			break;
			case 5:
				name="Violet";
			break;
			case 6:
				name="White";
			break;
			case 7:
				name="Purple";
			break;
			case 8:
				name="Pink";
			break;
			default:
			std::cerr << "NOT A VALID COLOR" << std::endl;
			break;
		}
		palette.push_back(PaletteColors(colors[newpalette[i].first],newpalette[i].second,name));
	}

	//std::vector<SDL_Color> temp(colors, colors + sizeof(colors) / sizeof(SDL_Color) );

	this->palette = palette;

}

//Print the Colors for debbuging purposes
void Board::printPalette(){
	std::cerr << "PRINT PALETTE" << std::endl;
	for(int i=0;(unsigned)i<palette.size();i++){
		std::cerr << "Palette: " << " num: " << i << " Name : " << palette[i].name << " Amount: " << palette[i].numofColor << " r: " << (int)palette[i].color.r << " g: " << (int)palette[i].color.g << " b: " << (int)palette[i].color.b << " a: " << (int)palette[i].color.a << std::endl;
	}
}

//Get Palette of a Display
std::vector<PaletteColors> Board::getPalette(){
	return this->palette;
}

//Check Collision of the Player and Board
bool Board::checkCollision(int posx,int posy){

	if( (posx < 0) || (posx+bwidth > width) ){
		return true;
	}
	if( (posy < 0) || (posy+bheight > height) ){
		return true;
	}
	return false;
}

//Make Board
void Board::makeBoard(){
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
			do{
				num=dist(engine);
				//std::cerr << "Tile Color :" << "num: " << num << " r: " << (int)this->palette[num].r << " g: " << (int)palette[num].g << " b: " << (int)palette[num].b << " a: " << (int)palette[num].a << std::endl;
				//if(this->palette[num].numofColor!=0){
				//	break;
				//}
			}while(this->palette[num].numofColor==0);
				tiles[i].push_back(Tiles(this->palette[num].color,temp));
				this->palette[num].numofColor--;
		}
	}
}

//Print a Board
void Board::printBoard(){
	std::cerr << "PRINT BOARD" << std::endl;
	for(int i=0;i<boardSize;i++){
		std::cerr << "Tiles: " << "size: " << tiles[i].size() << std::endl;
		for(int j=0;j<boardSize;j++){
			std::cerr << "Tile Created :" << "i: " << i << " j: " << j << std::endl;
			std::cerr << "Tile Position :" << "x: " << tiles[i][j].box.x << " y: " << tiles[i][j].box.y << " w: " << tiles[i][j].box.w << " h: " << tiles[i][j].box.h << std::endl;
			std::cerr << "Tile Color :" << " r: " << (int)tiles[i][j].color.r << " g: " << (int)tiles[i][j].color.g << " b: " << (int)tiles[i][j].color.b << " a: " << (int)tiles[i][j].color.a << std::endl;
		}
	}
	//printPalette();
}

//Get Width of Tiles
int Board::getBwidth(){
	return this->bwidth;
}

//Get Height of Tiles
int Board::getBheight(){
	return this->bheight;
}

//Get board Size if 3X3 board size is 3
int Board::getBoardSize(){
	return this->boardSize;
}

//Swap Colors of Two Tiles
void Board::swapColorsKeyboard(int x,int y,int num){

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

	Tiles temp = Tiles(tiles[x1][y1].color,tiles[x1][y1].box);
	tiles[x1][y1].color = tiles[x2][y2].color;
	tiles[x2][y2].color=temp.color;
}

void Board::swapColorsMouse(){
	if(clickedTiles[0]!=NULL && clickedTiles[1]!=NULL){
		Tiles temp = Tiles(clickedTiles[0]->color,clickedTiles[0]->box);
		clickedTiles[0]->color=clickedTiles[1]->color;
		clickedTiles[1]->color=temp.color;
		clickedTiles[0]=NULL;
		clickedTiles[1]=NULL;
	}
}

//Get Pointer to a tile on a board
Tiles* Board::getTileFromTiles(int i,int j){
	return &this->tiles[i][j];
}

void Board::getClickedTile(int posx,int posy,int num){
	int x, y;

	x=(posx/bwidth)%boardSize;
	y=(posy/bheight)%boardSize;

	std::cerr << "CLICKED TILE: " << " x: " << x << " y: " << y <<  " posx: " <<  posx   << " posy: " << posy << std::endl;

	(num%2==0)?clickedTiles[0]=&tiles[x][y]:clickedTiles[1]=&tiles[x][y];
}

void Board::deleteClickedTiles(){
	clickedTiles[0]=NULL;
	clickedTiles[1]=NULL;
}

SDL_Color Board::getTileColor(int i,int j){
	return this->tiles[i][j].getColor();
}

SDL_Rect Board::getTileBox(int i, int j){
	return this->tiles[i][j].getBox();
}
