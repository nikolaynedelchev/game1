#include <engine/engine.h>

struct Game
{
    uint64_t frameNumber = 0;
};
Game game;

dd::sprite heroSprite;
dd::sprite leftMissileSprite;
dd::sprite rightMissileSprite;
dd::sprite bulletSprite;

dd::bound heroBound;
dd::sound shotSound;

dd::anim runningAnim;
dd::anim runningAnim2;

dd::anim runningAnim3;


void LoadTestAnim()
{
    for (int i = 0; i < 6; i++)
    {
        dd::rect src;
        src.x = float(i * 144);
        src.y = float(2 * 144);
        src.width = 144;
        src.height = 144;
        auto frame = dd::gfx::load_sprite("test/test_animation.png", src, {});
        frame.bound.rects.push_back( dd::gfx::origin_rect(frame)  );
        dd::gfx::add_frame(runningAnim, frame);
    }
    dd::gfx::fps(runningAnim, 18.0f);
    runningAnim.loop = true;
    runningAnim.flip_x = true;
    runningAnim.position = {300, 300};
    runningAnim.visible = true;
    dd::gfx::pause(runningAnim, false);


    runningAnim2 = runningAnim;
    dd::gfx::fps(runningAnim2, 3.0f);
    runningAnim2.flip_x = false;
    runningAnim.position.y += 160;


    for (int i = 0; i < 5; i++)
    {
        dd::rect src;
        src.x = float(i * 144);
        src.y = float(0);
        src.width = 144;
        src.height = 144;
        auto frame = dd::gfx::load_sprite("test/test_animation.png", src, {});
        frame.bound.rects.push_back( dd::gfx::origin_rect(frame)  );
        dd::gfx::add_frame(runningAnim3, frame);
    }
    dd::gfx::fps(runningAnim3, 5);
    runningAnim3.loop = true;
    runningAnim3.flip_x = false;
    runningAnim3.position = {300, 650};
    runningAnim3.visible = true;
    dd::gfx::pause(runningAnim3, false);


}

void Init()
{
    int screenWidth = 1440;
    int screenHeight = 900;

    //dd::window::set_antialiasing_flag();
    //dd::window::set_fullscreen_flag();
    dd::window::set_vsync_flag();
    dd::window::init(screenWidth, screenHeight, "Raylib Force Exit Example");
    dd::audio::init();
    //dd::kbd::set_exitkey(dd::keys::NONE);
    //
    dd::time::target_fps(60);
    dd::mouse::cursor_hide();

    PrintLn("Loading resources...");
    //
    dd::transform heroTr = {{}, {0.30f, 0.35f}};
    dd::transform heroLeftMissilesTr = dd::transform{-80.0f, -80.0f, 1.0f, 0.8f} * heroTr;
    dd::transform heroRightMissilesTr = dd::transform{+80.0f, -80.0f, 1.0f, 0.8f} * heroTr;
    dd::transform bulletTr = dd::transform{{}, {0.3f, 0.5f}} * heroTr;

    heroSprite = dd::gfx::load_sprite("test/hero.png", {}, heroTr);
    //heroSprite.flip_x = true;
    //heroSprite.flip_y = true;
    heroSprite.position.x = 250.0f;
    heroSprite.position.y = 800.0f;
    heroBound.rects.push_back(heroTr * dd::rect{-50.0f, -40.0f, 100, 120});
    heroBound.rects.push_back(heroTr * dd::rect{-100.0f, 6.0f,   80,   70});
    heroBound.rects.push_back(heroTr * dd::rect{+20.0f, 6.0f,  80, 70});
    heroBound.rects.push_back(heroTr * dd::rect{-20.0f  , -80.0f, 40,  40});

    leftMissileSprite = dd::gfx::load_sprite("test/hero_missile.png", {}, heroLeftMissilesTr);
    rightMissileSprite = dd::gfx::load_sprite("test/hero_missile.png", {}, heroRightMissilesTr);
    bulletSprite = dd::gfx::load_sprite("test/bullet.png", {}, bulletTr);
    bulletSprite.bound.rects.push_back( dd::gfx::origin_rect(bulletSprite) );


    shotSound = dd::audio::load_sound( DD_RSS_FOLDER"/sounds/tests/shot.wav");

    LoadTestAnim();

    PrintLn("Resource loaded!");
}

