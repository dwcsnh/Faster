#include "corgi.h"

Corgi::Corgi()
{
	frameClipIndex = 0;
	xPos = 192;
	yPos = 432;
	xStep = 0;
	yStep = 0;
	frameWidth = 0;
	frameHeight = 0;
	corgiStatus = WALK_RIGHT;
	inputType.right = 0;
	inputType.left = 0;
	inputType.jump = 0;
	inputType.left = 0;
	onGround = false;
	electrocuted = false;
	rip = 0;
	sfxPlayed = false;

}

Corgi::~Corgi()
{

}

bool Corgi::LoadImg(std::string IMG_Path, SDL_Renderer* screen)
{
	bool loaded = BaseObject::LoadIMG(IMG_Path, screen);
	if (loaded == true)
	{
		frameWidth = rect.w / 32;
		frameHeight = rect.h;
	}

	return loaded;
}

void Corgi::SetClips()
{
	if (frameWidth > 0 and frameHeight > 0)
	{
		for (int i = 0; i < 32; i++) 
		{
			frameClip[i].x = i * frameWidth;
			frameClip[i].y = 0;
			frameClip[i].w = frameWidth;
			frameClip[i].h = frameHeight;
		}
	}
}

void Corgi::Show(SDL_Renderer* screen, int scrollingOffset)
{
	if (corgiStatus == WALK_LEFT and (inputType.left == 0 or inputType.right == 0))
	{
		LoadImg("asset//left sniffing corgi.png", screen);
		frameClipIndex++;
	}
	if (corgiStatus == WALK_RIGHT and (inputType.left == 0 or inputType.right == 0))
	{
		LoadImg("asset//right sniffing corgi.png", screen);
		frameClipIndex++;
	}
	if (inputType.left == 1 and corgiStatus == WALK_LEFT)
	{
		LoadImg("asset//corgi running to the left.png", screen);
		frameClipIndex++;
	}
	if (inputType.right == 1 and corgiStatus == WALK_RIGHT)
	{
		LoadImg("asset//corgi running to the right.png", screen);
		frameClipIndex++;
	}
	if (corgiStatus == WALK_RIGHT and onGround == false)
	{
		LoadImg("asset//corgi falling to the right.png", screen);
		frameClipIndex++;
	}
	if (corgiStatus == WALK_LEFT and onGround == false)
	{
		LoadImg("asset//corgi falling to the left.png", screen);
		frameClipIndex++;
	}
	if (electrocuted == true and corgiStatus == WALK_RIGHT)
	{
		LoadImg("asset//right electrocuted corgi.png", screen);
		frameClipIndex++;
		if (frameClipIndex >= 32)
		{
			rip ++;
		}

	}
	if (electrocuted == true and corgiStatus == WALK_LEFT)
	{
		LoadImg("asset//left electrocuted corgi.png", screen);
		frameClipIndex++;
		if (frameClipIndex >= 32)
		{
			rip ++;
		}
	}
	else if (scrollingOffset == 0)
	{
		LoadImg("asset//right sniffing corgi.png", screen);
		frameClipIndex++;
	}
	if (frameClipIndex >= 32)
	{
		frameClipIndex = 0;
	}

	rect.x = xPos - scrollingOffset;
	rect.y = yPos;

	SDL_Rect* CurrentClip = &frameClip[frameClipIndex];

	SDL_Rect destinationRect = { rect.x, rect.y, frameWidth, frameHeight };

	SDL_RenderCopy(screen, imageTexture, CurrentClip, &destinationRect);
}

