#ifndef COMMON_FUNCTION_H
#define COMMON_FUNCTION_H

#include<Windows.h>
#include<string>
#include<vector>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<iostream>
#include<algorithm>
#include<SDL.h>
#include<SDL_ttf.h>
#include<SDL_image.h>
#include<SDL_mixer.h>

//Game variable
static SDL_Window* gameWindow = NULL;
static SDL_Renderer* gameScreen = NULL;
static SDL_Event gameEvent;
static TTF_Font* gameFont;
static TTF_Font* scoreFont;
static Mix_Chunk* electrocutedSFX;
static Mix_Chunk* jumpingSFX;
static Mix_Chunk* buttonClickSFX;
static Mix_Chunk* gameOverSFX;
static Mix_Music* backgroundMusic;

// Sreen
const int FPS = 28;
const int SCREEN_WIDTH = 1008;
const int SCREEN_HEIGHT = 672;
const int SCREEN_BPP = 32;
const int RENDERER_DRAW_COLOR = 255;

// Map
#define TILE_SIZE 48
#define BLANK_TILE 0
#define MAX_MAP_X 30
#define MAX_MAP_Y 14

// Player's physics
#define GRAVITY 1.4
#define MAX_FALL_SPEED 22
#define PLAYER_SPEED 8
#define PLAYER_JUMP_SPEED 14

// score
const std::string highScoreFilePath = "highscore//highscore.txt";

typedef struct Input
{
	int left;
	int right;
	int jump;
	int fall;
};

typedef struct Map
{
	int tile[14][2000];
	const char* fileName;
};

#endif