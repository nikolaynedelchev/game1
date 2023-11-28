#include "all_modules.h"

int main()
{
    FroggerGame::game.Init();
    FroggerGame::game.MainLoop();
    FroggerGame::game.Deinit();
    return 0;
}
