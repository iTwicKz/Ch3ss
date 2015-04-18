#include "Board.cpp"
#include "CImg.h"
//#include "Piece.h"

//g++ main.cpp -lpthread -lX11 
//g++ -Wall -c

using namespace std;
using namespace cimg_library;

int main() 
{	
	//Piece testPiece;
	Board testBoard;
	
	testBoard.setupPieceArray();
	
	bool player = true;//true is white false is black
	bool selected = false;
	testBoard.setup();//setup board
	testBoard.updateBoard();
	
	while (!main_disp.is_closed()) //display loop until closed
	{
		main_disp.wait();
		if (main_disp.button() && main_disp.mouse_y()>=0) //if mouse is clicked on screen
		{
		const int x = main_disp.mouse_x();//get x coordinate
		const int y = main_disp.mouse_y();//get y coordinate
		
		selected = testBoard.handleClick(testBoard.returnPiece(x/PIXELSQUARESIZE,y/PIXELSQUARESIZE),x/PIXELSQUARESIZE,y/PIXELSQUARESIZE, selected);
		if(!selected)//change player
			player = !player;
		
		}
		testBoard.updateBoard();
	}
	return 0;
}
