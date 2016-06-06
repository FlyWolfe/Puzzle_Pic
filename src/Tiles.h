#ifndef _TILES_H_
#define _TILES_H_

#ifdef _WIN32
#include <SDL.h>
#elif defined __unix__ || defined __APPLE__
#include <SDL2/SDL.h>
#endif

#include <string>

/*
	Tiles CLASS
*********************/

class Tiles{

	public:
		SDL_Color color;					//Color of a box
		SDL_Rect box; 						//Rectangle Box of a box
		std::string name;


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

		std::string getName();

		void printTile();

};


#endif
