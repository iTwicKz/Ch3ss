#include "CImg.h"
#include "Piece.cpp"

#ifndef IMAGEPATH
#define IMAGEPATH "res/Default/"
#endif

#define BLANK -1
#define WHITEKING 30
#define WHITEQUEEN 28
#define WHITEKNIGHT 20
#define WHITEKNIGHTTWO 22
#define WHITEBISHOP 16
#define WHITEBISHOPTWO 18
#define WHITEROOK 24
#define WHITEROOKTWO 26
#define WHITEPAWN 0
#define WHITEPAWNTWO 1
#define WHITEPAWNTHREE 2
#define WHITEPAWNFOUR 3
#define WHITEPAWNFIVE 4
#define WHITEPAWNSIX 5
#define WHITEPAWNSEVEN 6
#define WHITEPAWNEIGHT 7
#define BLACKKING 31
#define BLACKQUEEN 29
#define BLACKKNIGHT 21
#define BLACKKNIGHTTWO 23
#define BLACKBISHOP 17
#define BLACKBISHOPTWO 19
#define BLACKROOK 25
#define BLACKROOKTWO 27
#define BLACKPAWN 8
#define BLACKPAWNTWO 9
#define BLACKPAWNTHREE 10
#define BLACKPAWNFOUR 11
#define BLACKPAWNFIVE 12
#define BLACKPAWNSIX 13
#define BLACKPAWNSEVEN 14 
#define BLACKPAWNEIGHT 15

//0-7 white pawns
//8-15 black pawns
//16,18 white bishops
//17,19 black bishops
//2

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

CImg<unsigned char> debugbox(4*PIXELSQUARESIZE,1*PIXELSQUARESIZE,1,3,0); //debug box

//Displays (each display is a new window)
CImgDisplay main_disp(chessboard,"Chess");
CImgDisplay debug_disp(debugbox,"Debug");

//Boardarray 
int boardarray[8][8];
//start outside the board
int lastx = 9;
int lasty = 9;
int lastp = BLANK;

//counter
int moveCount = 0;
//to write to screen/debug
const unsigned char green[] = { 0,255,0 };
		

class Board 
{
	friend class Piece;
	
	public:
		Board(){};
		//methods
		Piece* pieceArray[32];
		void setupPieceArray();
		void updateBoard();
		int returnPiece(int x, int y);
		int getMoveCount();
		CImg<unsigned char> parseDraw(int xx, int yy, int pp);
		void setup();
		void moveDraw(CImg<unsigned char> piece, int srcx, int srcy, int destx, int desty);
		bool handleClick(int p, int x, int y, bool select);
		bool collision(int moveX, int moveY, int positionX, int positionY);
		bool validMove(int srcx, int srcy, int destx, int desty);
};


