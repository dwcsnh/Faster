#include "TextManager.h"

GameText::GameText()
{
    textColor.r = 255;
    textColor.g = 255;
    textColor.b = 255;
    textTexture = NULL;
}
GameText::~GameText()
{
    if (textTexture != NULL)
    {
        SDL_DestroyTexture(textTexture);
    }
}

bool GameText::LoadText(SDL_Renderer* screen, TTF_Font* font)
{
    FreeTextTexture();
    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, renderingText.c_str(), textColor);
    if (textSurface != NULL)
    {
        //Create texture from surface pixels
        textTexture = SDL_CreateTextureFromSurface(screen, textSurface);
        if (textTexture != NULL)
        {
            //Get image dimensions
            textWidth = textSurface->w;
            textHeight = textSurface->h;
        }

        //Get rid off old surface
       // SDL_DestroyTexture(texture_);
        SDL_FreeSurface(textSurface);
    }

    //Return success
    return textTexture != NULL;
}

void GameText::FreeTextTexture()
{
    if (textTexture != NULL)
    {
        SDL_DestroyTexture(textTexture);
        textTexture = NULL;
    }
}

void GameText::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
    textColor.r = red;
    textColor.g = green;
    textColor.b = blue;
}

void GameText::SetTextColor(int type)
{
    if (type == RED_TEXT)
    {
        SDL_Color color = { 255, 0, 0 };
        textColor = color;
    }
    else if (type == WHITE_TEXT)
    {
        SDL_Color color = { 255, 255, 255 };
        textColor = color;
    }
    else if (type == BLACK_TEXT)
    {
        SDL_Color color = { 0, 0, 0 };
        textColor = color;
    }
    else if (type == BLUE_TEXT)
    {
        SDL_Color color = { 3, 120, 225 };
        textColor = color;
    }
    else
    {
        SDL_Color color = { 79, 144, 26 };
        textColor = color;
    }
}
void GameText::RenderText(SDL_Renderer* screen, int x, int y, SDL_Rect* clip)
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, textWidth, textHeight };

    //Set clip rendering dimensions
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    //Render to screen
    SDL_RenderCopy(screen, textTexture, clip, &renderQuad);

}