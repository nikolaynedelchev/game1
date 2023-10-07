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


void Init()
{
    int screenWidth = 1440;
    int screenHeight = 900;

    //dd::window::set_fullscreen_flag();
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
    heroSprite.position.x = 250.0f;
    heroSprite.position.y = 800.0f;
    heroBound.rects.push_back(heroTr * dd::rectangle{-50.0f, -40.0f, 100, 120});
    heroBound.rects.push_back(heroTr * dd::rectangle{-100.0f, 6.0f,   80,   70});
    heroBound.rects.push_back(heroTr * dd::rectangle{+20.0f, 6.0f,  80, 70});
    heroBound.rects.push_back(heroTr * dd::rectangle{-20.0f  , -80.0f, 40,  40});

    leftMissileSprite = dd::gfx::load_sprite("test/hero_missile.png", {}, heroLeftMissilesTr);
    rightMissileSprite = dd::gfx::load_sprite("test/hero_missile.png", {}, heroTr * heroRightMissilesTr);
    bulletSprite = dd::gfx::load_sprite("test/bullet.png", {}, heroTr * bulletTr);


    shotSound = dd::audio::load_sound("../resources/sounds/tests/shot.wav");

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
    while ( !dd::window::should_close() )
    {
        game.frameNumber++;

        if (1)
        {
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
                bulletsCooldown = 15;

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
                b.position.y -= 30;
                bullets.push_back(b);
            }
        }
        for(const auto& b : bullets) dd::gfx::draw(b);

        dd::gfx::begin();
        dd::gfx::clear(dd::colors::black);

        dd::gfx::write({"Hello world", {100, 100}, 50, dd::colors::red});
        dd::gfx::draw(heroSprite);

        if (showMissilies)
        {
            dd::gfx::draw(leftMissileSprite);
            dd::gfx::draw(rightMissileSprite);
        }

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
