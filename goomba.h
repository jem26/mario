#include "enemy.h"
class Goomba: public Enemy
{
public:
    Goomba();
    Goomba(int, int, int, int, int);
    void move( Tile *tiles[]);
	void render(SDL_Rect& camera);
};

Goomba::Goomba():Enemy(100,0,30,30,2)
{
}

Goomba::Goomba(int x, int y,int w, int h, int v): Enemy(x,y,w,h,v)
{
}

void Goomba::move(Tile *tiles[])
{
    mBox.x += mVelx;
    
    if((mBox.x < 80) || (mBox.x +mBox.w > LEVEL_WIDTH) || touchesWall(mBox, tiles) )
    {
        mVelx =-mVelx;
    }
}

void Goomba::render(SDL_Rect& camera)
{
	if(life)
	{	gGoombaTexture.render(mBox.x - camera.x, mBox.y - camera.y);
	}
	else
	{
		mBox.x = -100;
	}
}
