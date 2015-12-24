#include "Tiles.h"

#include <iostream>

Tiles::Tiles(Color newColor,Rect newTile){
	color = Color(newColor);
	tile = Rect(newTile);
}

Tiles::~Tiles(){
	std::cerr << "END OF TILE" << std::endl;
}

void Tiles::setColor(Color newColor){
	color = Color(newColor);
}

Color Tiles::getColor(){
	return this->color;
}

void Tiles::setTile(Rect newTile){
	tile = Rect(newTile);
}

SDL_Rect Tiles::getTile(){
	SDL_Rect r;
	r.x=this->tile.x;
	r.y=this->tile.y;
	r.w=this->tile.w;
	r.h=this->tile.h;
	return r;
}

/*void Tiles::renderTile(SDL_Renderer* renderer){

	if(!SDL_SetRenderDrawColor(renderer,color.r,color.g,color.b,color.a)){
		std::cerr << "Drawing Tile Error: " <<  SDL_GetError() << std::endl;
	}

	if(!SDL_RenderFillRect(renderer,&tile)){
		std::cerr << "Drawing Tile Error: " <<  SDL_GetError() << std::endl;
	}
}
*/


