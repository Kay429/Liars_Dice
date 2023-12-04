
// Liar's Dice
// By Kayleigh Kinsey

// This is a text-based version of the game Liar's Dice. (Rules for the game are in "Game Rules.txt")
// In this game, the user enters the number of players and a name for each player.
// The program will then roll each player's dice and the game can begin.
// On a player's turn, they will be shown their dice and asked to make a guess.
// The player must guess higher than the last player.
// Once the guess has been made, another player may call the first a liar.
// If someone chooses to call liar, the game ends.
// If the first player was lying, the one that called them out wins.
// If the first player was correct, then they win.
// The program will determine the winner and print a congratulations message.


#include "Game.h"

int main(){
	
	Game game;

	game.runGame();

	return 0;
}