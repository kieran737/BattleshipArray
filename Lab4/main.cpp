/*-----------------------------------------------------------------------------

Name: Kieran Hodge

Date: 29.01.2015

Lab number: 4

--------------------------------------------------------------------------------
Program Description: This Program is a Battleship game that will allow the user
to have 5 attempts at a 3 x 3 grid game, a set of coordinates will be generated
by the computer, the user will need to input 2 numbers (grid coordinates) within
each of their attempts and at the end of the game the user will be prompted to 
restart the program if they wish.
--------------------------------------------------------------------------------*/
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <windows.h>
#include <iomanip>
#include <string>

using namespace std;

const int ROWS = 3;
const int COLS = 3;
string validationString;
int shipSize = 2;


void printBoard(char board[][COLS]) {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			cout << board[i][j];
		}
		cout << endl;
	}
	return;
}
void generateShip(char board[][COLS], int shipSize) {
	int row,col,ort;
	//generates the ship in a certain part of the row and column
Randomize:
	do {
		row = rand()%ROWS;
		col = rand()%COLS;
		ort = rand()%2;
	} while (board[row][col] == 'S');

	if (ort == 0) {
		//Makes sure that the ship does not go outside of the playing board
		while (col + shipSize >= COLS) {
			col = rand()%COLS;
		}
		//If the above is correct then it will generate the ship
		for (int j = col; j < col + shipSize; j++) {			
			board[row][col] = 'S';
		}
	}
	//ship orientation
	if (ort == 1) {
		while (row + shipSize >= ROWS) {
			row = rand()%ROWS;
		}
		for (int i = row; i < row + shipSize; i++) {
			if (board[i][col] == 'S')
				goto Randomize;
		}
		for (int i = row; i < row + shipSize; i++) {
			board[i][col] = 'S';
		}
	}
	return;
}
//Checking to see if user has hit the ship
void checkBoard(char board[][COLS], bool &victory) {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (board[i][j] == 'S')
				victory = false;
		}
	}
}

int main(void) {
	//Starts restart Loop
	while (true) {
		srand(time(NULL));
		char board[ROWS][COLS], playerBoard[ROWS][COLS];
		//Creates board
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				board[i][j] = '.';
				playerBoard[i][j] = '.'; 	
			}

		}
		//Start of program
		cout << setw (50) << "Battleship Array! " <<endl; 
		int ship = 1;
		//Generates the ship and defines the size of the ship
		for (int i = 1; i <= ship; i++) {
			generateShip(board, shipSize);
		}
		//Instrustions / tutorial
		int attempts = 5, rowGuess, columnGuess;
		bool victory = false;
		cout << endl;
		cout << setw (46) << "INSTRUCTIONS" << endl;
		cout << setw (64) <<"You only have 5 guesses to find out where the" << endl;
		cout << setw (64) <<"enemy ship is, the grid is 3 x 3, This is how" << endl;
		cout << setw (63) << "you enter your coordinates into the grid:" << endl << endl;
		cout << setw (48) <<"[1 1][1 2][1 3]" << endl;
		cout << setw (48) <<"[2 1][2 2][2 3]" << endl;
		cout << setw (48) <<"[3 1][3 2][3 3]" << endl << endl;
		cout << setw (62) <<"Remember to put a space between the numbers" << endl;
		cout << setw (64) <<"each bracket is equal to one square on the grid" << endl;
		system ("pause");
		//checks to see if the player has any attempts left, decides whether the player has won or lost
		system("CLS");

		for (int n = 1; n <= attempts && !victory; n++) {		
			printBoard(playerBoard);
			system ("color 07");
			cout << "\nAttempt #" << n << ", Row and Column: ";
			cin >> rowGuess >> columnGuess;	
			cin.ignore();
			while (cin.fail())
			{
				cin.clear();
				getline (cin, validationString);
				system ("color 04");
				cout << "Invalid Input, Please Enter a Numeric Value: ", cin >> rowGuess >> columnGuess;
			}
			if (board[rowGuess - 1][columnGuess - 1] == 'S') {
				cout << "You made a hit!\n";
				system ("color 02");
				Sleep (1000);
				board[rowGuess - 1][columnGuess - 1] = '*';
				playerBoard[rowGuess - 1][columnGuess - 1] = '*';
			}
			else if (board[rowGuess - 1][columnGuess - 1] == '.') {
				cout << "You missed.\n";
				system ("color 04");
				Sleep (1000);
				board[rowGuess - 1][columnGuess - 1] = 'o';
				playerBoard[rowGuess - 1][columnGuess - 1] = 'o';
			}
			victory = true;
			checkBoard(board, victory);
		}
		//Results
		system ("CLS");
		cout << "\n\n\n\n";
		cout << setw (46) << "Results: " << endl;
		printBoard(board);
		cout << "A  \".\" is open sea." << endl;
		cout << "An \"*\" is a hit on the enemy battleship." << endl;
		cout << "An \"S\" is the surviving enemy battleship." << endl;
		cout << "An \"o\" is a missed attempt." << endl << endl;
		if (victory)
		{
			system ("color 02");
			Sleep (1000);
			cout << setw (64) <<"Congratulations, you sunk the enemy battleship!" << endl << endl;
		}
		else
		{
			system ("color 04");
			Sleep (1000);
			cout << setw (59) <<"You didn't sink the enemy battleship" << endl << endl;	

		}
		//Restart Loop
		char answer;
		while(true) { 

			system ("color 07");
			cout << setw (60) << "Would you like to play again (y/n)\n ";
			cin >> answer;
			if(answer == 'y' || answer == 'Y' || answer == 'n'|| answer == 'N') {
				system ("cls");
				break;
			}
			else
				system ("color 04");
			cout << setw (47) << "Invalid input\n\n";
			Sleep (500);
		}
		if (answer == 'n' || answer == 'N') {
			system ("color 05");
			cout << "\n\n\n\n\n\n";
			cout << setw (60) << "Thank you for playing, See you next time!";
			Sleep (2000);
			break;
		}
	}
}