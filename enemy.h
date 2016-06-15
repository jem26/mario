#ifndef ENEMY_H
#define ENEMY_H
class Enemy
{
public:
    Enemy();
    Enemy(int,int,int,int,int);
    SDL_Rect getBox();
    bool getLife();
    void setLife(bool);
protected:
    SDL_Rect mBox;
    int mVelx;
    bool hit;
    bool life;
};

Enemy::Enemy()
{
    hit = false;
    life = true;
	static const int ENEMY_WIDTH = 30;
	static const int ENEMY_HEIGHT = 30;
	static const int ENEMY_VEL = 2;
	mBox.x = 100;
	mBox.y = SCREEN_HEIGHT - ENEMY_HEIGHT - TILE_HEIGHT;
	mBox.w = ENEMY_WIDTH;
	mBox.h = ENEMY_HEIGHT;
	mVelx = ENEMY_VEL;
}

Enemy::Enemy(int x, int y, int w, int h, int v)
{
	static const int ENEMY_WIDTH = w;
	static const int ENEMY_HEIGHT = h;
	static const int ENEMY_VEL = v;
	mBox.x = x;
	mBox.y = SCREEN_HEIGHT - ENEMY_HEIGHT - (y * TILE_HEIGHT);
	mBox.w = ENEMY_WIDTH;
	mBox.h = ENEMY_HEIGHT;
	mVelx = ENEMY_VEL;
    life = true;


}

SDL_Rect Enemy::getBox()
{
    return mBox;
}

bool Enemy::getLife()
{
    return life;
}

void Enemy::setLife(bool l)
{
    life = l;
}
#endif
