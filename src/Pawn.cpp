#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include "Piece.h"
#include "Piece.cpp"
using namespace std;

Pawn::Pawn(bool none) : Piece(bool white, int positionX, int positionY){
		this->type = 0 //Pawn
		move.push_back() = 0;
		move.push_back() = 0;
		this->position[0] = positionX;	//X Location
		this->position[1] = positionY;	//Y location
		this->sprite = "PawnPics";	//Ask Darien
		this->white = white;
		this->dead = false;

		this->firstMoved = true;
	}

virtual void Pawn::movePiece(){

		int val1 = -1;
		int val2 = -2;
		
		if(white){
			val1 = abs(val1);
			val2 = abs(val2);
		}
		if(firstMoved && move[1] - position[1] == val2 && position[0] == move[0]){
			firstMoved = false;
			//check collision() to check if it can move there
			//if(collision()){
			position[0] = moved[0];
			position[1] = moved[1];
			//}
		}
		else if(move[1] - position[1] == val1 && position[0] == move[0]){
			firstMoved = false;
			//we can move dat
			if(collision()){
			position[0] = moved[0];
			position[1] = moved[1];
			}
		}
		else if(move[1] - position[1] == val1 && abs(move[1] - position[1]) == 1){
			if(collision()){
				firstMoved = false;
				kill(move);
				position[0] = moved[0];
				position[1] = moved[1];
			}
		}

		int end = 0;			//set end location for black
		if(white) end = 7;		//set end location for white
		if(position[1] == end) transformer();

		//put en passat VW in here
		else cout<<"Brahhhhhhhhhhh you can't move dat";

		collisionDetect();
} 

int Pawn::getType(){
		return type;
	}

void Pawn::transformer(){
		bool chosen = false;
		while (!chosen){
			string option;
			cout << "Who do you want to be: \n Queen, Weenie, Rook, Bishop, Knight, King Weenie!";
			cin >> option;

			string lowerOption = "";
			for(unsigned i = 0; i < option.size(); i++){
				lowerOption += tolower(option.at(i));
			}
			
			if(lowerOption.compare("queen") == 0){
				chosen = true;
				//create a new queen with location = position
			}
			else if(lowerOption.compare("rook") == 0){
				chosen = true;
				//create a new rook with location = position
			}
			else if(lowerOption.compare("bishop") == 0){
				chosen = true;
				//create a new bishop with location = position
			}
			else if(lowerOption.compare("knight") == 0){
				chosen = true;
				//create a new knight with location = position
			}
			else if(lowerOption.compare("king weenie") == 0){
				cout << "ALL HAIL KING WEENIE!!!!!!! but seriously..." << endl;
			}
			else if(lowerOption.compare("weenie") == 0){
				cout << "Oh. Choose another... weenie" << endl;
			}
			else cout << "Sorry. That is not an option. Please choose again" << endl;
		}
	}