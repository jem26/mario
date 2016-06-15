#include <stdlib.h>
#include "enemy.h"
class Koopa: public Enemy
{
public:
    Koopa();
    Koopa(int, int,int,int,int);
    void move( Tile *tiles[]);
    void render(SDL_Rect& camera);
private:
    int travelMax;
    int distTravel;
};

Koopa::Koopa():Enemy(50,2,40,57,3)
{
    travelMax = TILE_WIDTH*4;
    distTravel = 0;
}
Koopa::Koopa(int x, int y, int w, int h, int v):Enemy(x,y,w,h,v)
{
    travelMax = TILE_WIDTH*4;
    distTravel = 0;
}

void Koopa::move(Tile *tiles[])
{
    mBox.x += mVelx;
    distTravel += abs(mVelx);
    if((mBox.x <0) || (mBox.x +mBox.w > LEVEL_WIDTH) || touchesWall(mBox, tiles) || distTravel >= travelMax)
    {
        mVelx =-mVelx;
    }
    if (distTravel >= travelMax)
        distTravel = 0;
}

void Koopa::render(SDL_Rect& camera)
{
	if(life)
	{
    	gKoopaTexture.render(mBox.x - camera.x, mBox.y - camera.y);
	}
	else
	{
		mBox.x = -100;
		mBox.y = -100;
	}
}
