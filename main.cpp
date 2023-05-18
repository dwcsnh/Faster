#include "CommonFunction.h"
#include "BaseObject.h"
#include "corgi.h"
#include "GameMap.h"
#include "Timer.h"
#include "Menu.h"
#include "Attack.h"

BaseObject gameBackground;

bool InitData();
bool LoadSkyBackground();
void Close();
void FreeMemory();
int readHighscore();

int main(int argc, char* argv[])
{
	int played = 0;
play_again:
	int highScore = readHighscore();
	srand(time(0));
	FreeMemory();
	if (InitData() == false)
	{
		return -1;
	}
	if (LoadSkyBackground() == false)
	{
		return -1;
	}

	int entrance = 0;
	bool isQuit = false;
	Menu gameMenu;
	if (played == 0)
	{
		entrance = gameMenu.ShowMenu(gameScreen, gameFont, "asset//menu background.png", buttonClickSFX);
		if (entrance == 1)
		{
			isQuit = true;
		}
		else
		{
			isQuit = false;
			played++;
		}
	}

	int ans = 0;
	int gameOver = 0;
	Timer timer;
	int start = 0;
	int scrollingOffset = 0;
	int mapLoaded = 1;
	int score = 0;
	int resume = 0;
	int playMusic = 0;
	std::vector<Attack*> ThreatList;

	GameMap gameMap;
	gameMap.LoadMap("map/infiniteMap0.dat", mapLoaded);
	gameMap.LoadTiles(gameScreen);


	Corgi gamePlayer;
	gamePlayer.LoadImg("asset//right sniffing corgi.png", gameScreen);
	gamePlayer.SetClips();

	for (int i = 0; i < 3; i++)
	{
		Attack* playerAttack = new Attack[3];
		playerAttack->LoadAttackIMG("asset//attack.png", gameScreen);
		playerAttack->SetAttackClip();
		ThreatList.push_back(playerAttack);
	}

	GameText gameResult;
	gameResult.SetTextColor(GameText::WHITE_TEXT);


	while (isQuit == false)
	{
		timer.start();
		if (playMusic == 0 and start == 1)
		{
			Mix_PlayMusic(backgroundMusic, 0);
			playMusic = 1;
		}
		if (Mix_PlayingMusic() == 0)
		{
			playMusic = 0;
		}
		if (gamePlayer.GetXPosition() > scrollingOffset + SCREEN_WIDTH / 2 and start == 1 and resume == 0)
		{
			scrollingOffset += PLAYER_SPEED;
		}
		else if (start == 1 and resume == 0)
		{
			scrollingOffset += 5;
		}
		
		if (scrollingOffset > 1440 * mapLoaded - SCREEN_WIDTH)
		{
			int num = rand() % 4 + 1;
			std::string mapPath = "map/infiniteMap";
			std::string mapIndex = std::to_string(num);
			mapPath += mapIndex;
			mapPath += ".dat";
			const char* cMapPath = mapPath.c_str();
			mapLoaded ++;
			gameMap.LoadMap(cMapPath, mapLoaded);
		}
		while (SDL_PollEvent(&gameEvent) != 0)
		{
			if (gameEvent.type == SDL_QUIT)
			{
				isQuit = true;
			}
			if (gameEvent.key.keysym.sym == SDLK_ESCAPE)
			{
				resume = 1;
			}
			gamePlayer.HandleInputAction(gameEvent, gameScreen, scrollingOffset, jumpingSFX);
		}

		SDL_SetRenderDrawColor(gameScreen, RENDERER_DRAW_COLOR, RENDERER_DRAW_COLOR, RENDERER_DRAW_COLOR, RENDERER_DRAW_COLOR);
		SDL_RenderClear(gameScreen);

		gameBackground.Render(gameScreen);

		Map mapData = gameMap.GetMap();

		gameMap.DrawMap(gameScreen, scrollingOffset);
		
		gamePlayer.HandlePlayerMovements(mapData, scrollingOffset, gameOver, gameOverSFX);

		score = (gamePlayer.GetXPosition() - 96) / 48;
		
		gamePlayer.Show(gameScreen, scrollingOffset);

		if (start == 1)
		{
			gameMenu.ShowScore(gameScreen, scoreFont, score, highScore);
			for (int i = 0; i < 3; i++)
			{
				Attack* spinningSaw = ThreatList.at(i);
				if (spinningSaw != NULL)
				{
					spinningSaw->RenderAttack(gameScreen, scrollingOffset, i * 48);
				}
			}
		}

		if (start == 0)
		{
			start = gameMenu.StartGame(gameScreen, gameFont, buttonClickSFX);
		}
		if (resume == 1)
		{
			resume = gameMenu.ResumeGame(gameScreen, gameFont, buttonClickSFX);
		}
		else if (resume == 2)
		{
			isQuit = true;
		}

		//show result

		if (gameOver == 1)
		{
			Mix_PauseMusic();
			int ending = gameMenu.GameOverNotification(gameScreen, gameFont, "asset//game over background.png", "Play Again", "Exit", score, highScore, buttonClickSFX);

			if (ending == 1) {
				isQuit = true;
			}
			else {
				isQuit = false;
				gameOver = 0;
				goto play_again;
			}
		}

		SDL_RenderPresent(gameScreen);

		int realTime = timer.GetTick();
		int secondPerLoop = 1000 / FPS;

		if (realTime < secondPerLoop)
		{
			int delay = secondPerLoop - realTime;
			SDL_Delay(delay);
		}
	}
	
	
	return 0;
}


