#include "Board.cpp"
#include "CImg.h"
using namespace cimg_library;

int main() 
{	
	bool selectedalready = false;
	setup();//setup board
	updateboard();
	while (!main_disp.is_closed()) //display loop until closed
	{
		main_disp.wait();
		if (main_disp.button() && main_disp.mouse_y()>=0) //if mouse is clicked on screen
		{
		const int x = main_disp.mouse_x();//get x coordinate
		const int y = main_disp.mouse_y();//get y coordinate
		
		//TODO NEEDS TO WORK WITH PIECE OBJECTS
		//TEST CODE ONLY!
		
		handleclick(returnpiece(x/60,y/60),x/60,y/60,selectedalready);
		selectedalready = !selectedalready;//flips
		
		//END TEST CODE
		
		
		
		}
	}
	return 0;
}
