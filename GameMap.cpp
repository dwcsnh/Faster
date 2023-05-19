#include "GameMap.h"

void GameMap::LoadMap(const char* IMG_path, int mapLoaded) // thêm 1 biến chỉ số map đã load
{
	FILE* fp = NULL;
	fopen_s(&fp, IMG_path, "rb"); // read map file
	if (fp == NULL)
	{
		return;
	}

	for (int i = 0; i < MAX_MAP_Y; i++) // read and set tile type (number) for every position on map
	{
		for (int j = (mapLoaded - 1) * MAX_MAP_X; j < mapLoaded * MAX_MAP_X; j++) // when reach new map -> mapLoaded++ -> load new map
		{
			fscanf_s(fp, "%d", &gameMap.tile[i][j]);
		}
	}

	gameMap.fileName = IMG_path;
	fclose(fp);
}

void GameMap::LoadTiles(SDL_Renderer* screen)
{
	char file_img[30];
	FILE* fp = NULL;

	for (int i = 0; i < MAX_TILE_TYPE; i++) // load tiles as images base on tile types (number) loaded before
	{
		sprintf_s(file_img, "map/%d.png", i);

		fopen_s(&fp, file_img, "rb");
		if (fp == NULL)
		{
			continue;
		}

		fclose(fp);

		tileMap[i].LoadIMG(file_img, screen);
	}
}

void GameMap::DrawMap(SDL_Renderer* screen, int scrollingOffset)
{
		int mapX = 0;
		int mapY = 0;

		int x1Position = (scrollingOffset % TILE_SIZE) * -1; // the mising proportion of first-column tiles
		int x2Position = x1Position + SCREEN_WIDTH + (x1Position == 0 ? 0 : TILE_SIZE);

		int y1Position = 0; // the missing proportion of first-row tiles
		int y2Position = SCREEN_HEIGHT ;

		for (int i = y1Position; i < y2Position; i += TILE_SIZE) // render tiles based on calculated position
		{
			mapX = scrollingOffset / TILE_SIZE; // check the x index of the first tile that the map scrolls to

			for (int j = x1Position; j < x2Position; j += TILE_SIZE)
			{
				int val = gameMap.tile[mapY][mapX];

				if (val > 0)
				{
					tileMap[val].SetRectPosition(j, i);
					tileMap[val].Render(screen);
				}
				mapX++;
			}
			mapY++;
		}
}