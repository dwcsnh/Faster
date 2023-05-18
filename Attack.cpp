#include"Attack.h"

Attack::Attack()
{
	yPos = 0;
	frameWidth = 0;
	frameHeight = 0;
	frameClipIndex = 0;
}
Attack::~Attack()
{

}

bool Attack::LoadAttackIMG(std::string IMG_Path, SDL_Renderer* screen)
{
	bool loaded = BaseObject::LoadIMG(IMG_Path, screen);
	if (loaded == true)
	{
		frameWidth = rect.w / 32;
		frameHeight = rect.h;
	}
	return loaded;
}

void Attack::SetAttackClip()
{
	if (frameWidth > 0 and frameHeight > 0)
	{
		for (int i = 0; i < 22; i++)
		{
			frameClip[i].x = i * frameWidth;
			frameClip[i].y = 0;
			frameClip[i].w = frameWidth;
			frameClip[i].h = frameHeight;
		}
	}
}

void Attack::RenderAttack(SDL_Renderer* screen, int scrollingOffset, int yPos)
{
	frameClipIndex++;
	if (frameClipIndex >= 22)
	{
		frameClipIndex = 0;
	}
	SDL_Rect* CurrentClip = &frameClip[frameClipIndex];

	SDL_Rect destinationRect = { 0, yPos, frameWidth, frameHeight };

	SDL_RenderCopy(screen, imageTexture, CurrentClip, &destinationRect);
}