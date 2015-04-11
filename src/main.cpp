#include "Board.cpp"
#include "CImg.h"
using namespace cimg_library;

int main() 
{	
	int x = 0;//x coordinate on grid to convert to the array divide by 60
	int y = 0;//y coordinate on grid to convert to the array divide by 60
	setup();
	while (!main_disp.is_closed()) //display loop until closed
	{
		main_disp.wait();
		if (main_disp.button() && main_disp.mouse_y()>=0) //if mouse is clicked on screen
		{
			x = main_disp.mouse_x();//get x coordinate
			y = main_disp.mouse_y();//get y coordinate
			movedraw(bpawn, 0, 0, x/60, y/60, false);
			updateboard();
		}
	}
	return 0;
}
