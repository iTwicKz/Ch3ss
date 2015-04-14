bool Rook::movePiece() {
	
	bool valid = false;
	
	bool firstMoved = true;

	if(move[0] != position[0] && move[1] != position[1]){	//checks if user has set move to current space
		int moveSpacesHor = move[0] - position[0];
		int moveSpacesVer = move[1] - position[1];
		
		if(collision(move, position)){				//if there is NOT an object in its path
			if(moveSpacesHor!=0 && move[1] == position[1]) {
				if(collisionAttack(move)){
					//kill(move);
				}
				position[0] = move[0];
				position[1] = move[1];
				firstMoved = false;
				valid = true;
				
			} else if(moveSpacesVer !=0 && move[0] == position[0]) {
				if(collisionAttack(move)) {
					//kill(move);
				}
				position[0] = move[0];
				position[1] = move[1];
				firstMoved = false;
				valid = true;
				
			} else cout<<"Brahhhhhhhhhhh you can't move dat";
			
			//Work on castling	
		}
	}

	else cout<<"That is the spot you are currently in";		//Most likely simply ignore
	
	return valid;
	
}
