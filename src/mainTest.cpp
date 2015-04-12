#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "pieceTest.h"


using namespace std;

int main()
{
	Pawn pawn(true, 0, 0);
	
	cout << pawn.getType() << endl;
	
	Bishop bishop(false, 0, 0);
	
	cout << bishop.getType() << endl;
	
	Knight knight(true, 0, 0);
	
	cout << knight.getType() << endl;
	
	Rook rook(false, 0, 0);
	
	cout << rook.getType() << endl;
	
	Queen queen(true, 0, 0);
	
	cout << queen.getType() << endl;
	
	King king(false, 0, 0);
	
	cout << king.getType() << endl;
	
	
	
	
	return 0;
}
