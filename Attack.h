#ifndef ATTACK_H
#define ATTACK_H

#include"BaseObject.h"

class Attack : public BaseObject
{
public:
	Attack();
	~Attack();

	bool LoadAttackIMG(std::string IMG_path, SDL_Renderer* screen);
	void SetAttackClip();
	void RenderAttack(SDL_Renderer* screen, int scrollingOffsset, int yPos);

private:
	int yPos;

	int frameWidth;
	int frameHeight;

	SDL_Rect frameClip[22];
	int frameClipIndex;
};
#endif