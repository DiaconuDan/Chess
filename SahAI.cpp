// SahAI.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

string game = "running", winner;
char M[9][9];
char player='X', computer='0';
int sizee, PeonMovements[10], playerPeonsCount = 8;
int sizeeComputer, ComputerPeonMovements[10], computerPeonsCount = 8;
char ComputerPeonsLine[10], ComputerPeonColumn[10];



// ---------------------------------------- CHESS TABLE FUNCTIONS --------------------------------- //

void CreateChessTable()
{
	for ( int i = 1 ; i <= 8; i++)
		for (int j = 1; j <= 8; j++)
		{
			if (i != 8 && i != 1) { M[i][j] = '.'; }
			else
			{
				if (i == 1) { M[i][j] = 'X'; }
				if (i == 8) { M[i][j] = '0'; }
			}
		}
}

void PrintChessTable()
{
	cout << "- ";
	for (int i = 1; i <= 8; i++) { cout << i << " "; }
	cout << '\n';
	for (int i = 1; i <= 8; i++)
	{
		cout << i << " ";
		for (int j = 1; j <= 8; j++)
		{
			cout << M[i][j] << " ";
		}
		cout << '\n';
	}
	cout << '\n';
}


// ---------------------------------------- PLAYER ------------------------------------------------ //

int ValidPeon(int line, int column)
{
	// IF he can move forward

	if (M[line][column] != player) return 0; // we can't move a free space or a computer peon

	int ok = 0;
	


	if (M[line + 1][column] == '.' ) // move forward, space free
	{
		PeonMovements[0] = line + 1;
		PeonMovements[1] = column;
		sizee += 2;
		ok = 1;
	}
	if (M[line + 1][column - 1] == computer) // eat left
	{
		PeonMovements[2] = line + 1;
		PeonMovements[3] = column - 1;
		sizee += 2;
		ok = 1;
	}
	if (M[line + 1][column + 1] == computer)
	{
		sizee += 2;
		PeonMovements[4] = line + 1;
		PeonMovements[5] = column + 1;
		ok = 1;
	}
	
	return ok;
}


int ValidMove(int PeonLine, int PeonColumn, int MoveLine, int MoveColumn)
{
	if ( PeonLine == 1 && MoveLine == 3 && M[MoveLine][MoveColumn] == '.') return 1 ; // este valida si mutarea unui prim pion cu 2 
	int i = 0;
	while (i < sizee)
	{
		if (PeonMovements[i] == MoveLine && PeonMovements[i + 1] == MoveColumn)
		{
			sizee = 0;
			return 1;
		}
		i = i + 2;
	}
	
	return 0;
}


void PlayerMove()
{
	int MoveLine, MoveColumn;
	cout << '\n';
	cout << "Player turn now. " << '\n';
	int PeonLine, PeonColumn, ok=0;
	
	while( ok == 0)
	{
		cout << "Peon to move: ";
		cin >> PeonLine >> PeonColumn;
		ok = ValidPeon(PeonLine, PeonColumn);
		if ( ok == 0)
		{
			cout << "Not a valid Peon. Insert a valid one " << '\n' ;
		}
	}

	ok = 0;
	while (ok == 0)
	{
		cout << "Place to move the peon: ";
		cin >> MoveLine >> MoveColumn;
		ok = ValidMove(PeonLine, PeonColumn, MoveLine, MoveColumn);
		if (ok == 0)
		{
			cout << "You can't go there. Insert a valid move" << '\n';
		}
	}

	if (M[MoveLine][MoveColumn] == computer)
	{
		computerPeonsCount--;
		M[PeonLine][PeonColumn] = '.';
		M[MoveLine][MoveColumn] = player;
	}
	else
		if (M[MoveLine][MoveColumn] == '.')
		{
			M[PeonLine][PeonColumn] = '.';
			M[MoveLine][MoveColumn] = player;
		}
	cout << '\n';
	cout << '\n';
}

// ---------------------------------------- COMPUTER ------------------------------------------------ //



int ComputerValidPeon(int line, int column)
{
	// IF he can move forward
	int ok = 0;

	if (M[line][column] != computer ) return 0; // we can't move a free space or a player peon

	if (M[line - 1][column] == '.')
	{
		ComputerPeonMovements[0] = line - 1;
		ComputerPeonMovements[1] = column;
		sizeeComputer += 2;
		ok = 1;
	}
	if (M[line - 1][column - 1] == player)
	{
		ComputerPeonMovements[2] = line - 1;
		ComputerPeonMovements[3] = column - 1;
		sizeeComputer += 2;
		ok = 1;
	}
	if (M[line - 1][column + 1] == player)
	{
		sizeeComputer += 2;
		ComputerPeonMovements[4] = line - 1;
		ComputerPeonMovements[5] = column + 1;
		ok = 1;
	}

	return ok;
}


