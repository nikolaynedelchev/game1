#include <dd.h>
//#include <engine_ex.h>

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
        auto frame = dd::sprite::load("test/test_animation.png", src, {});
        frame.bound.rects.push_back( frame.origin_rect()  );
        runningAnim.add_frame(frame);
    }
    runningAnim.fps(18.0f);
    runningAnim.loop = true;
    runningAnim.flip_x = true;
    runningAnim.position = {300, 300};
    runningAnim.visible = true;
    runningAnim.pause(false);

    runningAnim2 = runningAnim;
    runningAnim2.fps(3.0f);
    runningAnim2.flip_x = false;
    runningAnim.position.y += 160;


    for (int i = 0; i < 5; i++)
    {
        dd::rect src;
        src.x = float(i * 144);
        src.y = float(0);
        src.width = 144;
        src.height = 144;
        auto frame = dd::sprite::load("test/test_animation.png", src, {});
        frame.bound.rects.push_back( frame.origin_rect()  );
        runningAnim3.add_frame(frame);
    }
    runningAnim3.fps(5.0f);
    runningAnim3.loop = true;
    runningAnim3.flip_x = false;
    runningAnim3.position = {300, 650};
    runningAnim3.visible = true;
    runningAnim3.pause(false);
}

void Init()
{
    dd::rss_folder(DD_RSS_FOLDER);
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

    dd::println("Loading resources...");
    //
    dd::transform heroTr = {{}, {0.30f, 0.35f}};
    dd::transform heroLeftMissilesTr = dd::transform{-80.0f, -80.0f, 1.0f, 0.8f} * heroTr;
    dd::transform heroRightMissilesTr = dd::transform{+80.0f, -80.0f, 1.0f, 0.8f} * heroTr;
    dd::transform bulletTr = dd::transform{{}, {0.3f, 0.5f}} * heroTr;

    heroSprite = dd::sprite::load("test/hero.png", {}, heroTr);
    //heroSprite.flip_x = true;
    //heroSprite.flip_y = true;
    heroSprite.position.x = 250.0f;
    heroSprite.position.y = 800.0f;
    heroBound.rects.push_back(heroTr * dd::rect{-50.0f, -40.0f, 100, 120});
    heroBound.rects.push_back(heroTr * dd::rect{-100.0f, 6.0f,   80,   70});
    heroBound.rects.push_back(heroTr * dd::rect{+20.0f, 6.0f,  80, 70});
    heroBound.rects.push_back(heroTr * dd::rect{-20.0f  , -80.0f, 40,  40});

    leftMissileSprite = dd::sprite::load("test/hero_missile.png", {}, heroLeftMissilesTr);
    rightMissileSprite = dd::sprite::load("test/hero_missile.png", {}, heroRightMissilesTr);
    bulletSprite = dd::sprite::load("test/bullet.png", {}, bulletTr);
    bulletSprite.bound.rects.push_back( bulletSprite.origin_rect() );


    shotSound = dd::audio::load_sound( DD_RSS_FOLDER"/sounds/tests/shot.wav");

    LoadTestAnim();

    dd::println("Resource loaded!");
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
            if (dd::kbd::key_down(dd::keys::P))     { runningAnim.pause(!runningAnim.paused()); }

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
                    bullets.back().position = leftMissileSprite.global_pos();
                    bullets.push_back(bulletSprite);
                    bullets.back().position = rightMissileSprite.global_pos();
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

        dd::gfx::begin();
        dd::gfx::clear(dd::colors::black);

        runningAnim.draw();
        runningAnim2.draw();
        runningAnim3.draw();

        heroSprite.draw();

        if (showMissilies)
        {
            leftMissileSprite.draw();
            rightMissileSprite.draw();
        }

        //dd::gfx::draw(dd::gfx::global_pos(leftMissileSprite), dd::colors::blue, true);
        //dd::gfx::draw(dd::gfx::global_pos(rightMissileSprite), dd::colors::green, true);

        dd::gfx::write({  fmt::format("{}", leftMissileSprite.global_pos()), {100, 100}, 40.0f, dd::colors::red });
        dd::gfx::write({  fmt::format("{}", leftMissileSprite.position), {100, 150}, 40.0f, dd::colors::red});
        dd::gfx::write({  fmt::format("{}", leftMissileSprite.global_rect()), {100, 190}, 40.0f, dd::colors::red });
        dd::gfx::write({  fmt::format("Hits: {}", hits), {100, 240}, 40.0f, dd::colors::red });


        heroBound.draw(heroSprite.position);



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
