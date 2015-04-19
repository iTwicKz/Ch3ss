//#pragma once

//#ifndef PAWN_H
//#define PAWN_H
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
//#include "cimg.h"
//#include "boardTest.h"
/*#ifndef IMAGEPATH
#define IMAGEPATH "res/Default/"
#endif

#define BLANK -1
#define WHITEKING 1
#define WHITEQUEEN 2
#define WHITEKNIGHT 3
#define WHITEBISHOP 4
#define WHITEROOK 5
#define WHITEPAWN 6
#define BLACKKING 7
#define BLACKQUEEN 8
#define BLACKKNIGHT 9
#define BLACKBISHOP 10
#define BLACKROOK 11
#define BLACKPAWN 12
//0-7 white pawns
//8-15 black pawns
//16,18 white bishops
//17,19 black bishops

#define PIXELSQUARESIZE 100
//#define XPADDING 10
//#define YPADDING 10*/

int passantCount = 0;
int passantPiece[2];

using namespace std;
//using namespace cimg_library;

//each piece is 60px by 60px chessboard is 480px by 480px or 60px * 8
		/*CImg<unsigned char> chessboard(IMAGEPATH "chessboard.png"); 

		CImg<unsigned char> wlking(IMAGEPATH "King-White-Light.jpg");
		CImg<unsigned char> wdking(IMAGEPATH "King-White-Dark.jpg");
		CImg<unsigned char> wlqueen(IMAGEPATH "Queen-White-Light.jpg");
		CImg<unsigned char> wdqueen(IMAGEPATH "Queen-White-Dark.jpg");
		CImg<unsigned char> wlknight(IMAGEPATH "Knight-White-Light.jpg");
		CImg<unsigned char> wdknight(IMAGEPATH "Knight-White-Dark.jpg");
		CImg<unsigned char> wlbishop(IMAGEPATH "Bishop-White-Light.jpg");
		CImg<unsigned char> wdbishop(IMAGEPATH "Bishop-White-Dark.jpg");
		CImg<unsigned char> wlrook(IMAGEPATH "Rook-White-Light.jpg");
		CImg<unsigned char> wdrook(IMAGEPATH "Rook-White-Dark.jpg");
		CImg<unsigned char> wlpawn(IMAGEPATH "Pawn-White-Light.jpg");
		CImg<unsigned char> wdpawn(IMAGEPATH "Pawn-White-Dark.jpg");
		CImg<unsigned char> blking(IMAGEPATH "King-Black-Light.jpg");
		CImg<unsigned char> bdking(IMAGEPATH "King-Black-Dark.jpg");
		CImg<unsigned char> blqueen(IMAGEPATH "Queen-Black-Light.jpg");
		CImg<unsigned char> bdqueen(IMAGEPATH "Queen-Black-Dark.jpg");
		CImg<unsigned char> blknight(IMAGEPATH "Knight-Black-Light.jpg");
		CImg<unsigned char> bdknight(IMAGEPATH "Knight-Black-Dark.jpg");
		CImg<unsigned char> blbishop(IMAGEPATH "Bishop-Black-Light.jpg");
		CImg<unsigned char> bdbishop(IMAGEPATH "Bishop-Black-Dark.jpg");
		CImg<unsigned char> blrook(IMAGEPATH "Rook-Black-Light.jpg");
		CImg<unsigned char> bdrook(IMAGEPATH "Rook-Black-Dark.jpg");
		CImg<unsigned char> blpawn(IMAGEPATH "Pawn-Black-Light.jpg");
		CImg<unsigned char> bdpawn(IMAGEPATH "Pawn-Black-Dark.jpg");
		CImg<unsigned char> lblank(IMAGEPATH "Blank-Light.jpg");
		CImg<unsigned char> dblank(IMAGEPATH "Blank-Dark.jpg");

		CImg<unsigned char> debugbox(4*PIXELSQUARESIZE,1*PIXELSQUARESIZE,1,3,0); //debug box

		//Displays (each display is a new window)
		CImgDisplay main_disp(chessboard,"Chess");
		CImgDisplay debug_disp(debugbox,"Debug");

		//Boardarray 
		int boardarray[8][8];
		//start outside the board
		int lastx = 9;
		int lasty = 9;
		int lastp = BLANK;

		//counter
		int moveCount = 0;
		//to write to screen/debug
		const unsigned char green[] = { 0,255,0 };*/


