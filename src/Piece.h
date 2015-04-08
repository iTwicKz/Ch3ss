#pragma once

//#ifndef PAWN_H
//#define PAWN_H
#include <vector>

using namespace std;


class Piece {
	protected:
		int type;					//Queen, King, etc.
		vector<int>move;			//Location
		vector<int>position;		//Position in 2D Array Gameboard
		int sprite;					//Image file link
		bool white;					//black or white
		bool dead;					//on board or not
		virtual void movePiece() const;


	public:
		Piece(bool white, int positionX, int positionY, int type, int sprite){
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
		bool firstMoved;		//checks if pawn has been moved

	public:
		Pawn(bool white, int positionX, int positionY, int type = 0, int sprite = 0) : 
			Piece(white, positionX, positionY, type, sprite){
			firstMoved = true;
		};
		virtual void movePiece();
		int getType();			//returns type of piece
		void transformer();		//once across board, option to change
};


class Bishop : public Piece{

	public:
		Bishop(bool white, int positionX, int positionY, int type = 1, int sprite = 1) : 
			Piece(white, positionX, positionY, type, sprite){
		};
		void movePiece();
		int getType();			//returns type of piece
};