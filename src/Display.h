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

#include "Board.h"


/*
	DISPLAY CLASS
*********************/
class Display{

	public:
		//Texture texture;
		//TextTexture text;
		SDL_Window* window;
		SDL_Renderer* renderer;

		Board board;

		Tiles *clickedTiles[2];

		//Contructor
		Display();
		Display(std::string name, 				//Name of Window
				int initialPosX,				//intial X position of the window
				int initialPosY,				//intial Y position of the window
				int newWidth,					//Width of Window;
				int newHeight,					//Height of Window;
				int size						//Size of the Board;
				);

		void initSDL();							//Initialize SDL
		void initTTF();							//Initialize TTF

		void createWindow(	std::string name,	//Name of Window
							int initialPosX,	//Initial X Position of Window
							int initialPosY,	//Initial Y Position of Window
							int width,			//Width of Window
							int height 			//Height of Window
							);
		void createRenderer();					//Creates the SDL Renderer

		void setupRenderer(int width,int height);	//Setup the renderer target and scale of Renderer

		void render(SDL_Rect box);				//Render Player and Board
		void renderPlayer(SDL_Rect box, int boardSize);		//Render The Player
		void renderTile(int x,int y);			//Render Tiles

		void renderBoard(int boardSize);	//Render the Board

		void renderPlayerScale(					//Change the Thickness of the Line for the Player
					SDL_Rect* newBox,			//Players Box
					int boardSize
					);
		int getWidth();							//Get width of Display
		int getHeight();						//Get height of Display

		void close();
};


#endif
