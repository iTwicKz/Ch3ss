#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include "Piece.h"
#include "Piece.cpp"
using namespace std;

void Bishop::movePiece(){

	if(move[0] != position[0] && move[1] != position[1]){
		if(abs(move[0] - position[0]) == abs(move[1] - position[1])){
			if(collisionPath()){			//checks if there are any paths in the piece's path
				if(collisionAttack()){		//checks if there is an object in move destination	
					kill(move);					//kills opposing piece if so
				}
				position[0] = move[0];		//occupies the spot
				position[1] = move[1];
			}
		}
	}

	else cout<<"Brahhhhhhhhhhh you can't move dat";
} 

int Bishop::getType(){
		return type;
	}