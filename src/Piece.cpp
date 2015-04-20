#include "Piece.h"
#include "Board.h"

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

bool Piece::getFirstMoved(){
	return firstMoved;
}
//----------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------
bool Pawn::moveLegal(int x, int y, int srcX, int srcY, int destPiece){ // fix en passant

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


void Pawn::setPassantCount(int passantCount){
	this->passantCount = passantCount;
}

int Pawn::getPassantCount(){
	return passantCount;
}

void Pawn::setTransform(){	//just queens for now

	CImg<unsigned char> dialbox(4*PIXELSQUARESIZE,1*PIXELSQUARESIZE,1,3,0);
	CImgDisplay dial_disp(dialbox, "Please select which piece you want");
	pawnTrans = true;


	int input;
	if(white)
	{
		
	dialbox.draw_image(0, 0, wlknight);
	dialbox.draw_image(100, 0, wlbishop);
	dialbox.draw_image(200, 0, wlrook);
	dialbox.draw_image(300, 0, wlqueen);
	dialbox.display(dial_disp);
	while (!dial_disp.is_closed())
		{ 
			dial_disp.wait();
		if (dial_disp.button() && dial_disp.mouse_y()>=0) //if mouse is clicked on screen
			{		

			const int x = dial_disp.mouse_x();//get x coordinate
			if(x < 100)
				pieceRule = 20;
			else if( x < 200)
				pieceRule = 16;
			else if(x < 300)
				pieceRule = 24;
			else if(x < 400)
				pieceRule = 28;
			}
		}
	}
	else//blakc
	{
			dialbox.draw_image(0, 0, blknight);
	dialbox.draw_image(100, 0, blbishop);
	dialbox.draw_image(200, 0, blrook);
	dialbox.draw_image(300, 0, blqueen);
	dialbox.display(dial_disp);
	while (!dial_disp.is_closed())
		{ 
			dial_disp.wait();
		if (dial_disp.button() && dial_disp.mouse_y()>=0) //if mouse is clicked on screen
			{		

			const int x = dial_disp.mouse_x();//get x coordinate
			if(x < 100)
				pieceRule = 21;
			else if( x < 200)
				pieceRule = 17;
			else if(x < 300)
				pieceRule = 25;
			else if(x < 400)
				pieceRule = 29;
			}
		}
	}
}


bool Pawn::getPawnTrans(){
	return pawnTrans;
}

int Pawn::getPieceRule(){
	return pieceRule;
}
//----------------------------------------------------------------------------------------------------------------
bool Bishop::moveLegal(int x, int y, int srcX, int srcY, int destPiece){

	bool valid = false;

	if(srcX == -2)
	{
		if(abs(x - position[0]) == abs(y - position[1]))
		{
			valid = true;
		}


	}
	else if(abs(x - srcX) == abs(y - srcY)){
		valid = true;
	}
	
	return valid;
	
} 
//----------------------------------------------------------------------------------------------------------------
bool Knight::moveLegal(int x, int y, int srcX, int srcY, int destPiece){

	bool valid = false;
	
	move[0] = x;
	move[1] = y;

	if(srcX == -2)
	{
		int moveSpaceHor = move[0] - position[0];
		int moveSpaceVer = move[1] - position[1];

		if((abs(moveSpaceHor) == 1 || abs(moveSpaceHor) == 2) && abs(moveSpaceHor) + abs(moveSpaceVer) == 3)
		{
			valid = true;
		}
	
	}
	else
	{
		int moveSpaceHor = move[0] - srcX;
		int moveSpaceVer = move[1] - srcY;

		if((abs(moveSpaceHor) == 1 || abs(moveSpaceHor) == 2) && abs(moveSpaceHor) + abs(moveSpaceVer) == 3)
			valid = true;
	}
	
	return valid;
	
} 
//----------------------------------------------------------------------------------------------------------------
bool Rook::moveLegal(int x, int y, int srcX, int srcY, int destPiece) {
	
	bool valid = false;
	
	bool firstMoved = true;
	
	move[0] = x;
	move[1] = y;

	if(srcX == -2)
	{
		int moveSpacesHor = move[0] - position[0];
		int moveSpacesVer = move[1] - position[1];
	
		if(moveSpacesHor!=0 && move[1] == position[1]) 
		{
			valid = true;
		
		} 
		else if(moveSpacesVer !=0 && move[0] == position[0]) 
		{
			valid = true;
		} 
		else cout<<"Brahhhhhhhhhhh you can't move dat";

	}
	else
	{
		int moveSpacesHor = move[0] - srcX;
		int moveSpacesVer = move[1] - srcY;
	
		if(moveSpacesHor!=0 && move[1] == srcY) 
		{
			valid = true;
		} 
		else if(moveSpacesVer !=0 && move[0] == srcX) 
		{
			valid = true;
		} 
		else cout<<"Brahhhhhhhhhhh you can't move dat";

	}
	
	return valid;
	
}

void Rook::setFirstMoved(){
	firstMoved = false;
}
//----------------------------------------------------------------------------------------------------------------
bool Queen::moveLegal(int x, int y, int srcX, int srcY, int destPiece) {

	bool valid = false;
	
	move[0] = x;
	move[1] = y;

	if(srcX == -2)
	{
		int moveSpacesHor = move[0] - position[0];
		int moveSpacesVer = move[1] - position[1];
			

		if( moveSpacesHor!=0 && move[1] == position[1]) {
				valid = true;
			
		} else if(moveSpacesVer !=0 && move[0] == position[0]) {
				valid = true;
			
		} else if(abs(moveSpacesHor) == abs(moveSpacesVer)) {
				valid = true;
			
		} else cout<<"Brahhhhhhhhhhh you can't move dat";

	}
	else
	{
		int moveSpacesHor = move[0] - srcX;
		int moveSpacesVer = move[1] - srcY;
			

		if( moveSpacesHor!=0 && move[1] == srcY) {
				valid = true;
			
		} else if(moveSpacesVer !=0 && move[0] == srcX) {
				valid = true;
			
		} else if(abs(moveSpacesHor) == abs(moveSpacesVer)) {
				valid = true;
			
		} else cout<<"Brahhhhhhhhhhh you can't move dat";

	}
	
	
	return valid;
	
}
//----------------------------------------------------------------------------------------------------------------
bool King::moveLegal(int x, int y, int srcX, int srcY, int destPiece) {

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
		
	}
	else cout<<"Brahhhhhhhhhhh you can't move dat";

	return valid;
}

void King::setFirstMoved(){
	firstMoved = false;
}
//----------------------------------------------------------------------------------------------------------------

