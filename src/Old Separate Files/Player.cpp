#include <cmath> 
#include <string>
#include <iostream>
#include <vector>

//#include "pawn.cpp"
//#include "collision.cpp"
//#include "Board.cpp"
//#include "piece.h"
//#include "piece.cpp"

#define BLANK 0
#define WHITEKING 1
#define WHITEQUEEN 2
#define WHITEKNIGHT 3
#define WHITEBISHOP 4
#define WHITEROOK 5
#define WHITEPAWN 6
#define BLACKKING 7
#define BLACKQUEEN 8
#define BLACKKNIGHT 9
#define BLACKBISHOP 10
#define BLACKROOK 11
#define BLACKPAWN 12




using namespace std;

class Player
{
	private:
		int color; //0 = white, 1 = black
		bool check;
		bool checkmate;
	
	
	public:
		Player(int chosenColor);
		int getColor();
		bool getCheck();
		bool getCheckmate();
		bool isCheck(int x, int y);
		
};


Player::Player(int chosenColor)
{
	color = chosenColor;
	check = false;
	checkmate = false;
}

int Player::getColor()
{
	return color;
}

bool Player::getCheck()
{
	return check;
}

bool Player::getCheckmate()
{
	return checkmate;
}

bool Player::isCheck(int x, int y)
{
	//kings position --
	//pos of move
	//checks all pieces moves if collides into kings pos
	//if in check, checks kings valid move options
	//checks to see if new valid spots are also "in check"
	
	
	
	if(color == 0) //white player
	{
		int pieceLocations[7][7];
		vector<int>kingPosition;
	
		for(int i = 0; i < 8; i++)
		{
			for(int j = 0; j < 8; j++)
			{
				pieceLocations[i][j] == returnpiece(i, j);
				if(pieceLocations[i][j] == 1)
				{
					kingPosition.push_back(i);
					kingPosition.push_back(j);
				}
			}
		}
		
		
		
	}
	else //black player
	{
		
	}
	
	
}
