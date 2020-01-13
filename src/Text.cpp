#include "Text.h"

#include <stdexcept>

#pragma region Constructor/Destructor
Text::Text(
    SDL_Renderer* renderer,
    FontFace fontFace,
    int pointSize,
    SDL_Color color,
    std::string content
) : 
    renderer(renderer),
    fontFace(fontFace),
    pointSize(pointSize),
    color(color),
    content(content)
{
    // Find the font for the given typeface and point size,
    // or create it if it doesn't exist.
    auto fontMapIndex = std::pair(fontFace, pointSize);
    if (Text::fontMap.count(fontMapIndex) > 0)
    {
        this->font = Text::fontMap.at(fontMapIndex);
    }
    else
    {
        auto newFont = std::make_shared<Text::Font>(fontFace, pointSize);
        Text::fontMap.insert_or_assign(fontMapIndex, newFont);
        this->font = newFont;
    }

    // Render texture
    this->updateTexture();
}
#pragma endregion

#pragma region Public methods
void Text::SetContent(std::string content)
{
    this->content = content;
    this->updateTexture();
}

void Text::SetX(double x)
{
    this->x = x;
}

void Text::SetY(double y)
{
    this->y = y;
}

/* IGameEntity */
void Text::Draw()
{
    SDL_Rect targetRect{
        static_cast<int>(this->x),      // X
        static_cast<int>(this->y),      // Y
        static_cast<int>(this->width),  // W
        static_cast<int>(this->height)  // H
    };
    SDL_RenderCopyEx(
        this->renderer,
        this->texture,
        nullptr,
        &targetRect,
        0,
        nullptr,
        SDL_RendererFlip::SDL_FLIP_NONE
    );
}

void Text::Update(std::chrono::nanoseconds deltaTime)
{ }
#pragma endregion

#pragma region Public static methods
void Text::Initialize()
{
    // Initialize SDL2_TTF
    if (TTF_Init() == -1)
    {
        std::string errorString = "Unable to initialize SDL_ttf! SDL_Error: " + std::string(SDL_GetError());
        throw std::runtime_error(errorString);
    }
    Text::initialized = true;
}
#pragma endregion

#pragma region Private methods
void Text::updateTexture()
{
    // If we already have a texture, destroy it
    if (this->texture != nullptr)
    {
        SDL_DestroyTexture(this->texture);
        this->texture = nullptr;
    }

    // Render to temporary new surface
    SDL_Surface* surface = TTF_RenderText_Solid(
        this->font->GetTTFFont(),
        this->content.c_str(),
        this->color
    );
    
    // Create texture
    this->texture = SDL_CreateTextureFromSurface(this->renderer, surface);

    // Update bounds
    this->width = surface->w;
    this->height = surface->h;
    
    // Free surface
    SDL_FreeSurface(surface);
}
#pragma endregion

#pragma region Private static member initialization
bool Text::initialized = false;

std::map<FontFace, std::string> Text::fontFaceFileMap {
    { FontFace::Default, "assets/slkscr.ttf" }
};

std::map<std::pair<FontFace, int>, std::shared_ptr<Text::Font>> Text::fontMap {};
#pragma endregion

#pragma region Font class
Text::Font::Font(FontFace fontFace, int pointSize)
{
    std::string filePath = Text::fontFaceFileMap[fontFace];
    this->font = TTF_OpenFont(filePath.c_str(), pointSize);
}

Text::Font::~Font()
{
    TTF_CloseFont(this->font);
}

TTF_Font* Text::Font::GetTTFFont()
{
    return this->font;
}
#pragma endregion