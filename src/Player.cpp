#include "Player.h"


/*
	PLAYER CLASS FUNCTION DEFINITIONS
*********************/

//Constructor of Player CLass

Player::Player(){}

Player::Player(SDL_Rect newBox, int boundary){
	name="DEATH";
	box = newBox;
	swap=false;
	this->boundary = boundary;
}

//Set Player Name
void Player::setName(std::string newName){
	this->name=newName;
}

//Get Player Name
std::string Player::getName(){
	return this->name;
}

//Set Player Box
void Player::setBox(SDL_Rect newBox){
	this->box=newBox;
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

bool Player::moveUP(){
/*	if((box.y-box.h) >= check){
		box.y-=box.h;
		return true;
	}
	return false;*/
	if((box.y/box.h)%boundary > 0){
		box.y-=box.h;
		return true;
	}
	return false;
}

bool Player::moveDOWN(){
	/*if((box.h+box.y) < (check-box.h)){
		box.y+=box.h;
		return true;
	}
	return false;*/

	if((box.y/box.h)%boundary < boundary-1){
		box.y+=box.h;
		return true;
	}
	return false;
}

bool Player::moveRIGHT(){
	/*if((box.w+box.x) < (check-box.w)){
		box.x+=box.w;
		return true;
	}
	return false;*/

	if((box.x/box.w)%boundary < boundary-1){
		box.x+=box.w;
		return true;
	}
	return false;
}

bool Player::moveLEFT(){
	/*if((box.x-box.w) >= check){
		box.x-=box.w;
		return true;
	}
	return false;*/

	if((box.x/box.w)%boundary > 0){
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
