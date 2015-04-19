#include "Piece.h"

int* Piece::getPosition(){
		return position;
}

int Piece::getType(){
	return type;
}

bool Piece::getWhite(){
	return this->white;
}

bool Piece::getDead(){
	return dead;
}

void Piece::setPosition(int x, int y){
	position[0] = x;
	position[1] = y;
}

void Piece::setDied(){
	dead = true;
}

int Piece::getX()
{
	return position[0];
}

int Piece::getY()
{
	return position[1];
}

//----------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------
bool Pawn::moveLegal(int x, int y, int destPiece){ // fix en passant

	bool valid = false; 
	
	move[0] = x;
	move[1] = y;

	int val1 = -1;
	int val2 = -2;
	
	if(!white){
		val1 = abs(val1);
		val2 = abs(val2);
	}
	
	if(firstMoved && (move[1] - position[1] == val2) && (position[0] == move[0]) && destPiece == -1)	//marks that the object has moved
	{
		valid = true;			
		
	}
	else if(move[1] - position[1] == val1 && position[0] == move[0] && destPiece == -1)	//marks that the object has moved
	{
		valid = true;
	}
	else if(move[1] - position[1] == val1 && abs(move[0] - position[0]) == 1 && destPiece != -1)
	{
		//check for attack
		valid = true;
	}
	else cout<<"Brahhhhhhhhhhh you can't move dat";		
	
	/*
	int end = 0;			//set opposing board row location for black
	if(white) end = 7;		//set opposing board row location for white

	if(position[1] == end)
	{
		transformer();
		valid = true;
		firstMoved = false;
	}
	*/
		
	return valid;
		
}

void Pawn::setFirstMoved(){
	firstMoved = false;
}
/*
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
*/
//----------------------------------------------------------------------------------------------------------------
bool Bishop::moveLegal(int x, int y, int destPiece){

	bool valid = false;
	
	move[0] = x;
	move[1] = y;

	if(abs(move[0] - position[0]) == abs(move[1] - position[1])){
		valid = true;
	}
	
	else cout<<"Brahhhhhhhhhhh you can't move dat";
	
	return valid;
	
} 
//----------------------------------------------------------------------------------------------------------------
bool Knight::moveLegal(int x, int y, int destPiece){

	bool valid = false;
	
	move[0] = x;
	move[1] = y;


	int moveSpaceHor = move[0] - position[0];
	int moveSpaceVer = move[1] - position[1];
	
	if((abs(moveSpaceHor) == 1 || abs(moveSpaceHor) == 2) && abs(moveSpaceHor) + abs(moveSpaceVer) == 3)
	{
		valid = true;
	}
	
	return valid;
	
} 
//----------------------------------------------------------------------------------------------------------------
bool Rook::moveLegal(int x, int y, int destPiece) {
	
	bool valid = false;
	
	bool firstMoved = true;
	
	move[0] = x;
	move[1] = y;

	
	int moveSpacesHor = move[0] - position[0];
	int moveSpacesVer = move[1] - position[1];
	
	if(moveSpacesHor!=0 && move[1] == position[1]) 
	{
		valid = true;
		
	} else if(moveSpacesVer !=0 && move[0] == position[0]) 
	{
		valid = true;
	} else cout<<"Brahhhhhhhhhhh you can't move dat";
	
	//Work on castling	
		
	
	return valid;
	
}

void Rook::setFirstMoved(){
	firstMoved = false;
}
//----------------------------------------------------------------------------------------------------------------
bool Queen::moveLegal(int x, int y, int destPiece) {

	bool valid = false;
	
	move[0] = x;
	move[1] = y;


	int moveSpacesHor = move[0] - position[0];
	int moveSpacesVer = move[1] - position[1];
		

	if( moveSpacesHor!=0 && move[1] == position[1]) {
			valid = true;
		
	} else if(moveSpacesVer !=0 && move[0] == position[0]) {
			valid = true;
		
	} else if(abs(moveSpacesHor) == abs(moveSpacesVer)) {
			valid = true;
		
	} else cout<<"Brahhhhhhhhhhh you can't move dat";

		
	
	return valid;
	
}
//----------------------------------------------------------------------------------------------------------------
bool King::moveLegal(int x, int y, int destPiece) {

	bool valid = false;
	
	move[0] = x;
	move[1] = y;

	if(move[0] - position[0] == 0 && abs(move[1] - position[1]) == 1) //Vertical move
	{
		valid = true;
	} 
	else if(abs(move[0] - position[0]) == 1 && move[1] - position[1] == 0) //Horizontal move
	{
		valid = true;
	} 
	else if(abs(move[0] - position[0]) == 1 && abs(move[1] - position[1]) == 1) //Diagonal Move
	{
		valid = true;
	} 
	else if (abs(move[0] - position[0]) == 2 && firstMoved && move[1]==position[1]) //castle
	{
		/*if(move[0] == 6 && collision(move,position) && !collisionAttack(move)) 
		{
			if(isCheck(4,position[1]) && isCheck(5,position[1]) && isCheck(6,position[1])) //castle right
			{
				position[0] = move[0];
				position[1] = move[1];
				valid = true;
				if(white)
					castle(white, right);
				else(black)
					castle(black, right);
					
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
		}*/
	}
	else cout<<"Brahhhhhhhhhhh you can't move dat";

	return valid;
}

void King::setFirstMoved(){
	firstMoved = false;
}
//----------------------------------------------------------------------------------------------------------------

