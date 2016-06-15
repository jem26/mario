//Loads media
bool loadMedia( Tile* tiles[] );

bool loadMedia( Tile* tiles[] )
{
    //Loading success flag
    bool success = true;
    //Load right dot texture
    if( !gDotRightTexture.loadFromFile( "pictures/MarioAnimateRight.bmp" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    
    if(!gDotLeftTexture.loadFromFile("pictures/MarioAnimateLeft.bmp"))
    {
        printf("Failed to load dot texture!\n");
        success=false;
    }
    
    //Load tile texture
    if( !gTileTexture.loadFromFile( "pictures/tiles.png" ) )
    {
        printf( "Failed to load tile set texture!\n" );
        success = false;
    }
    
    //Load thwomp texture
    if( !gThwompTexture.loadFromFile( "pictures/thwomp.png" ) )
    {
        printf( "Failed to load thwomp texture!\n" );
        success = false;
    }
    
    //Load flag texture
    if( !gFlagTexture.loadFromFile( "pictures/flagpole.png" ))
    {
        printf( "Failed to load thwomp texture!\n" );
        success = false;
    }
    

    //Load tile map
    if( !setTiles( tiles ) )
    {
        printf( "Failed to load tile set!\n" );
        success = false;
    }
    
    //load main menu
    if( !gMenuTexture.loadFromFile("pictures/menu.bmp") )
    {
        printf("Failed to load menu texture!\n");
        success = false;
    }
    
    if( !gLoseTexture.loadFromFile("pictures/endscreen.bmp"))
    {
        printf("Failed to load lose screen texture!\n");
        success = false;
    }
    
    if( !gWinTexture.loadFromFile("pictures/winscreen.bmp"))
    {
        printf("Failed to load lose screen texture!\n");
        success = false;
    }
    
    //load goomba
    if(!gGoombaTexture.loadFromFile("pictures/goomba.bmp"))
    {
        printf("Failed to load goomba!\n");
        success=false;
    }
    
    if(!gKoopaTexture.loadFromFile("pictures/koopa.bmp"))
    {
        printf("Failed to load koopa!\n");
        success=false;
    }
    
    else
    {
        //Set sprite clips
        gSpriteClips[ 0 ].x =   0;
        gSpriteClips[ 0 ].y =   0;
        gSpriteClips[ 0 ].w =  60;
        gSpriteClips[ 0 ].h =  40;
        
        gSpriteClips[ 1 ].x =  60;
        gSpriteClips[ 1 ].y =   0;
        gSpriteClips[ 1 ].w =  60;
        gSpriteClips[ 1 ].h =  40;
        
        gSpriteClips[ 2 ].x =  120;
        gSpriteClips[ 2 ].y =   0;
        gSpriteClips[ 2 ].w =  60;
        gSpriteClips[ 2 ].h =  40;
        
        gSpriteClips[ 3 ].x = 180;
        gSpriteClips[ 3 ].y =   0;
        gSpriteClips[ 3 ].w =  60;
        gSpriteClips[ 3 ].h =  40;
        
        gSpriteClips[ 4 ].x = 240;
        gSpriteClips[ 4 ].y =   0;
        gSpriteClips[ 4 ].w =  60;
        gSpriteClips[ 4 ].h =  40;
    }
    
    gFont = TTF_OpenFont( "SuperMario256.ttf", 20 );
    if( gFont == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        //Render text
        SDL_Color textColor = { 0, 0, 0 };
        if( !gTextTexture.loadFromRenderedText( "Score: ", textColor ) )
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
        if (!gLifeTexture.loadFromRenderedText("Lives: ", textColor ))
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
        if( !gTimeTexture.loadFromRenderedText( "Time: ", textColor ))
        {
        	printf("Failed to render text texture!\n");
        	success = false;
        }
        if (!gHighScoresTexture.loadFromRenderedText( "High Scores: ", textColor ))
        {
            printf("Failed to render text texture!\n");
            success = false;
        }
    }
    
    gMusic = Mix_LoadMUS( "sounds/mario.wav" );
    if( gMusic == NULL )
    {
        printf( "Failed to load main music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    //Load sound effects
    gCoin = Mix_LoadWAV( "sounds/coin.wav" );
    if( gCoin == NULL )
    {
        printf( "Failed to load coin sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    gBump = Mix_LoadWAV( "sounds/bump.wav" );
    if( gBump == NULL )
    {
        printf( "Failed to load bump sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    gDie = Mix_LoadWAV( "sounds/mariodie.wav" );
    if( gDie == NULL )
    {
        printf( "Failed to load die sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    gOver = Mix_LoadWAV( "sounds/gameover.wav" );
    if( gOver == NULL )
    {
        printf( "Failed to load game over sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    gJump = Mix_LoadWAV( "sounds/jump.wav" );
    if( gJump == NULL )
    {
        printf( "Failed to load jump sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    gPowerUpAppears = Mix_LoadWAV( "sounds/powerupappears.wav" );
    if( gPowerUpAppears == NULL )
    {
        printf( "Failed to load power up appears sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    gPowerUp = Mix_LoadWAV( "sounds/powerup.wav" );
    if( gPowerUp == NULL )
    {
        printf( "Failed to load power up sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    

    return success;
}
