class Rook : public Piece {
	
	Rook(bool firstMoved) : Piece (bool white, int positionX, int positionY) {
		
		//Don't know what to do about initiating firstmoved
		this->type = 3 //Rook
		this->move[0] = 0;
		this->move[1] = 0;
		this->position[0] = positionX;	//X Location
		this->position[1] = positionY;	//Y location
		this->sprite = "RookPics";	//Ask Darien
		this->white = white;
		this->dead = false;
	}
	
	void move() {
		int moveSpacesHor = move[0] - position[0];
		int moveSpacesVer = move[1] - position[1]
		
		if( moveSpacesHor!=0 && move[1] == position[1]) {
			if( collision() ) {
				position[0] = move[0];
				firstMoved = true;
			}
		} else if( moveSpacesVer !=0 && move[0] == position[0]) {
			if( collision() ) {
				position[1] = move[1];
				firstMoved = true;
			}
		} else cout<<"Brahhhhhhhhhhh you can't move dat";
		//Work on castling	
	}
