//Using SDL, SDL_image, standard IO, strings, and file streams
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <unistd.h>
#include <iostream>
#include "main.h"
using namespace std;

int main( int argc, char* args[] )
{
    system("clear");
    ofstream out_data;
    out_data.open("scores.txt", std::ios::app);
	printf("Welcome to Mario Time Trials!\n");
	printf("Click on Start to play\n");
	printf("Created by: Chris Rho, James Farrington, Jamie Maher, and Joey Curci\n");
    SDL_Event e;
    int frame = 0;
    string str_score = "Score: ";
    string str_lives = "Lives: ";
    string str_time = "Time: ";

    
    flagBox.x = LEVEL_WIDTH - 80;
    flagBox.y = SCREEN_HEIGHT-FLAG_HEIGHT-TILE_HEIGHT+120;
    
    flagBox.w = FLAG_WIDTH;
    flagBox.h = FLAG_HEIGHT;
    
    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //The level tiles
        Tile* tileSet[ TOTAL_TILES ];
        Dot dot;
        Goomba goomba(100,0,30,30,2);
        Goomba goomba2(2960,0,30,30,2);
        Koopa koopa1(400, 3,40,57,3);
        Koopa koopa2(3440,2,40,57,3);
        Thwomp thwomp1(1520,1);
        
        //Load media
        if( !loadMedia( tileSet ) )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            //Main loop flag
            bool start = false;
            Mix_PlayMusic( gMusic, -1 );

            //Level camera
            SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

            //start button
            SDL_Rect StartButton;
            StartButton.x=208;
            StartButton.y=317;
            StartButton.w=225;
            StartButton.h=75;

            //handle main menu
            while( !start  && !quit && !win)
            {
                //find mouse
                while(SDL_PollEvent(&e)!=0)
                {
                    if(e.type == SDL_QUIT)
                    {
                        final_quit = true;
                        quit = true;
                    }

                    if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
                    {
                        //get mouse position
                        int x, y;
                        SDL_GetMouseState(&x, &y);
                        bool inside = true;
                        //check if mouse inside button
                        if(x<StartButton.x)
                        {
                            inside = false;
                        }
                        else if(x>StartButton.x+StartButton.w)
                        {
                            inside = false;
                        }
                        else if(y<StartButton.y)
                        {
                            inside = false;
                        }
                        else if(y>StartButton.y + StartButton.h)
                        {
                            inside = false;
                        }
                        //change color and check for click
                        if(inside)
                        {
                            SDL_SetRenderDrawColor(gRenderer,0,255,255,255);

                            //check for click
                            if(e.type == SDL_MOUSEBUTTONDOWN)
                            {
                                start=true; //begin game
                            }
                        }
                        else
                        {
                            SDL_SetRenderDrawColor(gRenderer,0,255,255,255);
                        }
                    }
                }
                //clear screen
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF,0xFF);
                SDL_RenderClear( gRenderer );
                //Present title screen
                gMenuTexture.render(0,0,NULL,0,NULL,SDL_FLIP_NONE );
                SDL_RenderDrawRect(gRenderer, &StartButton);
                SDL_RenderPresent( gRenderer );
            }

            //While application is running
            while( !quit && !win )
            {
                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                        final_quit = true;
                    }

                    dot.handleEvent( e );
                }

                //Move the dot
                dot.move( tileSet );
                goomba.move(tileSet);
                goomba2.move(tileSet);
                koopa1.move(tileSet);
                koopa2.move(tileSet);
                thwomp1.move(tileSet);
                dot.setCamera( camera );
                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );

                //Render level
                for( int i = 0; i < TOTAL_TILES; ++i )
                {
                    tileSet[ i ]->render( camera );
                }

                //Render dot
                SDL_Rect* currentClip = &gSpriteClips[ frame / 4 ];

                dot.render( camera, dot.getdirection(), currentClip );
                goomba.render( camera );
                goomba2.render( camera );
                koopa1.render( camera );
                koopa2.render( camera );
                thwomp1.render( camera );
                gFlagTexture.render( flagBox.x - camera.x, flagBox.y - camera.y );

                gTextTexture.render( ( SCREEN_WIDTH - gTextTexture.getWidth() ) / 12, ( SCREEN_HEIGHT - gTextTexture.getHeight() ) / 12 );


                gLifeTexture.render( ( SCREEN_WIDTH -gLifeTexture.getWidth() ) / 1.2, ( SCREEN_HEIGHT - gTextTexture.getHeight() ) / 12 );

                gTimeTexture.render( ( SCREEN_WIDTH / 2 -gTimeTexture.getWidth()), (SCREEN_HEIGHT - gTimeTexture.getHeight())/12);


                str_score = str_score + std::to_string(score);
                str_lives = str_lives + std::to_string(dot.getLives());
                str_time = str_time + std::to_string(SDL_GetTicks()/1000);
                gTextTexture.loadFromRenderedText(str_score, {0,0,0});
                gLifeTexture.loadFromRenderedText(str_lives, {0,0,0,});
                gTimeTexture.loadFromRenderedText(str_time, {0,0,0,});
                str_score = "Score: ";
                str_lives = "Lives: ";
                str_time = "Time: ";
                //Go to next frame
                if (dot.isMoving())
                {
                    ++frame;
                }
                else
                {
                    if (dot.getdirection() == 1)
                        frame = 0;
                    else
                        frame = 1;
                }

                //Cycle animation
                if( frame / 4 >= WALKING_ANIMATION_FRAMES )
                {
                    frame = 0;
                }

                if (checkCollision(goomba.getBox(), dot.getBox()))
                {
                    if (checkEnemyHit(goomba.getBox(), dot.getBox()))
                    {
                        goomba.setLife(false);
                        Mix_PauseMusic();
                        Mix_PlayChannel( -1, gBump, 0 );
                        Mix_ResumeMusic();
                        score+=150;
                    }
                    else
                    {
                        dot.setXPos(10);
                        lives--;

                        if (dot.getLives() == 0 )
                            quit = true;
                    }
                }

                else if (checkCollision(koopa1.getBox(), dot.getBox()))
                {
                    if (checkEnemyHit(koopa1.getBox(), dot.getBox()))
                    {
                        koopa1.setLife(false);
                        Mix_PauseMusic();
                        Mix_PlayChannel( -1, gBump, 0 );
                        Mix_ResumeMusic();
                        score+=200;
                    }
                    else
                    {
                        dot.setXPos(10);
                        lives--;
                        if (dot.getLives() == 0)
                            quit = true;
                    }
                }

                else if (checkCollision(koopa2.getBox(), dot.getBox()))
                {
                    if (checkEnemyHit(koopa2.getBox(), dot.getBox()))
                    {
                        koopa2.setLife(false);
                        Mix_PauseMusic();
                        Mix_PlayChannel( -1, gBump, 0 );
                        Mix_ResumeMusic();
                        score+=200;
                    }
                    else
                    {
                        dot.setXPos(10);
                        lives--;
                        if (dot.getLives() == 0)
                            quit = true;
                    }
                }

                else if (checkCollision(goomba2.getBox(), dot.getBox()))
                {
                    if (checkEnemyHit(goomba2.getBox(), dot.getBox()))
                    {
                        goomba2.setLife(false);
                        Mix_PauseMusic();
                        Mix_PlayChannel( -1, gBump, 0 );
                        Mix_ResumeMusic();
                        score+=200;
                    }
                    else
                    {
                        dot.setXPos(10);
                        lives--;
                        if (dot.getLives() == 0)
                            quit = true;
                    }
                }

                else if(checkCollision(thwomp1.getBox(), dot.getBox()))
                {

                    if (checkThwompHit(thwomp1.getBox(), dot.getBox())==2)
                    {
                        int thwomp1Y = thwomp1.getYPos();
                        dot.setYPos(thwomp1Y);
                    }
                    else
                    {
                        dot.setXPos(10);
                        lives--;
                        if (dot.getLives() == 0)
                            quit = true;
                    }
                }
                //Update screen
                SDL_RenderPresent( gRenderer );
            }
        }
        //Free resources and close SDL
        if( win )
        {
            Mix_PauseMusic();
            Mix_PlayChannel(-1, gOver, 0);
            
            string final_points = std::to_string(score);
            string final_time = std::to_string(SDL_GetTicks()/1000);
            string final_score = std::to_string(score - 15*(SDL_GetTicks()/1000) + 150*lives);

            gTextTexture.loadFromRenderedText(final_points, {255,255,255,});
            gLifeTexture.loadFromRenderedText(final_score, {255,255,255,});
            gTimeTexture.loadFromRenderedText(final_time, {255,255,255,});

            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderClear( gRenderer );

            gWinTexture.render(0,0,NULL,0,NULL,SDL_FLIP_NONE );

            gTimeTexture.render( ( SCREEN_WIDTH /2-100), ( SCREEN_HEIGHT - 275 ) );
            gTextTexture.render( ( SCREEN_WIDTH /2-100), ( SCREEN_HEIGHT - 230 ) );
            gLifeTexture.render( ( SCREEN_WIDTH /2-100), ( SCREEN_HEIGHT - 185 ) );

            out_data << final_score+"\n";
            out_data.close();
            system("sort -nr scores.txt > scores_temp.txt");
            system("rm scores.txt");
            system("mv scores_temp.txt scores.txt");

            ifstream in_data("scores.txt");
            string line;
            int counter = 0;

            gHighScoresTexture.loadFromRenderedText("High Scores: \n", {255,255,255,});
            gHighScoresTexture.render( ( SCREEN_WIDTH /2), ( SCREEN_HEIGHT - 300) );

            if (in_data.is_open())
            {
                while ( getline (in_data,line) && counter < 10)
                {
                    gHighScoresTexture.loadFromRenderedText(line, {255,255,255,});
                    gHighScoresTexture.render( ( SCREEN_WIDTH /2+100), ( SCREEN_HEIGHT - 275 + 20*counter ) );
                    counter++;
                }
                in_data.close();
            }

            SDL_RenderPresent( gRenderer );
        }
        else if (!final_quit)
        {
            Mix_PauseMusic();
            Mix_PlayChannel(-1, gDie, 0);
            SDL_RenderClear( gRenderer );
            gLoseTexture.render(0,0,NULL,0,NULL,SDL_FLIP_NONE );
            SDL_RenderPresent( gRenderer );
        }

        while (!final_quit)
        {
            while( SDL_PollEvent( &e ) != 0 )
            {
                //User requests quit
                if( e.type == SDL_QUIT )
                {
                    final_quit = true;
                }

                dot.handleEvent( e );
            }
        }
        close( tileSet );
    }

    printf("Good bye, play again!\n");
    return 0;

}
