#include <vector>

using namespace std;

class Piece {
	protected:
		int type;				//Queen, King, etc.
		vector<int>move;			//Location
		vector<int>position;		//Position in 2D Array Gameboard
		int sprite;				//Image file link
		bool white;				//black or white
		bool dead;				//on board or not


	public:
		void parseMove(string position);		//Changes from A1 to 00 and H8 to 77, put into move()
		vector<int> getPosition();					//inteact with 2D array, check legal move
		void died();							//determines if piece is taken, mutates bool dead
		int getType();
		bool getWhite();
		bool getDead();
};

class Pawn : public Piece{
	private:
		bool firstMoved;		//checks if pawn has been moved

	public:
		Pawn() : Piece (bool white, int positionX, int positionY);
		void move();
		int getType();			//returns type of piece
		void transformer();		//once across board, option to change
};

class Bishop : public Piece{

	public:
		Pawn() : Piece (bool white, int positionX, int positionY);
		void move();
		int getType();
		int getType();			//returns type of piece
};