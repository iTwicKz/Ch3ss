//http://ubuntuforums.org/showthread.php?t=645321 to help build makefile
#include "CImg.h"
using namespace cimg_library;

//INIT each piece is 60px by 60px chessboard is 480px by 480px or 60px * 8
CImg<unsigned char> board("chessboard.png");
CImg<unsigned char> wking("Chess_klt60.png");
CImg<unsigned char> bking("Chess_kdt60.png");
CImg<unsigned char> wqueen("Chess_qlt60.png");
CImg<unsigned char> bqueen("Chess_qdt60.png");
CImg<unsigned char> wknight("Chess_nlt60.png");
CImg<unsigned char> bknight("Chess_ndt60.png");
CImg<unsigned char> wbishop("Chess_blt60.png");
CImg<unsigned char> bbishop("Chess_bdt60.png");
CImg<unsigned char> wrook("Chess_rlt60.png");
CImg<unsigned char> brook("Chess_rdt60.png");
CImg<unsigned char> wpawn("Chess_plt60.png");
CImg<unsigned char> bpawn("Chess_pdt60.png");
CImg<unsigned char> dsquare("dsq.png");
CImg<unsigned char> lsquare("lsq.png");
//ENDINIT

CImgDisplay main_disp(board,"Chess");

void setup();
void movedraw(CImg<unsigned char> piece, int srcx, int scry, int destx, int desty);
void displayloop();
int main() 
{
	//const unsigned char red[] = { 255,0,0 }, green[] = { 0,255,0 }, blue[] = { 0,0,255 };//for writing messages
	
	setup();
	
	while (!main_disp.is_closed()) //display loop until closed
	{
		main_disp.wait();
		//board.display(main_disp);//update board
		if (main_disp.button() && main_disp.mouse_y()>=0) //if mouse is clicked on screen
		{
		const int x = main_disp.mouse_x();
		const int y = main_disp.mouse_y();
		
		movedraw(bpawn, 2, 1, x/60, y/60);
		//board.draw_image(x,y,0,0,bking,bking.getchannel(3),1,1);
		//board.draw_image(x,y,bking);
		board.display(main_disp);//update board
		}
	}
	return 0;
}
void setup()
{
	//setup board
	board.draw_image(0,420,wrook);
	board.draw_image(60,420,wknight);
	board.draw_image(120,420,wbishop);
	board.draw_image(180,420,wqueen);
	board.draw_image(240,420,wking);
	board.draw_image(300,420,wbishop);
	board.draw_image(360,420,wknight);
	board.draw_image(420,420,wrook);
	
	board.draw_image(0,360,wpawn);
	board.draw_image(60,360,wpawn);
	board.draw_image(120,360,wpawn);
	board.draw_image(180,360,wpawn);
	board.draw_image(240,360,wpawn);
	board.draw_image(300,360,wpawn);
	board.draw_image(360,360,wpawn);
	board.draw_image(420,360,wpawn);
	
	board.draw_image(0,0,brook);
	board.draw_image(60,0,bknight);
	board.draw_image(120,0,bbishop);
	board.draw_image(180,0,bqueen);
	board.draw_image(240,0,bking);
	board.draw_image(300,0,bbishop);
	board.draw_image(360,0,bknight);
	board.draw_image(420,0,brook);
	
	board.draw_image(0,60,bpawn);
	board.draw_image(60,60,bpawn);
	board.draw_image(120,60,bpawn);
	board.draw_image(180,60,bpawn);
	board.draw_image(240,60,bpawn);
	board.draw_image(300,60,bpawn);
	board.draw_image(360,60,bpawn);
	board.draw_image(420,60,bpawn);
	
	board.display(main_disp);
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
	board.display(main_disp);//update board
}