void Corgi::HandleInputAction(SDL_Event events, SDL_Renderer* screen, int scrollingOffset, Mix_Chunk* sfx)
{
	if (events.type == SDL_KEYDOWN and scrollingOffset != 0)
	{
		switch (events.key.keysym.sym)
		{
			case SDLK_RIGHT:
			{
				corgiStatus = WALK_RIGHT;
				inputType.right = 1;
				inputType.left = 0;
			}
			break;

			case SDLK_d:
			{
				corgiStatus = WALK_RIGHT;
				inputType.right = 1;
				inputType.left = 0;
			}
			break;

			case SDLK_LEFT:
			{
				corgiStatus = WALK_LEFT;
				inputType.left = 1;
				inputType.right = 0;
			}
			break;

			case SDLK_a:
			{
				corgiStatus = WALK_LEFT;
				inputType.left = 1;
				inputType.right = 0;
			}
			break;

			case SDLK_w:
			{
				inputType.jump = 1;
				Mix_PlayChannel(-1, sfx, 0);
			}
			break;

			case SDLK_UP:
			{
				inputType.jump = 1;
				Mix_PlayChannel(-1, sfx, 0);
			}
			break;
		}
	}
		
	else if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_RIGHT:
		{
			inputType.right = 0;
			xStep = 0;
		}
		break;

		case SDLK_d:
		{
			inputType.right = 0;
			xStep = 0;
		}
		break;

		case SDLK_LEFT:
		{
			inputType.left = 0;
			xStep = 0;
		}
		break;

		case SDLK_a:
		{
			inputType.left = 0;
			xStep = 0;
		}
		break;

		case SDLK_w:
		{
			inputType.jump = 0;
		}
		break;

		case SDLK_UP:
		{
			inputType.jump = 0;
		}
		break;
		}
	}
	
}

void Corgi::HandlePlayerMovements(Map& mapData, int scrollingOffset, int& gameOver, Mix_Chunk* sfx, Mix_Chunk* sfx1)
{
	xStep = 0;
	yStep += GRAVITY;

	if (yStep >= MAX_FALL_SPEED)
	{
		yStep = MAX_FALL_SPEED;
	}

	if (inputType.left == 1)
	{
		xStep = -PLAYER_SPEED;
	}
	else if (inputType.right == 1)
	{
		xStep = +PLAYER_SPEED;
	}
	if (inputType.jump == 1)
	{
		if (onGround == true)
		{
			yStep -= PLAYER_JUMP_SPEED;
			onGround = false;
		}
		inputType.jump = 0;
	}


	xPos += xStep;
	yPos += yStep;

	CheckCollisionWithMap(mapData, scrollingOffset, gameOver, sfx, sfx1);
}

