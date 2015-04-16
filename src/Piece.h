//#pragma once

//#ifndef PAWN_H
//#define PAWN_H
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
int passantCount = 0;
int passantPiece[2];

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
		bool collisionAttack(int move[]);
		Piece* pieceArray[32];
		void setupPieceArray();
		
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
		bool movePiece(int x, int y);	//checks if the move is allowed and if so, mutates position
		int getType();				//returns type of piece
		void transformer();			//once across board, option to change
};


class Bishop : public Piece{

	public:
		Bishop(bool white, int positionX, int positionY, int type = 1, string sprite = "BishopPic") : 
			Piece(white, positionX, positionY, type, sprite){
		};
		~Bishop(){};
		bool movePiece(int x, int y);	//checks if the move is allowed and if so, mutates position
		int getType();				//returns type of piece
};

class Knight : public Piece{
	public:
		Knight(bool white, int positionX, int positionY, int type = 2, string sprite = "KnightPic") : 
			Piece(white, positionX, positionY, type, sprite){
		};
		~Knight(){};
		bool movePiece(int x, int y);	//checks if the move is allowed and if so, mutates position
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
		bool movePiece(int x, int y);	//checks if the move is allowed and if so, mutates position
		int getType();				//returns type of piece
};

class Queen : public Piece{

	public:
		Queen(bool white, int positionX, int positionY, int type = 4, string sprite = "QueenPic") : 
			Piece(white, positionX, positionY, type, sprite){
		};
		~Queen(){};
		bool movePiece(int x, int y);	//checks if the move is allowed and if so, mutates position
		int getType();				//returns type of piece
};

class King : public Piece{
	private:
		bool firstMoved; // true = on its first move, false = moved already
	
	public:
		King(bool white, int positionX, int positionY, int type = 5, string sprite = "KingPic") :
			Piece(white, positionX, positionY, type, sprite){
				firstMoved = true;
		};
		~King(){};
		bool movePiece(int x, int y);
		int getType();
};

