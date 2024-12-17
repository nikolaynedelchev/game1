#include "all_modules.h"
#include <tiny_dnn/tiny_dnn.h>

int main()
{
    tiny_dnn::network<tiny_dnn::sequential> net;
    (void)net;

    FroggerGame::game.Init();
    FroggerGame::game.MainLoop();
    FroggerGame::game.Deinit();
    return 0;
}
