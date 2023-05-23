#include "Menu.h"

Menu::Menu()
{

}
Menu::~Menu()
{

}

int Menu::ShowMenu(SDL_Renderer* screen, TTF_Font* font, std::string path, Mix_Chunk* sfx)
{
	menu:
	GameText button1; // play game
	button1.SetTextColor(GameText::WHITE_TEXT);
	button1.SetText("Play Game");

	GameText button2; // about
	button2.SetTextColor(GameText::WHITE_TEXT);
	button2.SetText("Tutorials");

	GameText button3; // exit
	button3.SetTextColor(GameText::WHITE_TEXT);
	button3.SetText("Exit");

	BaseObject menu;
	menu.LoadIMG(path, screen);
	SDL_SetRenderDrawColor(screen, RENDERER_DRAW_COLOR, RENDERER_DRAW_COLOR, RENDERER_DRAW_COLOR, RENDERER_DRAW_COLOR);
	SDL_RenderClear(screen);
	menu.RenderBackground(screen, NULL);

	SDL_Event gEvent;
	while (true)
	{
		button1.LoadText(screen, font);
		int h1 = button1.GetTextHeight();
		int w1 = button1.GetTextWidth();
		SDL_Rect button1Dimension;
		button1Dimension.x = (SCREEN_WIDTH - w1) / 2;
		button1Dimension.y = (SCREEN_HEIGHT - h1) / 2;
		button1.RenderText(screen, button1Dimension.x, button1Dimension.y);

		button2.LoadText(screen, font);
		int h2 = button2.GetTextHeight();
		int w2 = button2.GetTextWidth();
		SDL_Rect button2Dimension;
		button2Dimension.x = (SCREEN_WIDTH - w2) / 2;
		button2Dimension.y = button1Dimension.y + 60;
		button2.RenderText(screen, button2Dimension.x, button2Dimension.y);
		
		button3.LoadText(screen, font);
		int h3 = button3.GetTextHeight();
		int w3 = button3.GetTextWidth();
		SDL_Rect button3Dimension;
		button3Dimension.x = (SCREEN_WIDTH - w3) / 2;
		button3Dimension.y = button1Dimension.y + 120;
		button3.RenderText(screen, button3Dimension.x, button3Dimension.y);

		SDL_RenderPresent(screen);

		while (SDL_PollEvent(&gEvent) != 0)
		{
			if (gEvent.type == SDL_QUIT)
			{
				return 1;
			}
			else if (gEvent.type == SDL_MOUSEMOTION || gEvent.type == SDL_MOUSEBUTTONDOWN)
			{
				int x, y;
				SDL_GetMouseState(&x, &y);

				if (x > button1Dimension.x && x < button1Dimension.x + w1 && y > button1Dimension.y && y < button1Dimension.y + h1)
				{
					button1.SetTextColor(GameText::RED_TEXT);
					if (gEvent.button.button == SDL_BUTTON_LEFT and gEvent.button.state == SDL_PRESSED)
					{
						Mix_PlayChannel(-1, sfx, 0);
						return 0;
					}
				}
				else
				{
					button1.SetTextColor(GameText::WHITE_TEXT);
				}

				if (x > button3Dimension.x && x < button3Dimension.x + w3 && y > button3Dimension.y && y < button3Dimension.y + h3)
				{
					button3.SetTextColor(GameText::RED_TEXT);
					if (gEvent.button.button == SDL_BUTTON_LEFT and gEvent.button.state == SDL_PRESSED)
					{
						Mix_PlayChannel(-1, sfx, 0);
						return 1;
					}
				}
				else
				{
					button3.SetTextColor(GameText::WHITE_TEXT);
				}

				if (x > button2Dimension.x && x < button2Dimension.x + w2 && y > button2Dimension.y && y < button2Dimension.y + h2)
				{
					button2.SetTextColor(GameText::RED_TEXT);
					if (gEvent.button.button == SDL_BUTTON_LEFT and gEvent.button.state == SDL_PRESSED)
					{
						Mix_PlayChannel(-1, sfx, 0);
						BaseObject Tutorial;
						Tutorial.LoadIMG("asset//menu tutorial.png", screen);
						SDL_SetRenderDrawColor(screen, RENDERER_DRAW_COLOR, RENDERER_DRAW_COLOR, RENDERER_DRAW_COLOR, RENDERER_DRAW_COLOR);
						SDL_RenderClear(screen);
						Tutorial.RenderBackground(screen, NULL);
						SDL_RenderPresent(screen);
						while (true)
						{
							while (SDL_PollEvent(&gEvent) != 0)
							{
								if (gEvent.type == SDL_QUIT)
								{
									return 1;
								}
								else if (gEvent.type == SDL_KEYDOWN)
								{
									if (gEvent.key.keysym.sym == SDLK_ESCAPE)
									{
										menu.Free();
										Tutorial.Free();
										button1.FreeTextTexture();
										button2.FreeTextTexture();
										button3.FreeTextTexture();
										goto menu;
									}
								}
							}
						}
					}
				}
				else
				{
					button2.SetTextColor(GameText::WHITE_TEXT);
				}


			}
		}

	}

	return 1;
}

