#include "game.h"

namespace ndn::CheckersGame
{
dd::engine engine;

void GameModule::Init()
{
    auto res = engine.init(DD_RSS_FOLDER, 600, 800, "FROGGER", false);
    //auto res = engine.init_fs(DD_RSS_FOLDER, "FROGGER");
    systemWidth = res.x;
    systemHeight = res.y;
    engine.target_fps(60);
    engine.mouse_cursor_show();

    dd::println("Checkers");
}

void GameModule::MainLoop()
{
    while ( !engine.should_close() )
    {
        Update();
        Draw();
    }
}

void GameModule::Deinit()
{
    engine.close();
}

void GameModule::Update()
{
    UpdateCamera();
    remainingTime -= engine.frame_time();
    if (remainingTime < 0.0f) remainingTime = 0.0f;

    // Update game modules
}

void GameModule::Draw()
{
    engine.begin_frame();
    engine.clear_frame(dd::colors::light_gray);
    dd::rect test = {0, 0, systemWidth, systemHeight};
    //test.draw(dd::colors::red, false);

    for (int i = 0; i < 8; i++)for (int j = 0; j < 8; j++)
    {
        dd::line l = {float(i) * (systemWidth / 20.0f), 0,
                      float(i) * (systemWidth / 20.0f), systemHeight};
        l.draw(dd::colors::green);
    }

    engine.camera_on(camera);
    engine.clipping_on(clippingRect);

    DrawBackground();

    engine.clipping_off();
    engine.camera_off();
    clippingRect.draw(dd::colors::red, false);
    engine.end_frame();
}

void GameModule::UpdateCamera()
{
    if (engine.key_pressed(dd::keys::A)) camera.offset.x -= 30;
    if (engine.key_pressed(dd::keys::D)) camera.offset.x += 30;
    if (engine.key_pressed(dd::keys::W)) camera.offset.y -= 30;
    if (engine.key_pressed(dd::keys::S)) camera.offset.y += 30;
    if (engine.key_pressed(dd::keys::Q)) camera.scale -= 0.1f;
    if (engine.key_pressed(dd::keys::E)) camera.scale += 0.1f;
}

void GameModule::DrawBackground()
{

}

GameModule game;
}
