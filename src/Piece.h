//#pragma once

//#ifndef PAWN_H
//#define PAWN_H
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
//int passantCount = 0;
//int passantPiece[2];

using namespace std;

class Piece {
	protected:
		int type;					//Queen, King, 	etc.
		int move[2];
		int position[2];
		string sprite;				//Image file link
		bool white;					//black or white
		bool dead;					//on board or not
		
		int blackScore;
		int whiteScore;
		int counterGraveyard;
		bool firstMoved;
		

	public:
		Piece(){};
		Piece(bool white, int positionX, int positionY, int type, string sprite){
			this->type = type;
			this->sprite = sprite;
			move[0] = 0;
			move[1] = 0;
			this->white = white; 
			position[0] = positionX;
			position[1] = positionY;
			this->blackScore = 0;
			this->whiteScore = 0;
			firstMoved = true;
			//int counterGraveyard = 0;
			
		}
		virtual bool moveLegal(int x, int y, int destPiece){};
		int* getPosition();							//inteact with 2D array, check legal move								//determines if piece is taken, mutates bool dead
		int getType();	
		bool getWhite();
		bool getDead();
		//void kill(int move[]);
		//Piece* pieceArray[32];
		void setPosition(int x ,int y);
		void setDied();
		virtual void setFirstMoved(){};
		
};

class Pawn : public Piece{
	//private:
	//	bool firstMoved;			//checks if pawn has been moved for two move rule
		

	public:
		Pawn(bool white, int positionX, int positionY, int type = 0, string sprite = "PawnPic") : 
			Piece(white, positionX, positionY, type, sprite){
			//firstMoved = true;
		};
		~Pawn(){};
		bool moveLegal(int x, int y, int destPiece);	//checks if the move is allowed and if so, mutates position
		void setFirstMoved();
		//void transformer();			//once across board, option to change
};


class Bishop : public Piece{

	public:
		Bishop(bool white, int positionX, int positionY, int type = 1, string sprite = "BishopPic") : 
			Piece(white, positionX, positionY, type, sprite){
		};
		~Bishop(){};
		bool moveLegal(int x, int y, int destPiece);	//checks if the move is allowed and if so, mutates position
};

class Knight : public Piece{
	public:
		Knight(bool white, int positionX, int positionY, int type = 2, string sprite = "KnightPic") : 
			Piece(white, positionX, positionY, type, sprite){
		};
		~Knight(){};
		bool moveLegal(int x, int y, int destPiece);	//checks if the move is allowed and if so, mutates position
};

class Rook : public Piece{

	//private:
	//	bool firstMoved;			//checks if rook has been moved for castling rule

	public:
		Rook(bool white, int positionX, int positionY, int type = 3, string sprite = "RookPic") : 
			Piece(white, positionX, positionY, type, sprite){
	//		firstMoved = true;
		};
		~Rook(){};
		bool moveLegal(int x, int y, int destPiece);	//checks if the move is allowed and if so, mutates position
		void setFirstMoved();
};

class Queen : public Piece{

	public:
		Queen(bool white, int positionX, int positionY, int type = 4, string sprite = "QueenPic") : 
			Piece(white, positionX, positionY, type, sprite){
		};
		~Queen(){};
		bool moveLegal(int x, int y, int destPiece);	//checks if the move is allowed and if so, mutates position
};

class King : public Piece{
//	private:
//		bool firstMoved; // true = on its first move, false = moved already
	
	public:
		King(bool white, int positionX, int positionY, int type = 5, string sprite = "KingPic") :
			Piece(white, positionX, positionY, type, sprite){
//				firstMoved = true;
		};
		~King(){};
		bool moveLegal(int x, int y, int destPiece);
		void setFirstMoved();
};
