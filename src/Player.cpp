#include "Player.h"


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
