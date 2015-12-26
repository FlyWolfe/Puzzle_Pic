#ifndef _PLAYER_H_
#define _PLAYER_H_

/*
	PLAYER CLASS
*********************/ 

class Player{
	private:
		std::string name;			//Name Of Player
		SDL_Rect box;				//Box of Player
		bool swap;					//Bool fo knowing When to Swap tiles

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

		void switchSwap();			//Toggle the Boolean for swapping Tiles
		bool getSwap();				//Get Swap Boolean

		//void renderPlayer(SDL_Renderer renderer);
};

#endif