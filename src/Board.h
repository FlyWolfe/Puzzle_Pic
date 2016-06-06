#ifndef _BOARD_H_
#define _BOARD_H_

#include <string>
#include <iostream>
#include <vector>
#include <utility>

#include "Tiles.h"

enum {
	UP,
	DOWN,
	LEFT,
	RIGHT
};



struct PaletteColors{

	SDL_Color color;
	int numofColor;
	std::string name;

	PaletteColors(){}
	PaletteColors(SDL_Color c,int num, std::string n){
		color=c;
		numofColor=num;
		name=n;
	}
};


/*
	BOARD CLASS
*********************/
class Board{

	public:
		std::vector<PaletteColors> palette; //Colors in the Game

		int bwidth;						//Width of Tiles
		int bheight;					//Height of Tiles

		int width;
		int height;

		std::vector<std::vector<Tiles> > tiles; //Vector of vectors of Tiles

		Tiles *clickedTiles[2];

		int boardSize;					//Number of a Row if 3X3 the boardsize is 3


		//Contructor
		Board();
		Board(
				int width,
				int height,
				int size						//Size of the Board;

      	);

		void setPalette(						//Create the Colors of the Display
				std::vector<std::pair<int,int> >
				);
		std::vector<PaletteColors> getPalette();	//Get the Colors of the Display
		void printPalette();					//Print the Colors for debbuging purposes

		void makeBoard();						//Make the game board
		void printBoard();						//Print Game Board in the terminal

		bool checkCollision(int posx,int posy);	//Check the Collision of the Player with the window boundaries

		int getWidth();
		int getHeight();

		int getBwidth();						//Get tile width
		int getBheight();						//Get tile height

		int getBoardSize();						//Get board size

		void swapColorsKeyboard(						//Swap Tile Colors
					int x1,int y1,				//The x and y position of tile
					int num
					);

		void swapColorsMouse();

		Tiles* getTileFromTiles(int i,int j);	//Get the pointer a tile in the Board

		void getClickedTile(int posx,int posy,int num);
		void deleteClickedTiles();

		SDL_Color getTileColor(int i,int j);
		SDL_Rect getTileBox(int i, int j);

};




#endif
