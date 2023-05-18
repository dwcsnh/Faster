#ifndef CORGI_H
#define CORGI_H

#include "BaseObject.h"
#include "Attack.h"

class Corgi : public BaseObject
{
public:
	Corgi();
	~Corgi();
	enum WalkType // corgi's directional status
	{
		WALK_RIGHT = 0,
		WALK_LEFT = 1,
		ATTACKING = 2,
	};

	bool LoadImg(std::string IMG_Path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des, int scrollingOffset);
	void HandleInputAction(SDL_Event events, SDL_Renderer* screen, int scrollingOffset, Mix_Chunk* sfx);
	void SetClips(); 
	void HandlePlayerMovements(Map& mapData, int scrollingOffset, int& gameOver, Mix_Chunk* sfx);
	void CheckCollisionWithMap(Map& mapData, int scrollingOffset, int& gameOver, Mix_Chunk* sfx);
	void SetRedundantXY(const int& mapX, const int mapY)
	{
		redundantX = mapX;
		redundantY = mapY;
	}
	void CenterCorgiOnMap(Map& mapData, int scrollingOffset);
	bool GetMiddleStatus()
	{
		return middle;
	}
	float GetXPosition()
	{
		return xPos;
	}

private:
	float xStep;
	float yStep;

	float xPos;
	float yPos;

	int frameWidth; //corgi's width
	int frameHeight;

	SDL_Rect frameClip[32];
	Input inputType;
	int frameClipIndex;
	int corgiStatus;
	bool onGround;
	bool middle;

	int redundantX;
	int redundantY;
};

#endif 