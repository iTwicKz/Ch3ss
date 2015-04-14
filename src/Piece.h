//#pragma once

//#ifndef PAWN_H
//#define PAWN_H
#include <vector>
#include <string>
#include <iostream>
#include <cmath>


using namespace std;

class Piece {
	protected:
		int type;					//Queen, King, 	etc.
		//vector<int>move;			//Location
		//vector<int>position;		//Position in 2D Array Gameboard
		int move[2];
		int position[2];
		string sprite;				//Image file link
		bool white;					//black or white
		bool dead;					//on board or not
		//virtual void movePiece() const;
		int blackScore;
		int whiteScore;
		int counterGraveyard;
		

	public:
			Piece(){};
		Piece(bool white, int positionX, int positionY, int type, string sprite){
			this->type = type;
			this->sprite = sprite;
			//move.push_back(0);
			//move.push_back(0);
			move[0] = 0;
			move[1] = 0;
			this->white = white;
			//position.push_back(positionX);
			//position.push_back(positionY); 
			position[0] = positionX;
			position[1] = positionY;
			this->blackScore = 0;
			this->whiteScore = 0;
			//int counterGraveyard = 0;
			
		}
		void movePiece();
		void parseMove(string position);			//Changes from A1 to 00 and H8 to 77, put into move()
		int* getPosition();					//inteact with 2D array, check legal move
		void died();								//determines if piece is taken, mutates bool dead
		int getType();	
		bool getWhite();
		bool getDead();
		//void kill(int move[]);
		bool collision(int move[], int position[]);
		void changeType(int t);
};


class Pawn : public Piece{
	private:
		bool firstMoved;			//checks if pawn has been moved for two move rule

	public:
		Pawn(bool white, int positionX, int positionY, int type = 0, string sprite = "PawnPic") : 
			Piece(white, positionX, positionY, type, sprite){
			firstMoved = true;
		};
		~Pawn(){};
		int* movePiece(int x, int y);	//checks if the move is allowed and if so, mutates position
		int getType();				//returns type of piece
		void transformer();			//once across board, option to change
};


class Bishop : public Piece{

	public:
		Bishop(bool white, int positionX, int positionY, int type = 1, string sprite = "BishopPic") : 
			Piece(white, positionX, positionY, type, sprite){
		};
		~Bishop(){};
		void movePiece();	//checks if the move is allowed and if so, mutates position
		int getType();				//returns type of piece
};

class Knight : public Piece{

	public:
		Knight(bool white, int positionX, int positionY, int type = 2, string sprite = "KnightPic") : 
			Piece(white, positionX, positionY, type, sprite){
		};
		~Knight(){};
		void movePiece();	//checks if the move is allowed and if so, mutates position
		int getType();				//returns type of piece
};

class Rook : public Piece{

	private:
		bool firstMoved;			//checks if rook has been moved for castling rule

	public:
		Rook(bool white, int positionX, int positionY, int type = 3, string sprite = "RookPic") : 
			Piece(white, positionX, positionY, type, sprite){
			firstMoved = true;
		};
		~Rook(){};
		void movePiece();	//checks if the move is allowed and if so, mutates position
		int getType();				//returns type of piece
};

class Queen : public Piece{

	public:
		Queen(bool white, int positionX, int positionY, int type = 4, string sprite = "QueenPic") : 
			Piece(white, positionX, positionY, type, sprite){
		};
		~Queen(){};
		void movePiece();	//checks if the move is allowed and if so, mutates position
		int getType();				//returns type of piece
};

class King : public Piece{
	
	public:
		King(bool white, int positionX, int positionY, int type = 5, string sprite = "KingPic") :
			Piece(white, positionX, positionY, type, sprite){
		};
		~King(){};
		void movePiece();
		int getType();
};

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

