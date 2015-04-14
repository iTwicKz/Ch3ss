#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "pieceTest.h"


using namespace std;

int main()
{

	Piece* pieceArray[32];

	

	for(int index = 0; index < 32; index++)	//creating pawns
	{	
		if(index < 8)
			pieceArray[index] = new Pawn(true, index, 6);	//white pawns
		else if(index < 16)
			pieceArray[index] = new Pawn(false, index - 7, 1);	//black pawns
		else if(index < 20)
		{
			if(index % 2 == 0)
				pieceArray[index] = new Bishop(true, (3*((index/2)-7))-1, 7);		//white bishops
			else
				pieceArray[index] = new Bishop(false, (3*(((index-1)/2)-7))-1, 0);	//black bishops
		}
		else if(index < 24)
		{
			if(index % 2 == 0)
				pieceArray[index] = new Knight(true, (5*((index/2)-10)) + 1 , 7);		//white knight
			else
				pieceArray[index] = new Knight(false, (5*(((index-1)/2)-10)) + 1 , 0);	//black knight
		}
		else if(index < 28)
		{
			if(index % 2 == 0)
				pieceArray[index] = new Rook(true, (7*((index/2)-12)), 7);		//white knight
			else
				pieceArray[index] = new Rook(false, (7*(((index-1)/2)-12)), 0);		//black knight
		}
	}




	



	Pawn pawn1(true, 0, 0);
	
	cout << pawn.getType() << endl;
	
	Bishop bishop(false, 0, 0);
	
	cout << bishop.getType() << endl;
	
	Knight knight(true, 0, 0);
	
	cout << knight.getType() << endl;
	
	Rook rook(false, 0, 0);
	
	cout << rook.getType() << endl;
	
	Queen queen(true, 0, 0);
	
	cout << queen.getType() << endl;
	
	King king(false, 0, 0);
	
	cout << king.getType() << endl;
	
	
	boolean canMove = false;

	switch(type){
		case: 0{
			pawn
		}
	}
	
	return 0;
}