int Menu::ResumeGame(SDL_Renderer* screen, TTF_Font* font, Mix_Chunk* sfx)
{
	GameText button1; // continue
	button1.SetTextColor(GameText::WHITE_TEXT);
	button1.SetText("Continue?");

	GameText button2; // exit
	button2.SetTextColor(GameText::WHITE_TEXT);
	button2.SetText("Exit");

	GameText button3; // return to menu
	button3.SetTextColor(GameText::WHITE_TEXT);
	button3.SetText("Menu");

	SDL_Event gEvent;
	while (true)
	{
		button1.LoadText(screen, font);
		int h1 = button1.GetTextHeight();
		int w1 = button1.GetTextWidth();
		SDL_Rect button1Dimension;
		button1Dimension.x = (SCREEN_WIDTH - w1) / 2;
		button1Dimension.y = (SCREEN_HEIGHT - h1) / 2 - 20;
		button1.RenderText(screen, button1Dimension.x, button1Dimension.y);

		button2.LoadText(screen, font);
		int h2 = button2.GetTextHeight();
		int w2 = button2.GetTextWidth();
		SDL_Rect button2Dimension;
		button2Dimension.x = (SCREEN_WIDTH - w2) / 2;
		button2Dimension.y = button1Dimension.y + 120;
		button2.RenderText(screen, button2Dimension.x, button2Dimension.y);

		button3.LoadText(screen, font);
		int h3 = button3.GetTextHeight();
		int w3 = button3.GetTextWidth();
		SDL_Rect button3Dimension;
		button3Dimension.x = (SCREEN_WIDTH - w3) / 2;
		button3Dimension.y = button1Dimension.y + 60;
		button3.RenderText(screen, button3Dimension.x, button3Dimension.y);

		SDL_RenderPresent(screen);

		while (SDL_PollEvent(&gEvent) != 0)
		{
			if (gEvent.type == SDL_QUIT)
			{
				return 1;
			}
			else if (gEvent.type == SDL_MOUSEMOTION || gEvent.type == SDL_MOUSEBUTTONDOWN)
			{
				int x, y;
				SDL_GetMouseState(&x, &y);

				if (x > button1Dimension.x && x < button1Dimension.x + w1 && y > button1Dimension.y && y < button1Dimension.y + h1)
				{
					button1.SetTextColor(GameText::RED_TEXT);
					if (gEvent.button.button == SDL_BUTTON_LEFT and gEvent.button.state == SDL_PRESSED)
					{
						Mix_PlayChannel(-1, sfx, 0);
						return 0;
					}
				}
				else
				{
					button1.SetTextColor(GameText::WHITE_TEXT);
				}

				if (x > button2Dimension.x && x < button2Dimension.x + w2 && y > button2Dimension.y && y < button2Dimension.y + h2)
				{
					button2.SetTextColor(GameText::RED_TEXT);
					if (gEvent.button.button == SDL_BUTTON_LEFT and gEvent.button.state == SDL_PRESSED)
					{
						Mix_PlayChannel(-1, sfx, 0);
						return 2;
					}
				}
				else
				{
					button2.SetTextColor(GameText::WHITE_TEXT);
				}

				if (x > button3Dimension.x && x < button3Dimension.x + w3 && y > button3Dimension.y && y < button3Dimension.y + h3)
				{
					button3.SetTextColor(GameText::RED_TEXT);
					if (gEvent.button.button == SDL_BUTTON_LEFT and gEvent.button.state == SDL_PRESSED)
					{
						Mix_PlayChannel(-1, sfx, 0);
						return 3;
					}
				}
				else
				{
					button3.SetTextColor(GameText::WHITE_TEXT);
				}
			}
		}

	}
	return 1;
}

