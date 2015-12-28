#include "Tiles.h"

/*
	TILES CLASS FUNCTION DEFINITIONS
*********************/ 


//Empty Constructor 
TILES::TILES(){
	this->color = WHITE;
}


//Constructor for setting a box with a Color and Rectangle
TILES::TILES(SDL_Color newColor,SDL_Rect newBox){
	this->color = newColor;
	this->box = newBox;
}

/*
TILES::~TILES(){
	std::cerr << "END OF box" << std::endl;
}
*/

//Set Color 
void TILES::setColor(SDL_Color newColor){
	//std::cerr << "SET COLOR" << std::endl;
	this->color = newColor;
}

//Get Color
SDL_Color TILES::getColor(){
	return this->color;
}

//Set box Box
void TILES::setbox(SDL_Rect newBox){
	this->box = newBox;
}

//Get box Box
SDL_Rect TILES::getbox(){
	return this->box;
}