void Deinit()
{
    dd::window::close();
}

void MainLoop()
{
    bool showMissilies = true;
    int bulletsCooldown = 0;
    int equipCooldown = 0;
    std::vector<dd::sprite> bullets;

    dd::gfx::set_font("OpenSans-Regular.ttf");
    int hits = 0;
    while ( !dd::window::should_close() )
    {
        game.frameNumber++;

        if (1)
        {
            if (dd::kbd::key_down(dd::keys::P))     { dd::gfx::pause(runningAnim,
                                                     !dd::gfx::paused(runningAnim)); }

            if (dd::kbd::key_down(dd::keys::UP))    {  heroSprite.position.y -= 3.0f;}
            if (dd::kbd::key_down(dd::keys::DOWN))  {  heroSprite.position.y += 3.0f;}
            if (dd::kbd::key_down(dd::keys::LEFT))  {  heroSprite.position.x -= 3.0f;}
            if (dd::kbd::key_down(dd::keys::RIGHT)) {  heroSprite.position.x += 3.0f;}
            if (dd::kbd::key_down(dd::keys::F))     {  dd::window::toggle_fullscreen(); }
            if (equipCooldown <= 0)
            {
                if (dd::kbd::key_down(dd::keys::LEFT_CONTROL)) 
                {
                    equipCooldown = 10;
                    showMissilies = !showMissilies; 
                }
            }
            else if (dd::kbd::key_up(dd::keys::LEFT_CONTROL))
            {
                equipCooldown = 0;
            }
            heroSprite.position += dd::mouse::delta();
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
            if ( dd::kbd::key_down(dd::keys::SPACE) || dd::mouse::btn_down(0))
            {  
                runningAnim3.flip_x = !runningAnim3.flip_x;
                bulletsCooldown = 25;

                bullets.push_back(bulletSprite);
                bullets.back().position = heroSprite.position;
                if (showMissilies)
                {
                    bullets.push_back(bulletSprite);
                    bullets.back().position = dd::gfx::global_pos(leftMissileSprite);
                    bullets.push_back(bulletSprite);
                    bullets.back().position = dd::gfx::global_pos(rightMissileSprite);
                } 
                dd::audio::play(shotSound);
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
                if (dd::gfx::collision(runningAnim, b) ||
                    dd::gfx::collision(runningAnim2, b))
                {
                    hits++;
                }
                else
                {
                    bullets.push_back(b);
                }
            }
        }
        for(const auto& b : bullets) dd::gfx::draw(b);

        runningAnim.position.x += 6.0;
        runningAnim2.position.x -= 1.0;
        if (runningAnim.position.x > 1440 + 72) runningAnim.position.x = -72;
        if (runningAnim2.position.x < -72) runningAnim2.position.x = 1440 + 72;

        dd::gfx::update(runningAnim);
        dd::gfx::update(runningAnim2);
        dd::gfx::update(runningAnim3);

        dd::gfx::begin();
        dd::gfx::clear(dd::colors::black);

        dd::gfx::draw(runningAnim);
        dd::gfx::draw(runningAnim2);
        dd::gfx::draw(runningAnim3);

        dd::gfx::draw(heroSprite);

        if (showMissilies)
        {
            dd::gfx::draw(leftMissileSprite);
            dd::gfx::draw(rightMissileSprite);
        }

        //dd::gfx::draw(dd::gfx::global_pos(leftMissileSprite), dd::colors::blue, true);
        //dd::gfx::draw(dd::gfx::global_pos(rightMissileSprite), dd::colors::green, true);

        dd::gfx::write({  fmt::format("{}", dd::gfx::global_pos(leftMissileSprite)), {100, 100}, 40.0f, dd::colors::red });
        dd::gfx::write({  fmt::format("{}", leftMissileSprite.position), {100, 150}, 40.0f, dd::colors::red});
        dd::gfx::write({  fmt::format("{}", dd::gfx::global_rect(leftMissileSprite)), {100, 190}, 40.0f, dd::colors::red });
        dd::gfx::write({  fmt::format("Hits: {}", hits), {100, 240}, 40.0f, dd::colors::red });


        //dd::gfx::draw(heroBound, heroSprite.position);



        dd::gfx::end();
    }
}

int main()
{
    Init();

    MainLoop(); // this is the real game

    Deinit();

    return 0;
}
