#include <memory>

#include "Game.h"

int main(int argc, char* args[])
{
    std::shared_ptr<Game> game = std::make_shared<Game>(1280, 720, 0);
    game->Start();
    return 0;
}
