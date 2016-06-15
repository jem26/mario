#include "main.h"
//Checks collision box against set of tiles
bool touchesWallTop( SDL_Rect box, Tile* tiles[] );

bool touchesWallTop( SDL_Rect box, Tile* tiles[] )
{
    //Go through the tiles
    for( int i = 0; i < TOTAL_TILES; ++i )
    {
        //If the tile is a wall type tile
        if( ( tiles[ i ]->getType() >02 ) && ( tiles[ i ]->getType() <= TILE_BOTTOMRIGHT ) )
        {
            //If the collision box touches the wall tile
            if( checkCollisionTop( box, tiles[ i ]->getBox() ) )
            {
                return true;
            }
        }
    }
    //If no wall tiles were touched
    return false;
}