void Piece::setupPieceArray()
{
	for(int index = 0; index < 32; index++)
		{	
			if(index < 8)
				pieceArray[index] = new Pawn(true, index, 6);								//white pawns
			else if(index < 16)
				pieceArray[index] = new Pawn(false, index - 7, 1);							//black pawns
			else if(index < 20)
			{
				if(index % 2 == 0)
					pieceArray[index] = new Bishop(true, (3*((index/2)-7))-1, 7);			//white bishops
				else
					pieceArray[index] = new Bishop(false, (3*(((index-1)/2)-7))-1, 0);		//black bishops
			}
			else if(index < 24)
			{
				if(index % 2 == 0)
					pieceArray[index] = new Knight(true, (5*((index/2)-10)) + 1 , 7);		//white knight
				else
					pieceArray[index] = new Knight(false, (5*(((index-1)/2)-10)) + 1 , 0);	//black knight
			}
			else if(index < 28)
			{
				if(index % 2 == 0)
					pieceArray[index] = new Rook(true, (7*((index/2)-12)), 7);				//white rook
				else
					pieceArray[index] = new Rook(false, (7*(((index-1)/2)-12)), 0);			//black rook
			}
			else if(index == 28) pieceArray[index] = new Queen(true, 3, 7);					//white queen
			else if(index == 29) pieceArray[index] = new Queen(false, 3, 0);				//black queen
			else if(index == 30) pieceArray[index] = new King(true, 4, 7);					//white king
			else if(index == 31) pieceArray[index] = new King(false, 4, 0);					//black king
		}
}
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
//----------------------------------------------------------------------------------------------------------------
bool Piece::collision(int move[], int position[]) { //Method that returns free as true or false
	
	int moveSpacesHor = move[0] - position[0];
	int moveSpacesVer = move[1] - position[1];
	bool free = true;
	if (abs(moveSpacesHor) == abs(moveSpacesVer)) { //Checks if diagnol
		if (moveSpacesHor == moveSpacesVer && moveSpacesHor > 0) {	//diagnol + +
			for ( int i = 1; i<abs(moveSpacesHor); i++) {
				if (returnPiece(position[0] + i, position[1] + i) != -1) {
					free = false;
				}
			}
		} else if (moveSpacesHor == moveSpacesVer && moveSpacesHor < 0) { //diagnol - -
			for ( int i = 1; i<abs(moveSpacesHor); i++) {
				if (returnPiece(position[0] - i, position[1] - i) != -1) {
					free = false;
				}
			}
		} else if (abs(moveSpacesHor) == moveSpacesVer) { //diagnol - +
			for ( int i = 1; i<abs(moveSpacesHor); i++) {
				if (returnPiece(position[0] - i, position[1] + i) != -1) {
					free = false;
				}
			}
		} else if (moveSpacesHor == abs(moveSpacesVer)) { //diagnol + -
			for ( int i = 1; i<abs(moveSpacesHor); i++) {
				if (returnPiece(position[0] + i, position[1] - i) != -1) {
					free = false;
				}
			}
		}
	} else if ((moveSpacesHor = 0) && (moveSpacesVer > 0)) { //Vertical +
		for ( int i = 1; i<moveSpacesVer; i++) {
			if (returnPiece(position[0], position[1] + i) != -1) {
					free = false;
				}
			}
	} else if ((moveSpacesHor = 0) && (moveSpacesVer < 0)) { //Vertical -
		for ( int i = 1; i<abs(moveSpacesVer); i++) {
			if (returnPiece(position[0], position[1] - i) != -1) {
					free = false;
				}
			}
	} else if ((moveSpacesVer = 0) && (moveSpacesHor > 0)) { //Horizontal +
		for ( int i = 1; i<moveSpacesHor; i++) {
			if (returnPiece(position[0] + 1, position[1]) != -1) {
					free = false;
				}
			}
	} else if ((moveSpacesVer = 0) && (moveSpacesHor < 0)) { //Horizontal -
		for ( int i = 1; i<abs(moveSpacesHor); i++) {
			if (returnPiece(position[0] - 1, position[1]) != -1) {
				free = false;
				}
			}
	}
	return free;
}
//----------------------------------------------------------------------------------------------------------------
bool Piece::collisionAttack(int move[]) //Method that returns free as true or false for moved spot
{
	bool occupied = false;
	if (returnPiece(move[0], move[1]) != -1) 
		occupied = true;
				
	return occupied;
		
}
//----------------------------------------------------------------------------------------------------------------
/*void Piece::kill(int move[]) //FIX
{
	addToGraveyard(counterGraveyard, returnpiece(move[0], move[1]);//add to graveyard array
	counterGraveyard++;
}*/
//----------------------------------------------------------------------------------------------------------------
bool Pawn::movePiece(int x, int y){ // fix en passant

	bool valid = false;
	int moveCount = getMoveCount(); //90, 91, 
	
	move[0] = x;
	move[1] = y;

	int val1 = -1;
	int val2 = -2;
	
	if(white){
		val1 = abs(val1);
		val2 = abs(val2);
	}
	
	
	
	if(move[0] != position[0] && move[1] != position[1]){	//checks if user has set move to current space
		if(firstMoved && move[1] - position[1] == val2 && position[0] == move[0]){	//marks that the object has moved
			if(collision(move, position)){			//if there is NOT an object in its path
				position[0] = move[0];		//occupies space
				position[1] = move[1];
				valid = true;
				firstMoved = false;
				passantCount = moveCount+1;
				passantPiece[0] = move[0];
				passantPiece[1] = move[1];
				
			}
		}
		else if(move[1] - position[1] == val1 && position[0] == move[0]){	//marks that the object has moved
			if(collision(move, position)){		//if there is NOT an object in its path
				position[0] = move[0];		//occupies space
				position[1] = move[1];
				valid = true;
				firstMoved = false;
			}
		}
		else if(move[1] - position[1] == val1 && abs(move[1] - position[1]) == 1){
			if(collisionAttack(move)){		//checks if there IS an object in that space
				firstMoved = false;			//marks that the object has moved
				valid = true;
				//KILL(MOVE);					//kills the opposing object NEEDS TO BE DONE ulaksdghfjklashdlfjkaghsdljkfaghsdf
				position[0] = move[0];		//occupies the space
				position[1] = move[1];
			} else if (passantCount = moveCount)
			{
				if(collisionAttack(passantPiece))
				{
					position[0] = move[0];		//occupies the space
					position[1] = move[1];
					kill(passantPiece);
					valid = true;
					firstMoved = false;
				}
			}
		}
		else cout<<"Brahhhhhhhhhhh you can't move dat";		
	}
	else cout<<"That is the spot you are currently in";		//Most likely simply ignore

	int end = 0;			//set opposing board row location for black
	if(white) end = 7;		//set opposing board row location for white
		if(position[1] == end)
		{
			transformer();
			valid = true;
			firstMoved = false;
		}
		
		
	return valid;
		
}