int Menu::GameOverNotification(SDL_Renderer* screen, TTF_Font* font, std::string path,
	std::string path1, std::string path2, int result, int &high_score, Mix_Chunk* sfx)
{

	GameText button1; // play again
	button1.SetTextColor(GameText::BLUE_TEXT);
	button1.SetText(path1);

	GameText button2; // exit
	button2.SetTextColor(GameText::BLUE_TEXT);
	button2.SetText(path2);

	BaseObject gameOver; // game over background
	gameOver.LoadIMG(path, screen);
	SDL_SetRenderDrawColor(screen, RENDERER_DRAW_COLOR, RENDERER_DRAW_COLOR, RENDERER_DRAW_COLOR, RENDERER_DRAW_COLOR);
	SDL_RenderClear(screen);
	gameOver.RenderBackground(screen, NULL);

	// score
	GameText Score;
	Score.SetTextColor(GameText::RED_TEXT);
	std::string scoreText = "Score: ";
	std::string score = std::to_string(result);
	scoreText += score;
	Score.SetText(scoreText);
	Score.LoadText(screen, font);
	int scoreTextWidth = Score.GetTextWidth();
	int scoreTextHeight = Score.GetTextHeight();
	SDL_Rect scoreTextDimension;
	scoreTextDimension.x = (SCREEN_WIDTH - scoreTextWidth) / 2;
	scoreTextDimension.y = SCREEN_HEIGHT / 2 - 100;
	Score.RenderText(screen, scoreTextDimension.x, scoreTextDimension.y);

	// high score
	GameText HighScore;
	std::string highScoreText;
	if (result > high_score)
	{
		high_score = result;
		std::ofstream outputFile(highScoreFilePath, std::ofstream::trunc);
		if (!outputFile.is_open())
		{
			std::cout << "Failed to open file." << std::endl;
		}
		outputFile << high_score;
		outputFile.close();
		highScoreText = "New High Score: ";
		HighScore.SetTextColor(GameText::GREEN_TEXT);
	}
	else
	{
		highScoreText = "High score: ";
		HighScore.SetTextColor(GameText::RED_TEXT);
	}
	std::string highScore = std::to_string(high_score);
	highScoreText += highScore;
	HighScore.SetText(highScoreText);
	HighScore.LoadText(screen, font);
	int highScoreTextWidth = HighScore.GetTextWidth();
	int highScoreTextHeight = HighScore.GetTextHeight();
	SDL_Rect highScoreTextDimension;
	highScoreTextDimension.x = (SCREEN_WIDTH - highScoreTextWidth) / 2;
	highScoreTextDimension.y = scoreTextDimension.y + 40;
	HighScore.RenderText(screen, highScoreTextDimension.x, highScoreTextDimension.y);

	SDL_Event gEvent;

	while (true)
	{
		// play again
		button1.LoadText(screen, font);
		int h1 = button1.GetTextHeight();
		int w1 = button1.GetTextWidth();
		SDL_Rect button1Dimension;
		button1Dimension.x = 300;
		button1Dimension.y = highScoreTextDimension.y + 100;
		button1.RenderText(screen, button1Dimension.x, button1Dimension.y);

		// exit
		button2.LoadText(screen, font);
		int h2 = button2.GetTextHeight();
		int w2 = button2.GetTextWidth();
		SDL_Rect button2Dimension;
		button2Dimension.x = SCREEN_WIDTH - 300 - w2;
		button2Dimension.y = highScoreTextDimension.y + 100;
		button2.RenderText(screen, button2Dimension.x, button2Dimension.y);

		SDL_RenderPresent(screen);

		while (SDL_PollEvent(&gEvent) != 0)
		{
			if (gEvent.type == SDL_QUIT)
			{
				return 1;
			}
			else if (gEvent.type == SDL_MOUSEMOTION || gEvent.type == SDL_MOUSEBUTTONDOWN)
			{
				int x, y;
				SDL_GetMouseState(&x, &y);

				if (x > button1Dimension.x && x < button1Dimension.x + w1 && y > button1Dimension.y && y < button1Dimension.y + h1)
				{
					button1.SetTextColor(GameText::GREEN_TEXT);
					if (gEvent.button.button == SDL_BUTTON_LEFT and gEvent.button.state == SDL_PRESSED)
					{
						Mix_PlayChannel(-1, sfx, 0);
						return 0;
					}
				}
				else
				{
					button1.SetTextColor(GameText::BLUE_TEXT);
				}

				if (x > button2Dimension.x && x < button2Dimension.x + w2 && y > button2Dimension.y && y < button2Dimension.y + h2)
				{
					button2.SetTextColor(GameText::RED_TEXT);
					if (gEvent.button.button == SDL_BUTTON_LEFT and gEvent.button.state == SDL_PRESSED)
					{
						Mix_PlayChannel(-1, sfx, 0);
						return 1;
					}
				}
				else
				{
					button2.SetTextColor(GameText::BLUE_TEXT);
				}


			}
		}
	}

	return 1;
}

