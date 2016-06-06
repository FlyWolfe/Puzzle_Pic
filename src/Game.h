#ifndef _GAME_H_
#define _GAME_H_

#include <string>

#include "Display.h"
#include "Player.h"

class Game{
	private:

		Display display;
		Player player;
		bool playGame;
		int numOfSwaps;

	public:

		Game();
		Game(std::string name,int size,int width,int height);

		void incrementNumSwaps();
		int getIncrementNumSwaps();

		void updateDisplay();
		void controls();

		bool getPlayGame();
};

#endif
