#ifndef MENU_H
#define MENU_H
#include "Global.h"
#include "BaseObject.h"
#include "TextManager.h"

class Menu : public BaseObject
{

public:
	Menu();
	~Menu();

	int ShowMenu(SDL_Renderer* screen, TTF_Font* font,std::string menuPicPath, Mix_Chunk* sfx);
	int GameOverNotification(SDL_Renderer* screen, TTF_Font* font, std::string gameOverPicPath,
		std::string path1, std::string path2, int result, int &high_score, Mix_Chunk* sfx);
	int StartGame(SDL_Renderer* screen, TTF_Font* font, Mix_Chunk* sfx);
	int ShowTutorials(SDL_Renderer* screen, TTF_Font* font, std::string tutorialPicPath);
	void ShowScore(SDL_Renderer* screen, TTF_Font* font, int score, int highScore);
	int ResumeGame(SDL_Renderer* screen, TTF_Font* font, Mix_Chunk* sfx);


private:
   
};
#endif