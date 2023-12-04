#include "Player.h"

Player::Player() {
	// Constructor

	name = "noname";

	// Assigns every element of dice with 0
	for (int i = 0; i < NUM_DICE; ++i) {
		dice[i] = 0;
	}
}

void Player::setName(string userName) {
	name = userName;
}

string Player::getName() {
	return name;
}

void Player::setPlayerNum(int num) {
	playerNum = num;
}

int Player::getPlayerNum() {
	return playerNum;
}

int Player::countDice(int n) {
	// Returns number of dice player has that equal n
	int counter = 0;
	for (int i = 0; i < NUM_DICE; ++i) {
		if (dice[i] == n) {
			++counter;
		}
	}
	return counter;
}

void Player::rollDice() {
	// Generates 5 random numbers in range 1-6 for player's dice
	// Assigns numbers to dice array
	int result;
	for (int i = 0; i < NUM_DICE; ++i) {
		result = rand() % 6 + 1;
		dice[i] = result;
	}
}

void Player::printOneDie(int val) {
	// Prints a die with val dots

	//Top
	cout << "---------" << endl;

	// First row
	if (val == 2 || val == 3) {
		cout << "|  o    |";
	}
	else if (val == 4 || val == 5 || val == 6) {
		cout << "| o   o |";
	}
	else {
		cout << "|       |";
	}
	cout << endl;

	// Second row
	if (val == 1 || val == 3 || val == 5) {
		cout << "|   o   |";
	}
	else if (val == 6) {
		cout << "| o   o |";
	}
	else {
		cout << "|       |";
	}
	cout << endl;

	// Third row
	if (val == 2 || val == 3) {
		cout << "|    o  |";
	}
	else if (val == 4 || val == 5 || val == 6) {
		cout << "| o   o |";
	}
	else {
		cout << "|       |";
	}
	cout << endl;

	//Bottom
	cout << "---------" << endl;

}

void Player::printAllDice() {
	// Prints a die for each element in dice array
	for (int i = 0; i < NUM_DICE; ++i) {
		printOneDie(dice[i]);
	}
}