#include <dd.h>
//#include <engine_ex.h>

struct Game
{
    uint64_t frameNumber = 0;
};
Game game;
dd::engine engine;
dd::sprite heroSprite;
dd::sprite leftMissileSprite;
dd::sprite rightMissileSprite;
dd::sprite bulletSprite;

dd::bound heroBound;
dd::sound shotSound;

dd::anim runningAnim;
dd::anim runningAnim2;

dd::anim runningAnim3;

dd::text hitsMsg;
dd::text hitsMsg2;
dd::text hitsMsg3;


void LoadTestAnim()
{
    for (int i = 0; i < 6; i++)
    {
        dd::rect src;
        src.x = float(i * 144);
        src.y = float(2 * 144);
        src.width = 144;
        src.height = 144;
        dd::sprite frame;
        frame.load("test/test_animation.png", src, {});
        frame.bound.rects.push_back( frame.origin_rect()  );
        runningAnim.add_frame(frame);
    }
    runningAnim.fps(12.0f);
    runningAnim.loop = true;
    runningAnim.flip_x = true;
    runningAnim.position = {300, 300};
    runningAnim.visible = true;
    runningAnim.pause(false);

    runningAnim2 = runningAnim;
    runningAnim2.fps(4.0f);
    runningAnim2.flip_x = false;
    runningAnim.position.y += 160;


    for (int i = 0; i < 5; i++)
    {
        dd::rect src;
        src.x = float(i * 144);
        src.y = float(0);
        src.width = 144;
        src.height = 144;
        dd::sprite frame;
        frame.load("test/test_animation.png", src, {});
        frame.bound.rects.push_back( frame.origin_rect()  );
        runningAnim3.add_frame(frame);
    }
    runningAnim3.fps(5.0f);
    runningAnim3.loop = true;
    runningAnim3.flip_x = false;
    runningAnim3.position = {300, 650};
    runningAnim3.visible = true;
    runningAnim3.pause(false);

    //
    hitsMsg.color = dd::colors::red;
    hitsMsg.position = {100, 40};
    hitsMsg.size = 40.0f;
    hitsMsg2 = hitsMsg;
    hitsMsg3 = hitsMsg;

    hitsMsg2.position = {100, 140};
    hitsMsg3.position = {100, 240};

    hitsMsg.set_font("OpenSans-Regular.ttf");
    hitsMsg3.set_font("OpenSans-Regular.ttf");
}

void Init()
{
    int screenWidth = 1440;
    int screenHeight = 900;

    //dd::window::set_antialiasing_flag();
    //dd::window::set_fullscreen_flag();
    engine.init(DD_RSS_FOLDER, screenWidth, screenHeight, "Raylib Force Exit Example");
    //dd::kbd::set_exitkey(dd::keys::NONE);
    //
    engine.target_fps(60);
    engine.mouse_cursor_hide();

    dd::println("Loading resources...");
    //
    dd::transform heroTr = {{}, {0.30f, 0.35f}};
    dd::transform heroLeftMissilesTr = dd::transform{-80.0f, -80.0f, 1.0f, 0.8f} * heroTr;
    dd::transform heroRightMissilesTr = dd::transform{+80.0f, -80.0f, 1.0f, 0.8f} * heroTr;
    dd::transform bulletTr = dd::transform{{}, {0.3f, 0.5f}} * heroTr;

    heroSprite.load("test/hero.png", {}, heroTr);
    //heroSprite.flip_x = true;
    //heroSprite.flip_y = true;
    heroSprite.position.x = 250.0f;
    heroSprite.position.y = 800.0f;
    heroBound.rects.push_back(heroTr * dd::rect{-50.0f, -40.0f, 100, 120});
    heroBound.rects.push_back(heroTr * dd::rect{-100.0f, 6.0f,   80,   70});
    heroBound.rects.push_back(heroTr * dd::rect{+20.0f, 6.0f,  80, 70});
    heroBound.rects.push_back(heroTr * dd::rect{-20.0f  , -80.0f, 40,  40});

    leftMissileSprite.load("test/hero_missile.png", {}, heroLeftMissilesTr);
    rightMissileSprite.load("test/hero_missile.png", {}, heroRightMissilesTr);
    bulletSprite.load("test/bullet.png", {}, bulletTr);
    bulletSprite.bound.rects.push_back( bulletSprite.origin_rect() );


    shotSound.load("tests/shot.wav");

    LoadTestAnim();

    dd::println("Resource loaded!");
}

