#include "CImg.h"
#include "pieceTest.h"

#ifndef IMAGEPATH
#define IMAGEPATH "res/"
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

#define PIXELSQUARESIZE 60

using namespace cimg_library;

//each piece is 60px by 60px chessboard is 480px by 480px or 60px * 8
CImg<unsigned char> chessboard(IMAGEPATH "chessboard.png");
CImg<unsigned char> wking(IMAGEPATH "Chess_klt60.png");
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
CImg<unsigned char> lsquare(IMAGEPATH "lsq.png");
CImg<unsigned char> debugbox(4*PIXELSQUARESIZE,1*PIXELSQUARESIZE,1,3,0);
//Displays (each display is a new window)
CImgDisplay main_disp(chessboard,"Chess");
CImgDisplay debug_disp(debugbox,"Debug");

//Boardarray 
int boardarray[8][8];
Piece* pieceArray[32];
//start outside the board
int lastx = 9;
int lasty = 9;
int lastp = BLANK;

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

void setup()
{
	
	//setup board
	//for painting
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			boardarray[i][j] = BLANK;
	
	//++++++++++++++++++++++++++++++++++ INITIALIZING PIECE ARRAY ++++++++++++++++++++++++++++++++//

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

	//+++++++++++++++++++++++++++++++++++++++++++ END ++++++++++++++++++++++++++++++++++++++++++++++//
	
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

void moveDraw(CImg<unsigned char> piece, int srcx, int srcy, int destx, int desty)//x and y are 0-7
{
	//check for the special moves en passant or castling or queening
	//Castling move was checked as valid in handleclick
	if((piece == bking && srcx+2 == destx) || (piece == wking && srcx+2 == destx))//only time the king can move 2
	{
		chessboard.draw_image(destx*PIXELSQUARESIZE, desty*PIXELSQUARESIZE, piece);
		if(piece == wking)//done this way to prevent falsely identified castling
		{
			chessboard.draw_image(5*PIXELSQUARESIZE, desty*PIXELSQUARESIZE, wrook);
			chessboard.draw_image(7*PIXELSQUARESIZE, desty*PIXELSQUARESIZE, lsquare);
			boardarray[5][desty] = boardarray[7][desty];//move piece to new position
			boardarray[7][desty] = BLANK;//override old one
		}
		if(piece == bking)
		{
			chessboard.draw_image(5*PIXELSQUARESIZE, desty*PIXELSQUARESIZE, brook);
			chessboard.draw_image(7*PIXELSQUARESIZE, desty*PIXELSQUARESIZE, dsquare);
			boardarray[5][desty] = boardarray[7][desty];//move piece to new position
			boardarray[7][desty] = BLANK;//override old one
		}
	}
	else if((piece == bking && srcx == destx+2) || (piece == wking && srcx == destx+2))
	{
		chessboard.draw_image(destx*PIXELSQUARESIZE, desty*PIXELSQUARESIZE, piece);
		if(piece == wking)//done this way to prevent falsely identified castling
		{
			chessboard.draw_image(4*PIXELSQUARESIZE, desty*PIXELSQUARESIZE, wrook);
			chessboard.draw_image(0, desty*PIXELSQUARESIZE, dsquare);
			boardarray[4][desty] = boardarray[0][desty];//move piece to new position
			boardarray[0][desty] = BLANK;//override old one
		}
		if(piece == bking)
		{
			chessboard.draw_image(4*PIXELSQUARESIZE, desty*PIXELSQUARESIZE, brook);
			chessboard.draw_image(0, desty*PIXELSQUARESIZE, lsquare);
			boardarray[4][desty] = boardarray[0][desty];//move piece to new position
			boardarray[0][desty] = BLANK;//override old one
		}
	}
	//Queening a pawn
	else if(piece == bpawn && desty == 7)
	{
		//
	}
	else if(piece == wpawn && desty == 0)
	{
		//
	}
	//The En Passant
	//else if(){}
	else
		chessboard.draw_image(destx*PIXELSQUARESIZE, desty*PIXELSQUARESIZE, piece);
	//determine if square is light or dark
		if(srcx%2 == 0 && srcy%2 == 0)
			chessboard.draw_image(srcx*PIXELSQUARESIZE,srcy*PIXELSQUARESIZE,lsquare);
		else if(srcx%2 == 0 && srcy != 0)
			chessboard.draw_image(srcx*PIXELSQUARESIZE,srcy*PIXELSQUARESIZE,dsquare);
		else if(srcx%2 != 0 && srcy%2 == 0)
			chessboard.draw_image(srcx*PIXELSQUARESIZE,srcy*PIXELSQUARESIZE,dsquare);
		else if(srcx%2 != 0 && srcy%2 != 0)
			chessboard.draw_image(srcx*PIXELSQUARESIZE,srcy*PIXELSQUARESIZE,lsquare);
		
		
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
		//check if valid move
		CImg<unsigned char> piece;
		if(lastp == WHITEKING)
			piece = wking;
		if(lastp == WHITEQUEEN)
			piece = wqueen;
		if(lastp == WHITEKNIGHT)
			piece = wknight;
		if(lastp == WHITEBISHOP)
			piece = wbishop;
		if(lastp == WHITEROOK)
			piece = wrook;
		if(lastp == WHITEPAWN)
			piece = wpawn;
		if(lastp == BLACKKING)
			piece = bking;
		if(lastp == BLACKQUEEN)
			piece = bqueen;
		if(lastp == BLACKKNIGHT)
			piece = bknight;
		if(lastp == BLACKBISHOP)
			piece = bbishop;
		if(lastp == BLACKROOK)
			piece = brook;
		if(lastp == BLACKPAWN)
			piece = bpawn;
		//CHECK VALID MOVE FIRST
		if(true)
			moveDraw(piece,lastx,lasty,x,y);
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
