
#include "Piece.cpp"

void Board::setupPieceArray() //Sets up Pieces
{
	for(int index = 0; index < 32; index++)
		{	
			if(index < 8)
				pieceArray[index] = new Pawn(true, index, 6);								//white pawns
			else if(index < 16)
				pieceArray[index] = new Pawn(false, index - 8, 1);							//black pawns
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
bool Board::collision(int moveX, int moveY, int positionX, int positionY) { //Method that returns whether their are pieces in between source piece and destination spot
	

	int moveSpacesHor = moveX - positionX;
	int moveSpacesVer = moveY - positionY;
	bool free = true;
	if (abs(moveSpacesHor) == abs(moveSpacesVer)) { //Checks if diagnol
		if (moveSpacesHor == moveSpacesVer && moveSpacesHor > 0) {	//diagnol + +
			for ( int i = 1; i<abs(moveSpacesHor); i++) {
				if (returnPiece(positionX + i, positionY + i) != -1) {
					free = false;
				}
			}
		} else if (moveSpacesHor == moveSpacesVer && moveSpacesHor < 0) { //diagnol - -
			for ( int i = 1; i<abs(moveSpacesHor); i++) {
				if (returnPiece(positionX - i, positionY - i) != -1) {
					free = false;
				}
			}
		} else if (abs(moveSpacesHor) == moveSpacesVer) { //diagnol - +
			for ( int i = 1; i<abs(moveSpacesHor); i++) {
				if (returnPiece(positionX - i, positionY + i) != -1) {
					free = false;
				}
			}
		} else if (moveSpacesHor == abs(moveSpacesVer)) { //diagnol + -
			for ( int i = 1; i<abs(moveSpacesHor); i++) {
				if (returnPiece(positionX + i, positionY - i) != -1) {
					free = false;
				}
			}
		}
	} else if ((moveSpacesHor == 0) && (moveSpacesVer > 0)) { //Vertical +
		for ( int i = 1; i<moveSpacesVer; i++) {
			if (returnPiece(positionX, positionY + i) != -1) {
					free = false;
				}
			}
	} else if ((moveSpacesHor == 0) && (moveSpacesVer < 0)) { //Vertical -
		for ( int i = 1; i<abs(moveSpacesVer); i++) {
			if (returnPiece(positionX, positionY - i) != -1) {
					free = false;
				}
			}
	} else if ((moveSpacesVer == 0) && (moveSpacesHor > 0)) { //Horizontal +
		for ( int i = 1; i<moveSpacesHor; i++) {
			if (returnPiece(positionX + i, positionY) != -1) {
					free = false;
				}
			}
	} else if ((moveSpacesVer == 0) && (moveSpacesHor < 0)) { //Horizontal -
		for ( int i = 1; i<abs(moveSpacesHor); i++) {
			if (returnPiece(positionX - i, positionY) != -1) {
				free = false;
				}
			}
	}
	
	return free;
}

bool Board::isCheck(int kingX, int kingY, int newX, int newY, int oldX, int oldY)  //Determines whether the king is in check
{
	if(newX == -2 && turn) 
	{
		for(int i = 0; i < 32; i++)		//Checks if white king is in check after black has moved
		{
			int xNum = -2;
			int yNum = -2;
			int tempI = -2;
				if(i >= 8 && i <= 15){
					if(pieceArray[i]->getPawnTrans()){
						xNum = pieceArray[i]->getX();
						yNum = pieceArray[i]->getY();
						tempI = pieceArray[i]->getPieceRule();
						
					}
				}

			if((i >= 8 && i <= 15) || i == 25 || i == 21 || i == 17 || i == 29 || i == 31 || i == 19 || i == 23 || i == 27)
			{
				if(tempI != -2)
				{
					if(pieceArray[tempI]->moveLegal(kingX, kingY, xNum, yNum, -2) && collision(kingX, kingY, pieceArray[i]->getX(), pieceArray[i]->getY()))
					{
					
					return true;
					}
				}
				else 
				{
					if(pieceArray[i]->moveLegal(kingX, kingY, xNum, yNum, -2) && collision(kingX, kingY, pieceArray[i]->getX(), pieceArray[i]->getY()))
					{
						
						return true;
					}
				}
			}
		}
	}
	
	else if(newX == -2 && !turn) 
	{
		for(int i = 0; i < 32; i++) //Checks if black king is in check after white has moved
		{
			int xNum = -2;
			int yNum = -2;
			int tempI = -2;
				if(i >= 0 && i <= 7){
					if(pieceArray[i]->getPawnTrans()){
						xNum = pieceArray[i]->getX();
						yNum = pieceArray[i]->getY();
						tempI = pieceArray[i]->getPieceRule();
						
					}
				}
			if((i >= 0 && i <= 7) || i == 24 || i == 20 || i == 16 || i == 28 || i == 30 || i == 18 || i == 22 || i == 26)
			{
				if(tempI != -2)
				{
					if(pieceArray[tempI]->moveLegal(kingX, kingY, xNum, yNum, -2) && collision(kingX, kingY, pieceArray[i]->getX(), pieceArray[i]->getY()))
					{
						
						return true;
					}
				}
				else
				{
					if(pieceArray[i]->moveLegal(kingX, kingY, xNum, yNum, -2) && collision(kingX, kingY, pieceArray[i]->getX(), pieceArray[i]->getY()))
					{
						
						return true;
					}
				}
	
			}
		}
	}
	
	else if(newX != -2 && turn) //White is in check and this sees if white player's move will move them out of check
	{
		if(boardarray[newX][newY] != -1) //White player defends by taking the piece that put it's king in check
		{
			int queenIndex; //Index to save attacker's spot
			int knightIndex; //Index to save defender's spot
			for(int i = 0; i < 32; i++) //gets rid of attacker hypothetically
			{	
				if(pieceArray[i]->getX() == newX && pieceArray[i]->getY() == newY)
				{
					queenIndex = i;
					pieceArray[i]->setPosition(-2, -20);
					
				}
			}
			for(int i = 0; i < 32; i++) //Puts defender in attacker's spot 
			{
				if(pieceArray[i]->getX() == oldX && pieceArray[i]->getY() == oldY)
				{
					knightIndex = i;
					pieceArray[i]->setPosition(newX, newY);
					
				}
			}
			int knightBoardIndex; //creates hypothetical board
			int queenBoardIndex;
			knightBoardIndex = boardarray[oldX][oldY];
			queenBoardIndex = boardarray[newX][newY];
			boardarray[newX][newY] = knightBoardIndex;
			boardarray[oldX][oldY] = -1;
			for(int i = 0; i < 32; i++) //Checks every piece to see if they can attack the king after white has made its move
			{
				int xNum = -2; //special instance for transformed pawns
				int yNum = -2;
				int tempI = -2;
				if(i >= 8 && i <= 15){
					if(pieceArray[i]->getPawnTrans()){
						xNum = pieceArray[i]->getX();
						yNum = pieceArray[i]->getY();
						tempI = pieceArray[i]->getPieceRule();
						
						}
					}

				if(((i >= 8 && i <= 15) || i == 25 || i == 21 || i == 17 || i == 29 || i == 31 || i == 19 || i == 23 || i == 27) && i != queenIndex && knightIndex != 30) //king wasn't the one that moved
				{
					if(tempI != -2)
					{
						if(pieceArray[tempI]->moveLegal(kingX, kingY, xNum, yNum, -2) && collision(kingX, kingY, pieceArray[i]->getX(), pieceArray[i]->getY()))
						{
							pieceArray[queenIndex]->setPosition(newX, newY);
							pieceArray[knightIndex]->setPosition(oldX, oldY);
							boardarray[oldX][oldY] = knightBoardIndex;
							boardarray[newX][newY] = queenBoardIndex;
							return true;
						}
					}
					else
					{
						if(pieceArray[i]->moveLegal(kingX, kingY, xNum, yNum, -2) && collision(kingX, kingY, pieceArray[i]->getX(), pieceArray[i]->getY()))
						{
							pieceArray[queenIndex]->setPosition(newX, newY);
							pieceArray[knightIndex]->setPosition(oldX, oldY);
							boardarray[oldX][oldY] = knightBoardIndex;
							boardarray[newX][newY] = queenBoardIndex;
							return true;
						}
					}
				}
				else if(((i >= 8 && i <= 15) || i == 25 || i == 21 || i == 17 || i == 29 || i == 31 || i == 19 || i == 23 || i == 27) && i != queenIndex && knightIndex == 30) //king was the one that moved
				{
					if(tempI != -2)
					{
						if(pieceArray[tempI]->moveLegal(newX, newY, xNum, yNum, -2) && collision(newX, newY, pieceArray[i]->getX(), pieceArray[i]->getY()))
						{ 
							pieceArray[queenIndex]->setPosition(newX, newY);
							pieceArray[knightIndex]->setPosition(oldX,oldY);
							boardarray[oldX][oldY] = knightBoardIndex;
							boardarray[newX][newY] = queenBoardIndex;
							return true;
						}
					}
					else
					{
						if(pieceArray[i]->moveLegal(newX, newY, xNum, yNum, -2) && collision(newX, newY, pieceArray[i]->getX(), pieceArray[i]->getY()))
						{ 
							pieceArray[queenIndex]->setPosition(newX, newY);
							pieceArray[knightIndex]->setPosition(oldX,oldY);
							boardarray[oldX][oldY] = knightBoardIndex;
							boardarray[newX][newY] = queenBoardIndex;
							return true;
						}
					}

				}
			}
		
			boardarray[oldX][oldY] = knightBoardIndex; //Resets hypotheticals
			boardarray[newX][newY] = queenBoardIndex;
		}
		
		else //white made a move that prevents check by blocking the attacker or moving the king out of the way
		{
			int pieceIndex; //saves piece spot
			for(int i = 0; i < 32; i++)
			{
				if(pieceArray[i]->getX() == oldX && pieceArray[i]->getY() == oldY)
				{
					pieceIndex = i;
					pieceArray[i]->setPosition(newX, newY);
					
				}
			}
			int boardIndex;	//creates hypothetical board
			boardIndex = boardarray[oldX][oldY];
			boardarray[newX][newY] = pieceIndex;
			boardarray[oldX][oldY] = -1;
			for(int i = 0; i < 32; i++) //Checks every piece to see if they can attack the king after white has made its move
			{
				int xNum = -2;
				int yNum = -2;
				int tempI = -2;
				if(i >= 8 && i <= 15){
					if(pieceArray[i]->getPawnTrans()){
						xNum = pieceArray[i]->getX();
						yNum = pieceArray[i]->getY();
						tempI = pieceArray[i]->getPieceRule();
					
						}
					}
				if(((i >= 8 && i <= 15) || i == 25 || i == 21 || i == 17 || i == 29 || i == 31 || i == 19 || i == 23 || i == 27) && pieceIndex != 30) //King didn't move
				{
					if(tempI != -2)
					{
						if(pieceArray[tempI]->moveLegal(kingX, kingY, xNum, yNum, -2) && collision(kingX, kingY, pieceArray[i]->getX(), pieceArray[i]->getY()))
						{
							pieceArray[pieceIndex]->setPosition(oldX, oldY);
							boardarray[oldX][oldY] = boardIndex;
							boardarray[newX][newY] = -1;
							return true;
						}
					}
					else
					{
						if(pieceArray[i]->moveLegal(kingX, kingY, xNum, yNum, -2) && collision(kingX, kingY, pieceArray[i]->getX(), pieceArray[i]->getY()))
						{
							pieceArray[pieceIndex]->setPosition(oldX, oldY);
							boardarray[oldX][oldY] = boardIndex;
							boardarray[newX][newY] = -1;
							return true;
						}
					}
				}
				else if(((i >= 8 && i <= 15) || i == 25 || i == 21 || i == 17 || i == 29 || i == 31 || i == 19 || i == 23 || i == 27) && pieceIndex == 30) //King did move
				{
					if(tempI != -2)
					{
						if(pieceArray[tempI]->moveLegal(newX, newY, xNum, yNum, -2) && collision(newX, newY, pieceArray[i]->getX(), pieceArray[i]->getY()))
						{
							pieceArray[pieceIndex]->setPosition(oldX, oldY);
							boardarray[oldX][oldY] = boardIndex;
							boardarray[newX][newY] = -1;
							return true;
						}
					}
					else
					{
						if(pieceArray[i]->moveLegal(newX, newY, xNum, yNum, -2) && collision(newX, newY, pieceArray[i]->getX(), pieceArray[i]->getY()))
						{
							pieceArray[pieceIndex]->setPosition(oldX, oldY);
							boardarray[oldX][oldY] = boardIndex;
							boardarray[newX][newY] = -1;
							return true;
						}
					}
				}
			}
			//pieceArray[pieceIndex]->setPosition(oldX, oldY);
			boardarray[oldX][oldY] = boardIndex; //Resets hypotheticals
			boardarray[newX][newY] = -1;

		}
		
		
	}

	else if(newX != -2 && !turn) //Black is in check and tries to save itself by taking attacking piece
	{
		if(boardarray[newX][newY] != -1) //whtie piece took attacking piece
		{
			int queenIndex; //sets up hypothetical
			int knightIndex; 
			for(int i = 0; i < 32; i++) //gets rid of attacker hypothetically
			{
				if(pieceArray[i]->getX() == newX && pieceArray[i]->getY() == newY)
				{
					queenIndex = i;
					pieceArray[i]->setPosition(-2, -20);
					//break;
				}
			}
			for(int i = 0; i < 32; i++) //puts defender in attacker spot hypothetically
			{
				if(pieceArray[i]->getX() == oldX && pieceArray[i]->getY() == oldY)
				{
					knightIndex = i;
					pieceArray[i]->setPosition(newX, newY);
					//break;
				}
			}
			int knightBoardIndex; //sets up hypothetical board
			int queenBoardIndex;
			knightBoardIndex = boardarray[oldX][oldY];
			queenBoardIndex = boardarray[newX][newY];
			boardarray[newX][newY] = knightBoardIndex;
			boardarray[oldX][oldY] = -1;
			for(int i = 0; i < 32; i++) //checks every piece to see if king is still in check
			{
				int xNum = -2;	//special situation for transformed pawns
				int yNum = -2;
				int tempI = -2;
				if(i >= 0 && i <= 7){
					if(pieceArray[i]->getPawnTrans()){
						xNum = pieceArray[i]->getX();
						yNum = pieceArray[i]->getY();
						tempI = pieceArray[i]->getPieceRule();
						//i = pieceArray[i]->getPieceRule();
						}
					}
				if(((i >= 0 && i <= 7) || i == 24 || i == 20 || i == 16 || i == 28 || i == 30 || i == 18 || i == 22 || i == 26) && /*i != queenIndex &&*/ knightIndex != 31) //King did not move
				{
					if(tempI != -2)
					{
						if(pieceArray[tempI]->moveLegal(kingX, kingY, xNum, yNum, -2) && collision(kingX, kingY, pieceArray[i]->getX(), pieceArray[i]->getY()))
						{
							pieceArray[queenIndex]->setPosition(newX, newY);
							pieceArray[knightIndex]->setPosition(oldX,oldY);
				
							boardarray[oldX][oldY] = knightBoardIndex;
							boardarray[newX][newY] = queenBoardIndex;
							return true;
						}
					}
					else
					{
						if(pieceArray[i]->moveLegal(kingX, kingY, xNum, yNum, -2) && collision(kingX, kingY, pieceArray[i]->getX(), pieceArray[i]->getY()))
						{
							pieceArray[queenIndex]->setPosition(newX, newY);
							pieceArray[knightIndex]->setPosition(oldX,oldY);
				
							boardarray[oldX][oldY] = knightBoardIndex;
							boardarray[newX][newY] = queenBoardIndex;
							return true;
						}
					}
				}
				else if(((i >= 0 && i <= 7) || i == 24 || i == 20 || i == 16 || i == 28 || i == 30 || i == 18 || i == 22 || i == 26) && i != queenIndex && knightIndex == 31) //King moved
				{
					if(tempI != -2)
					{
						if(pieceArray[tempI]->moveLegal(newX, newY, xNum, yNum, -2) && collision(newX, newY, pieceArray[i]->getX(), pieceArray[i]->getY()))
						{
							pieceArray[queenIndex]->setPosition(newX, newY);
							pieceArray[knightIndex]->setPosition(oldX,oldY);
				
							boardarray[oldX][oldY] = knightBoardIndex;
							boardarray[newX][newY] = queenBoardIndex;
							return true;
						}
					}
					else
					{
						if(pieceArray[i]->moveLegal(newX, newY, xNum, yNum, -2) && collision(newX, newY, pieceArray[i]->getX(), pieceArray[i]->getY()))
						{
							pieceArray[queenIndex]->setPosition(newX, newY);
							pieceArray[knightIndex]->setPosition(oldX,oldY);
				
							boardarray[oldX][oldY] = knightBoardIndex;
							boardarray[newX][newY] = queenBoardIndex;
							return true;
						}
					}
				}
			}
			//pieceArray[queenIndex]->setPosition(newX, newY);
			//pieceArray[knightIndex]->setPosition(oldX,oldY);
			boardarray[oldX][oldY] = knightBoardIndex; //resets hypothetical
			boardarray[newX][newY] = queenBoardIndex;
		}
		else //white piece moves to block check, or kings moves out of check
		{
		
			int pieceIndex; //creates hypothetical piece
			for(int i = 0; i < 32; i++) 
			{
				if(pieceArray[i]->getX() == oldX && pieceArray[i]->getY() == oldY)
				{
					pieceIndex = i;
					pieceArray[i]->setPosition(newX, newY);
					break;
				}
			}
			int boardIndex;	//creates hypothetical board
			boardIndex = boardarray[oldX][oldY];
			boardarray[newX][newY] = boardIndex;
			boardarray[oldX][oldY] = -1;
			for(int i = 0; i < 32; i++) //checks pieces to see if king is in check
			{
				int xNum = -2; //special case for transformed pawns
				int yNum = -2;
				int tempI = -2;
				if(i >= 0 && i <= 7){
					if(pieceArray[i]->getPawnTrans()){
						xNum = pieceArray[i]->getX();
						yNum = pieceArray[i]->getY();
						tempI = pieceArray[i]->getPieceRule();
						//i = pieceArray[i]->getPieceRule();
						}
					}
				if(((i >= 0 && i <= 7) || i == 24 || i == 20 || i == 16 || i == 28 || i == 30 || i == 18 || i == 22 || i == 26) && pieceIndex != 31) //king didn't move
				{
					if(tempI != -2)
					{
						if(pieceArray[tempI]->moveLegal(kingX, kingY, xNum, yNum, -2) && collision(kingX, kingY, pieceArray[i]->getX(), pieceArray[i]->getY()))
						{
							pieceArray[pieceIndex]->setPosition(oldX, oldY);
							boardarray[oldX][oldY] = boardIndex;
							boardarray[newX][newY] = -1;
							return true;
						}
					}
					else
					{
						if(pieceArray[i]->moveLegal(kingX, kingY, xNum, yNum, -2) && collision(kingX, kingY, pieceArray[i]->getX(), pieceArray[i]->getY()))
						{
							pieceArray[pieceIndex]->setPosition(oldX, oldY);
							boardarray[oldX][oldY] = boardIndex;
							boardarray[newX][newY] = -1;
							return true;
						}
					}
				}
				else if(((i >= 0 && i <= 7) || i == 24 || i == 20 || i == 16 || i == 28 || i == 30 || i == 18 || i == 22 || i == 26) && pieceIndex == 31) //king moved
				{
					if(tempI != -2)
					{
						if(pieceArray[tempI]->moveLegal(newX, newY, xNum, yNum, -2) && collision(newX, newY, pieceArray[i]->getX(), pieceArray[i]->getY()))
						{
							pieceArray[pieceIndex]->setPosition(oldX, oldY);
							boardarray[oldX][oldY] = boardIndex;
							boardarray[newX][newY] = -1;
							return true;
						}
					}
					else
					{
						if(pieceArray[i]->moveLegal(newX, newY, xNum, yNum, -2) && collision(newX, newY, pieceArray[i]->getX(), pieceArray[i]->getY()))
						{
							pieceArray[pieceIndex]->setPosition(oldX, oldY);
							boardarray[oldX][oldY] = boardIndex;
							boardarray[newX][newY] = -1;
							return true;
						}
					}
				}
			}
			
			
			
			//pieceArray[pieceIndex]->setPosition(oldX, oldY);
			boardarray[oldX][oldY] = boardIndex; //resets hypothetical 
			boardarray[newX][newY] = -1;
		}
		
	}


	return false;
}

//Board Methods defined 
void Board::updateBoard() //updates the board display after pieces have been drawn
{
	chessboard.display(main_disp);//update board
	debugbox.display(debug_disp);

	if(turn == true) //was blacks turn, checks for check
	{
		if(isCheck(pieceArray[30]->getX(), pieceArray[30]->getY(), -2, -2, -2, -2))
		{
			check = true;
			debugbox.fill(0).draw_text(0,0, "CHECK!", green);
		}
		
	}
	else if(turn == false) //was whites turn, checks for check
	{
		if(isCheck(pieceArray[31]->getX(), pieceArray[31]->getY(), -2, -2, -2, -2))
		{
			check = true;
			debugbox.fill(0).draw_text(0,0, "CHECK!", green);
		}
	}
}

int Board::returnPiece(int x, int y)//returns piece at spot on board given
{
	return boardarray[x][y];
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
		if(pp == WHITEKNIGHT || pp == WHITEKNIGHTTWO)
		piece = wlknight;
		if(pp == WHITEBISHOP || pp == WHITEBISHOPTWO)
		piece = wlbishop;
		if(pp == WHITEROOK || pp == WHITEROOKTWO)
		piece = wlrook;
		if(pp == WHITEPAWN || pp == WHITEPAWNTWO || pp == WHITEPAWNTHREE || pp == WHITEPAWNFOUR || pp == WHITEPAWNFIVE || pp == WHITEPAWNSIX || pp == WHITEPAWNSEVEN || pp == WHITEPAWNEIGHT)
		piece = wlpawn;
		if(pp == BLACKKING)
		piece = blking;
		if(pp == BLACKQUEEN)
		piece = blqueen;
		if(pp == BLACKKNIGHT || pp == BLACKKNIGHTTWO)
		piece = blknight;
		if(pp == BLACKBISHOP || pp == BLACKBISHOPTWO)
		piece = blbishop;
		if(pp == BLACKROOK || pp == BLACKROOKTWO)
		piece = blrook;
		if(pp == BLACKPAWN || pp == BLACKPAWNTWO || pp == BLACKPAWNTHREE || pp == BLACKPAWNFOUR || pp == BLACKPAWNFIVE || pp == BLACKPAWNSIX || pp == BLACKPAWNSEVEN || pp == BLACKPAWNEIGHT)
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
		if(pp == WHITEKNIGHT || pp == WHITEKNIGHTTWO)
		piece = wdknight;
		if(pp == WHITEBISHOP || pp == WHITEBISHOPTWO)
		piece = wdbishop;
		if(pp == WHITEROOK || pp == WHITEROOKTWO)
		piece = wdrook;
		if(pp == WHITEPAWN || pp == WHITEPAWNTWO || pp == WHITEPAWNTHREE || pp == WHITEPAWNFOUR || pp == WHITEPAWNFIVE || pp == WHITEPAWNSIX || pp == WHITEPAWNSEVEN || pp == WHITEPAWNEIGHT)
		piece = wdpawn;
		if(pp == BLACKKING)
		piece = bdking;
		if(pp == BLACKQUEEN)
		piece = bdqueen;
		if(pp == BLACKKNIGHT || pp == BLACKKNIGHTTWO)
		piece = bdknight;
		if(pp == BLACKBISHOP || pp == BLACKBISHOPTWO)
		piece = bdbishop;
		if(pp == BLACKROOK || pp == BLACKROOKTWO)
		piece = bdrook;
		if(pp == BLACKPAWN || pp == BLACKPAWNTWO || pp == BLACKPAWNTHREE || pp == BLACKPAWNFOUR || pp == BLACKPAWNFIVE || pp == BLACKPAWNSIX || pp == BLACKPAWNSEVEN || pp == BLACKPAWNEIGHT)
		piece = bdpawn;
		if(pp == BLANK)
		piece = dblank;
	}
	return(piece);
}

void Board::setup() //set up board 
{

	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			boardarray[i][j] = BLANK;
	
	//white pieces
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
	boardarray[5][7] = WHITEBISHOPTWO;
	chessboard.draw_image(6*PIXELSQUARESIZE,7*PIXELSQUARESIZE,wdknight);
	boardarray[6][7] = WHITEKNIGHTTWO;
	chessboard.draw_image(7*PIXELSQUARESIZE,7*PIXELSQUARESIZE,wlrook);
	boardarray[7][7] = WHITEROOKTWO;
	chessboard.draw_image(0*PIXELSQUARESIZE,6*PIXELSQUARESIZE,parseDraw(0,6,WHITEPAWN));
	boardarray[0][6] = WHITEPAWN;
	chessboard.draw_image(1*PIXELSQUARESIZE,6*PIXELSQUARESIZE,parseDraw(1,6,WHITEPAWN));
	boardarray[1][6] = WHITEPAWNTWO;
	chessboard.draw_image(2*PIXELSQUARESIZE,6*PIXELSQUARESIZE,parseDraw(2,6,WHITEPAWN));
	boardarray[2][6] = WHITEPAWNTHREE;
	chessboard.draw_image(3*PIXELSQUARESIZE,6*PIXELSQUARESIZE,parseDraw(3,6,WHITEPAWN));
	boardarray[3][6] = WHITEPAWNFOUR;
	chessboard.draw_image(4*PIXELSQUARESIZE,6*PIXELSQUARESIZE,parseDraw(4,6,WHITEPAWN));
	boardarray[4][6] = WHITEPAWNFIVE;
	chessboard.draw_image(5*PIXELSQUARESIZE,6*PIXELSQUARESIZE,parseDraw(5,6,WHITEPAWN));
	boardarray[5][6] = WHITEPAWNSIX;
	chessboard.draw_image(6*PIXELSQUARESIZE,6*PIXELSQUARESIZE,parseDraw(6,6,WHITEPAWN));
	boardarray[6][6] = WHITEPAWNSEVEN;
	chessboard.draw_image(7*PIXELSQUARESIZE,6*PIXELSQUARESIZE,parseDraw(7,6,WHITEPAWN));
	boardarray[7][6] = WHITEPAWNEIGHT;
		
	//black pieces
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
	boardarray[5][0] = BLACKBISHOPTWO;
	chessboard.draw_image(6*PIXELSQUARESIZE,0,blknight);
	boardarray[6][0] = BLACKKNIGHTTWO;
	chessboard.draw_image(7*PIXELSQUARESIZE,0,bdrook);
	boardarray[7][0] = BLACKROOKTWO;
	chessboard.draw_image(0*PIXELSQUARESIZE,1*PIXELSQUARESIZE,parseDraw(0,1,BLACKPAWN));
	boardarray[0][1] = BLACKPAWN;
	chessboard.draw_image(1*PIXELSQUARESIZE,1*PIXELSQUARESIZE,parseDraw(1,1,BLACKPAWN));
	boardarray[1][1] = BLACKPAWNTWO;
	chessboard.draw_image(2*PIXELSQUARESIZE,1*PIXELSQUARESIZE,parseDraw(2,1,BLACKPAWN));
	boardarray[2][1] = BLACKPAWNTHREE;
	chessboard.draw_image(3*PIXELSQUARESIZE,1*PIXELSQUARESIZE,parseDraw(3,1,BLACKPAWN));
	boardarray[3][1] = BLACKPAWNFOUR;
	chessboard.draw_image(4*PIXELSQUARESIZE,1*PIXELSQUARESIZE,parseDraw(4,1,BLACKPAWN));
	boardarray[4][1] = BLACKPAWNFIVE;
	chessboard.draw_image(5*PIXELSQUARESIZE,1*PIXELSQUARESIZE,parseDraw(5,1,BLACKPAWN));
	boardarray[5][1] = BLACKPAWNSIX;
	chessboard.draw_image(6*PIXELSQUARESIZE,1*PIXELSQUARESIZE,parseDraw(6,1,BLACKPAWN));
	boardarray[6][1] = BLACKPAWNSEVEN;
	chessboard.draw_image(7*PIXELSQUARESIZE,1*PIXELSQUARESIZE,parseDraw(7,1,BLACKPAWN));
	boardarray[7][1] = BLACKPAWNEIGHT;

	updateBoard();
}

void Board::moveDraw(CImg<unsigned char> piece, int srcX, int srcY, int destx, int desty)//called if move is valid to draw pieces
{


	if(boardarray[srcX][srcY] >= 0 && boardarray[srcX][srcY] <= 15){
		if(pieceArray[boardarray[srcX][srcY]]->getPawnTrans()){
			CImg<unsigned char> piecetodraw = parseDraw(destx, desty, pieceArray[boardarray[srcX][srcY]]->getPieceRule());
			piece = piecetodraw;
		}
	}
	chessboard.draw_image(destx*PIXELSQUARESIZE, desty*PIXELSQUARESIZE, piece);//draws piece
	
	chessboard.draw_image(srcX*PIXELSQUARESIZE, srcY*PIXELSQUARESIZE,parseDraw(srcX,srcY,BLANK));
	
	if(boardarray[destx][desty] != -1)
	{
		pieceArray[boardarray[destx][desty]]->setPosition(-2, -20);
	}
	pieceArray[boardarray[srcX][srcY]]->setPosition(destx, desty);//updates positions
	boardarray[destx][desty] = boardarray[srcX][srcY];//move piece to new position
	boardarray[srcX][srcY] = BLANK;//override old one
	updateBoard();
}

void Board::castling(bool *typeMoveLegal, int srcX, int srcY, int destx, int desty, int srcPiece){ //special move for castling 

	if(srcPiece == 31 && srcX == 4 && (destx == 6 || destx == 2) && pieceArray[srcPiece]->getFirstMoved()){ //black castling, split for both sides
		if(boardarray[5][srcY] == -1 && boardarray[6][srcY] == -1 && boardarray[7][srcY] == BLACKROOKTWO && pieceArray[BLACKROOKTWO]->getFirstMoved()){
			//pieceArray[BLACKROOKTWO]->setPosition(5, 0);
			moveDraw(bdrook, 7, 0, 5, 0);

			*typeMoveLegal = true;
		}
		if(boardarray [1][srcY] == -1 && boardarray[2][srcY] == -1 && boardarray[3][srcY] == -1 && boardarray[0][srcY] == BLACKROOK && pieceArray[BLACKROOK]->getFirstMoved()){
			//pieceArray[BLACKROOK]->setPosition(3, 0);
			moveDraw(bdrook, 0, 0, 3, 0);
			*typeMoveLegal = true;
		}
	}
	
	if(srcPiece == 30 && srcX == 4 && (destx == 6 || destx == 2) && pieceArray[srcPiece]->getFirstMoved()){ //white castling, split for both sides
		if(boardarray[5][7] == -1 && boardarray[6][7] == -1 && boardarray[7][7] == WHITEROOKTWO && pieceArray[WHITEROOKTWO]->getFirstMoved()){
			//pieceArray[WHITEROOKTWO]->setPosition(srcX, 5);
			moveDraw(wlrook, 7, 7, 5, 7);
			*typeMoveLegal = true;
		}
		if(boardarray [1][srcY] == -1 && boardarray[2][srcY] == -1 && boardarray[3][srcY] == -1 && boardarray[0][srcY] == WHITEROOK && pieceArray[WHITEROOK]->getFirstMoved()){
			//pieceArray[WHITEROOK]->setPosition(3, 7);
			moveDraw(wlrook, 0, 7, 3, 7);
			*typeMoveLegal = true;
		}
	}
}

void Board::enPassant(bool *typeMoveLegal, int srcX, int srcY, int destx, int desty, int srcPiece, bool whiteColorsrc, int srcPieceColor){ //special move for en passant
			
	if(typeMoveLegal && abs(srcY - desty) == 2)
	{
		pieceArray[srcPiece]->setPassantCount(moveCount + 1);
	}
	else if(!*typeMoveLegal)
	{
		int val1 = -1;
		if(whiteColorsrc) val1 = 1;
		if(boardarray[destx][desty+val1] != -1) //determines if pawn has only moved once, and it's on the next turn, and moves up twice - conditions for en passant
		{
			int whiteBack = -1;
			bool whetherWhite = true;
			whetherWhite = pieceArray[boardarray[destx][desty + val1]]->getWhite();
			if(whetherWhite)
				whiteBack = 1;
			else
				whiteBack = 2;

			if((srcY - desty == val1) && abs(destx - srcX) == 1)
			{
				if(boardarray[destx][desty + val1] >= 0 || boardarray[destx][desty + val1] <= 17)
				{
					if(moveCount == pieceArray[boardarray[destx][desty + val1]]->getPassantCount() && (whiteBack != srcPieceColor))
					{
						*typeMoveLegal = true;
						moveDraw(dblank, destx, desty + val1, destx, desty + val1); //move legal, sends it for drawing
					}
				}
			}
		}
	}
			
}	

bool Board::validMove(int srcX, int srcY, int destx, int desty) //determines if move is valid
{
		bool collisionLegal = false;
		bool typeMoveLegal = false;
		bool sameTeam = true;

		int idPiece = boardarray[srcX][srcY];
		int srcPiece = idPiece;
		if(srcPiece >= 0 && srcPiece <= 15) //special condition for pawn transformations
		{
			if(pieceArray[srcPiece]->getPawnTrans())
			{
				srcPiece = pieceArray[idPiece]->getPieceRule();
			}

		}
		
		int destPiece = boardarray[destx][desty]; //neccessary variables
		int srcPieceColor = 0;
		int destPieceColor = 0;
		bool whiteColorsrc = pieceArray[srcPiece]->getWhite();
		bool whiteColorDest = false;
		bool checkMove = true;
		int colorTurn = 0;

		if(turn)  //sets piece color, true is white
			colorTurn = 1;
		else
			colorTurn = 2;

		if(whiteColorsrc) srcPieceColor = 1; 
			else srcPieceColor = 2;

		if(colorTurn == srcPieceColor){					//checks for whose turn it is

			
			if(destPiece != -1){						//fixes OutofIndex error
				whiteColorDest = pieceArray[destPiece]->getWhite();

				if(whiteColorDest) destPieceColor = 1;		//checks for friendly fire
				else destPieceColor = 2;
			}
			else destPieceColor = 3;

			if(srcPieceColor == destPieceColor)
				sameTeam = false;
			
			typeMoveLegal = pieceArray[srcPiece]->moveLegal(destx, desty, srcX, srcY, destPiece); 
			collisionLegal = collision(destx, desty, srcX, srcY);		

			
			if(srcPiece == 31 || srcPiece == 30) //special instance for castling
				castling(&typeMoveLegal, srcX, srcY, destx, desty, srcPiece);

		
			if(typeMoveLegal && collisionLegal && turn) //legal move, white turn, checks if king is in check
			{
				if(isCheck(pieceArray[WHITEKING]->getX(), pieceArray[WHITEKING]->getY(), destx, desty, srcX, srcY))
				{
					checkMove = false;
				}
				else
					check = false;
			}
			else if(typeMoveLegal && collisionLegal && !turn) //legal move, black turn, checks if king is in check
			{
				if(isCheck(pieceArray[BLACKKING]->getX(), pieceArray[BLACKKING]->getY(), destx, desty, srcX, srcY))
				{
					checkMove = false;//sets valid move to false if king is still hypothetically in check, preventing your move from happening
				}
				else
					check = false;
			}	

	
			//EN PASSANT
			if((srcPiece >= 0 && srcPiece <= 15))
			//if((srcPiece >= 0 || srcPiece <= 17) && collisionLegal && sameTeam && checkMove)
			{
				enPassant(&typeMoveLegal, srcX, srcY, destx, desty, srcPiece, whiteColorsrc, srcPieceColor);
			}

			if(srcPiece >= 20 && srcPiece <= 23)
				collisionLegal = true;
	
			if(typeMoveLegal && collisionLegal && sameTeam && checkMove)//everything is true - valid move
			{
				if(srcPiece >= 0 && srcPiece <= 15){			//checks if that pawn is moved to other side
					if(whiteColorsrc && desty == 0){			//for white peices
						pieceArray[srcPiece]->setTransform();
					}
					if(!whiteColorsrc && desty == 7){			//for black pieces
						pieceArray[srcPiece]->setTransform();
					}
				}

				if(idPiece == 30 || idPiece == 31 || (idPiece <= 27 && idPiece >= 24) || (idPiece >= 0 && idPiece <= 15))
					pieceArray[srcPiece]->setFirstMoved();	
				moveCount++;
				turn = !turn;
				return true;
			}
		}

		return false; //false if move not valid
	
		
}

bool Board::handleClick(int p, int x, int y, bool select) //takes in player via clicks
{
	if(lastp == p) //if player re-clicks same piece, this deselects it
	{	
		CImg<unsigned char> originalPiece = parseDraw(lastx,lasty,lastPieceP);
		int srcPiece = boardarray[lastx][lasty];
		if(srcPiece >= 0 && srcPiece <= 15)
		{
			if(pieceArray[srcPiece]->getPawnTrans())
			{
				CImg<unsigned char> transImage = parseDraw(lastx, lasty, pieceArray[srcPiece]->getPieceRule());
				originalPiece = transImage;
			}
		}
		lastp = BLANK;
		chessboard.draw_image(lastx*PIXELSQUARESIZE, lasty*PIXELSQUARESIZE, originalPiece);
		debugbox.fill(0).draw_text(0, 0, "PIECE DESELECTED.", green);
		return false; //returns false to main, preventing moving your piece to the same spot which would switch turns if this returned true
	}
	else if(select && lastp != BLANK) //actual movement
	{
		//check what piece to draw
		CImg<unsigned char> piecetodraw = parseDraw(x,y,lastp);//Last p is the piece to move
		lastp = BLANK;//overwrite last piece to prevent double drawing
		
		//checks if valid move, then draws it
		if(validMove(lastx,lasty,x,y))
		{
			moveDraw(piecetodraw,lastx,lasty,x,y);
			lastPieceP = BLANK;
		}
		
		else //transform conditions
		{
			debugbox.fill(0).draw_text(0, 0, "INVALID MOVE.\n MOVE AGAIN.", green);
			int srcPiece = boardarray[lastx][lasty];
			
			CImg<unsigned char> originalPiece = parseDraw(lastx,lasty,lastPieceP);
			if(srcPiece >= 0 && srcPiece <= 15)
			{
				if(pieceArray[srcPiece]->getPawnTrans())
				{
					CImg<unsigned char> transImage = parseDraw(lastx, lasty, pieceArray[srcPiece]->getPieceRule());
					originalPiece = transImage;
				}
			}
			chessboard.draw_image(lastx*PIXELSQUARESIZE, lasty*PIXELSQUARESIZE, originalPiece);
			//debugbox.fill(0).draw_text(0, 0, "PIECE DESELECTED.", green);
		}
	}
	else //first move special case
	{
		if(p != BLANK){
		lastx = x;
		lasty = y;
		
			lastPieceP = p;
		lastp = p;

		CImg<unsigned char> outlines;
		outlines = selection;
		chessboard.draw_image(lastx*PIXELSQUARESIZE, lasty*PIXELSQUARESIZE, outlines);
		chessboard.draw_image(lastx*PIXELSQUARESIZE + 95, lasty*PIXELSQUARESIZE, outlines);
		debugbox.fill(0).draw_text(0, 0, "PIECE SELECTED.", green);
		}
	}
	return true; //if conditions are valid, this returns true to main
}
