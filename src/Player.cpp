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

bool Player::moveUP(int check){
	if((box.y-box.h) > check-1){
		box.y-=box.h;
		return true;
	}
	return false;
}

bool Player::moveDOWN(int check){
	if((box.y+box.h) < check-1){
		box.y+=box.h;
		return true;
	}
	return false;
}

bool Player::moveRIGHT(int check){
	if((box.x+box.w) < check-1){
		box.x+=box.w;
		return true;
	}
	return false;
}

bool Player::moveLEFT(int check){
	if((box.x-box.w) > check-1){
		box.x-=box.w;
		return true;
	}
	return false;
}

void Player::click(){
	this->clicks++;
}

int Player::getClicks(){
	return this->clicks;
}

//Toggle the swap Boolean
void Player::switchSwap(){
	this->swap=!this->swap;
}

//Get Swap Boolean
bool Player::getSwap(){
	return this->swap;
}

void Player::printBox(){
	std::cerr << " Name: " << this->name << " x: " << this->box.x << " y: " << this->box.y << " width: " << this->box.w << " height: " << this->box.h << std::endl;
}
