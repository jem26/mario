#include "main.h"

//Checks collision box against set of tiles
bool touchesWall( SDL_Rect box, Tile* tiles[] );

bool touchesWall( SDL_Rect box, Tile* tiles[] )
{
    //Go through the tiles
    for( int i = 0; i < TOTAL_TILES; ++i )
    {
        if( tiles[ i ]->getType() ==02)
        {
            //If the collision box touches the a coin
            if( checkCollision( box, tiles[ i ]->getBox() ) )
            {
                tiles[ i ]->setType(01);
                score = score + 100;
                Mix_PauseMusic();
                Mix_PlayChannel( -1, gCoin, 0 );
                Mix_ResumeMusic();
                
                return false;
            }
        }
        // if tile is question box
        if( tiles[ i ]->getType() ==05)
        {
        	if( checkCollision2( box, tiles[i]->getBox() ) )
        	{
        		tiles[ i ] -> setType(9);
        		tiles[ i - 62] -> setType(7);
                Mix_PauseMusic();
                Mix_PlayChannel( -1, gPowerUpAppears, 0 );
                Mix_ResumeMusic();
        		return true;
        	}
        }
        if( tiles[ i ]->getType() ==07)
        {
            //If the collision box touches the mushroom
            if( checkCollision( box, tiles[ i ]->getBox() ) )
            {
                tiles[ i ]->setType(01);
                lives++;
                Mix_PauseMusic();
                Mix_PlayChannel( -1, gPowerUp, 0 );
                Mix_ResumeMusic();
                return false;
                
            }
        }
        
        //If the tile is a wall type tile
        if( ( tiles[ i ]->getType() >02 ) && ( tiles[ i ]->getType() <= TILE_BOTTOMRIGHT ) )
        {
            //If the collision box touches the wall tile
            if( checkCollision( box, tiles[ i ]->getBox() ) )
            {
                return true;
            }
        }
    }
    
    //If no wall tiles were touched
    return false;
}
