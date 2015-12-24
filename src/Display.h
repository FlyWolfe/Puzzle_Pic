#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <cmath>
#include <random>
#include <iostream>


enum {
	IMG,
	BMP,
};

class Display{

	private:
		SDL_Texture* texture;
		SDL_Renderer* renderer;
		SDL_Surface* surface;
		SDL_Window* windows;

		std::vector<SDL_Color> palette;

		int width;
		int height;

		int bwidth;
		int bheight;

		int boardSize;

		std::vector<std::vector<Tiles> > tiles;

	public:

		Display(std::string name,int initialPosX,int initialPosY,int newWidth,int newHeight,int size);

		void initSDL();
		void initTTF();

		void setPalette();
		std::vector<SDL_Color> getPalette();
		void printPalette();

		void loadTexture();

		void createTexttexture();

		void createTexture();
		void createSurface(std::string filename);
		void createWindow(std::string name,int initialPosX,int initialPosY,int width,int height);
		void createRenderer();

		void textureFromSurface();
		void createRGBSurface();
		void surfaceFromImage(std::string filename);

		void setupRenderer();

		void makeBoard();

		void printBoard();

		bool checkCollision(int posx,int posy);

		void render(SDL_Rect box);
		void renderPlayer(SDL_Rect box);
		void renderTile();

		void renderBoard();

		void renderPlayerScale(SDL_Rect* newBox);

		void close();


		int getWidth();
		int getHeight();

		int getBwidth();
		int getBheight();

		int getBoardSize();

		void swapColors(int x1,int y1,int x2,int y2);

		Tiles* getTileFromTiles(int i,int j);

};


#endif