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
        std::string content
    );

    /* Public methods */
    void SetContent(std::string content);

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
    SDL_Renderer* renderer;
    FontFace fontFace;
    int pointSize;
    SDL_Color color;
    std::string content;
    std::shared_ptr<Font> font;
    SDL_Texture* texture;
    double x;
    double y;
    double width;
    double height;
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
    TTF_Font* font;
    SDL_Surface* surface;
};