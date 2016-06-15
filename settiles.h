//Sets tiles from tile map
bool setTiles( Tile *tiles[] );

bool setTiles( Tile* tiles[] )
{
    //Success flag
    bool tilesLoaded = true;
    
    //The tile offsets
    int x = 0, y = 0;
    
    //Open the map
    std::ifstream map( "lazy.map" );
    
    //If the map couldn't be loaded
    if( !map.is_open() )
    {
        printf( "Unable to load map file!\n" );
        tilesLoaded = false;
    }
    else
    {
        //Initialize the tiles
        for( int i = 0; i < TOTAL_TILES; ++i )
        {
            //Determines what kind of tile will be made
            int tileType = -1;
            
            //Read tile from map file
            map >> tileType;
            
            //If the was a problem in reading the map
            if( map.fail() )
            {
                //Stop loading map
                printf( "Error loading map: Unexpected end of file!\n" );
                tilesLoaded = false;
                break;
            }
            
            //If the number is a valid tile number
            if( ( tileType >= 0 ) && ( tileType < TOTAL_TILE_SPRITES ) )
            {
                tiles[ i ] = new Tile( x, y, tileType );
            }
            //If we don't recognize the tile type
            else
            {
                //Stop loading map
                printf( "Error loading map: Invalid tile type at %d!\n", i );
                tilesLoaded = false;
                break;
            }
            
            //Move to next tile spot
            x += TILE_WIDTH;
            
            //If we've gone too far
            if( x >= LEVEL_WIDTH )
            {
                //Move back
                x = 0;
                
                //Move to the next row
                y += TILE_HEIGHT;
            }
        }
        
        //Clip the sprite sheet
        if( tilesLoaded )
        {
            gTileClips[ TILE_CLOUD ].x = 0;
            gTileClips[ TILE_CLOUD ].y = 0;
            gTileClips[ TILE_CLOUD ].w = TILE_WIDTH;
            gTileClips[ TILE_CLOUD ].h = TILE_HEIGHT;
            
            gTileClips[ TILE_SKY ].x = 0;
            gTileClips[ TILE_SKY ].y = 80;
            gTileClips[ TILE_SKY ].w = TILE_WIDTH;
            gTileClips[ TILE_SKY ].h = TILE_HEIGHT;
            
            gTileClips[ TILE_COIN ].x = 0;
            gTileClips[ TILE_COIN ].y = 160;
            gTileClips[ TILE_COIN ].w = TILE_WIDTH;
            gTileClips[ TILE_COIN ].h = TILE_HEIGHT;
            
            gTileClips[ TILE_BLOCK ].x = 80;
            gTileClips[ TILE_BLOCK ].y = 0;
            gTileClips[ TILE_BLOCK ].w = TILE_WIDTH;
            gTileClips[ TILE_BLOCK ].h = TILE_HEIGHT;
            
            gTileClips[ TILE_BRICK ].x = 80;
            gTileClips[ TILE_BRICK ].y = 80;
            gTileClips[ TILE_BRICK ].w = TILE_WIDTH;
            gTileClips[ TILE_BRICK ].h = TILE_HEIGHT;
            
            gTileClips[ TILE_QUESTION ].x = 80;
            gTileClips[ TILE_QUESTION ].y = 160;
            gTileClips[ TILE_QUESTION ].w = TILE_WIDTH;
            gTileClips[ TILE_QUESTION ].h = TILE_HEIGHT;
            
            gTileClips[ TILE_TOP ].x = 160;
            gTileClips[ TILE_TOP ].y = 0;
            gTileClips[ TILE_TOP ].w = TILE_WIDTH;
            gTileClips[ TILE_TOP ].h = TILE_HEIGHT;
            
            gTileClips[ TILE_MUSHROOM ].x = 160;
            gTileClips[ TILE_MUSHROOM ].y = 80;
            gTileClips[ TILE_MUSHROOM ].w = TILE_WIDTH;
            gTileClips[ TILE_MUSHROOM ].h = TILE_HEIGHT;
            
            gTileClips[ TILE_BUSH ].x = 160;
            gTileClips[ TILE_BUSH ].y = 160;
            gTileClips[ TILE_BUSH ].w = TILE_WIDTH;
            gTileClips[ TILE_BUSH ].h = TILE_HEIGHT;
            
            gTileClips[ TILE_GRAYBRICK ].x = 240;
            gTileClips[ TILE_GRAYBRICK ].y = 0;
            gTileClips[ TILE_GRAYBRICK ].w = TILE_WIDTH;
            gTileClips[ TILE_GRAYBRICK ].h = TILE_HEIGHT;
            
            gTileClips[ TILE_RIGHT ].x = 240;
            gTileClips[ TILE_RIGHT ].y = 80;
            gTileClips[ TILE_RIGHT ].w = TILE_WIDTH;
            gTileClips[ TILE_RIGHT ].h = TILE_HEIGHT;
            
            gTileClips[ TILE_BOTTOMRIGHT ].x = 240;
            gTileClips[ TILE_BOTTOMRIGHT ].y = 160;
            gTileClips[ TILE_BOTTOMRIGHT ].w = TILE_WIDTH;
            gTileClips[ TILE_BOTTOMRIGHT ].h = TILE_HEIGHT;
        }
    }
    
    //Close the file
    map.close();
    
    //If the map was loaded fine
    return tilesLoaded;
}
