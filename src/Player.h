#ifndef _PLAYER_H_
#define _PLAYER_H_

#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
//#include <SDL_ttf.h>
#elif defined __unix__ || defined __APPLE__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>
#endif

#include <string>
#include <iostream>

/*
	PLAYER CLASS
*********************/

class Player{
	private:
		std::string name;			//Name Of Player
		SDL_Rect box;				//Box of Player
		bool swap;					//Bool fo knowing When to Swap tiles
		int clicks;

	public:
		Player();					//Empty Constructor
		Player(SDL_Rect newBox);	//Constructor Player from SDL_Rect box

		void setName(				//Set Name of Player
				std::string newName	//Name of Player
				);
		std::string getName();		//Get Name of Player

		void setBox(				//Set Box of the Player
				SDL_Rect newBox		//Box of the Player
				);
		SDL_Rect getBox();			//Get Box of the Player

		void setPos(int x,int y);	//Set Position of the Player

		int getPosx();				//Get X Position of the Player
		int getPosy();				//Get Y Position of the Player

		bool moveUP(int moveNum);
		bool moveDOWN(int moveNum);
		bool moveRIGHT(int moveNum);
		bool moveLEFT(int moveNum);

		void switchSwap();			//Toggle the Boolean for swapping Tiles
		bool getSwap();				//Get Swap Boolean

		void click();

		int getClicks();

		void printBox();

		//void renderPlayer(SDL_Renderer renderer);
};

#endif
