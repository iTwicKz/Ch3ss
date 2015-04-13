#include "CImg.h"
#include "pieceTest.h"
#include "pawnTest.cpp"

#ifndef IMAGEPATH
#define IMAGEPATH "res/"
#endif

#define BLANK 10
#define WHITEKING 11
#define WHITEQUEEN 12
#define WHITEKNIGHT 13
#define WHITEBISHOP 14
#define WHITEROOK 15
#define WHITEPAWN 16
#define BLACKKING 17
#define BLACKQUEEN 18
#define BLACKKNIGHT 19
#define BLACKBISHOP 20
#define BLACKROOK 21
#define BLACKPAWN 22

#define PAWN 0
#define BISHOP 1
#define KNIGHT 2
#define ROOK 3
#define QUEEN 4
#define KING 5
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
Piece piecearray[8][8];

//last coordinates start outside board
int lastx = 9;
int lasty = 9;
int lastp = 0;

//to write to screen/debug
const unsigned char green[] = { 0,255,0 };


//Board Methods
void updateboard()
{
	chessboard.display(main_disp);//update board
	debugbox.display(debug_disp);
}

int returnpiece(int x, int y)//returns piece at spot on board given
{
	return(boardarray[x][y]);
	//return piecearray[x][y].getType();
}

void setup()
{
	
	//setup board
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
		{
			boardarray[i][j] = BLANK;
			piecearray[i][j].changeType(BLANK);//TODO FIX
		}
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
	updateboard();
}

void movedraw(CImg<unsigned char> piece, int srcx, int srcy, int destx, int desty)//x and y are 0-7
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
		
		
		updateboard();
		boardarray[destx][desty] = boardarray[srcx][srcy];//move piece to new position
		boardarray[srcx][srcy] = BLANK;//override old one
}

void handleclick(int p, int x, int y, bool select)
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
			movedraw(piece,lastx,lasty,x,y);
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
