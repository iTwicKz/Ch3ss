#include <string>
#include <vector>
#include <iostream>
#include "Piece.h"
#include "Piece.cpp"
using namespace std;

Knight::Knight() : Piece (bool white, int positionX, int positionY){
		this->type = 2; //Knight
		this->move[0] = 0;
		this->move[1] = 0;
		this->position[0] = positionX;	//X Location
		this->position[1] = positionY;	//Y location
		this->sprite = "KnightPics";	//Ask Darien
		this->white = white;
		this->dead = false;

		this->firstMoved = true;
	}

void Knight::move(){

		int moveSpaceHor = move[0] - position[0];
		int moveSpaceVer = move[1] - position[1];
		
		if((abs(moveSpaceHor == 1 || moveSpaceHor == 2)) && abs(moveSpaceHor + moveSpaceVer) == 3){
			
			position[0] = move[0];
			position[1] = move[1];
			
			}else{
				
			cout << "Invalid movement children";
			
			
				};
		

		collisionDetect();
} 

int Knight::getType(){
		return type;
	}
