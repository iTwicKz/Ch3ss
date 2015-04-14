#include <iostream>
#include "pieceTest.h"

using namespace std;



bool Pawn::passant(){	
	
	int  board[8][8];										    //en passant
	int moveSpacesHor = move[0] - position[0];
	int moveSpacesVer = move[1] - position[1];
	bool free = true;
																   //store previous move
	bool firstMoved;											  //check if pawn moved 2 spaces
	
	if ((moveSpacesVer = 0) && (moveSpacesHor > 0)) { 			 //checks right 
			     
		if (moveSpacesHor == moveSpacesVer && moveSpacesHor > 0) {	
			for ( int i = 1; i<abs(moveSpacesHor); i++) {
				if (board[position[0] + i][position[1] + i] != 153) {
					free = false;
				}
			}
		}
			
	} else if ((moveSpacesVer = 0) && (moveSpacesHor < 0)) {  //checks left
		
		
		
		}
	
	return free;
	
}




