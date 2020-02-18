#pragma once

#include "IGameEntity.h"
#include "SDL_ttf.h"

#include <map>
#include <memory>
#include <string>
#include <utility>

enum class FontFace
{
    Default
};

class Text : public IGameEntity
{
public:
    /* Constructor/Destructor */
    Text(
        SDL_Renderer* renderer,
        FontFace fontFace,
        int pointSize,
        SDL_Color color,
        std::wstring content
    );

    /* Public methods */
    void SetContent(std::wstring content);
    double GetX();
    double GetY();
    void SetX(double x);
    void SetY(double y);
    void SetWidthScale(double widthScale);
    void SetHeightScale(double heightScale);
    double GetWidth();
    double GetHeight();
    double GetOpacity();
    void SetOpacity(double opacity);

    /* IGameEntity */
    void Draw() override;
    void Update(std::chrono::nanoseconds deltaTime) override;

    /* Public static methods */
    static void Initialize();

private:
    /* Forward private class declaration */
    class Font;

    /* Private methods */
    void updateTexture();

    /* Private static members */
    static bool initialized;
    static std::map<FontFace, std::string> fontFaceFileMap;
    static std::map<std::pair<FontFace, int>, std::shared_ptr<Text::Font>> fontMap;

    /* Private members */
    SDL_Renderer* renderer = nullptr;
    FontFace fontFace;
    int pointSize;
    SDL_Color color;
    std::wstring content;
    std::shared_ptr<Font> font {};
    SDL_Texture* texture = nullptr;
    double x = 0.0;
    double y = 0.0;
    double width = 0.0;
    double height = 0.0;
    double widthScale = 1.0;
    double heightScale = 1.0;
    double opacity = 1.0;
};

class Text::Font
{
public:
    /* Constructor/Destructor */
    Font(FontFace fontFace, int pointSize);
    ~Font();

    /* Public methods */
    TTF_Font* GetTTFFont();

private:
    /* Private members */
    TTF_Font* font = nullptr;
    SDL_Surface* surface = nullptr;
};