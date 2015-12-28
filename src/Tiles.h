#ifndef _TILES_H_
#define _TILES_H_

#include <SDL2/SDL.h>
#include "Util.h"

/*
	TILES CLASS
*********************/ 

class TILES{

	private:
		SDL_Color color;					//Color of a box
		SDL_Rect box; 						//Rectange Box of a box

	public:
		TILES();							//Empty Constructor of a box
		TILES(								//Constructor of a box from a Color and Rectangle
				SDL_Color newColor, 		//Color using SDL_Color
				SDL_Rect newBox			//Rectangle Box using SDL_Rect
				);
		//~TILES();

		void setColor(SDL_Color newColor);	//Set the Color of a box
		SDL_Color getColor();				//Get the Color of a box

		void setbox(SDL_Rect newBox);		//Set the Rectangle Box of a box 
		SDL_Rect getbox();					//Get the Rectangle Box of a box

		//void renderbox(SDL_Renderer renderer);

};


#endif