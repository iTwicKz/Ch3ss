#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include "Piece.h"
#include "Piece.cpp"
using namespace std;

void Queen::movePiece() {

	if(move[0] != position[0] && move[1] != position[1]){	//checks if user has set move to current space
		int moveSpacesHor = move[0] - position[0];
		int moveSpacesVer = move[1] - position[1];
		
		if(collisionPath()){			//checks if there are any paths in the piece's path
			if( moveSpacesHor!=0 && move[1] == position[1]) {
				if(collisionAttack()){		//checks if there is an object in move destination	
					kill(move);					//kills opposing piece if so
				}
					position[0] = move[0];		//occupies the spot
					position[1] = move[1];
				
			} else if( moveSpacesVer !=0 && move[0] == position[0]) {
				if(collisionAttack()){		//checks if there is an object in move destination	
					kill(move);					//kills opposing piece if so
				}
					position[0] = move[0];		//occupies the spot
					position[1] = move[1];
				
			} else if( abs(moveSpacesHor) == abs(moveSpacesVer)) {
				if(collisionAttack()){		//checks if there is an object in move destination	
					kill(move);					//kills opposing piece if so
				}
					position[0] = move[0];		//occupies the spot
					position[1] = move[1];
				
			} else cout<<"Brahhhhhhhhhhh you can't move dat";

		} else cout<<"There's an object in your path";	
	}
}

int Queen::getType(){
	return type;
}