void Corgi::CheckCollisionWithMap(Map& mapData, int scrollingOffset, int& gameOver, Mix_Chunk* sfx, Mix_Chunk* sfx1)
{
	int x1Index = 0; // Index of corgi image's left
	int x2Index = 0; // Index of corgi image's right

	int y1Index = 0; // Index of corgi's back
	int y2Index = 0; //Index of corgi's feet

	// Check collisions horizontally

	if (inputType.right == 0 or inputType.left == 0)
	{
		int middleRedundance = (frameHeight - 60) < TILE_SIZE ? (frameHeight - 60) : TILE_SIZE;

		x1Index = (xPos + xStep + 14) / TILE_SIZE;
		x2Index = (xPos + xStep + frameWidth) / TILE_SIZE;

		y1Index = (yPos + 60) / TILE_SIZE;
		y2Index = (yPos + 60 + middleRedundance - 1) / TILE_SIZE;
	}

	if (inputType.left == 1 or inputType.right == 1)
	{
		int middleRedundance = (frameHeight - 36) < TILE_SIZE ? (frameHeight - 36) : TILE_SIZE;

		x1Index = (xPos + xStep + 12) / TILE_SIZE; // to fit the corgi's butt
		x2Index = (xPos + xStep + frameWidth - 10) / TILE_SIZE; // to fit the corgi's mouth

		y1Index = (yPos + 36) / TILE_SIZE;
		y2Index = (yPos + 36 + middleRedundance - 1) / TILE_SIZE;
	}

	if (y1Index >= 0 and y2Index < MAX_MAP_Y) // Check if corgi is in map area
	{
		if (xStep >= 0) // corgi's moving to the right
		{
			if (mapData.tile[y1Index][x2Index] != BLANK_TILE or mapData.tile[y2Index][x2Index] != BLANK_TILE)
			{
				xPos = x2Index * TILE_SIZE - (frameWidth - 8);
				xStep = 0;
			}
		}

		else if (xStep <= 0) // corgi's moving to the left
		{
			if (mapData.tile[y1Index][x1Index] != BLANK_TILE or mapData.tile[y2Index][x1Index] != BLANK_TILE)
			{
				xPos = (x1Index + 1) * TILE_SIZE - 4;
				xStep = 0;
			}
		}
	}


	// Check collision vertically

	if ((inputType.right == 0 or inputType.left == 0) and corgiStatus == WALK_RIGHT)
	{
		int middleRedundance = (frameWidth - 10) < TILE_SIZE ? (frameWidth - 10) : TILE_SIZE;

		x1Index = (xPos + 14) / TILE_SIZE;
		x2Index = (xPos + 14 + middleRedundance ) / TILE_SIZE;

		y1Index = (yPos + yStep + 40) / TILE_SIZE;
		y2Index = (yPos + yStep + frameHeight - 1) / TILE_SIZE;
	}

	if ((inputType.right == 0 or inputType.left == 0) and corgiStatus == WALK_LEFT)
	{
		int middleRedundance = (frameWidth - 14) < TILE_SIZE ? (frameWidth - 14) : TILE_SIZE;

		x1Index = (xPos + 10) / TILE_SIZE;
		x2Index = (xPos + 10 + middleRedundance) / TILE_SIZE;

		y1Index = (yPos + yStep + 40) / TILE_SIZE;
		y2Index = (yPos + yStep + frameHeight - 1) / TILE_SIZE;
	}

	if (inputType.right == 1)
	{
		int middleRedundance = (frameWidth - 14) < TILE_SIZE ? (frameWidth - 14) : TILE_SIZE;

		x1Index = (xPos + 24) / TILE_SIZE;
		x2Index = (xPos + 18 + middleRedundance) / TILE_SIZE;

		y1Index = (yPos + yStep + 40) / TILE_SIZE;
		y2Index = (yPos + yStep + frameHeight - 1) / TILE_SIZE;
	}

	if (inputType.left == 1)
	{
		int middleRedundance = (frameWidth - 18) < TILE_SIZE ? (frameWidth - 18) : TILE_SIZE;

		x1Index = (xPos + 16) / TILE_SIZE;
		x2Index = (xPos + 14 + middleRedundance) / TILE_SIZE;

		y1Index = (yPos + yStep + 40) / TILE_SIZE;
		y2Index = (yPos + yStep + frameHeight - 1) / TILE_SIZE;
	}

	if (y1Index >= 0 and y2Index < MAX_MAP_Y) // Check if corgi is in map area
	{
		if (yStep > 0)
		{
			if (mapData.tile[y2Index][x1Index] != BLANK_TILE or mapData.tile[y2Index][x2Index] != BLANK_TILE)
			{
				yPos = y2Index * TILE_SIZE - frameHeight;
				yStep = 0;
				onGround = true;
			}
		}
		if (yStep < 0)
		{
			if (mapData.tile[y1Index][x1Index] != BLANK_TILE or mapData.tile[y1Index][x2Index] != BLANK_TILE)
			{
				yPos = (y1Index + 1) * TILE_SIZE - 34; // - 40 so that when corgi is renderer, its head will be close to the tile that it collides
				yStep = 0;
			}
		}
	}

	// check if corgi's out of map dimension
	if (rect.y > SCREEN_HEIGHT + 100)
	{
		gameOver = 1;
		Mix_PlayChannel(-1, sfx, 0);
	}

	// check if corgi's striked by lightning
	if (xPos - 70 < scrollingOffset)
	{
		if (sfxPlayed == false)
		{
			Mix_PlayChannel(-1, sfx1, 0);
			sfxPlayed = true;
		}

		electrocuted = true;
		
		if (rip == 2)
		{
			gameOver = 1;
			Mix_PlayChannel(-1, sfx, 0);
		}
	}
}