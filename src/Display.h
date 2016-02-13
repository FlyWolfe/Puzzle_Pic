#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#elif defined __unix__ || defined __APPLE__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

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
	DISPLAY CLASS
*********************/
class Display{

	private:
		SDL_Texture* texture;
		SDL_Renderer* renderer;
		SDL_Surface* surface;
		SDL_Window* windows;

		std::vector<PaletteColors> palette; //Colors in the Game

		int width;						//Width of Display Window
		int height;						//Height of Display Window

		int bwidth;						//Width of Tiles
		int bheight;					//Height of Tiles

		int boardSize;					//Number of a Row if 3X3 the boardsize is 3

		std::vector<std::vector<Tiles> > tiles; //Vector of vectors of Tiles

		Tiles *clickedTiles[2];

	public:
		//Contructor
		Display(std::string name, 				//Name of Window
				int initialPosX,				//intial X position of teh window
				int initialPosY,				//intial Y position of teh window
				int newWidth,					//Width of Window;
				int newHeight,					//Height of Window;
				int size						//Size of the Board;
				);

		void initSDL();							//Initialize SDL
		void initTTF();							//Initialize TTF

		void setPalette(						//Create the Colors of the Display
				std::vector<std::pair<int,int> >
				);						
		std::vector<PaletteColors> getPalette();	//Get the Colors of the Display
		void printPalette();					//Print the Colors for debbuging purposes

		void loadTexture();						//Load Textrues From file

		void createTexttexture();				//Create Textures from Text using TTF

		void createWindow(	std::string name,	//Name of Window
							int initialPosX,	//Initial X Position of Window
							int initialPosY,	//Initial Y Position of Window
							int width,			//Width of Window
							int height 			//Height of Window
							);
		void createRenderer();					//Creates the SDL Renderer

		void textureFromSurface();				//Creates A Texture From A Surface
		void createRGBSurface();				//Creates a Surface from RGB Masks
		void surfaceFromImage(					//Creates Surface from Imaeg using SDL_Image
					std::string filename		//Filename of Image
					);

		void setupRenderer();					//Setup the renderer target and scale of Renderer

		void makeBoard();						//Make the game board

		void printBoard();						//Print Game Board in the terminal

		bool checkCollision(int posx,int posy);	//Check the Collision of the Player with the window boundaries

		void getClickedTile(int posx,int posy,int num);

		void deleteClickedTiles();

		void render(SDL_Rect box);				//Render Player and Board
		void renderPlayer(SDL_Rect box);		//Render The Player
		void renderTile(int x,int y);						//Render Tiles

		void renderBoard();						//Render the Board

		void renderPlayerScale(					//Change the Thickness of the Line for the Player
					SDL_Rect* newBox			//Players Box
					);

		void close();							//Close the Display and SDL


		int getWidth();							//Get width of Display
		int getHeight();						//Get height of Display

		int getBwidth();						//Get tile width
		int getBheight();						//Get tile height

		int getBoardSize();						//Get board size

		void swapColorsKeyboard(						//Swap Tile Colors
					int x1,int y1,				//The x and y position of tile
					int num
					);

		void swapColorsMouse();

		Tiles* getTileFromTiles(int i,int j);	//Get the pointer a tile in the Board

};


#endif
