#ifndef _TILES_H_
#define _TILES_H_

#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
//#include <SDL_ttf.h>
#elif defined __unix__ || defined __APPLE__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>
#endif

/*
	Tiles CLASS
*********************/ 

class Tiles{

	private:
		SDL_Color color;					//Color of a box
		SDL_Rect box; 						//Rectange Box of a box

	public:
		Tiles();							//Empty Constructor of a box
		Tiles(								//Constructor of a box from a Color and Rectangle
				SDL_Color newColor, 		//Color using SDL_Color
				SDL_Rect newBox			//Rectangle Box using SDL_Rect
				);
		//~Tiles();

		void setColor(SDL_Color newColor);	//Set the Color of a box
		SDL_Color getColor();				//Get the Color of a box

		void setBox(SDL_Rect newBox);		//Set the Rectangle Box of a box 
		SDL_Rect getBox();					//Get the Rectangle Box of a box

		void printTile();

		//void renderbox(SDL_Renderer renderer);

};


#endif
