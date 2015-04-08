#include <string>
#include <vector>
#include <iostream>
#include "Piece.h"

using namespace std;

//Piece::Piece(void){}

//Piece::~Piece(void){}


void Piece::movePiece(){
	cout<<"";
};

void Piece::parseMove(string position){		//desired move format = A1 <= desiredMove <= H8
		
	bool invalidString = true;
	if(position.size() == 2){
		if((position.at(0) >= 65 && position.at(0) <= 72) || 
			(position.at(0) >= 97 && position.at(0) <= 104)){
			if(position.at(1) >= 49 && position.at(1) <= 56){
				invalidString = false;
				char x = toupper(position.at(0));
				move[0] = static_cast<int>(x) - 65;
				move[1] = position.at(1) - '0' - 1;
				movePiece();
			}
		}
	}
	if(!invalidString){
		cout << "You suck. Think about it";
	}
		
}

vector<int> Piece::getPosition(){
		return position;
}

void Piece::died(){
		dead = true;
}

int Piece::getType(){
	return type;
}

bool Piece::getWhite(){
	return white;
}

bool Piece::getDead(){
	return dead;
}

int main(){
	Piece *pawn1 = new Pawn(true, 0, 0);
}