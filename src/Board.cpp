#include "CImg.h"
//#include "Piece.h"

#ifndef IMAGEPATH
#define IMAGEPATH "res/Default"
#endif

#define BLANK -1
#define WHITEKING 1
#define WHITEQUEEN 2
#define WHITEKNIGHT 3
#define WHITEBISHOP 4
#define WHITEROOK 5
#define WHITEPAWN 6
#define BLACKKING 7
#define BLACKQUEEN 8
#define BLACKKNIGHT 9
#define BLACKBISHOP 10
#define BLACKROOK 11
#define BLACKPAWN 12
//0-7 white pawns
//8-15 black pawns
//16,18 white bishops
//17,19 black bishops

#define PIXELSQUARESIZE 100
//#define XPADDING 10
//#define YPADDING 10

using namespace cimg_library;

//each piece is 60px by 60px chessboard is 480px by 480px or 60px * 8
CImg<unsigned char> chessboard(IMAGEPATH "chessboard.png");

CImg<unsigned char> wlking(IMAGEPATH "King-White-Light.jpg");
CImg<unsigned char> wdking(IMAGEPATH "King-White-Dark.jpg");
CImg<unsigned char> wlqueen(IMAGEPATH "Queen-White-Light.jpg");
CImg<unsigned char> wdqueen(IMAGEPATH "Queen-White-Dark.jpg");
CImg<unsigned char> wlknight(IMAGEPATH "Knight-White-Light.jpg");
CImg<unsigned char> wdknight(IMAGEPATH "Knight-White-Dark.jpg");
CImg<unsigned char> wlbishop(IMAGEPATH "Bishop-White-Light.jpg");
CImg<unsigned char> wdbishop(IMAGEPATH "Bishop-White-Dark.jpg");
CImg<unsigned char> wlrook(IMAGEPATH "Rook-White-Light.jpg");
CImg<unsigned char> wdrook(IMAGEPATH "Rook-White-Dark.jpg");
CImg<unsigned char> wlpawn(IMAGEPATH "Pawn-White-Light.jpg");
CImg<unsigned char> wdpawn(IMAGEPATH "Pawn-White-Dark.jpg");
CImg<unsigned char> blking(IMAGEPATH "King-Black-Light.jpg");
CImg<unsigned char> bdking(IMAGEPATH "King-Black-Dark.jpg");
CImg<unsigned char> blqueen(IMAGEPATH "Queen-Black-Light.jpg");
CImg<unsigned char> bdqueen(IMAGEPATH "Queen-Black-Dark.jpg");
CImg<unsigned char> blknight(IMAGEPATH "Knight-Black-Light.jpg");
CImg<unsigned char> bdknight(IMAGEPATH "Knight-Black-Dark.jpg");
CImg<unsigned char> blbishop(IMAGEPATH "Bishop-Black-Light.jpg");
CImg<unsigned char> bdbishop(IMAGEPATH "Bishop-Black-Dark.jpg");
CImg<unsigned char> blrook(IMAGEPATH "Rook-Black-Light.jpg");
CImg<unsigned char> bdrook(IMAGEPATH "Rook-Black-Dark.jpg");
CImg<unsigned char> blpawn(IMAGEPATH "Pawn-Black-Light.jpg");
CImg<unsigned char> bdpawn(IMAGEPATH "Pawn-Black-Dark.jpg");
CImg<unsigned char> lblank(IMAGEPATH "Blank-Light.jpg");
CImg<unsigned char> dblank(IMAGEPATH "Blank-Dark.jpg");
/*CImg<unsigned char> wking(IMAGEPATH "Chess_klt60.png");
CImg<unsigned char> bking(IMAGEPATH "Chess_kdt60.png");
CImg<unsigned char> wqueen(IMAGEPATH "Chess_qlt60.png");
CImg<unsigned char> bqueen(IMAGEPATH "Chess_qdt60.png");
CImg<unsigned char> wknight(IMAGEPATH "Chess_nlt60.png");
CImg<unsigned char> bknight(IMAGEPATH "Chess_ndt60.png");
CImg<unsigned char> wbishop(IMAGEPATH "Chess_blt60.png");
CImg<unsigned char> bbishop(IMAGEPATH "Chess_bdt60.png");
CImg<unsigned char> wrook(IMAGEPATH "Chess_rlt60.png");
CImg<unsigned char> brook(IMAGEPATH "Chess_rdt60.png");
CImg<unsigned char> wpawn(IMAGEPATH "Chess_plt60.png");
CImg<unsigned char> bpawn(IMAGEPATH "Chess_pdt60.png");
CImg<unsigned char> dsquare(IMAGEPATH "dsq.png");
CImg<unsigned char> lsquare(IMAGEPATH "lsq.png");*/
CImg<unsigned char> debugbox(4*PIXELSQUARESIZE,1*PIXELSQUARESIZE,1,3,0);
//Displays (each display is a new window)
CImgDisplay main_disp(chessboard,"Chess");
CImgDisplay debug_disp(debugbox,"Debug");

//Boardarray 
int boardarray[8][8];
//Piece* pieceArray[32];
//start outside the board
int lastx = 9;
int lasty = 9;
int lastp = BLANK;

//counter
int movecount = 0;
//to write to screen/debug
const unsigned char green[] = { 0,255,0 };


//Board Methods
void updateBoard()
{
	chessboard.display(main_disp);//update board
	debugbox.display(debug_disp);
}

int returnPiece(int x, int y)//returns piece at spot on board given
{
	/*for(int i = 0; i < 32; i++)
	{
		if((x == pieceArray[i]->getX()) && (y == pieceArray[i]->getY()))
		{
			return(i);
		}
	}
	return(BLANK);//no spot*/
	return(boardarray[x][y]);
}

