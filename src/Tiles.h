#ifndef _TILES_H_
#define _TILES_H_

#include <SDL.h>
#include "Util.h"

/*
	TILES CLASS
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
		//~TILES();

		void setColor(SDL_Color newColor);	//Set the Color of a box
		SDL_Color getColor();				//Get the Color of a box

		void setbox(SDL_Rect newBox);		//Set the Rectangle Box of a box
		SDL_Rect getbox();					//Get the Rectangle Box of a box

		//void renderbox(SDL_Renderer renderer);

};


#endif
