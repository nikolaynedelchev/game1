#include "game.h"
#include <tiny_dnn/tiny_dnn.h>

int main()
{
    tiny_dnn::network<tiny_dnn::sequential> net;
    (void)net;

    ndn::CheckersGame::game.Init();
    ndn::CheckersGame::game.MainLoop();
    ndn::CheckersGame::game.Deinit();
    return 0;
}
