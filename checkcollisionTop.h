//Box collision detector
bool checkCollisionTop( SDL_Rect a, SDL_Rect b );

bool checkCollisionTop( SDL_Rect a, SDL_Rect b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    
    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;
    
    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;
    
    //If any of the sides from A are outside of B
	if ((rightA - leftB > 0) && (leftA - rightB<0)){
		if (((bottomA-topB <=5) && (bottomA-topB >=-5)))
    	{
    		return true;
    	}
    }
    return false;
}
