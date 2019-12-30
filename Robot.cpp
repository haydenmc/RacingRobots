#include "Robot.h"

Robot::Robot(
    SDL_Renderer* renderer,
    std::string name,
    std::string imagePath
) : 
    Graphic(renderer, imagePath),
    name(name)
{ }