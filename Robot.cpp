#include "Robot.h"

#include <iostream>

Robot::Robot(
    SDL_Renderer* renderer,
    std::wstring name,
    std::string imagePath
) : 
    Graphic(renderer, imagePath),
    name(name)
{
    std::wcout << L"Constructing robot '" << name << std::endl;
}