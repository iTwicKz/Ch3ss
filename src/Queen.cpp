class Queen : public Piece {
	
	Queen : Piece (bool white, int positionX, int positionY) {
		this->type = 4 //Queen
		this->move[0] = 0;
		this->move[1] = 0;
		this->position[0] = positionX;	//X Location
		this->position[1] = positionY;	//Y location
		this->sprite = "QueenPics";	//Ask Darien
		this->white = white;
		this->dead = false;
	}
	
	void move() {
		int moveSpacesHor = move[0] - position[0];
		int moveSpacesVer = move[1] - position[1]
		
		if( moveSpacesHor!=0 && move[1] == position[1]) {
			if( collision() ) {
				position[0] = move[0];
			}
		} else if( moveSpacesVer !=0 && move[0] == position[0]) {
			if( collision() ) {
				position[1] = move[1];
			}
		} else if( abs(moveSpacesHor) == abs(moveSpacesVer)) {
			if( collision() ) {
				position[0] = move[0];
				position[1] = move[1];
			} 
		} else cout<<"Brahhhhhhhhhhh you can't move dat";	
	}
