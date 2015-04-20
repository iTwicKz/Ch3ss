#include "Piece.h"
#include "Board.h"

int* Piece::getPosition(){					//returns position of Piece object
		return position;	
}

int Piece::getType(){						//returns the integer identifier of Piece object
	return type;
}

bool Piece::getWhite(){						//returns where the Piece object is white or not
	return this->white;
}

bool Piece::getDead(){						//returns whether or not the object is dead or not
	return dead;
}

void Piece::setPosition(int x, int y){		//mutates position array in Piece object
	position[0] = x;							//x value
	position[1] = y;							//y value
}

void Piece::setDied(){						//sets the Piece object as dead
	dead = true;
}

int Piece::getX(){							//returns X position of object
	return position[0];
}

int Piece::getY(){							//returns Y position of object
	return position[1];
}

bool Piece::getFirstMoved(){				//returns wherther or not the object has moved yet
	return firstMoved;
}
//----------------------------------------------------------------------------------------------------------------//
	//------------------------------------------------PAWN--------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//
bool Pawn::moveLegal(int x, int y, int srcX, int srcY, int destPiece){ 					//Pawn Move Laws are checked

	bool valid = false; 
	
	move[0] = x;
	move[1] = y;

	int val1 = -1;
	int val2 = -2;
	
	if(!white)					//restricts only forward movement for both black and white
	{
		val1 = abs(val1);
		val2 = abs(val2);
	}
	
	if(firstMoved && (move[1] - position[1] == val2) && (position[0] == move[0]) && destPiece == -1)	//checks for first double jump special move
	{
		valid = true;	
	}
	else if(move[1] - position[1] == val1 && position[0] == move[0] && destPiece == -1)					//checks for normal one forward jump move
	{
		valid = true;
	}
	else if(move[1] - position[1] == val1 && abs(move[0] - position[0]) == 1 && destPiece != -1)		//checks for diagnol attack move
	{
		valid = true;
	}
		
	return valid;
		
}

void Pawn::setFirstMoved(){							//sets that the Pawn has moved
	firstMoved = false;
}

void Pawn::setPassantCount(int passantCount){		//sets that the object has moved two spaces and is vulnerable to en passant attack
	this->passantCount = passantCount;
}

int Pawn::getPassantCount(){						//returns whether or not Pawn can be killed by en passant
	return passantCount;
}

void Pawn::setTransform(){							//if Pawn reaches other side, Pawn can be changed to Knight, Bishop, Rook or Queen

	CImg<unsigned char> dialbox(4*PIXELSQUARESIZE,1*PIXELSQUARESIZE,1,3,0);			//new pop-up window
	CImgDisplay dial_disp(dialbox, "Select Piece and Close Window");				//name and initialization of new window
	pawnTrans = true;			//sets that the Pawn is transforming

	int input;			
	if(white)					//checks for white pawns
	{
		dialbox.draw_image(0, 0, wlknight);			//white knight image
		dialbox.draw_image(100, 0, wlbishop);		//white bishop image
		dialbox.draw_image(200, 0, wlrook);			//white rook image
		dialbox.draw_image(300, 0, wlqueen);		//white queen image
		dialbox.display(dial_disp);						//displays box
		while (!dial_disp.is_closed())			//continues to register clicks until window is closed
			{ 
				dial_disp.wait();
				if (dial_disp.button() && dial_disp.mouse_y()>=0) //if mouse is clicked on screen
				{		
					const int x = dial_disp.mouse_x(); 	//get x coordinate
					if(x < 100)
						pieceRule = 20;					//Transform to Knight Piece
					else if(x < 200)
						pieceRule = 16;					//Transform to Bishop Piece
					else if(x < 300)
						pieceRule = 24;					//Transform to Rook Piece
					else if(x < 400)
						pieceRule = 28;					//Transform to Queen Piece
				}
			}
	}
	else						//checks for black pawns
	{
		dialbox.draw_image(0, 0, blknight);			//black knight image
		dialbox.draw_image(100, 0, blbishop);		//black bishop image
		dialbox.draw_image(200, 0, blrook);			//black rook image
		dialbox.draw_image(300, 0, blqueen);		//black queen image
		dialbox.display(dial_disp);						//displays box
		while (!dial_disp.is_closed())
		{ 
			dial_disp.wait();
			if (dial_disp.button() && dial_disp.mouse_y()>=0) //if mouse is clicked on screen
			{		
				const int x = dial_disp.mouse_x();	//get x coordinate
				if(x < 100)
					pieceRule = 21;					//Transform to Knight Piece
				else if( x < 200)
					pieceRule = 17;					//Transform to Bishop Piece
				else if(x < 300)
					pieceRule = 25;					//Transform to Rook Piece
				else if(x < 400)
					pieceRule = 29;					//Transform to Queen Piece
			}
		}
	}
}


bool Pawn::getPawnTrans(){			//checks whether or not the Pawn has transformed
	return pawnTrans;
}

int Pawn::getPieceRule(){			//returns the secret mask of the Pawn who transformed
	return pieceRule;
}
//----------------------------------------------------------------------------------------------------------------//
	//------------------------------------------------BISHOP-------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//
bool Bishop::moveLegal(int x, int y, int srcX, int srcY, int destPiece){		//Bishop Move Laws are Checked

	bool valid = false;

	if(srcX == -2)			//checks move laws for hypothetical check moves
	{
		if(abs(x - position[0]) == abs(y - position[1]))	//checks if move is diagnol
		{
			valid = true;
		}
	}
	else if(abs(x - srcX) == abs(y - srcY)){				//checks if move is diagnol for actual move 
		valid = true;
	}
	
	return valid;
} 
//----------------------------------------------------------------------------------------------------------------//
	//------------------------------------------------KNIGHT-------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//
