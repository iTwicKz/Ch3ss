#include "CImg.h"		//our image rendering


#ifndef IMAGEPATH		
#define IMAGEPATH "res/Default/"	//image files source folder
#endif

//--------------------------MACRO DEFINITIONS----------------------------------//
#define BLANK -1 				//blank space identifier
#define WHITEKING 30			//white king identifier
#define WHITEQUEEN 28			//white queen identifier
#define WHITEKNIGHT 20			//white knight identifier
#define WHITEKNIGHTTWO 22		//second white knight identifier
#define WHITEBISHOP 16			//white bishop identifier
#define WHITEBISHOPTWO 18		//second white bishop identifier
#define WHITEROOK 24			//white rook identifier
#define WHITEROOKTWO 26			//second white rook identifier
#define WHITEPAWN 0 			//white pawn identifier
#define WHITEPAWNTWO 1 			//second white pawn identifier
#define WHITEPAWNTHREE 2 		//third white pawn identifier
#define WHITEPAWNFOUR 3 		//fourth white pawn identifier
#define WHITEPAWNFIVE 4 		//fifth white pawn identifier
#define WHITEPAWNSIX 5 			//sixth white pawn identifier
#define WHITEPAWNSEVEN 6 		//seventh white pawn identifier
#define WHITEPAWNEIGHT 7 		//eighth white pawn identifier
#define BLACKKING 31 			//black king identifier
#define BLACKQUEEN 29 			//black queen identifier
#define BLACKKNIGHT 21 			//black knight identifier
#define BLACKKNIGHTTWO 23 		//second black knight identifier
#define BLACKBISHOP 17 			//black bishop identifier
#define BLACKBISHOPTWO 19 		//second black bishop identifier
#define BLACKROOK 25 			//black rook identifier
#define BLACKROOKTWO 27  		//second black rook identifier
#define BLACKPAWN 8  			//black pawn identifier
#define BLACKPAWNTWO 9			//second black pawn identifier
#define BLACKPAWNTHREE 10 		//third black pawn identifier
#define BLACKPAWNFOUR 11  		//fourth black pawn identifier
#define BLACKPAWNFIVE 12 		//fifth black pawn identifier
#define BLACKPAWNSIX 13 		//sixth black pawn identifier
#define BLACKPAWNSEVEN 14  		//seventh black pawn identifier
#define BLACKPAWNEIGHT 15  		//eighth black pawn identifier

#define PIXELSQUARESIZE 100		//changes simple intergers into pixels blocks to form buttons
//------------------------------------------------------------------------------//

using namespace cimg_library;	//image rendering

//--------------------------IMAGE FILES----------------------------------------//
  //each piece is 60px by 60px chessboard is 480px by 480px or 60px * 8//
CImg<unsigned char> chessboard(IMAGEPATH "chessboard.jpg"); 

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

CImg<unsigned char> selection(IMAGEPATH "selection.jpg");

//------------------------------------------------------------------------------//

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
int lastPieceP = BLANK;

//counter
int moveCount = 0;
//to write to screen/debug
const unsigned char green[] = { 0,255,0 };
bool turn = true; //true = white's turn, false = black's turn
bool check = false;

class Board 
{
	friend class Piece;		//allows for Piece to have certain access to Board class
	
	public:
		Board(){};			//Board default constructor
		Piece* pieceArray[32];	//Array which houses all 32 Piece Objects and, in turn, thier information
		//Methods
		void setupPieceArray();	//initialized PieceArray with loops
		void updateBoard();		//redraws the board onto the screen
		int returnPiece(int x, int y);	//returns piece identitfier based on position on board
		int getMoveCount();				//returns the amount of counts that have occurred in the game
		CImg<unsigned char> parseDraw(int xx, int yy, int pp);		//converts piece identifier into image file path
		void setup();			//setup for board array and game display
		void moveDraw(CImg<unsigned char> piece, int srcX, int srcY, int destx, int desty);		//draws moving of pieces after validation process
		bool handleClick(int p, int x, int y, bool select);										//handles selection, deselection, and movement for pieces on board
		bool collision(int moveX, int moveY, int positionX, int positionY);						//returns whether or not there is a clear legal path between the source and destination
		bool validMove(int srcX, int srcY, int destx, int desty);								//checks if move is a legal move based on collision, piece laws, friendly fire, and check
		void enPassant(bool *typeMoveLegal, int srcX, int srcY, int destx, int desty, int srcPiece, bool whiteColorsrc, int srcPieceColor);		//handles special en passant move for pawns
		void castling(bool *typeMoveLegal, int srcX, int srcY, int destx, int desty, int srcPiece);		//handles special castling move for kings and rooks
		bool isCheck(int kingX, int kingY, int newX, int newY, int oldX, int oldY);					//checks for check
};


