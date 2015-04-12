//#pragma once

//#ifndef PAWN_H
//#define PAWN_H
#include <vector>
#include <string>
#include <iostream>

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
		virtual void movePiece() = 0;
		void parseMove(string position);			//Changes from A1 to 00 and H8 to 77, put into move()
		int* getPosition();					//inteact with 2D array, check legal move
		void died();								//determines if piece is taken, mutates bool dead
		int getType();	
		bool getWhite();
		bool getDead();
		void kill(int move[]);
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
		virtual int* movePiece(int x, int y);	//checks if the move is allowed and if so, mutates position
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

class Queen : public Piece{

	public:
		Queen(bool white, int positionX, int positionY, int type = 4, string sprite = "QueenPic") : 
			Piece(white, positionX, positionY, type, sprite){
		};
		~Queen(){};
		virtual void movePiece();	//checks if the move is allowed and if so, mutates position
		int getType();				//returns type of piece
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

/*void Piece::kill(int move[])
{
	addToGraveyard(counterGraveyard, returnpiece(move[0], move[1]);//add to graveyard array
	counterGraveyard++;
}*/
