#include "Player.h"



Player::Player(int w,int h){
	name="DEATH";
	box=Rect(0,0,w,h);
}

Player::~Player(){
	std::cerr << "END OF PLAYER" << std::endl;
}

void Player::setName(std::string newName){
	name=newName;
}
std::string Player::getName(){
	return this->name;
}

void Player::setBox(Rect newbox){
	box=Rect(newbox);
}
SDL_Rect Player::getBox(){
	SDL_Rect r;
	r.x=this->box.x;
	r.y=this->box.y;
	r.w=this->box.w;
	r.h=this->box.h;
	return r;
}


/*void Player::renderPlayer(SDL_Renderer* renderer){

	if(!SDL_SetRenderDrawColor(renderer,0,0,0,255)){
		std::cerr << "Drawing Player Error: " <<  SDL_GetError() << std::endl;
	}

	if(!SDL_RenderDrawRect(renderer,&box)){
		std::cerr << "Drawing Player Error: " <<  SDL_GetError() << std::endl;
	}
}*/

