
class Thwomp
{
public:
    static const int THWOMP_WIDTH = 65;
    static const int THWOMP_HEIGHT = 70;

    static const int THWOMP_VEL = 1;

    Thwomp();
    Thwomp(int, int);
    void move( Tile *tiles[]);
    void render(SDL_Rect& camera);
    SDL_Rect getBox();
	int getYPos();

private:
    SDL_Rect mBox;
    int mVely;
    bool hit;
};

Thwomp::Thwomp()
{
    mBox.x = 100;
    mBox.y = SCREEN_HEIGHT - THWOMP_HEIGHT - TILE_HEIGHT;
    mBox.w = THWOMP_WIDTH;
    mBox.h = THWOMP_HEIGHT;
    mVely = THWOMP_VEL;
    hit = false;
}

Thwomp::Thwomp(int x, int y)
{
    mBox.x = x;
    mBox.y = SCREEN_HEIGHT - THWOMP_HEIGHT - (y *TILE_HEIGHT);
    mBox.w = THWOMP_WIDTH;
    mBox.h = THWOMP_HEIGHT;
    mVely = THWOMP_VEL;
    hit = false;
}

void Thwomp::move(Tile *tiles[])
{
    mBox.y += mVely;

    if((mBox.y > 400) || (mBox.y < 300) )
    {
        mVely =-mVely;
    }
}

//get position
int Thwomp::getYPos()
{
	return mBox.y;
}

void Thwomp::render(SDL_Rect& camera)
{
    gThwompTexture.render(mBox.x - camera.x, mBox.y - camera.y);
}

SDL_Rect Thwomp::getBox()
{
    return mBox;
}


