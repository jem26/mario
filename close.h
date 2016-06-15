//Frees media and shuts down SDL
void close( Tile* tiles[] );

void close( Tile* tiles[] )
{
    //Deallocate tiles
    for( int i = 0; i < TOTAL_TILES; ++i )
    {
        if( tiles[ i ] == NULL )
        {
            delete tiles[ i ];
            tiles[ i ] = NULL;
        }
    }
    
    //Free loaded images
    gDotRightTexture.free();
    gDotLeftTexture.free();
    gTileTexture.free();
    gMenuTexture.free();
    gLoseTexture.free();
    gTimeTexture.free();
    
    Mix_FreeChunk( gCoin );

    gCoin = NULL;
    
    //Free the music
    Mix_FreeMusic( gMusic );
    gMusic = NULL;
    
    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;
    
    gTextTexture.free();
    
    //Free global font
    TTF_CloseFont( gFont );
    gFont = NULL;
    
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
    Mix_CloseAudio();
}
