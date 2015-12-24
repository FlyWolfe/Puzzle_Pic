#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Util.h"
#include <iostream>


class Player{
	private:
		std::string name;
		Rect box;

	public:
		Player();
		Player(int w,int h);
		~Player();

		void setName(std::string newName);
		std::string getName();

		void setBox(Rect newbox);
		SDL_Rect getBox();

		//void renderPlayer(SDL_Renderer renderer);

};

#endif