#ifndef _GAME_H_
#define _GAME_H_

#include "Player.h"
#include "Tiles.h"

class Game{
	private:

		Player player;
		std::vector<std::vector<Tiles> > tiles;

		int boardSize;

		int bwidth,bheight;

		int numOfSwaps;
		bool swap;

	public:

		Game(int size,int w,int h,int newbwidth,int newbheight);

		void swapColors(Tiles tile1,Tiles tile2);

		void incrementSwaps();
		int getNumSwaps();

		void switchSwap();
		bool getSwap();

		void makeBoard(int bwidth,int bheight);

		bool checkCollision(int posx,int posy,int width, int height);

		//void renderBoard(SDL_Renderer renderer);

		Player getPlayer();

		Tiles getTileFromTiles(int i,int j);
		Tiles getTiles();

};

#endif