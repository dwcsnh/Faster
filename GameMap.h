#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "CommonFunction.h"
#include "BaseObject.h"

#define MAX_TILE_TYPE 20

class TileMap : public BaseObject
{
public:
	TileMap() { ; }
	~TileMap() { ; }

};

class GameMap
{
public:
	GameMap() { ; }
	~GameMap() { ; }
	void LoadMap(const char* IMG_path, int mapLoaded);
	void LoadTiles(SDL_Renderer* screen);
	void DrawMap(SDL_Renderer* screen, int scrollingOffset);
	Map GetMap() const { return gameMap; };
	void SetMap(Map& mapData) { gameMap = mapData; };

private:
	Map gameMap;
	TileMap tileMap[MAX_TILE_TYPE];

};

#endif // !GAME_MAP_H