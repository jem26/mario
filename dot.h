//The dot that will move around on the screen
#include "main.h"
class Dot
{
public:
    //The dimensions of the dot
    static const int DOT_WIDTH = 50;
    static const int DOT_HEIGHT = 40;
    
    //Maximum axis velocity of the dot
    static const int DOT_VEL =5;
    
    //Initializes the variables
    Dot();
    
    //Takes key presses and adjusts the dot's velocity
    void handleEvent( SDL_Event& e );
    
    //Moves the dot and check collision against tiles
    void move( Tile *tiles[] );
    
    //Centers the camera over the dot
    void setCamera( SDL_Rect& camera );
    
    //Shows the dot on the screen
    void render( SDL_Rect& camera, int direction, SDL_Rect* clip = NULL );
    
    //handle direction
    int getdirection();
    
    SDL_Rect getBox();
    void setXPos(int);
	void setYPos(int);
    int getLives();
    bool isMoving();
    bool getJumping();
    int getScore();
    int changeHeight;
    
private:
    //Collision box of the dot
    SDL_Rect mBox;
    
    //The velocity of the dot
    int mVelX, mVelY;
    
    //checks to see if object is jumping
    bool isJumping;
    bool isFalling;
    bool moving;
    
    //height right before jump
    int prevHeight;
    int jumpHeight;
    
    int direction; //1 is right 0 is left
};

Dot::Dot()
{
    //Initialize the collision box
    mBox.x = 10;
    mBox.y = SCREEN_HEIGHT-DOT_HEIGHT-TILE_HEIGHT+80;
    
    mBox.w = DOT_WIDTH;
    mBox.h = DOT_HEIGHT;
    
    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
    
    //Initialize Jumping
    isJumping=false;
    isFalling=false;
    moving=false;
    prevHeight=SCREEN_HEIGHT-DOT_HEIGHT-TILE_HEIGHT;
    changeHeight=0;
    jumpHeight=250;
    direction =1;
}

int Dot::getdirection()
{
    return direction;
}

void Dot::setXPos(int x)
{
    mBox.x = x;
}

SDL_Rect Dot::getBox()
{
    return mBox;
}

void Dot::handleEvent(SDL_Event& e)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_UP:
                if(!isFalling)
                {
                    mVelY=-2.0*DOT_VEL;
                    isJumping = true;
                    Mix_PauseMusic();
                    Mix_PlayChannel( -1, gJump, 0 );
                    Mix_ResumeMusic();
                }
                break;
            case SDLK_RIGHT: mVelX += DOT_VEL; direction=1; moving=true; break;
            case SDLK_LEFT: mVelX -= DOT_VEL; direction=0; moving=true; break;
        }
    }
    else if(e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_RIGHT: mVelX -= DOT_VEL; moving=false; break;
            case SDLK_LEFT: mVelX += DOT_VEL; moving=false; break;
        }
    }
}


void Dot::move( Tile *tiles[] )
{
    //Move the dot left or right
    mBox.x += mVelX;
    
    //If the dot went too far to the left or right or touched a wall
    if( ( mBox.x < 0 ) || ( mBox.x + DOT_WIDTH > LEVEL_WIDTH ) || touchesWall( mBox, tiles ) )
    {
        //move back
        mBox.x -= mVelX;
    }
    
    //Move the dot up or down
    mBox.y += mVelY;
    
    //check to see if still moving in y direction
    changeHeight = mBox.y - prevHeight;
	deltaHeight = changeHeight; 
    if (changeHeight > 0){//to prevent the ability to jump if not on a solid block
        isFalling = 1;
    }
	//if just landed
    if (changeHeight == 0 && isFalling == 1 && isJumping == 0)
    {
        isFalling = 0;
        mBox.y = (SCREEN_HEIGHT-(((SCREEN_HEIGHT-mBox.y)/TILE_HEIGHT)+1)*TILE_HEIGHT + DOT_HEIGHT);
        //adjust jump Height
        jumpHeight = 280 +(SCREEN_HEIGHT - mBox.y)-TILE_HEIGHT;
		mVelY = 0; 
    }
    if (changeHeight == 0 && isJumping ==1){//for when user bumps head into block
        jumpHeight = SCREEN_HEIGHT - mBox.y - 280;
        mBox.y -= mVelY;
        isFalling = true;
        isJumping = false;
    }
    prevHeight = mBox.y;
    
    //If the dot went too far up or down or touched a wall
    if (!touchesWallTop(mBox, tiles) && !isJumping){
    	mVelY = 2.5*DOT_VEL;
		isFalling = 1;


    }
    if( touchesWall( mBox, tiles ) )
    {
        //move back
        mBox.y -= mVelY;
    }
    //If the player has reached jump height
    if( ( mBox.y < SCREEN_HEIGHT-jumpHeight )/* || ( mBox.y + DOT_HEIGHT > SCREEN_HEIGHT )*/ )
    {
        mVelY=2.5*DOT_VEL;
    }
    if( ( mBox.y < SCREEN_HEIGHT-jumpHeight ))
    {
        isFalling = true;
        isJumping = false;
    }

    //check to see if player fell off level (lose life set back to start)
    if (mBox.y > SCREEN_HEIGHT){
        lives = lives - 1;
        if(lives==0)
        {
        	quit = true;
        }
        
        mBox.y = SCREEN_HEIGHT-DOT_HEIGHT-TILE_HEIGHT;
        mBox.x = 10;
        
    }

    //Player reaches end of level spot
    if (mBox.x > LEVEL_WIDTH - 100 )
    {
        win = true;
    }

}

void Dot::setCamera( SDL_Rect& camera )
{
    //Center the camera over the dot
    camera.x = ( mBox.x + DOT_WIDTH / 2 ) - SCREEN_WIDTH / 2;
    camera.y = ( mBox.y + DOT_HEIGHT / 2 ) - SCREEN_HEIGHT / 4;
    
    //Keep the camera in bounds
    if( camera.x < 0 )
    {
        camera.x = 0;
    }
    if( camera.y < 0 )
    {
        camera.y = 0;
    }
    if( camera.x > LEVEL_WIDTH - camera.w )
    {
        camera.x = LEVEL_WIDTH - camera.w;
    }
    if( camera.y > LEVEL_HEIGHT - camera.h )
    {
        camera.y = LEVEL_HEIGHT - camera.h;
    }
}

void Dot::render( SDL_Rect& camera, int direction, SDL_Rect* clip )
{
    if (direction==1)
        gDotRightTexture.render( mBox.x - camera.x, mBox.y - camera.y, clip );
    else
        gDotLeftTexture.render( mBox.x - camera.x, mBox.y - camera.y, clip );
}


int Dot::getLives()
{
    return lives;
}

bool Dot::isMoving()
{
    return moving;
}

bool Dot::getJumping()
{
    return isJumping;
}

void Dot::setYPos(int y)
{
	mBox.y = y - DOT_HEIGHT - 25;
	isFalling = false;
    jumpHeight = 280 +(SCREEN_HEIGHT - mBox.y) - TILE_HEIGHT;
}

int Dot::getScore()
{
    return score;
}
