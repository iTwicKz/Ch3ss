#include "CImg.h"

#ifndef IMAGEPATH
#define IMAGEPATH "res/"
#endif

using namespace cimg_library;

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
//CImg<unsigned char> graveyard(500,400,1,3,0);
	
//Displays (each display is a new window)
CImgDisplay main_disp(chessboard,"Chess");
//CImgDisplay graveyard_disp(graveyard,"Graveyard");

//Board Methods
void updateboard()
{
	chessboard.display(main_disp);//update board
}
void setup()
{
	//setup board
	//white
	chessboard.draw_image(0,420,wrook);
	chessboard.draw_image(60,420,wknight);
	chessboard.draw_image(120,420,wbishop);
	chessboard.draw_image(180,420,wqueen);
	chessboard.draw_image(240,420,wking);
	chessboard.draw_image(300,420,wbishop);
	chessboard.draw_image(360,420,wknight);
	chessboard.draw_image(420,420,wrook);
	for(int i = 0; i <=420; i+=60)
		chessboard.draw_image(i,360,wpawn);
		
	//black
	chessboard.draw_image(0,0,brook);
	chessboard.draw_image(60,0,bknight);
	chessboard.draw_image(120,0,bbishop);
	chessboard.draw_image(180,0,bqueen);
	chessboard.draw_image(240,0,bking);
	chessboard.draw_image(300,0,bbishop);
	chessboard.draw_image(360,0,bknight);
	chessboard.draw_image(420,0,brook);
	for(int i = 0; i <=420; i+=60)
		chessboard.draw_image(i,60,bpawn);
	updateboard();
}
void movedraw(CImg<unsigned char> piece, int srcx, int srcy, int destx, int desty)//x and y are 0-7
{
	chessboard.draw_image(destx*60, desty*60, piece);
	
	//determine if square is light or dark
	if(srcx%2 == 0 && srcy%2 == 0)
		chessboard.draw_image(srcx*60,srcy*60,lsquare);
	else if(srcx%2 == 0 && srcy != 0)
		chessboard.draw_image(srcx*60,srcy*60,dsquare);
	else if(srcx%2 != 0 && srcy%2 == 0)
		chessboard.draw_image(srcx*60,srcy*60,dsquare);
	else if(srcx%2 != 0 && srcy%2 != 0)
		chessboard.draw_image(srcx*60,srcy*60,lsquare);
		
	updateboard();
	
	srcx =destx;
	srcy =desty;
}
