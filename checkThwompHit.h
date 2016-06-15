//Box collision detector
int checkThwompHit( SDL_Rect a, SDL_Rect b );

int checkThwompHit( SDL_Rect a, SDL_Rect b )
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
    if(topA <= topB && bottomA < bottomB && bottomA > topB) //get crushed
    {
        return 0; //you dead
    }
    else if(topB <= topA && bottomB < bottomA && bottomB > topA) //on top
    {
        return 2;
    }
    else //hit side
    {
        return 1;
    }
}
