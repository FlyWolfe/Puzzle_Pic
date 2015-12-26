#ifndef _TILES_H_
#define _TILES_H_


/*
	TILES CLASS
*********************/ 

class Tiles{

	private:
		SDL_Color color;					//Color of a Tile
		SDL_Rect tile; 						//Rectange Box of a Tile

	public:
		Tiles();							//Empty Constructor of a Tile
		Tiles(								//Constructor of a Tile from a Color and Rectangle
				SDL_Color newColor, 		//Color using SDL_Color
				SDL_Rect newTile			//Rectangle Box using SDL_Rect
				);
		//~Tiles();

		void setColor(SDL_Color newColor);	//Set the Color of a Tile
		SDL_Color getColor();				//Get the Color of a Tile

		void setTile(SDL_Rect newTile);		//Set the Rectangle Box of a Tile 
		SDL_Rect getTile();					//Get the Rectangle Box of a Tile

		//void renderTile(SDL_Renderer renderer);

};


#endif