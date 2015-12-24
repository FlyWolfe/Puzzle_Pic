#include "Display.h"


std::random_device seeder;
std::mt19937 engine(seeder());


Display::Display(std::string name,int initialPosX,int initialPosY,int newWidth,int newHeight,int size):
	width(newWidth), height(newHeight),boardSize(size), bwidth(width/size), bheight(height/size){
	/*initSDL();
	initTTF();

	createWindow(name,initialPosX,initialPosY,width,height);
	createRGBSurface();
	textureFromSurface();
	createRenderer();

	setupRenderer();*/

	//setpalette();
}


void Display::initSDL(){
	if(!SDL_Init(SDL_INIT_EVERYTHING)) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        exit(1);
        //return false;
    }
    //return true;
}

void Display::initTTF(){
	if(!TTF_Init()){
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        exit(1);
        //return false;
    }
    //return true;
}
/*
//void Display::setpalette(){

	/* std::vector<Color>  colors{
		{0,128,0,255}, //green
		{255,165,0,255}, //orange
		{0,0,255,255}, //blue
		{255,0,0,255}, //red
		{255,255,0,255}, //yellow
		{238,130,238,255}, //violet
		{255,255,255,255}, //white
		{0,0,0,255}, //black
		{128,0,128,255}, //purple
		{255,192,203,255} //pink
	};

	this->palette = colors;*/

//}

//SDL_Palette* Display::getpalette(){
//	return this->palette;
//}

/*
void Display::createTexture(int flag){
	
}

void Display::loadTexture(){

}

void Display::textureFromSurface(){
	texture=SDL_CreateTextureFromSurface(renderer,surface);
	if(!texture){
    	std::cerr << "Texture from Surface Error: " << SDL_GetError() << std::endl;
    	exit(1);
    	//return false;
	}
	SDL_FreeSurface(surface);
	//return true;

}

void Display::createTexttexture(){

}

void Display::createSurface(int flag,std::string filename){
	if(filename.empty()){
		surface=SDL_CreateRGBSurface(0,width,height,32,32,32,32,32);
	}else{
		switch(flag){
			case IMG:
				surface=IMG_Load(filename.c_str());
			case BMP:
				surface=SDL_LoadBMP(filename.c_str());
		}
	}
	if(!surface){
        std::cerr << "Create Surface Error: " << SDL_GetError() << std::endl;
        exit(1);
        //return false;
    }
    //return true;
}

void Display::createRGBSurface(){
	surface=SDL_CreateRGBSurface(0,width,height,32,32,32,32,32);
	if(!surface){
        std::cerr << "Create RGB Surface Error: " << SDL_GetError() << std::endl;
        exit(1);
        //return false;
    }
}

void Display::surfaceFromImage(std::string filename){
	surface=IMG_Load(filename.c_str());
	if(!surface){
        std::cerr << "Create Surface from Image Error: " << SDL_GetError() << std::endl;
        exit(1);
        //return false;
    }
    //return true;
}



void Display::createWindow(std::string name,int initialPosX,int initialPosY,int width,int height){

	// Create an application windows with the following settings:
    windows = SDL_CreateWindow(
        name.c_str(),                  							// windows title
        initialPosX,           							// initial x position
        initialPosY,           							// initial y position
        width,                              			// width, in pixels
        height,                             			// height, in pixels
        SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI	 	// flags 
    );
    if(!windows){
    	std::cerr << "Create windows Error: " << name << " " << SDL_GetError() << std::endl;
    	exit(1);
    	//return false;
    }
    //return true;

}

void Display::createRenderer(){

	renderer = SDL_CreateRenderer(
		windows, 						//the windows where rendering is displayed
		-1, 							//the index of the rendering driver to initialize, or -1 to initialize the first one supporting the requested flags
		SDL_RENDERER_ACCELERATED		//flags
		);

	if(!renderer){
    	std::cerr << "Create Renderer Error: " << SDL_GetError() << std::endl;
    	exit(1);
    	//return false;
    }
    //return true;
}

void Display::setupRenderer(){

	// Set size of renderer to the same as windows
	SDL_RenderSetLogicalSize(renderer, width, height);

	// Set color of renderer clear to white
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255 );
}

void Display::renderBoard(){

	for(int i=0;i<boardSize;i++){
		for(int j=0;j<boardSize;j++){
			if(!SDL_SetRenderDrawColor(renderer,0,0,0,255)){
				std::cerr << "Drawing Board Tile Error: " <<  SDL_GetError() << std::endl;
			}
			SDL_Rect r;
			r.x=0;
			r.y=0;
			r.w=width;
			r.h=height;
			if(!SDL_RenderDrawRect(renderer,&r)){
				std::cerr << "Drawing Board Tile Error: " <<  SDL_GetError() << std::endl;
			}
		}
	}
} 


void Display::makeBoard(Game game){
	std::uniform_int_distribution<int> dist(0,9);
	int num;
	game.getTiles() = tiles(tst, std::vector<Tiles>(tst));
	SDL_Rect temp;
	temp.w=bwidth;
	temp.h=bheight;
	for(int i=0;i<width;i+=bwidth){
		temp.x=i;
		for(int j=0;j<height;j+=bheight){
			temp.y=j;
			num=dist(engine);
			game.getTileFromTiles(i,j)=Tiles(palette[num],temp);
		}
	}
}

void Display::renderBoard(Game game){

	for(int i=0;i<boardSize;i++){
		for(int j=0;j<boardSize;j++){
			if(!SDL_SetRenderDrawColor(renderer,game.getTileFromTiles(i,j).getColor().r,game.getTileFromTiles(i,j).getColor().g,game.getTileFromTiles(i,j).getColor().b,game.getTileFromTiles(i,j).getColor().a)){
				std::cerr << "Drawing Board Tile Error: " <<  SDL_GetError() << std::endl;
			}
			SDL_Rect r=game.getTileFromTiles(i,j).getTile();
			if(!SDL_RenderDrawRect(renderer,&r)){
				std::cerr << "Drawing Board Tile Error: " <<  SDL_GetError() << std::endl;
			}
		}
	}
} 

void Display::renderTile(Game game,int i,int j){

	if(!SDL_SetRenderDrawColor(renderer,game.getTileFromTiles(i,j).getColor().r,game.getTileFromTiles(i,j).getColor().g,game.getTileFromTiles(i,j).getColor().b,game.getTileFromTiles(i,j).getColor().a)){
		std::cerr << "Drawing Tile Error: " <<  SDL_GetError() << std::endl;
	}
	SDL_Rect r=game.getTileFromTiles(i,j).getTile();
	if(!SDL_RenderDrawRect(renderer,&r)){
		std::cerr << "Drawing Tile Error: " <<  SDL_GetError() << std::endl;
	}
}

void Display::renderPlayer(Game game){

	if(!SDL_SetRenderDrawColor(renderer,0,0,0,255)){
		std::cerr << "Drawing Player Error: " <<  SDL_GetError() << std::endl;
	}
	SDL_Rect r=game.getPlayer().getBox();
	if(!SDL_RenderDrawRect(renderer,&r)){
		std::cerr << "Drawing Player Error: " <<  SDL_GetError() << std::endl;
	}
}

void Display::render(Game game){
	// Change color to white
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	//clear screen
	SDL_RenderClear(renderer);

	// Render the tiles
	

	// Render the Player
	
	
	// Render the changes above
	SDL_RenderPresent(renderer);
}

void Display::close(){

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(windows);
	SDL_Quit();

}*/