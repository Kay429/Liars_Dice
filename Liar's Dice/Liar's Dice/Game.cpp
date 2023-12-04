#include "Game.h"

void Game::runGame() {

	string userString;

	srand(time(0)); // Seed the RNG

	printRules();
	obtainNumPlayers();
	initializePlayers();

	// Clear out cin before obtaining names
	cin.clear();
	cin.ignore(100, '\n');

	// Roll dice and obtain name for each player
	for (int i = 0; i < numPlayers; ++i) {
		cout << "What is the name of player " << i + 1 << "?" << endl;
		getline(cin, userString); 
		// Error documentation:
		// I had some trouble with the first player's name being set to whitespace. 
		// To fix this, I added some code to clear out cin
		// before using getline
		playersVector[i]->setName(userString);
		playersVector[i]->rollDice();
	}

	cout << endl << endl;

	// runTurn() for each player until gameOver
	while (!gameOver) {
		for (int i = 0; i < numPlayers; ++i) {
			runTurn(playersVector[i]);
			if (gameOver) {
				break;
			}
		}
	}

}

void Game::printRules() {
	//Reads rules for the game from "Game Rules.txt" and prints them.

	string currLine;

	ifstream rules("Game Rules.txt");

	while (getline(rules, currLine)) {
		cout << currLine << endl;
	}
	cout << endl << endl;
	rules.close();

}

void Game::obtainNumPlayers() {
	// Recieves and validates user input
	// then assigns user input to numPlayers

	int userInput = 0;
	cout << "How many players?" << endl;
	do {
		cout << "There must be 2 or more." << endl;
		cin >> userInput;
		if (!cin) {
			// If user entered a string, clears out cin
			cin.clear();
			cin.ignore(100, '\n');
		}
	} while (userInput < 2);

	numPlayers = userInput;
}

void Game::initializePlayers() {
	// Creates numPlayers Player objects and appends them to playersVector
	// Also sets playerNum for each object
	for (int i = 0; i < numPlayers; ++i) {
		playersVector.push_back(new Player);
		playersVector[i]->setPlayerNum(i);
	}
}

void Game::obtainGuess() {
	// Recieves and validates user input for a 2 number guess
	// then updates currGuess with user input

	int firstNum = 0;
	int secondNum = 0;

	// First number
	do {
		cout << "How many dice?" << endl;
		cin >> firstNum;
		if (!cin) {
			// If user entered a string, clears out cin
			cin.clear();
			cin.ignore(100, '\n');
		}
		if (firstNum <= lastGuess) {
			cout << "Your guess must be higher than the last one." << endl;
			cout << "The last guess was " << lastGuess << endl;
		}
	} while (firstNum < 1 || firstNum <= lastGuess); 

	lastGuess = firstNum; // Update lastGuess

	// Second number
	do {
		cout << "What number is on the dice?" << endl;
		cin >> secondNum;
		if (!cin) {
			// If user entered a string, clears out cin
			cin.clear();
			cin.ignore(100, '\n');
		}
		if (secondNum < 1 || secondNum > 6) {
			cout << "Please input a number between 1 and 6" << endl;
		}
	} while (secondNum < 1 || secondNum > 6);

	// Assign values to currGuess
	currGuess[0] = firstNum;
	currGuess[1] = secondNum;
}

bool Game::evaluateGuess() {
	// Determines whether guess is correct or not
	// and returns a boolean based on whether the guess is true or false
	// The guess is true if firstNum is <= the number of dice with secondNum

	int count = 0;
	int firstNum = currGuess[0];
	int secondNum = currGuess[1];

	// Determine the number of dice with secondNum for each player
    // and total them up in count
	for (int i = 0; i < numPlayers; ++i) {
		count += playersVector[i]->countDice(secondNum);
	}
	return (count >= firstNum); 
	// Error Documentation:
	// At first I required count to be equal to firstNum,
	// This was causing the game to be difficult
	// to win.
	// I found the issue by starting in the method
	// that outputs the win statement and working
	// my way backwards until I found the problem.
}

void Game::printPlayerList() {
	//Prints out the elements of playersVector
	for (int i = 0; i < numPlayers; ++i) {
		cout << "Player " << i + 1 << " : " << playersVector[i]->getName() << endl;
	}
}

void Game::callLiar(int playerNum) {
	// Gives option for a player to call liar
	// If user agrees that someone would like to call liar,
	// a list of players is displayed and the user must confirm
	// who called liar.
	// The indices of both the guesser and accuser are passed
	// to endGame.

	string userInput;
	int userNum;

	do {
		cout << "Would someone like to call liar? (y/n)" << endl;
		cin >> userInput;
	} while (userInput != "n" && userInput != "y");

	if (userInput == "y") {
		cout << "Which player called liar?" << endl;
		printPlayerList();
		do {
			cout << "Enter a number from the list." << endl;
			cin >> userNum;
			if (!cin) {
				// If user entered a string, clears out cin
				cin.clear();
				cin.ignore(100, '\n');
			}
			if (userNum == playerNum + 1) {
				// Makes sure the player number entered does not match playerNum
				cout << "You cannot call yourself out!" << endl;
			}
		} while (userNum < 1 || userNum > numPlayers || userNum == playerNum + 1);

		endGame(playerNum, userNum - 1);
	}
}

void Game::endGame(int player1Num, int player2Num) {
	// Calls evaluateGuess() and prints message describing who won

	cout << endl;
	if (evaluateGuess()) {
		cout << playersVector[player1Num]->getName();
		cout << " guessed correctly!" << endl;
		cout << "You are the winner! Congratulations!" << endl;
	}
	else {
		cout << playersVector[player1Num]->getName();
		cout << " was lying!" << endl;
		cout << "That means " << playersVector[player2Num]->getName();
		cout << " is the winner! Congratulations!" << endl;
	}

	gameOver = true;
}

void Game::runTurn(Player* currPlayer) {
	// Print's currPlayer's dice
	// Obtains currPlayer's guess
	// Then allows other players to call liar
	cout << currPlayer->getName() << "'s turn!" << endl;
	currPlayer->printAllDice();
	cout << "Time to guess!" << endl;
	obtainGuess();
	callLiar(currPlayer->getPlayerNum());
}