#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include "piece.h"
#include "collision.cpp"

using namespace std;
int* Pawn::movePiece(int x, int y){

		int *returnPosition = new int[2];

		int val1 = -1;
		int val2 = -2;
		
		if(white){
			val1 = abs(val1);
			val2 = abs(val2);
		}
	if(move[0] != position[0] && move[1] != position[1]){	//checks if user has set move to current space
		if(firstMoved && move[1] - position[1] == val2 && position[0] == move[0]){
			firstMoved = false;			//marks that the object has moved
			if(!collision(move, position)){			//if there is NOT an object in its path
				position[0] = move[0];		//occupies space
				position[1] = move[1];
			}
		}
		else if(move[1] - position[1] == val1 && position[0] == move[0]){
			firstMoved = false;			//marks that the object has moved
			if(!collision(move, position)){		//if there is NOT an object in its path
				position[0] = move[0];		//occupies space
				position[1] = move[1];
			}
		}
		else if(move[1] - position[1] == val1 && abs(move[1] - position[1]) == 1){
			if(collision(move, position)){		//checks if there IS an object in that space
				firstMoved = false;			//marks that the object has moved
				//kill(move);					//kills the opposing object
				position[0] = move[0];		//occupies the space
				position[1] = move[1];
			}
		}
		else cout<<"Brahhhhhhhhhhh you can't move dat";
		

		
		
		
	}
	else cout<<"That is the spot you are currently in";		//Most likely simply ignore

		int end = 0;			//set opposing board row location for black
		if(white) end = 7;		//set opposing board row location for white
		if(position[1] == end) transformer();
		
		//put en passat VW in here
		
		
	returnPosition[0] = move[0];
	returnPosition[1] = move[1];
	
	return returnPosition;
		
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