class Board;
int returnPiece(int x, int y);
int getMoveCount();
bool isCheck(int x, int y);

//===========================================================================================================================================================================================================================
//-----------------------------------------------------------------------------------------------------------------
class Piece {
	
	friend class Board;
	
	
	
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
		int  getX();							//inteact with 2D array, check legal move
		int getY();
		void died();								//determines if piece is taken, mutates bool dead
		int getType();	
		bool getWhite();
		bool getDead();
		//void kill(int move[]);
		bool collision(int move[], int position[]);
		bool collisionAttack(int move[]);
		static Piece* pieceArray[32];
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

int Piece::getX()
{
	return position[0];
}

int Piece::getY()
{
	return position[1];
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
/*void Piece::kill(int move[]) 
{
	addToGraveyard(counterGraveyard, returnpiece(move[0], move[1]);//add to graveyard array
	counterGraveyard++;
}*/
//----------------------------------------------------------------------------------------------------------------
bool Pawn::movePiece(int x, int y){

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
			} else if (passantCount == moveCount)
			{
				if(collisionAttack(passantPiece))
				{
					position[0] = move[0];		//occupies the space
					position[1] = move[1];
					//kill(passantPiece);
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
bool King::movePiece(int x, int y) { //FIX MOVING ROOKS POSITION WITH CASTLING

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
						
				}
			}
			else if ((move[0] == 2) && collision(move,position) && !collisionAttack(move))
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
//===========================================================================================================================================================================================================================




/*class Board 
{
	friend class Piece;
	
	public:
		//methods
		void updateBoard();
		int returnPiece(int x, int y);
		int getMoveCount();
		CImg<unsigned char> parseDraw(int xx, int yy, int pp);
		void setup();
		void moveDraw(CImg<unsigned char> piece, int srcx, int srcy, int destx, int desty);
		bool handleClick(int p, int x, int y, bool select);
};

//Board Methods defined
void Board::updateBoard()
{
	chessboard.display(main_disp);//update board
	debugbox.display(debug_disp);
}

int Board::returnPiece(int x, int y)//returns piece at spot on board given
{
	for(int i = 0; i < 32; i++)
	{
		if((x == Piece::pieceArray[i]->getX()) && (y == Piece::pieceArray[i]->getY()))
		{
			return(i);
		}
	}
	return(BLANK);//no spot
	//return(boardarray[x][y]);
}

int Board::getMoveCount()
{
	return moveCount;
}

CImg<unsigned char> Board::parseDraw(int xx, int yy, int pp)//draw light pieces on light squares, dark pieces on dark squares
{
	bool color = true; //true is light, false is dark
	//determine if square is light or dark
	if(xx%2 == 0 && yy%2 == 0)
		color = true;
	else if(xx%2 == 0 && yy != 0)
		color = false;
	else if(xx%2 != 0 && yy%2 == 0)
		color = false;
	else if(xx%2 != 0 && yy%2 != 0)
		color = true;
		
	//assign image to variables
	CImg<unsigned char> piece;
	if(color)
	{
		if(pp == WHITEKING)
		piece = wlking;
		if(pp == WHITEQUEEN)
		piece = wlqueen;
		if(pp == WHITEKNIGHT)
		piece = wlknight;
		if(pp == WHITEBISHOP)
		piece = wlbishop;
		if(pp == WHITEROOK)
		piece = wlrook;
		if(pp == WHITEPAWN)
		piece = wlpawn;
		if(pp == BLACKKING)
		piece = blking;
		if(pp == BLACKQUEEN)
		piece = blqueen;
		if(pp == BLACKKNIGHT)
		piece = blknight;
		if(pp == BLACKBISHOP)
		piece = blbishop;
		if(pp == BLACKROOK)
		piece = blrook;
		if(pp == BLACKPAWN)
		piece = blpawn;
		if(pp == BLANK)
		piece = lblank;
	}
	else
	{
		if(pp == WHITEKING)
		piece = wdking;
		if(pp == WHITEQUEEN)
		piece = wdqueen;
		if(pp == WHITEKNIGHT)
		piece = wdknight;
		if(pp == WHITEBISHOP)
		piece = wdbishop;
		if(pp == WHITEROOK)
		piece = wdrook;
		if(pp == WHITEPAWN)
		piece = wdpawn;
		if(pp == BLACKKING)
		piece = bdking;
		if(pp == BLACKQUEEN)
		piece = bdqueen;
		if(pp == BLACKKNIGHT)
		piece = bdknight;
		if(pp == BLACKBISHOP)
		piece = bdbishop;
		if(pp == BLACKROOK)
		piece = bdrook;
		if(pp == BLACKPAWN)
		piece = bdpawn;
		if(pp == BLANK)
		piece = dblank;
	}
	return(piece);
}

void Board::setup()
{
	
	//setup board
	//for painting
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			boardarray[i][j] = BLANK;
	
	//white
	chessboard.draw_image(0,7*PIXELSQUARESIZE,wdrook);
	boardarray[0][7] = WHITEROOK;
	chessboard.draw_image(1*PIXELSQUARESIZE,7*PIXELSQUARESIZE,wlknight);
	boardarray[1][7] = WHITEKNIGHT;
	chessboard.draw_image(2*PIXELSQUARESIZE,7*PIXELSQUARESIZE,wdbishop);
	boardarray[2][7] = WHITEBISHOP;
	chessboard.draw_image(3*PIXELSQUARESIZE,7*PIXELSQUARESIZE,wlqueen);
	boardarray[3][7] = WHITEQUEEN;
	chessboard.draw_image(4*PIXELSQUARESIZE,7*PIXELSQUARESIZE,wdking);
	boardarray[4][7] = WHITEKING;
	chessboard.draw_image(5*PIXELSQUARESIZE,7*PIXELSQUARESIZE,wlbishop);
	boardarray[5][7] = WHITEBISHOP;
	chessboard.draw_image(6*PIXELSQUARESIZE,7*PIXELSQUARESIZE,wdknight);
	boardarray[6][7] = WHITEKNIGHT;
	chessboard.draw_image(7*PIXELSQUARESIZE,7*PIXELSQUARESIZE,wlrook);
	boardarray[7][7] = WHITEROOK;
	for(int i = 0; i <=7; i++)
	{
		chessboard.draw_image(i*PIXELSQUARESIZE,6*PIXELSQUARESIZE,parseDraw(i,6,WHITEPAWN));
		boardarray[i][6] = WHITEPAWN;
	}
		
	//black
	chessboard.draw_image(0,0,blrook);
	boardarray[0][0] = BLACKROOK;
	chessboard.draw_image(1*PIXELSQUARESIZE,0,bdknight);
	boardarray[1][0] = BLACKKNIGHT;
	chessboard.draw_image(2*PIXELSQUARESIZE,0,blbishop);
	boardarray[2][0] = BLACKBISHOP;
	chessboard.draw_image(3*PIXELSQUARESIZE,0,bdqueen);
	boardarray[3][0] = BLACKQUEEN;
	chessboard.draw_image(4*PIXELSQUARESIZE,0,blking);
	boardarray[4][0] = BLACKKING;
	chessboard.draw_image(5*PIXELSQUARESIZE,0,bdbishop);
	boardarray[5][0] = BLACKBISHOP;
	chessboard.draw_image(6*PIXELSQUARESIZE,0,blknight);
	boardarray[6][0] = BLACKKNIGHT;
	chessboard.draw_image(7*PIXELSQUARESIZE,0,bdrook);
	boardarray[7][0] = BLACKROOK;
	for(int i = 0; i <=7; i++)
	{
		chessboard.draw_image(i*PIXELSQUARESIZE,1*PIXELSQUARESIZE,parseDraw(i,1,BLACKPAWN));
		boardarray[i][1] = BLACKPAWN;
	}
	updateBoard();
}


void Board::moveDraw(CImg<unsigned char> piece, int srcx, int srcy, int destx, int desty)//x and y are 0-7 only call if your move is valid you dummy
{
	moveCount++;
	//check for the special moves en passant or castling or queening
	//Castling move was checked as valid in handleclick
	if((piece == blking && srcx+2 == destx) || (piece == wlking && srcx+2 == destx) || (piece == bdking && srcx+2 == destx) || (piece == wdking && srcx+2 == destx))//only time the king can move 2
	{
		chessboard.draw_image(destx*PIXELSQUARESIZE, desty*PIXELSQUARESIZE, piece);
		if(piece == wlking || piece == wdking)//done this way to prevent falsely identified castling
		{
			chessboard.draw_image(5*PIXELSQUARESIZE, desty*PIXELSQUARESIZE, parseDraw(5,desty,BLACKROOK));
			chessboard.draw_image(7*PIXELSQUARESIZE, desty*PIXELSQUARESIZE, lblank);
			boardarray[5][desty] = boardarray[7][desty];//move piece to new position
			boardarray[7][desty] = BLANK;//override old one
		}
		if(piece == blking || piece == bdking)
		{
			chessboard.draw_image(5*PIXELSQUARESIZE, desty*PIXELSQUARESIZE, parseDraw(5,desty,BLACKROOK));
			chessboard.draw_image(7*PIXELSQUARESIZE, desty*PIXELSQUARESIZE, dblank);
			boardarray[5][desty] = boardarray[7][desty];//move piece to new position
			boardarray[7][desty] = BLANK;//override old one
		}
	}
	else if((piece == blking && srcx == destx+2) || (piece == wlking && srcx == destx+2) || (piece == bdking && srcx == destx+2) || (piece == wdking && srcx == destx+2))
	{
		chessboard.draw_image(destx*PIXELSQUARESIZE, desty*PIXELSQUARESIZE, piece);
		if(piece == wlking || piece == wdking)//done this way to prevent falsely identified castling
		{
			chessboard.draw_image(4*PIXELSQUARESIZE, desty*PIXELSQUARESIZE, parseDraw(4,desty,WHITEROOK));
			chessboard.draw_image(0, desty*PIXELSQUARESIZE, dblank);
			boardarray[4][desty] = boardarray[0][desty];//move piece to new position
			boardarray[0][desty] = BLANK;//override old one
		}
		if(piece == blking || piece == bdking)
		{
			chessboard.draw_image(4*PIXELSQUARESIZE, desty*PIXELSQUARESIZE, parseDraw(4,desty,BLACKROOK));
			chessboard.draw_image(0, desty*PIXELSQUARESIZE, lblank);
			boardarray[4][desty] = boardarray[0][desty];//move piece to new position
			boardarray[0][desty] = BLANK;//override old one
		}
	}
	//Queening a pawn
	else if((piece == blpawn && desty == 7) || (piece == bdpawn && desty == 0))
	{
		//
	}
	else if((piece == wlpawn && desty == 0) || (piece == wdpawn && desty == 0))
	{
		//
	}
	//The En Passant
	//else if(){}
	else
		chessboard.draw_image(destx*PIXELSQUARESIZE, desty*PIXELSQUARESIZE, piece);
	
	chessboard.draw_image(srcx*PIXELSQUARESIZE, srcy*PIXELSQUARESIZE,parseDraw(srcx,srcy,BLANK));
		
	
	boardarray[destx][desty] = boardarray[srcx][srcy];//move piece to new position
	boardarray[srcx][srcy] = BLANK;//override old one
	updateBoard();
}

bool Board::handleClick(int p, int x, int y, bool select)
{
	if(lastp == p)
	{
		lastp = BLANK;
		debugbox.fill(0).draw_text(0, 0, "PIECE DESELECTED.", green);
		return false;
	}
	else if(select && lastp != BLANK)//if they select a piece of their color
	{
		//check what piece to draw
		CImg<unsigned char> piecetodraw = parseDraw(x,y,p);
		
		//CHECK VALID MOVE FIRST
		if(true)
			moveDraw(piecetodraw,lastx,lasty,x,y);
		else
			debugbox.fill(0).draw_text(0, 0, "INVALID MOVE.\n MOVE AGAIN.", green);
	}
	else
	{
		lastx = x;
		lasty = y;
		lastp = p;
		debugbox.fill(0).draw_text(0, 0, "PIECE SELECTED.", green);
	}
	return true;
}

*/




























