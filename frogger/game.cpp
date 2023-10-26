#include "all_headers.h"

namespace FroggerGame
{

void GameModule::Init()
{
    auto res = engine.init(DD_RSS_FOLDER, 800, 600, "FROGGER", false);
    //auto res = engine.init_fs(DD_RSS_FOLDER, "FROGGER");
    systemWidth = res.x;
    systemHeight = res.y;
    engine.target_fps(60);
    engine.mouse_cursor_hide();

    dd::println("Loading resources...");
    rss.Load();

    float scaleFactor = systemHeight / rss.screen.height;
    float gameScrW = rss.screen.width * scaleFactor; // 618.5567

    camera.scale = scaleFactor;
    camera.offset.x = systemWidth / 2.0f - gameScrW / 2.0f;

    clippingRect.x = camera.offset.x;
    clippingRect.y = 0;
    clippingRect.width = gameScrW;
    clippingRect.height = systemHeight - 1;

    dd::println("CLIPPING RECT: {}", clippingRect);
    frogger.Init();
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
    if (false == rss.music.is_playing())
    {
        rss.music.volume(0.2f);
        rss.music.play();
    }
    UpdateCamera();
    remainingTime -= engine.frame_time();
    if (remainingTime < 0.0f) remainingTime = 0.0f;
    frogger.Update();
}

void GameModule::Draw()
{
    engine.begin_frame();
    engine.clear_frame(dd::colors::light_gray);
    dd::rect test = {0, 0, systemWidth, systemHeight};
    //test.draw(dd::colors::red, false);

    for (int i = 0; i < 40; i++)
    {
        dd::line l = {float(i) * (systemWidth / 20.0f), 0,
                      float(i) * (systemWidth / 20.0f), systemHeight};
        //l.draw(dd::colors::green);
    }

    engine.camera_on(camera);
    engine.clipping_on(clippingRect);

    DrawBackground();
    DrawTime();

    homes.Draw();
    frogger.Draw();

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
    rss.riverRect.draw(dd::colors::dark_blue, true);

    rss.landRect.draw(dd::colors::black, true);

    rss.homesBackground.draw_at({0, HEADER_H},
                                dd::anchors::up_left);

    rss.walkway.draw_at({0, HEADER_H + HOMES_H + 5 * ROW_H},
                        dd::anchors::up_left);

    rss.walkway.draw_at({0, HEADER_H + HOMES_H + 11 * ROW_H},
                        dd::anchors::up_left);
}

void GameModule::DrawTime()
{
    dd::text t;
    t.symbols = "TIME";
    t.set_font("OpenSans-Regular.ttf");
    t.font_size = 30;
    t.color = dd::colors::yellow;
    t.position = {rss.screen.width, rss.screen.height};
    t.anchor = dd::anchors::down_right;
    t.draw();

    dd::rect textRect = t.rect();
    textRect.y += 8;
    textRect.height -= 14;

    dd::rect timeRect;
    timeRect.width = std::floor((remainingTime / levelTime) * (rss.screen.width - textRect.width));
    timeRect.height = textRect.height;
    timeRect.position({0, 0});

    timeRect.x = std::floor(textRect.x - timeRect.size().x);
    timeRect.y = std::floor(textRect.y);
    timeRect.draw(dd::colors::green, true);
}

void GameModule::DrawLives()
{

}

void GameModule::DrawScore()
{

}


dd::engine engine;
GameModule game;
}
