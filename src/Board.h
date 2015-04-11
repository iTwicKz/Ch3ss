//for compiliation help: http://ubuntuforums.org/showthread.php?t=645321
#pragma once

#include "CImg.h"
#include <string>

#ifndef IMAGEPATH
#define IMAGEPATH "res/"
#endif

using namespace cimg_library;

class Board
{
	//each piece is 60px by 60px chessboard is 480px by 480px or 60px * 8
	private:
		CImg<unsigned char> board(IMAGEPATH "chessboard.png");
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
		//CImg<unsigned char> graveyard(480,480,1,3,0);
	
	//Displays (each display is a new window)
	protected:
		CImgDisplay main_disp(board,"Chess");
		//CImgDisplay graveyard_disp(graveyard,"Graveyard");
	
	//rest of class is public
	public:

	//Constructors
	Board()
	{
		//TODO finish constructors
	}
	
	//Board Class Methods
	void updateboard()
	{
		board.display(main_disp);//update board
	}
	void getPiece(std::string sprite)
	{
		//TODO
	}
	void setup()
	{
		//setup board
		//white
		board.draw_image(0,420,wrook);
		board.draw_image(60,420,wknight);
		board.draw_image(120,420,wbishop);
		board.draw_image(180,420,wqueen);
		board.draw_image(240,420,wking);
		board.draw_image(300,420,wbishop);
		board.draw_image(360,420,wknight);
		board.draw_image(420,420,wrook);
		for(int i = 0; i <=420; i+=60)
			board.draw_image(i,360,wpawn);

		//black
		board.draw_image(0,0,brook);
		board.draw_image(60,0,bknight);
		board.draw_image(120,0,bbishop);
		board.draw_image(180,0,bqueen);
		board.draw_image(240,0,bking);
		board.draw_image(300,0,bbishop);
		board.draw_image(360,0,bknight);
		board.draw_image(420,0,brook);
		for(int i = 0; i <=420; i+=60)
			board.draw_image(i,60,bpawn);

		updateboard();
	}
	void movedraw(CImg<unsigned char> piece, int srcx, int srcy, int destx, int desty)//x and y are 0-7
	{
		board.draw_image(destx*60, desty*60, piece);
		
		//determine if square is light or dark
		if(srcx%2 == 0 && srcy%2 == 0)
			board.draw_image(srcx*60,srcy*60,lsquare);
		else if(srcx%2 == 0 && srcy != 0)
			board.draw_image(srcx*60,srcy*60,dsquare);
		else if(srcx%2 != 0 && srcy%2 == 0)
			board.draw_image(srcx*60,srcy*60,dsquare);
		else if(srcx%2 != 0 && srcy%2 != 0)
			board.draw_image(srcx*60,srcy*60,lsquare);
		
		updateboard();
	
		srcx =destx;
		srcy =desty;
	}
}
