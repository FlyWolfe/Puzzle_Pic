#include "Tiles.h"


SDL_Color BLACK = {0,0,0,255};        //Color BLACK
SDL_Color WHITE = {255,255,255,255};  //Color WHITE

/*
	Tiles CLASS FUNCTION DEFINITIONS
*********************/


//Empty Constructor 
Tiles::Tiles(){
	this->color = WHITE;
}


//Constructor for setting a box with a Color and Rectangle
Tiles::Tiles(SDL_Color newColor,SDL_Rect newBox){
	this->color = newColor;
	this->box = newBox;
}

/*
Tiles::~Tiles(){
	std::cerr << "END OF box" << std::endl;
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

//Set box Box
void Tiles::setBox(SDL_Rect newBox){
	this->box = newBox;
}

//Get box Box
SDL_Rect Tiles::getBox(){
	return this->box;
}



