bool King::movePiece() {

	bool valid = false;

	if(move[0] != position[0] && move[1] != position[1]) //checks if user has set move to current space
	{	
		if(move[0] - position[0] == 0 && abs(move[1] - position[1]) == 1) //Vertical move
		{
			if(collisionAttack(move))
			{	
				//kill(move);
			
			position[0] = move[0];		
			position[1] = move[1];
			valid = true;
			}
		} 
		else if(abs(move[0] - position[0]) == 1 && move[1] - position[1] == 0) //Horizontal move
		{
			if(collisionAttack(move))
			{	
				//kill(move);
			
			position[0] = move[0];		
			position[1] = move[1];
			valid = true;
			}
		} 
		else if(abs(move[0] - position[0]) == 1 && abs(move[1] - position[1]) == 1) //Diagonal Move
		{
			if(collisionAttack(move))
			{	
				//kill(move);
			
			position[0] = move[0];		
			position[1] = move[1];
			valid = true;
			}
		} 
		else if (abs(move[0] - position[0]) == 2 && firstMoved && move[1]==position[1]) //castle
		{
			if(move[0] == 6 && collision(move,position) && collisionAttack(move)) 
			{
				if(isCheck(4,position[1]) && isCheck(5,position[1]) && isCheck(6,position[1])) //castle right
				{
				position[0] = move[0];
				position[1] = move[1];
				//MOVE ROOK?
				}
			}
			else if (move[0] = 2 && collision(move,position) && collisionAttack(move))
			{
				if(isCheck(2,position[1]) && isCheck(3,position[1]) && isCheck(4,position[1])) //castle left
				{
				position[0] = move[0];
				position[1] = move[1];
				//MOVE ROOK?
				}
			}
		}
		else cout<<"Brahhhhhhhhhhh you can't move dat";
	}
	else cout<<"That is the spot you are currently in";		//Most likely simply ignore
	
	return valid;
}
