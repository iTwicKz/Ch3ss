#include <iostream>
#include <cmath> 
int board[8][8];
int move[2] = {4,2};
int position[2] = {6,3};
using namespace std;

void kill(int move[], int position[]) {
	//update board
	
	//Piece at that position dies
	if (board[move[0]][move[1]] != 153 && board[position[0]][position[1]].getWhite() != board[move[0]][move[1]].getWhite()) {
		board[move[0]][move[1]].died(); //set opposing objects protected value of "dead" to true
		//board[move[0]][move[1]] = 153;
		//graveyard
		board[position[0]][position[1]] = board[move[0]][move[1]];//piece?
	}
	
}
