#include "Tiles.h"

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