void Pawn::transformer(){ //UPDATE WITH PIECEARRAY
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
bool Bishop::movePiece(int x, int y){

	bool valid = false;
	
	move[0] = x;
	move[1] = y;

	if(move[0] != position[0] && move[1] != position[1]){	//checks if user has set move to current space
		if(abs(move[0] - position[0]) == abs(move[1] - position[1])){
			if(collision(move, position)){			//checks if there are any paths in the piece's path
				if(collisionAttack(move)){		//checks if there is an object in move destination	
					//kill(move);					//kills opposing piece if so
				}
				position[0] = move[0];		//occupies the spot
				position[1] = move[1];
				valid = true;
			}
		}
	}

	else cout<<"Brahhhhhhhhhhh you can't move dat";
	
	return valid;
	
} 
//----------------------------------------------------------------------------------------------------------------
bool Knight::movePiece(int x, int y){

	bool valid = false;
	
	move[0] = x;
	move[1] = y;

	if(move[0] != position[0] && move[1] != position[1]){	//checks if user has set move to current space
		int moveSpaceHor = move[0] - position[0];
		int moveSpaceVer = move[1] - position[1];
		
		if((abs(moveSpaceHor == 1 || moveSpaceHor == 2)) && abs(moveSpaceHor) + abs(moveSpaceVer) == 3){
			if(collisionAttack(move)){		//checks if there IS an object in that space
				//kill(move);					//kills the opposing object
			}
				position[0] = move[0];		//occupies the space
				position[1] = move[1];
				valid = true;

			}else{
				cout << "Invalid movement children";	
			}
		
	}

	else cout<<"That is the spot you are currently in";		//Most likely simply ignore
	
	return valid;
	
} 
//----------------------------------------------------------------------------------------------------------------
bool Rook::movePiece(int x, int y) {
	
	bool valid = false;
	
	bool firstMoved = true;
	
	move[0] = x;
	move[1] = y;

	if(move[0] != position[0] && move[1] != position[1]){	//checks if user has set move to current space
		int moveSpacesHor = move[0] - position[0];
		int moveSpacesVer = move[1] - position[1];
		
		if(collision(move, position)){				//if there is NOT an object in its path
			if(moveSpacesHor!=0 && move[1] == position[1]) {
				if(collisionAttack(move)){
					//kill(move);
				}
				position[0] = move[0];
				position[1] = move[1];
				firstMoved = false;
				valid = true;
				
			} else if(moveSpacesVer !=0 && move[0] == position[0]) {
				if(collisionAttack(move)) {
					//kill(move);
				}
				position[0] = move[0];
				position[1] = move[1];
				firstMoved = false;
				valid = true;
				
			} else cout<<"Brahhhhhhhhhhh you can't move dat";
			
			//Work on castling	
		}
	}

	else cout<<"That is the spot you are currently in";		//Most likely simply ignore
	
	return valid;
	
}
//----------------------------------------------------------------------------------------------------------------
bool Queen::movePiece(int x, int y) {

	bool valid = false;
	
	move[0] = x;
	move[1] = y;

	if(move[0] != position[0] && move[1] != position[1]){	//checks if user has set move to current space
		int moveSpacesHor = move[0] - position[0];
		int moveSpacesVer = move[1] - position[1];
		
		if(collision(move, position)){			//checks if there are any paths in the piece's path
			if( moveSpacesHor!=0 && move[1] == position[1]) {
				if(collisionAttack(move)){		//checks if there is an object in move destination	
					//kill(move);					//kills opposing piece if so
				}
					position[0] = move[0];		//occupies the spot
					position[1] = move[1];
					
					valid = true;
				
			} else if(moveSpacesVer !=0 && move[0] == position[0]) {
				if(collisionAttack(move)){		//checks if there is an object in move destination	
					//kill(move);					//kills opposing piece if so
				}
					position[0] = move[0];		//occupies the spot
					position[1] = move[1];
					valid = true;
				
			} else if(abs(moveSpacesHor) == abs(moveSpacesVer)) {
				if(collisionAttack(move)){		//checks if there is an object in move destination	
					//kill(move);					//kills opposing piece if so
				}
					position[0] = move[0];		//occupies the spot
					position[1] = move[1];
					valid = true;
				
			} else cout<<"Brahhhhhhhhhhh you can't move dat";

		} else cout<<"There's an object in your path";	
	}
	else cout<<"That is the spot you are currently in";		//Most likely simply ignore
	
	return valid;
	
}
//----------------------------------------------------------------------------------------------------------------
bool King::movePiece(int x, int y) {

	bool valid = false;
	
	move[0] = x;
	move[1] = y;

	if(move[0] != position[0] && move[1] != position[1]) //checks if user has set move to current space
	{	
		if(move[0] - position[0] == 0 && abs(move[1] - position[1]) == 1) //Vertical move
		{
			if(collisionAttack(move))
			{	
				//kill(move);
			}
			position[0] = move[0];		
			position[1] = move[1];
			valid = true;
			
		} 
		else if(abs(move[0] - position[0]) == 1 && move[1] - position[1] == 0) //Horizontal move
		{
			if(collisionAttack(move))
			{	
				//kill(move);
			}
			position[0] = move[0];		
			position[1] = move[1];
			valid = true;
			
		} 
		else if(abs(move[0] - position[0]) == 1 && abs(move[1] - position[1]) == 1) //Diagonal Move
		{
			if(collisionAttack(move))
			{	
				//kill(move);
			}
			position[0] = move[0];		
			position[1] = move[1];
			valid = true;
			
		} 
		else if (abs(move[0] - position[0]) == 2 && firstMoved && move[1]==position[1]) //castle
		{
			if(move[0] == 6 && collision(move,position) && !collisionAttack(move)) 
			{
				if(isCheck(4,position[1]) && isCheck(5,position[1]) && isCheck(6,position[1])) //castle right
				{
					position[0] = move[0];
					position[1] = move[1];
					valid = true;
					if(white)
						castle(white, right)
					else(black)
						castle(black, right)
						
				}
			}
			else if (move[0] = 2 && collision(move,position) && !collisionAttack(move))
			{
				if(isCheck(2,position[1]) && isCheck(3,position[1]) && isCheck(4,position[1])) //castle left
				{
					position[0] = move[0];
					position[1] = move[1];
					valid = true;
				}
			}
		}
		else cout<<"Brahhhhhhhhhhh you can't move dat";
	}
	else cout<<"That is the spot you are currently in";		//Most likely simply ignore
	
	return valid;
}
//----------------------------------------------------------------------------------------------------------------

