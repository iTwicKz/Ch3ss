#include "Board.h"


void Board::setupPieceArray()
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

//Board Methods defined
void Board::updateBoard()
{
	chessboard.display(main_disp);//update board
	debugbox.display(debug_disp);
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

bool Board::collision(int moveX, int moveY, int positionX, int positionY) { //Method that returns free as true or false
	

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
			if (returnPiece(positionX + 1, positionY) != -1) {
					free = false;
				}
			}
	} else if ((moveSpacesVer == 0) && (moveSpacesHor < 0)) { //Horizontal -
		for ( int i = 1; i<abs(moveSpacesHor); i++) {
			if (returnPiece(positionX - 1, positionY) != -1) {
				free = false;
				}
			}
	}
	return free;
}


void Board::moveDraw(CImg<unsigned char> piece, int srcx, int srcy, int destx, int desty)//x and y are 0-7 only call if your move is valid you dummy
{
	
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
	/*//Queening a pawn
	else if((piece == blpawn && desty == 7) || (piece == bdpawn && desty == 0))
	{
		//
	}
	else if((piece == wlpawn && desty == 0) || (piece == wdpawn && desty == 0))
	{
		//
	}*/
	//The En Passant
	//else if(){}
	else
		chessboard.draw_image(destx*PIXELSQUARESIZE, desty*PIXELSQUARESIZE, piece);
	
	chessboard.draw_image(srcx*PIXELSQUARESIZE, srcy*PIXELSQUARESIZE,parseDraw(srcx,srcy,BLANK));
		
	
	boardarray[destx][desty] = boardarray[srcx][srcy];//move piece to new position
	boardarray[srcx][srcy] = BLANK;//override old one
	updateBoard();
}

bool Board::validMove(int srcx, int srcy, int destx, int desty)
{
		bool collisionLegal = false;
		bool typeMoveLegal = false;
		int srcPiece = boardarray[srcx][srcy];
		int destPiece = boardarray[destx][desty];

		typeMoveLegal = pieceArray[srcPiece]->moveLegal(destx, desty); 
		collisionLegal = collision(srcx, srcy, destx, desty);

		if(srcPiece >= 20 && srcPiece <= 23)
			collisionLegal = true;

		if(typeMoveLegal && collisionLegal)
		{
			if(srcPiece == 30 || srcPiece == 31 || (srcPiece <= 27 && srcPiece >= 24) || (srcPiece <= 0 && srcPiece >= 15))
				pieceArray[srcPiece]->setFirstMoved();	
			pieceArray[srcPiece]->setPosition(destx, desty);
			return true;
		}

		return false;
	
		
}

bool Board::handleClick(int p, int x, int y, bool select)
{
		if(lastp == p)
	{
		lastp = BLANK;
		debugbox.fill(0).draw_text(0, 0, "PIECE DESELECTED.", green);
		return false;
	}
	else if(select && lastp != BLANK)
	{
		//check what piece to draw
		CImg<unsigned char> piecetodraw = parseDraw(x,y,lastp);//Last p is the piece to move
		lastp = BLANK;//overwrite last piece to prevent double drawing
		//CHECK VALID MOVE FIRST
		if(validMove(lastx,lasty,x,y))
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
