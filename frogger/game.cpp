#include "all_headers.h"

namespace FroggerGame
{

void GameModule::Init()
{
    engine.init(DD_RSS_FOLDER, screenWidth, screenHeight, "FROGGER", true);
    engine.target_fps(60);
    engine.mouse_cursor_hide();

    dd::println("Loading resources...");
    Rss::LoadResources();

    float scaleFactor = screenHeight / height;
    float gameScrW = width * scaleFactor; // 618.5567

    camera.scale = scaleFactor;
    camera.offset.x = screenWidth / 2.0f - gameScrW / 2.0f;

    clippingRect.x = camera.offset.x;
    clippingRect.y = 0;
    clippingRect.width = gameScrW;
    clippingRect.height = screenHeight - 1;

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
    UpdateCamera();
    remainingTime -= engine.frame_time();
    if (remainingTime < 0.0f) remainingTime = 0.0f;
    frogger.Update();
}

void GameModule::Draw()
{
    engine.begin_frame();
    engine.clear_frame(dd::colors::light_gray);
    dd::rect test = {0, 0, screenWidth, screenHeight};
    //test.draw(dd::colors::red, false);

    for (int i = 0; i < 40; i++)
    {
        dd::line l = {float(i) * (screenWidth / 20.0f), 0,
                      float(i) * (screenWidth / 20.0f), screenHeight};
        //l.draw(dd::colors::green);
    }

    engine.camera_on(camera);
    //engine.clipping_on(clippingRect);

    //DrawBackground();
    //DrawTime();

    //homes.Draw();
    frogger.Draw();

    auto cr = clippingRect;
    cr.width /= 2;
    dd::println("PPP: {}", cr.x + cr.width);
    cr.draw(dd::colors::red, false);
    engine.clipping_off();
    engine.camera_off();
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
    dd::rect riverRect = {0, 0, width, HEADER_H + HOMES_H + 5.5f * ROW_H};
    riverRect.draw(dd::colors::dark_blue, true);

    dd::rect landRect = {0, HEADER_H + HOMES_H + 5.5 * ROW_H, width, 6.5 * ROW_H + FOOTER_H};
    landRect.draw(dd::colors::black, true);

    auto homesSprite = Rss::GetSprite("homes_background");
    homesSprite.change_anchor(dd::anchors::up_left);
    homesSprite.position = {0, HEADER_H};
    homesSprite.draw();

    auto riverLand = Rss::GetSprite("walkway");
    riverLand.change_anchor(dd::anchors::up_left);
    riverLand.position = {0, HEADER_H + HOMES_H + 5 * ROW_H};
    riverLand.draw();

    auto land = Rss::GetSprite("walkway");
    land.change_anchor(dd::anchors::up_left);
    land.position = {0, HEADER_H + HOMES_H + 11 * ROW_H};
    land.draw();
}

void GameModule::DrawTime()
{
    dd::text t;
    t.symbols = "TIME";
    t.set_font("OpenSans-Regular.ttf");
    t.font_size = 30;
    t.color = dd::colors::yellow;
    t.position = {width, height};
    t.anchor = dd::anchors::down_right;
    t.draw();

    dd::rect textRect = t.rect();
    textRect.y += 8;
    textRect.height -= 14;

    dd::rect timeRect;
    timeRect.width = int((remainingTime / levelTime) * (width - textRect.width));
    timeRect.height = textRect.height;
    timeRect.position({0, 0});

    timeRect.x = int(textRect.x - timeRect.size().x);
    timeRect.y = int(textRect.y);
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
