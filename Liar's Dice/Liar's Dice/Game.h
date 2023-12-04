#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include "Player.h"

using namespace std;

class Game {
	public:

		void runGame();

	private:

		void printRules(); //Reads rules for the game from "Game Rules.txt" and prints them.

		void obtainNumPlayers();
		void initializePlayers();

		void obtainGuess();
		bool evaluateGuess(); // Returns true if currGuess is correct and false otherwise

		void printPlayerList(); //Prints out the elements of playersVector

		void callLiar(int); // Gives option to call liar and runs endGame if someone agrees
		void endGame(int, int); // Prints message declaring the winner and sets gameOver to true
		void runTurn(Player* currPlayer);
		
		int numPlayers;
		int currGuess[2]; // A two number guess
		int lastGuess; // The last player's first number. The next player must guess higher.

		vector<Player*> playersVector;

		bool gameOver = false;
		
};