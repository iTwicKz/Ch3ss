#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include "Piece.h"
#include "Piece.cpp"
using namespace std;
	
void Rook::movePiece() {

	if(move[0] != position[0] && move[1] != position[1]){	//checks if user has set move to current space
		int moveSpacesHor = move[0] - position[0];
		int moveSpacesVer = move[1] - position[1];
		
		if(!collisionPath()){				//if there is NOT an object in its path
			if( moveSpacesHor!=0 && move[1] == position[1]) {
				if(collisionAttack()){
					kill(move);
				}
				position[0] = move[0];
				position[1] = move[1];
				firstMoved = false;
				
			} else if( moveSpacesVer !=0 && move[0] == position[0]) {
				if( collisionAttack() ) {
					kill(move);
				}
				position[0] = move[0];
				position[1] = move[1];
				firstMoved = false;
				
			} else cout<<"Brahhhhhhhhhhh you can't move dat";
			//Work on castling	
		}
	}

	else cout<<"That is the spot you are currently in";		//Most likely simply ignore

}

int Rook::getType(){
	return type;
}