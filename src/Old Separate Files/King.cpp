bool King::movePiece() {

	bool valid = false;

	if(move[0] != position[0] && move[1] != position[1]) //checks if user has set move to current space
	{	
		if(move[0] - position[0] == 0 && abs(move[1]) - abs(position[1]) == 1)
		{
			if(collisionAttack(move))	
				//kill(move);
			
			position[0] = move[0];		
			position[1] = move[1];
			valid = true;
		} 
		else if(abs(move[0]) - abs(position[0]) == 1 && move[1] - position[1] == 0)
		{
			if(collisionAttack(move))	
				//kill(move);
			
			position[0] = move[0];		
			position[1] = move[1];
			valid = true;
		} 
		else if(abs(move[0]) - abs(position[0]) == 1 && abs(move[1]) - abs(position[1]) == 1)
		{
			if(collisionAttack(move))	
				//kill(move);
			
			position[0] = move[0];		
			position[1] = move[1];
			valid = true;
		} 
		else cout<<"Brahhhhhhhhhhh you can't move dat";
	}
	else cout<<"That is the spot you are currently in";		//Most likely simply ignore
	
	return valid;
}