void Deinit()
{
    engine.close();
}

void MainLoop()
{
    bool showMissilies = true;
    int bulletsCooldown = 0;
    int equipCooldown = 0;
    std::vector<dd::sprite> bullets;

    //engine.set_font("OpenSans-Regular.ttf");
    int hits = 0;
    while ( !engine.should_close() )
    {
        game.frameNumber++;

        if (1)
        {
            if (engine.key_down(dd::keys::P))     { runningAnim.pause(!runningAnim.paused()); }

            if (engine.key_down(dd::keys::UP))    {  heroSprite.position.y -= 3.0f;}
            if (engine.key_down(dd::keys::DOWN))  {  heroSprite.position.y += 3.0f;}
            if (engine.key_down(dd::keys::LEFT))  {  heroSprite.position.x -= 3.0f;}
            if (engine.key_down(dd::keys::RIGHT)) {  heroSprite.position.x += 3.0f;}
            if (engine.key_down(dd::keys::F))     {  engine.toggle_fullscreen_win(); }
            if (equipCooldown <= 0)
            {
                if (engine.key_down(dd::keys::LEFT_CONTROL)) 
                {
                    equipCooldown = 10;
                    showMissilies = !showMissilies; 
                }
            }
            else if (engine.key_up(dd::keys::LEFT_CONTROL))
            {
                equipCooldown = 0;
            }
            heroSprite.position += engine.mouse_delta();
        }

        if (heroSprite.position.y < 650.0f)
        {
            heroSprite.position.y = 650.0f;
        }
        if (heroSprite.position.y > 850.0f)
        {
            heroSprite.position.y = 850.0f;
        }
        if (heroSprite.position.x < 0.0f)
        {
            heroSprite.position.x = 0.0f;
        }
        if (heroSprite.position.x > 1440.0f)
        {
            heroSprite.position.x = 1440.0f;
        }

        leftMissileSprite.position = heroSprite.position;
        rightMissileSprite.position = heroSprite.position;

        if (bulletsCooldown <= 0)
        {
            if ( engine.key_down(dd::keys::SPACE) || engine.mouse_btn_down(0))
            {  
                runningAnim3.flip_x = !runningAnim3.flip_x;
                bulletsCooldown = 25;

                bullets.push_back(bulletSprite);
                bullets.back().position = heroSprite.position;
                if (showMissilies)
                {
                    bullets.push_back(bulletSprite);
                    bullets.back().position = leftMissileSprite.global_pos();
                    bullets.push_back(bulletSprite);
                    bullets.back().position = rightMissileSprite.global_pos();
                } 
                shotSound.play();
            }
        }
        else
        {
            bulletsCooldown--;
        }

        std::vector<dd::sprite> tmpBullets = std::move(bullets);
        for(auto& b : tmpBullets)
        {
            if (b.position.y > 0)
            {
                b.position.y -= 5;
                if (runningAnim.collision(b) ||
                    runningAnim2.collision(b))
                {
                    hits++;
                }
                else
                {
                    bullets.push_back(b);
                }
            }
        }
        for(const auto& b : bullets) b.draw();

        runningAnim.position.x += 6.0;
        runningAnim2.position.x -= 1.0;
        if (runningAnim.position.x > 1440 + 72) runningAnim.position.x = -72;
        if (runningAnim2.position.x < -72) runningAnim2.position.x = 1440 + 72;

        runningAnim.update();
        runningAnim2.update();
        runningAnim3.update();

        engine.begin_frame();
        engine.clear_frame(dd::colors::black);

        runningAnim.draw();
        runningAnim2.draw();
        runningAnim3.draw();

        heroSprite.draw();

        if (showMissilies)
        {
            leftMissileSprite.draw();
            rightMissileSprite.draw();
        }
        hitsMsg.write( fmt::format("Hits: {}", hits) );
        hitsMsg2.write("Test Text 1234 222");
        hitsMsg3.write("Test Text 1234 333");

        heroBound.draw(heroSprite.position);

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
