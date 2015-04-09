#pragma once

//#ifndef PAWN_H
//#define PAWN_H
#include <vector>

using namespace std;


class Piece {
	protected:
		int type;					//Queen, King, 	etc.
		vector<int>move;			//Location
		vector<int>position;		//Position in 2D Array Gameboard
		string sprite;				//Image file link
		bool white;					//black or white
		bool dead;					//on board or not
		//virtual void movePiece() const;


	public:
		Piece(bool white, int positionX, int positionY, int type, string sprite){
			this->type = type;
			this->sprite = sprite;
			move.push_back(0);
			move.push_back(0);
			this->white = white;
			position.push_back(positionX);
			position.push_back(positionY); 
		}
		virtual void movePiece() = 0;
		void parseMove(string position);			//Changes from A1 to 00 and H8 to 77, put into move()
		vector<int> getPosition();					//inteact with 2D array, check legal move
		void died();								//determines if piece is taken, mutates bool dead
		int getType();	
		bool getWhite();
		bool getDead();
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
		virtual void movePiece();	//checks if the move is allowed and if so, mutates position
		int getType();				//returns type of piece
		void transformer();			//once across board, option to change
};


class Bishop : public Piece{

	public:
		Bishop(bool white, int positionX, int positionY, int type = 1, string sprite = "BishopPic") : 
			Piece(white, positionX, positionY, type, sprite){
		};
		~Bishop(){};
		virtual void movePiece();	//checks if the move is allowed and if so, mutates position
		int getType();				//returns type of piece
};

class Knight : public Piece{

	public:
		Knight(bool white, int positionX, int positionY, int type = 2, string sprite = "KnightPic") : 
			Piece(white, positionX, positionY, type, sprite){
		};
		~Knight(){};
		virtual void movePiece();	//checks if the move is allowed and if so, mutates position
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
		virtual void movePiece();	//checks if the move is allowed and if so, mutates position
		int getType();				//returns type of piece
};