int* Piece::getPosition(){
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

void Piece::changeType(int t)
{
	this-> type = t;
}

bool Piece::collision(int move[], int position[]) { //Method that returns free as true or false
	
	int board[8][8];
	
	int moveSpacesHor = move[0] - position[0];
	int moveSpacesVer = move[1] - position[1];
	bool free = true;
	if (abs(moveSpacesHor) == abs(moveSpacesVer)) { //Checks if diagnol
		if (moveSpacesHor == moveSpacesVer && moveSpacesHor > 0) {	//diagnol + +
			for ( int i = 1; i<abs(moveSpacesHor); i++) {
				if (board[position[0] + i][position[1] + i] != 153) {
					free = false;
				}
			}
		} else if (moveSpacesHor == moveSpacesVer && moveSpacesHor < 0) { //diagnol - -
			for ( int i = 1; i<abs(moveSpacesHor); i++) {
				if (board[position[0] - i][position[1] - i] != 153) {
					free = false;
				}
			}
		} else if (abs(moveSpacesHor) == moveSpacesVer) { //diagnol - +
			for ( int i = 1; i<abs(moveSpacesHor); i++) {
				if (board[position[0] - i][position[1] + i] != 153) {
					free = false;
				}
			}
		} else if (moveSpacesHor == abs(moveSpacesVer)) { //diagnol + -
			for ( int i = 1; i<abs(moveSpacesHor); i++) {
				if (board[position[0] + i][position[1] - i] != 153) {
					free = false;
				}
			}
		}
	} else if ((moveSpacesHor = 0) && (moveSpacesVer > 0)) { //Vertical +
		for ( int i = 1; i<moveSpacesVer; i++) {
			if (board[position[0]][position[1] + i] != 153) {
					free = false;
				}
			}
	} else if ((moveSpacesHor = 0) && (moveSpacesVer < 0)) { //Vertical -
		for ( int i = 1; i<abs(moveSpacesVer); i++) {
			if (board[position[0]][position[1] - i] != 153) {
					free = false;
				}
			}
	} else if ((moveSpacesVer = 0) && (moveSpacesHor > 0)) { //Horizontal +
		for ( int i = 1; i<moveSpacesHor; i++) {
			if (board[position[0] + 1][position[1]] != 153) {
					free = false;
				}
			}
	} else if ((moveSpacesVer = 0) && (moveSpacesHor < 0)) { //Horizontal -
		for ( int i = 1; i<abs(moveSpacesHor); i++) {
			if (board[position[0] - 1][position[1]] != 153) {
				free = false;
				}
			}
	}
	return free;
}

/*void Piece::kill(int move[])
{
	addToGraveyard(counterGraveyard, returnpiece(move[0], move[1]);//add to graveyard array
	counterGraveyard++;
}*/

//----------------------------------------------------------------------------------------------------------------
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

//----------------------------------------------------------------------------------------------------------------
void Bishop::movePiece(){

	if(move[0] != position[0] && move[1] != position[1]){	//checks if user has set move to current space
		if(abs(move[0] - position[0]) == abs(move[1] - position[1])){
			if(collision(move, position)){			//checks if there are any paths in the piece's path
				if(collision(move, position)){		//checks if there is an object in move destination	
					//kill(move);					//kills opposing piece if so
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
//----------------------------------------------------------------------------------------------------------------
void Knight::movePiece(){

	if(move[0] != position[0] && move[1] != position[1]){	//checks if user has set move to current space
		int moveSpaceHor = move[0] - position[0];
		int moveSpaceVer = move[1] - position[1];
		
		if(!collision(move, position)){				//if there is NOT an object in its path
			if((abs(moveSpaceHor == 1 || moveSpaceHor == 2)) && abs(moveSpaceHor) + abs(moveSpaceVer) == 3){
				if(collision(move, position)){		//checks if there IS an object in that space
					//kill(move);					//kills the opposing object
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
//----------------------------------------------------------------------------------------------------------------
void Rook::movePiece() {

	if(move[0] != position[0] && move[1] != position[1]){	//checks if user has set move to current space
		int moveSpacesHor = move[0] - position[0];
		int moveSpacesVer = move[1] - position[1];
		
		if(!collision(move, position)){				//if there is NOT an object in its path
			if( moveSpacesHor!=0 && move[1] == position[1]) {
				if(collision(move, position)){
					//kill(move);
				}
				position[0] = move[0];
				position[1] = move[1];
				firstMoved = false;
				
			} else if( moveSpacesVer !=0 && move[0] == position[0]) {
				if( collision(move, position) ) {
					//kill(move);
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
//----------------------------------------------------------------------------------------------------------------
void Queen::movePiece() {

	if(move[0] != position[0] && move[1] != position[1]){	//checks if user has set move to current space
		int moveSpacesHor = move[0] - position[0];
		int moveSpacesVer = move[1] - position[1];
		
		if(collision(move, position)){			//checks if there are any paths in the piece's path
			if( moveSpacesHor!=0 && move[1] == position[1]) {
				if(collision(move, position)){		//checks if there is an object in move destination	
					//kill(move);					//kills opposing piece if so
				}
					position[0] = move[0];		//occupies the spot
					position[1] = move[1];
				
			} else if( moveSpacesVer !=0 && move[0] == position[0]) {
				if(collision(move, position)){		//checks if there is an object in move destination	
					//kill(move);					//kills opposing piece if so
				}
					position[0] = move[0];		//occupies the spot
					position[1] = move[1];
				
			} else if( abs(moveSpacesHor) == abs(moveSpacesVer)) {
				if(collision(move, position)){		//checks if there is an object in move destination	
					//kill(move);					//kills opposing piece if so
				}
					position[0] = move[0];		//occupies the spot
					position[1] = move[1];
				
			} else cout<<"Brahhhhhhhhhhh you can't move dat";

		} else cout<<"There's an object in your path";	
	}
	else cout<<"That is the spot you are currently in";		//Most likely simply ignore
}

int Queen::getType(){
	return type;
}
//----------------------------------------------------------------------------------------------------------------
void King::movePiece() {

	if(move[0] != position[0] && move[1] != position[1]) //checks if user has set move to current space
	{	
		if(move[0] - position[0] == 0 && abs(move[1]) - abs(position[1]) == 1)
		{
			if(collision(move, position))
			{	
				//kill(move);	
				position[0] = move[0];		
				position[1] = move[1];
				
			}
		} 
		else if(abs(move[0]) - abs(position[0]) == 1 && move[1] - position[1] == 0)
		{
			if(collision(move, position))
			{	
				//kill(move);	
				position[0] = move[0];		
				position[1] = move[1];
				
			}
		} 
		else if(abs(move[0]) - abs(position[0]) == 1 && abs(move[1]) - abs(position[1]) == 1)
		{
			if(collision(move, position))
			{	
				//kill(move);	
				position[0] = move[0];		
				position[1] = move[1];
				
			}
		} 
		else cout<<"Brahhhhhhhhhhh you can't move dat";
	}
	else cout<<"That is the spot you are currently in";		//Most likely simply ignore
}

int King::getType(){
	return type;
}
//----------------------------------------------------------------------------------------------------------------




