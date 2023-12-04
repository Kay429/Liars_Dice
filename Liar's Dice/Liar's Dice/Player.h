#pragma once

#include <string>
#include <array>
#include <random>
#include <iostream>

using namespace std;

class Player {

	public:

		Player();
		void setName(string);
		string getName();
		void setPlayerNum(int);
		int getPlayerNum();

		int countDice(int); // Returns number of dice player has that equal specified int
		void rollDice(); // Generates 5 random numbers in range 1-6 for player's dice
		void printAllDice();

	private:
		string name;
		const int NUM_DICE = 5;
		int dice[5];
		int playerNum;

		void printOneDie(int);
};