int getMoveCount()
{
	return movecount;
}

void setup()
{
	
	//setup board
	//for painting
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			boardarray[i][j] = BLANK;
	
	/*++++++++++++++++++++++++++++++++++ INITIALIZING PIECE ARRAY ++++++++++++++++++++++++++++++++//

	for(int index = 0; index < 32; index++)	//creating pawns
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
				pieceArray[index] = new Rook(true, (7*((index/2)-12)), 7);			//white knight
			else
				pieceArray[index] = new Rook(false, (7*(((index-1)/2)-12)), 0);			//black knight
		}
		else if(index == 28) pieceArray[index] = new Queen(true, 3, 7);					//white queen
		else if(index == 29) pieceArray[index] = new Queen(false, 3, 0);				//black queen
		else if(index == 30) pieceArray[index] = new King(true, 4, 7);					//white king
		else if(index == 31) pieceArray[index] = new King(false, 4, 0);					//black king
	}

	//+++++++++++++++++++++++++++++++++++++++++++ END ++++++++++++++++++++++++++++++++++++++++++++++*/
	
	//white
	chessboard.draw_image(0,7*PIXELSQUARESIZE,wrook);
	boardarray[0][7] = WHITEROOK;
	chessboard.draw_image(1*PIXELSQUARESIZE,7*PIXELSQUARESIZE,wknight);
	boardarray[1][7] = WHITEKNIGHT;
	chessboard.draw_image(2*PIXELSQUARESIZE,7*PIXELSQUARESIZE,wbishop);
	boardarray[2][7] = WHITEBISHOP;
	chessboard.draw_image(3*PIXELSQUARESIZE,7*PIXELSQUARESIZE,wqueen);
	boardarray[3][7] = WHITEQUEEN;
	chessboard.draw_image(4*PIXELSQUARESIZE,7*PIXELSQUARESIZE,wking);
	boardarray[4][7] = WHITEKING;
	chessboard.draw_image(5*PIXELSQUARESIZE,7*PIXELSQUARESIZE,wbishop);
	boardarray[5][7] = WHITEBISHOP;
	chessboard.draw_image(6*PIXELSQUARESIZE,7*PIXELSQUARESIZE,wknight);
	boardarray[6][7] = WHITEKNIGHT;
	chessboard.draw_image(7*PIXELSQUARESIZE,7*PIXELSQUARESIZE,wrook);
	boardarray[7][7] = WHITEROOK;
	for(int i = 0; i <=7; i++)
	{
		chessboard.draw_image(i*PIXELSQUARESIZE,6*PIXELSQUARESIZE,wpawn);
		boardarray[i][6] = WHITEPAWN;
	}
		
	//black
	chessboard.draw_image(0,0,brook);
	boardarray[0][0] = BLACKROOK;
	chessboard.draw_image(1*PIXELSQUARESIZE,0,bknight);
	boardarray[1][0] = BLACKKNIGHT;
	chessboard.draw_image(2*PIXELSQUARESIZE,0,bbishop);
	boardarray[2][0] = BLACKBISHOP;
	chessboard.draw_image(3*PIXELSQUARESIZE,0,bqueen);
	boardarray[3][0] = BLACKQUEEN;
	chessboard.draw_image(4*PIXELSQUARESIZE,0,bking);
	boardarray[4][0] = BLACKKING;
	chessboard.draw_image(5*PIXELSQUARESIZE,0,bbishop);
	boardarray[5][0] = BLACKBISHOP;
	chessboard.draw_image(6*PIXELSQUARESIZE,0,bknight);
	boardarray[6][0] = BLACKKNIGHT;
	chessboard.draw_image(7*PIXELSQUARESIZE,0,brook);
	boardarray[7][0] = BLACKROOK;
	for(int i = 0; i <=7; i++)
	{
		chessboard.draw_image(i*PIXELSQUARESIZE,60,bpawn);
		boardarray[i][1] = BLACKPAWN;
	}
	updateBoard();
}

CImg<unsigned char> parseDraw(int xx, int yy, int pp)//draw light pieces on light squares, dark pieces on dark squares
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

void moveDraw(CImg<unsigned char> piece, int srcx, int srcy, int destx, int desty)//x and y are 0-7 only call if your move is valid you dummy
{
	movecount++;
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
	else if((piece == blking && srcx == destx+2) || (piece == wlking && srcx == destx+2)(piece == bdking && srcx == destx+2) || (piece == wdking && srcx == destx+2))
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
	//Queening a pawn
	else if((piece == blpawn && desty == 7) || (piece == bdpawn && desty == 0))
	{
		//
	}
	else if((piece == wlpawn && desty == 0) || (piece == wdpawn && desty == 0))
	{
		//
	}
	//The En Passant
	//else if(){}
	else
		chessboard.draw_image(destx*PIXELSQUARESIZE, desty*PIXELSQUARESIZE, piece);
	
	chessboard.draw_image(srcx*PIXELSQUARESIZE, srcy*PIXELSQUARESIZE,parseDraw(srcx,srcy,BLANK));
		
	updateBoard();
	boardarray[destx][desty] = boardarray[srcx][srcy];//move piece to new position
	boardarray[srcx][srcy] = BLANK;//override old one
}

void handleClick(int p, int x, int y, bool select)
{
	if(lastp == p)
	{
		lastp = BLANK;
		debugbox.fill(0).draw_text(0, 0, "PIECE DESELECTED.", green);
	}
	else if(select && (lastp != BLANK))//if they select a piece of their color
	{
		//check what piece to draw
		CImg<unsigned char> piecetodraw = parseDraw(x,y,p);
		//CHECK VALID MOVE FIRST
		if(true)
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
}
