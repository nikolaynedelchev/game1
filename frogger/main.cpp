#include <dd.h>
#include "all_headers.h"

int main()
{
    FroggerGame::game.Init();
    FroggerGame::game.MainLoop();
    FroggerGame::game.Deinit();
    return 0;
}
