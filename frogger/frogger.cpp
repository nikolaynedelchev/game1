#include <dd.h>

dd::engine engine;
dd::sprite allSprites;
dd::rect testRect = {50, 100, 120, 150};
dd::transform scale;

void Init()
{
    int screenWidth = 1440;
    int screenHeight = 900;
    engine.init(DD_RSS_FOLDER, screenWidth, screenHeight, "FROGGER", false);
    //
    engine.target_fps(60);
    engine.mouse_cursor_hide();

    dd::println("Loading resources...");
    //
    allSprites.load("sprites.png", {}, {});


    dd::println("Resource loaded!");
}

void Deinit()
{
    engine.close();
}

void MainLoop()
{
    while ( !engine.should_close() )
    {
        if (engine.key_down(dd::keys::UP))    { scale.offset.y -= 10; }
        if (engine.key_down(dd::keys::DOWN))    { scale.offset.y += 10; }
        if (engine.key_down(dd::keys::LEFT))    { scale.offset.x -= 10; }
        if (engine.key_down(dd::keys::RIGHT))    { scale.offset.x += 10; }
        if (engine.key_down(dd::keys::A)) {scale.scale += dd::vec(0.02f, 0.02f); }
        if (engine.key_down(dd::keys::Z)) {scale.scale -= dd::vec(0.02f, 0.02f); }

        engine.global_transform(scale);
        engine.begin_frame();
        engine.clear_frame(dd::colors::black);

        allSprites.position = {720, 450};
        allSprites.draw();

        dd::sprite testSprite;
        testSprite.load("sprites.png", testRect, {});

        testSprite.position = testRect.size() / 2.0f;
        testSprite.draw();

        dd::rect boundRect = testRect;
        boundRect += allSprites.global_rect().position();
        boundRect.draw(dd::colors::red, false);

        
        engine.end_frame();
    }
}

int main()
{
    Init();

    MainLoop(); // this is the real game

    Deinit();

    return 0;
}