bool InitData()
{
	bool success = true;
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret < 0)
	{
		return false;
	}
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	gameWindow = SDL_CreateWindow("Faster!", 
								SDL_WINDOWPOS_CENTERED, 
								SDL_WINDOWPOS_CENTERED, 
								SCREEN_WIDTH, SCREEN_HEIGHT, 
								SDL_WINDOW_SHOWN);
	if (!gameWindow)
	{
		std::cout << "Unable to initialize window!" << std::endl;
		success = false;
	}
	else
	{
		std::cout << "Initialize window successfully!" << std::endl;

		gameScreen = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED);
		if (!gameScreen)
		{
			std::cout << "Unable to initialize renderer!" << std::endl;
			success = false;
		}
		else
		{
			std::cout << "Initialize renderer successfully!" << std::endl;

			SDL_SetRenderDrawColor(gameScreen, RENDERER_DRAW_COLOR, RENDERER_DRAW_COLOR, RENDERER_DRAW_COLOR, RENDERER_DRAW_COLOR);
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) && imgFlags))
			{
				success = false;
			}
			else 
			{
				TTF_Init();
				if (TTF_Init() == -1)
				{
					success = false;
				}
				else
				{
					gameFont = TTF_OpenFont("asset//deluxe.ttf", 17);
					scoreFont = TTF_OpenFont("asset//DisposableDroid.ttf", 20);
					if (gameFont == NULL or scoreFont == NULL)
					{
						std::cout << "Unable to initialize font!" << std::endl;
						success = false;
					}
					else
					{
						std::cout << "Initialize font successfully!" << std::endl;
						Mix_Init(MIX_INIT_MP3);
						if (Mix_Init(MIX_INIT_MP3) == -0)
						{
							return false;
						}
						if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
						{
							return false;
						}
						jumpingSFX = Mix_LoadWAV("SFX//Jump.wav");
						gameOverSFX = Mix_LoadWAV("SFX//Game Over.wav");
						buttonClickSFX = Mix_LoadWAV("SFX//Game Click.wav");
						backgroundMusic = Mix_LoadMUS("SFX//backgroundmusic.mp3");
						if (jumpingSFX == NULL or gameOverSFX == NULL or buttonClickSFX == NULL or backgroundMusic == NULL)
						{
							success = false;
						}
					}
				}
			}
		}
	}

	return success;
}

bool LoadSkyBackground()
{
	bool sky = gameBackground.LoadIMG("asset//game background.png", gameScreen);
	if (!sky)
	{
		return false;
	}
	return true;
}

void Close()
{
	gameBackground.Free();
	SDL_DestroyRenderer(gameScreen);
	gameScreen = NULL;

	SDL_DestroyWindow(gameWindow);
	gameWindow = NULL;

	IMG_Quit();
	SDL_Quit();
}

void FreeMemory()
{
	gameBackground.Free();
	SDL_DestroyRenderer(gameScreen);
	gameScreen = NULL;
	SDL_DestroyWindow(gameWindow);
	gameWindow = NULL;
}

int readHighscore()
{
	std::ifstream inputFile(highScoreFilePath);

	if (!inputFile.is_open())
	{
		std::cout << "Failed to open file" << std::endl;
		return -1;
	}
	int num;
	if (inputFile >> num)
	{
		std::cout << "Current highscore: " << num << std::endl;
	}
	else
	{
		std::cout << "Failed to read number from file." << std::endl;
	}
	inputFile.close();
	return num;
}