bool Knight::moveLegal(int x, int y, int srcX, int srcY, int destPiece){		//Knight Move Laws are Checked

	bool valid = false;
	
	move[0] = x;
	move[1] = y;

	if(srcX == -2)			//checks move laws for hypothetical check moves
	{
		int moveSpaceHor = move[0] - position[0];		//counts spaces moving left and right
		int moveSpaceVer = move[1] - position[1];		//counts spaces moving up and down

		if((abs(moveSpaceHor) == 1 || abs(moveSpaceHor) == 2) && abs(moveSpaceHor) + abs(moveSpaceVer) == 3)	//checks that moves are in Knight box
		{
			valid = true;
		}
	}
	else					//checks move laws for action moves
	{
		int moveSpaceHor = move[0] - srcX;				//counts spaces moving left and right
		int moveSpaceVer = move[1] - srcY;				//counts spaces moving up and down

		if((abs(moveSpaceHor) == 1 || abs(moveSpaceHor) == 2) && abs(moveSpaceHor) + abs(moveSpaceVer) == 3)	//checks that moves are in Knight box
			valid = true;
	}
	return valid;
} 
//----------------------------------------------------------------------------------------------------------------//
	//------------------------------------------------ROOK--------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//
bool Rook::moveLegal(int x, int y, int srcX, int srcY, int destPiece) {			//Rook Move Laws are Checked
	
	bool valid = false;
	
	bool firstMoved = true;		//sets that the object has now moved (actual rule if you touched the Rook, castling is no longer allowed)
	
	move[0] = x;
	move[1] = y;

	if(srcX == -2)			//checks move laws for hypothetical check moves
	{
		int moveSpacesHor = move[0] - position[0];		//counts spaces moving left and right
		int moveSpacesVer = move[1] - position[1];		//counts spaces moving up and down
	
		if(moveSpacesHor!=0 && move[1] == position[1]) 	//checks for horizontal movement
		{
			valid = true;
		
		} 
		else if(moveSpacesVer !=0 && move[0] == position[0]) 	//checks for vertical movement
		{
			valid = true;
		} 
	}
	else					//checks move laws for action moves
	{
		int moveSpacesHor = move[0] - srcX;				//counts spaces moving left and right
		int moveSpacesVer = move[1] - srcY;				//counts spaces moving up and down
	
		if(moveSpacesHor!=0 && move[1] == srcY) 		//checks for horizontal movement
		{
			valid = true;
		} 
		else if(moveSpacesVer !=0 && move[0] == srcX) 			//checks for vertical movement
		{
			valid = true;
		} 
	}
	
	return valid;
}

void Rook::setFirstMoved(){			//sets that the rook has been moved
	firstMoved = false;
}
//----------------------------------------------------------------------------------------------------------------//
	//------------------------------------------------QUEEN--------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//
bool Queen::moveLegal(int x, int y, int srcX, int srcY, int destPiece) {		//Queen Move Laws are Checked

	bool valid = false;
	
	move[0] = x;
	move[1] = y;

	if(srcX == -2)			//checks move laws for hypothetical check moves
	{
		int moveSpacesHor = move[0] - position[0];		//counts spaces moving left and right
		int moveSpacesVer = move[1] - position[1];		//counts spaces moving up and down
			

		if( moveSpacesHor!=0 && move[1] == position[1]) {	//checks for horizontal movement
				valid = true;
			
		} else if(moveSpacesVer !=0 && move[0] == position[0]) {	//checks for vertical movement
				valid = true;
			
		} else if(abs(moveSpacesHor) == abs(moveSpacesVer)) {		//checks for diagonol movement
				valid = true;
		}

	}
	else					//checks move laws for action moves
	{
		int moveSpacesHor = move[0] - srcX;				//counts spaces moving left and right
		int moveSpacesVer = move[1] - srcY;				//counts spaces moving up and down
			

		if( moveSpacesHor!=0 && move[1] == srcY) {			//checks for horizontal movement
				valid = true;
			
		} else if(moveSpacesVer !=0 && move[0] == srcX) {	//checks for vertiical movement
				valid = true;
			
		} else if(abs(moveSpacesHor) == abs(moveSpacesVer)) {		//checks for diagonol movement
				valid = true;
		}
	}
	return valid;
}
//----------------------------------------------------------------------------------------------------------------//
	//------------------------------------------------KING--------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//
bool King::moveLegal(int x, int y, int srcX, int srcY, int destPiece) {				//King Move Laws are Checked

	bool valid = false;
	
	move[0] = x;
	move[1] = y;

	if(move[0] - position[0] == 0 && abs(move[1] - position[1]) == 1) 			//checks for vertical movement
	{
		valid = true;
	} 
	else if(abs(move[0] - position[0]) == 1 && move[1] - position[1] == 0)		//checks for horizontal movement
	{
		valid = true;
	} 
	else if(abs(move[0] - position[0]) == 1 && abs(move[1] - position[1]) == 1) //checks for diagonol movement
	{
		valid = true;
	} 
	else if (abs(move[0] - position[0]) == 2 && firstMoved && move[1]==position[1]) //Castling move Validity
	{
	}
	return valid;
}

void King::setFirstMoved(){			//sets that the object has already been moved
	firstMoved = false;	
}
//----------------------------------------------------------------------------------------------------------------//

