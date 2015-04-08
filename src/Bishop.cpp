#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include "Piece.h"
#include "Piece.cpp"
using namespace std;

Bishop::Bishop() : Piece(){

}

Bishop::Bishop() : Piece(bool white, int positionX, int positionY){
		this->type = 1 //Bishop
		move.push_back() = 0;
		move.push_back() = 0;
		this->position[0] = positionX;	//X Location
		this->position[1] = positionY;	//Y location
		this->sprite = "BishopPics";	//Ask Darien
		this->white = white;
		this->dead = false;
	}

virtual void Bishop::movePiece(){

		if(abs(move[0] - position[0]) == abs(move[1] - position[1]){
			if(collision()){
				position[0] = move[0];
				position[1] = move[1];
			}
		}

		else cout<<"Brahhhhhhhhhhh you can't move dat";
} 

int Bishop::getType(){
		return type;
	}