int Menu::StartGame(SDL_Renderer* screen, TTF_Font* font, Mix_Chunk* sfx)
{
	std::string noti = "Press any key to start game!";
	GameText StartGame;
	StartGame.SetTextColor(GameText::WHITE_TEXT);
	StartGame.SetText(noti);
	SDL_Event gEvent;

	while (true)
	{
		StartGame.LoadText(screen, font);
		int w = StartGame.GetTextWidth();
		int h = StartGame.GetTextHeight();
		int x = (SCREEN_WIDTH - w) / 2;
		int y = 96;
		StartGame.RenderText(screen, x, y);
		SDL_RenderPresent(screen);
		while (SDL_PollEvent(&gEvent) != 0)
		{
			if (gEvent.type == SDL_KEYDOWN or gEvent.type == SDL_MOUSEBUTTONDOWN)
			{
				Mix_PlayChannel(-1, sfx, 0);
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
	return 0;
}

void Menu::ShowScore(SDL_Renderer* screen, TTF_Font* font, int score, int highScore)
{
	std::string scoreText = "Score: ";
	std::string scoreValue = std::to_string(score);
	scoreText += scoreValue;
	scoreText += " m";

	std::string highScoreText = "High Score: ";
	std::string highScoreValue = std::to_string(highScore);
	highScoreText += highScoreValue;
	highScoreText += " m";

	GameText gHighScore;
	gHighScore.SetTextColor(GameText::WHITE_TEXT);
	gHighScore.SetText(highScoreText);
	gHighScore.LoadText(screen, font);
	int w1 = gHighScore.GetTextWidth();
	int h1 = gHighScore.GetTextHeight();
	gHighScore.RenderText(screen, SCREEN_WIDTH - w1 - 20, 20);

	GameText gScore;
	gScore.SetTextColor(GameText::WHITE_TEXT);
	gScore.SetText(scoreText);
	gScore.LoadText(screen, font);
	gScore.RenderText(screen, SCREEN_WIDTH - w1 - 20, 50);

}