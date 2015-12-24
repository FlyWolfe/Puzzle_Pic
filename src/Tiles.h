#ifndef _TILES_H_
#define _TILES_H_

#include "Util.h"

class Tiles{

	private:
		SDL_Color color;
		SDL_Rect tile; 

	public:
		Tiles();
		Tiles(SDL_Color newColor, SDL_Rect newTile);
		~Tiles();

		void setColor(SDL_Color newColor);
		SDL_Color getColor();

		void setTile(Rect newTile);
		SDL_Rect getTile();

		//void renderTile(SDL_Renderer renderer);

};

#endif