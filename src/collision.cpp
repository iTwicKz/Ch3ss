#include <cmath> 
#include <string>
#include <iostream>
using namespace std;
int board[8][8];
int move[2] = {4,2};
int position[2] = {6,3};
bool collision (int move[], int position[]) {
	int moveSpacesHor = move[0] - position[0];
	int moveSpacesVer = move[1] - position[1];
	bool free = true;
	if (abs(moveSpacesHor) == abs(moveSpacesVer)) { //Checks if diagnol
		if (moveSpacesHor == moveSpacesVer && moveSpacesHor > 0) {	//diagnol + +
			for ( int i = 1; i<abs(moveSpacesHor); i++) {
				if (board[position[0] + i][position[1] + i] != 153) {
					free = false;
				}
			}
		} else if (moveSpacesHor == moveSpacesVer && moveSpacesHor < 0) { //diagnol - -
			for ( int i = 1; i<abs(moveSpacesHor); i++) {
				if (board[position[0] - i][position[1] - i] != 153) {
					free = false;
				}
			}
		} else if (abs(moveSpacesHor) == moveSpacesVer) { //diagnol - +
			for ( int i = 1; i<abs(moveSpacesHor); i++) {
				if (board[position[0] - i][position[1] + i] != 153) {
					free = false;
				}
			}
		} else if (moveSpacesHor == abs(moveSpacesVer)) { //diagnol + -
			for ( int i = 1; i<abs(moveSpacesHor); i++) {
				if (board[position[0] + i][position[1] - i] != 153) {
					free = false;
				}
			}
		}
	} else if ((moveSpacesHor = 0) && (moveSpacesVer > 0)) { //Vertical +
		for ( int i = 1; i<moveSpacesVer; i++) {
			if (board[position[0]][position[1] + i] != 153) {
					free = false;
				}
			}
	} else if ((moveSpacesHor = 0) && (moveSpacesVer < 0)) { //Vertical -
		for ( int i = 1; i<abs(moveSpacesVer); i++) {
			if (board[position[0]][position[1] - i] != 153) {
					free = false;
				}
			}
	} else if ((moveSpacesVer = 0) && (moveSpacesHor > 0)) { //Horizontal +
		for ( int i = 1; i<moveSpacesHor; i++) {
			if (board[position[0] + 1][position[1]] != 153) {
					free = false;
				}
			}
	} else if ((moveSpacesVer = 0) && (moveSpacesHor < 0)) { //Horizontal -
		for ( int i = 1; i<abs(moveSpacesHor); i++) {
			if (board[position[0] - 1][position[1]] != 153) {
				free = false;
				}
			}
	}
	return free;
}




//Pawn		0
//knight	1
//Bishop	2
//Rook		3
//Queen		4
//King		5
