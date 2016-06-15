class Tile
{
public:
    //Initializes position and type
    Tile( int x, int y, int tileType );
    
    //Shows the tile
    void render( SDL_Rect& camera );
    
    //Get the tile type
    int getType();
    
    //Set the tile type
    void setType(int);
    
    //Get the collision box
    SDL_Rect getBox();
    
private:
    //The attributes of the tile
    SDL_Rect mBox;
    
    //The tile type
    int mType;
};

int Tile::getType()
{
    return mType;
}

void Tile::setType(int a)
{
    mType = a;
}



Tile::Tile( int x, int y, int tileType )
{
    //Get the offsets
    mBox.x = x;
    mBox.y = y;
    
    //Set the collision box
    mBox.w = TILE_WIDTH;
    mBox.h = TILE_HEIGHT;
    
    //Get the tile type
    mType = tileType;
}

void Tile::render( SDL_Rect& camera )
{
    //If the tile is on screen
    if( checkCollision( camera, mBox ) )
    {
        //Show the tile
        gTileTexture.render( mBox.x - camera.x, mBox.y - camera.y, &gTileClips[ mType ] );
    }
}


SDL_Rect Tile::getBox()
{
    return mBox;
}
