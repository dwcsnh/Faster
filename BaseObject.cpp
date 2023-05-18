#include "CommonFunction.h"
#include "BaseObject.h"

BaseObject::BaseObject()
{
	imageTexture = NULL;
	rect.x = 0;
	rect.y = 0;
	rect.w = 0;
	rect.h = 0;
}

BaseObject::~BaseObject()
{

}

bool BaseObject::LoadIMG(std::string IMG_path, SDL_Renderer* screen)
{
	Free();
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadSurface = IMG_Load(IMG_path.c_str());
	if (!loadSurface)
	{
		std::cout << "Error loading image: " << IMG_path << IMG_GetError() << std::endl;
	}
	else 
	{
		newTexture = SDL_CreateTextureFromSurface(screen, loadSurface);
		if (!newTexture)
		{
			std::cout << "Unable to create texture from: " << IMG_path << SDL_GetError() << std::endl;
		}
		else
		{
			rect.w = loadSurface->w;
			rect.h = loadSurface->h;
		}
		SDL_FreeSurface(loadSurface);
	}
	imageTexture = newTexture;
	return imageTexture != NULL;
}

void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip)
{
	SDL_Rect renderquad = { rect.x, rect.y, rect.w, rect.h };
	SDL_RenderCopy(des, imageTexture, clip, &renderquad);
}

void BaseObject::RenderBackground(SDL_Renderer* screen, const SDL_Rect* clip)
{
	SDL_Rect renderquad = { rect.x, rect.y, SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_RenderCopy(screen, imageTexture, NULL, &renderquad);
}

void BaseObject::Free()
{
	if (imageTexture != NULL)
	{
		SDL_DestroyTexture(imageTexture);
		imageTexture = NULL;
		rect.w = 0;
		rect.h = 0;
	}
}