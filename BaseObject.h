#ifndef BASE_OBJECT_H
#define BASE_OBJECT_H
#include "CommonFunction.h"

class BaseObject
{
public:
	BaseObject();
	~BaseObject();
	void SetRectPosition(const int& x, const int& y)
	{
		rect.x = x;
		rect.y = y;
	}
	SDL_Rect GetRect() const
	{
		return rect;
	}
	SDL_Texture* GetObject()const
	{
		return imageTexture;
	}
	virtual bool LoadIMG(std::string IMG_path, SDL_Renderer* screen);
	SDL_Texture* LoadTexture(std::string IMG_path);
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void Free();
	void RenderBackground(SDL_Renderer* screen, const SDL_Rect* clip = NULL);

protected:
	SDL_Texture* imageTexture;
	SDL_Rect rect;

};

#endif // !BASE_OBJECT_H