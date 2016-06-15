
class Mushroom
{
public:
    static const int MUSHROOM_WIDTH = 30;
    static const int MUSHROOM_HEIGHT = 30;
    
    static const int MUSHROOM_VEL = 0;
    Mushroom();
    Mushroom(int, int);
    void move( Tile *tiles[]);
    void render(SDL_Rect& camera);
    SDL_Rect getBox();
    bool showMushroom;
    void remove();
private:
    SDL_Rect mBox;
    int mVelx;
    bool hit;
};

Mushroom::Mushroom()
{
    mBox.x = 100;
    mBox.y = SCREEN_HEIGHT - MUSHROOM_HEIGHT - TILE_HEIGHT;
    mBox.w = MUSHROOM_WIDTH;
    mBox.h = MUSHROOM_HEIGHT;
    mVelx = MUSHROOM_VEL;
    
    hit = false;
}
void Mushroom::remove()
{
    mBox.x = -500;
}
Mushroom::Mushroom(int x, int y)
{
    mBox.x = x;
    mBox.y = SCREEN_HEIGHT - MUSHROOM_HEIGHT - (y *TILE_HEIGHT);
    mBox.w = MUSHROOM_WIDTH;
    mBox.h = MUSHROOM_HEIGHT;
    mVelx = MUSHROOM_VEL;
    
    hit = false;
}

void Mushroom::move(Tile *tiles[])
{
    mBox.x += mVelx;
    
    if((mBox.x <0) || (mBox.x +MUSHROOM_WIDTH > LEVEL_WIDTH) || touchesWall(mBox, tiles))
    {
        mVelx =-mVelx;
    }
}

void Mushroom::render(SDL_Rect& camera)
{
    gMushroomTexture.render(mBox.x - camera.x, mBox.y - camera.y);
}

SDL_Rect Mushroom::getBox()
{
    return mBox;
}
