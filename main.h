#ifndef MAIN_H
#define MAIN_H

#include "constants.h"

//Score

int score = 0;
int lives = 3;
int deltaHeight = 0;
//Load Map
int reload = 0;
bool quit = false;
bool win = false;
bool start = false;
bool final_quit = false;

SDL_Renderer* gRenderer = NULL;
SDL_Window* gWindow = NULL;
TTF_Font *gFont = NULL;
#include "ltexture.h"

LTexture gTileTexture;
LTexture gMenuTexture;
LTexture gLoseTexture;
LTexture gWinTexture;
LTexture gDotRightTexture;
LTexture gDotLeftTexture;
LTexture gGoombaTexture;
LTexture gKoopaTexture;
LTexture gFlagTexture;
LTexture gTextTexture;
LTexture gLifeTexture;
LTexture gTimeTexture;
LTexture gHighScoresTexture;
LTexture gPromptTextTexture;
LTexture gThwompTexture;
SDL_Rect gSpriteClips[ WALKING_ANIMATION_FRAMES ];
LTexture gSpriteSheetTexture;
SDL_Rect gTileClips[ TOTAL_TILE_SPRITES ];
SDL_Rect flagBox;

Mix_Music *gMusic = NULL;
Mix_Chunk *gCoin = NULL;
Mix_Chunk *gBump = NULL;
Mix_Chunk *gDie = NULL;
Mix_Chunk *gOver = NULL;
Mix_Chunk *gJump = NULL;
Mix_Chunk *gPowerUpAppears = NULL;
Mix_Chunk *gPowerUp = NULL;

#include "checkcollision.h"
#include "checkcollisionTop.h"
#include "checkcollision2.h"
#include "checkEnemyHit.h"
#include "tile.h"
#include "toucheswall.h"
#include "toucheswallTop.h"
#include "dot.h"
#include "goomba.h"
#include "enemy.h"
#include "koopa.h"
#include "thwomp.h"
#include "init.h"
#include "settiles.h"
#include "loadmedia.h"
#include "close.h"
#include "checkThwompHit.h"

#endif

