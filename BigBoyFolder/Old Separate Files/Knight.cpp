#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include "Piece.h"
#include "Piece.cpp"
using namespace std;

void Knight::movePiece(){

	if(move[0] != position[0] && move[1] != position[1]){	//checks if user has set move to current space
		int moveSpaceHor = move[0] - position[0];
		int moveSpaceVer = move[1] - position[1];
		
		if(!collisionPath()){				//if there is NOT an object in its path
			if((abs(moveSpaceHor == 1 || moveSpaceHor == 2)) && abs(moveSpaceHor) + abs(moveSpaceVer) == 3){
				if(collisionAttack()){		//checks if there IS an object in that space
					kill(move);					//kills the opposing object
				}
					position[0] = move[0];		//occupies the space
					position[1] = move[1];
	
			}else{
				cout << "Invalid movement children";	
			}
		}
	}

	else cout<<"That is the spot you are currently in";		//Most likely simply ignore
} 

int Knight::getType(){
		return type;
	}
