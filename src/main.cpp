#include "Board.h"

int main() 
{	
	Board b;
	b.setup();
	while (!b.main_disp.is_closed()) //display loop until closed
	{
		b.main_disp.wait();
		if (b.main_disp.button() && b.main_disp.mouse_y()>=0) //if mouse is clicked on screen
		{
		const int x = b.main_disp.mouse_x();//get x coordinate
		const int y = b.main_disp.mouse_y();//get y coordinate
		
		b.updateboard();
		}
	}
	return 0;
}
