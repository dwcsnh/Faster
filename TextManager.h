#ifndef TEXT_MANAGER_H
#define TEXT_MANAGER_H

#include "CommonFunction.h"
#include "BaseObject.h"

class GameText : public BaseObject
{
public:
    GameText();
    ~GameText();

    enum TextColor
    {
        RED_TEXT = 0,
        WHITE_TEXT = 1,
        BLACK_TEXT = 2,
        BLUE_TEXT = 3,
        GREEN_TEXT = 4,
    };

    bool LoadText(SDL_Renderer* screen, TTF_Font* font);
    void FreeTextTexture();

    void SetColor(Uint8 red, Uint8 green, Uint8 blue);
    void SetTextColor(int type);

    void RenderText(SDL_Renderer* screen, int x, int y, SDL_Rect* clip = NULL);

    int GetTextWidth() const { return textWidth; }
    int GetTextHeight() const { return textHeight; }
    void SetText(const std::string& text) { renderingText = text; }
    std::string GetText() const { return renderingText; }

private:
    std::string renderingText;
    SDL_Color textColor;
    SDL_Texture* textTexture;
    int textWidth;
    int textHeight;
};

#endif