int ComputerValidMove(int PeonLine, int PeonColumn, int MoveLine, int MoveColumn)
{
	if (PeonLine == 1 && MoveLine == 3 && M[MoveLine][MoveColumn] == '.') return 1; // este valida si mutarea unui prim pion cu 2 
	int i = 0;
	while (i < sizeeComputer)
	{
		if (ComputerPeonMovements[i] == MoveLine &&  ComputerPeonMovements[i + 1] == MoveColumn)
		{
			sizeeComputer = 0;
			return 1;
		}
		i = i + 2;
	}
	return 0;
}


void createComputerPeonsArray()
{
	int count = 0;
	for (int i = 1; i <= 8; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			if (M[i][j] == computer)
			{
				count++;
				ComputerPeonsLine[count] = i;
				ComputerPeonColumn[count] = j;
			}
		}
	}
}

void EasyComputerMove()
{
	int randomPeon, randomMove;
	int MoveLine, MoveColumn;
	cout << '\n';
	cout << "Computer turn now. " << '\n';
	int PeonLine, PeonColumn, ok = 0;

	while (ok == 0)
	{
		
		createComputerPeonsArray();
		randomPeon = rand() % computerPeonsCount + 1;
		
		PeonLine = ComputerPeonsLine[randomPeon];
		PeonColumn = ComputerPeonColumn[randomPeon];
		
		ok = ComputerValidPeon(PeonLine, PeonColumn);
	
	}

	ok = 0;
	while (ok == 0)
	{
		randomMove = rand() % 3 + 1;
		if ( randomMove == 1 ) // make 1 step forward to free space (DOT)
		{
			MoveLine = PeonLine - 1;
			MoveColumn = PeonColumn;
		}
		if (randomMove == 2) // EAT PLAYER PEON from left
		{
			MoveLine = PeonLine - 1;
			MoveColumn = PeonColumn-1;
		}
		if (randomMove == 3) // EAT PLAYER PEON from right
		{
			MoveLine = PeonLine - 1;
			MoveColumn = PeonColumn + 1;
		}
	
		ok = ComputerValidMove(PeonLine, PeonColumn, MoveLine, MoveColumn);
	}

	if (M[MoveLine][MoveColumn] == player)
	{
		playerPeonsCount--;
		M[PeonLine][PeonColumn] = '.';
		M[MoveLine][MoveColumn] = computer;
	}
	else
		if (M[MoveLine][MoveColumn] == '.')
		{
			M[PeonLine][PeonColumn] = '.';
			M[MoveLine][MoveColumn] = computer;
		}
}




// ---------------------------------------------------------------  CHECK FINAL TABLE SITUATION --------------------------------

bool NewMovesExistance()
{
	for (int i = 1; i <= 8; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			if (M[i][j] != '.')
			{
				if (ValidPeon(i, j) == 1) { return true; }
			}
		}
	}
	return false;
}


void CheckGameStatus()
{
	for (int i = 1; i <= 8; i++) // if there is a peon on last position
	{
		if (M[1][i] == '0') { game = "finished"; winner = "computer"; }
		if (M[8][i] == 'X') { game = "finished"; winner = "player"; }
	}

	if (computerPeonsCount == 0) { game = "finished"; winner = "player"; }
	if (playerPeonsCount == 0) { game = "finished"; winner = "computer"; }

	if (NewMovesExistance() == false)
	{
		game = "finished";
		winner = "draw";
	}

}



void PrintMatchResult()
{
	if (winner == "player")
	{
		cout << '\n';
		cout << "GREAT JOB! Player has destroyed the easy random computer!";
	}
	if (winner == "computer")
	{
		cout << '\n';
		cout << "SORRY! But the easy random computer beat you!";
	}
	if (winner == "Draw")
	{
		cout << '\n';
		cout << "DRAW! Try your luck next time against the easy random computer!";
	}
}


// --------------------------------------- MAIN ------------------------------------------------------- //

int main()
{
	int PlayerOrComputer=0;
	string PlayerCommand="play";

	srand(time(NULL));
	PlayerOrComputer = rand() % 2;
	CreateChessTable();

	if (PlayerOrComputer == 0) { cout << '\n'<<  "Player starts" << '\n'; }
	else
		cout << "Computer starts";
	int k = 0;
	PrintChessTable();
	while (game != "finished" )
	{
		
		if (PlayerOrComputer == 0)
		{
			PlayerMove();
			sizee = 0;
			PlayerOrComputer = 1;
		}
		else
		{
			EasyComputerMove();
			sizeeComputer = 0;
			PlayerOrComputer = 0;
		}
		PrintChessTable();
		CheckGameStatus();

	
	}
	PrintMatchResult();
	cin >> PlayerOrComputer; // altfel, programul se inchide instant si nu vezi ce rezultat afiseaza
    return 0;
}

