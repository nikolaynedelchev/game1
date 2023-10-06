#include <engine/engine.h>

struct Game
{
    uint64_t frameNumber = 0;
};
Game game;

Sprite testSprite;
Sprite heroSprite;
Sprite heroUpSprite;
Sprite powerupSprite;
Sprite leftMissileSprite;
Sprite rightMissileSprite;
Sprite bulletSprite;

Bound heroBound;

Bound testBound;

Sound shotSound;
void Init()
{
    int screenWidth = 1680;
    int screenHeight = 1050;

    //SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(screenWidth, screenHeight, "Raylib Force Exit Example");
    InitAudioDevice();
    //SetExitKey(KEY_NULL);
    SetTargetFPS(60);
    HideCursor();

    PrintLn("Loading resources...");
    //
    testSprite = CreateSprite("test/coins.png", {});
    testSprite.targetShape.width = 80;
    testSprite.targetShape.height = 80;
    //
    float heroScale = 0.5f;
    heroSprite = CreateSprite("test/hero.png", {}, heroScale);
    heroSprite.position.x = 250.0f;
    heroSprite.position.y = 800.0f;
    heroBound.rects.push_back({-25.0f, -20.0f, 50, 60});
    heroBound.rects.push_back({-50.0f, 3.0f, 40, 35});
    heroBound.rects.push_back({+10.0f, 3.0f, 40, 35});
    heroBound.rects.push_back({-10.0f, -40.0f, 20, 20});

    //heroBound.circles.push_back({{0.0f, -150.0f}, 35.0f});
    //heroBound.circles.push_back({{0.0f, 160.0f}, 30.0f});


    testBound.rects.push_back({-55.0f, 3.0f, 40, 35});
    testBound.rects.push_back({+85.0f, 3.0f, 40, 35});
    testBound.circles.push_back({{360.0f, 5.0f}, 35.0f});
    testBound.circles.push_back({{620.0f, 8.0f}, 30.0f});


    heroUpSprite = CreateSprite("test/hero_up.png", {});
    leftMissileSprite = CreateSprite("test/hero_missile.png", {}, heroScale * 0.8f, {-45, +40});
    rightMissileSprite = CreateSprite("test/hero_missile.png", {}, heroScale * 0.8f, {+45, +40});
    bulletSprite = CreateSprite("test/bullet.png", {}, heroScale * 0.4f);

    powerupSprite = CreateSprite("test/powerup.png", {});

    shotSound = LoadSound("../resources/sounds/tests/shot.wav");


    PrintLn("Resource loaded!");
}

void Deinit()
{
    CloseWindow();
}

void MainLoop()
{
    bool showMissilies = true;
    int bulletsCooldown = 0;
    int equipCooldown = 0;
    std::vector<Sprite> bullets;
    while (!WindowShouldClose())
    {
        game.frameNumber++;
        BeginDrawing();

        //heroSprite.position.x += float(GetRandomValue(0, 99) - 50) / 50.0f;
        //heroSprite.position.y += float(GetRandomValue(0, 99) - 50) / 100.0f;

        if (1)
        {
            if (IsKeyDown(KEY_UP))    {  heroSprite.position.y -= 3.0f;}
            if (IsKeyDown(KEY_DOWN))  {  heroSprite.position.y += 3.0f;}
            if (IsKeyDown(KEY_LEFT))  {  heroSprite.position.x -= 3.0f;}
            if (IsKeyDown(KEY_RIGHT)) {  heroSprite.position.x += 3.0f;}
            if (IsKeyDown(KEY_F))     { ToggleFullscreen(); }
            if (equipCooldown <= 0)
            {
                if (IsKeyDown(KEY_LEFT_CONTROL)) 
                {
                    equipCooldown = 10;
                    showMissilies = !showMissilies; 
                }
            }
            else if (IsKeyUp(KEY_LEFT_CONTROL))
            {
                equipCooldown = 0;
            }
            heroSprite.position += GetMouseDelta();
        }

        if (heroSprite.position.y < 750.0f)
        {
            heroSprite.position.y = 750.0f;
        }
        if (heroSprite.position.y > 1000.0f)
        {
            heroSprite.position.y = 1000.0f;
        }
        if (heroSprite.position.x < 0.0f)
        {
            heroSprite.position.x = 0.0f;
        }
        if (heroSprite.position.x > 1680.0f)
        {
            heroSprite.position.x = 1680.0f;
        }

        if (bulletsCooldown <= 0)
        {
            if (IsKeyDown(KEY_SPACE) || IsMouseButtonDown(0))  
            {  
                bulletsCooldown = 15;

                bullets.push_back(bulletSprite);
                bullets.back().position = heroSprite.position;
                bullets.push_back(bulletSprite);
                if (showMissilies)
                {
                    bullets.back().position = heroSprite.position + Vector2{+40.0f, +35.0f};
                    bullets.push_back(bulletSprite);
                    bullets.back().position = heroSprite.position + Vector2{-40.0f, +35.0f};
                } 
                PlaySound(shotSound);
            }
        }
        else
        {
            bulletsCooldown--;
        }
        std::vector<Sprite> tmpBullets = std::move(bullets);
        for(auto& b : tmpBullets)
        {
            if (b.position.y > 0)
            {
                b.position.y -= 30;
                bullets.push_back(b);
            }
        }
        for(const auto& b : bullets) DrawSprite(b);

        ClearBackground(BLACK);
        string msg = fmt::format("X={}, Y={}", leftMissileSprite.targetShape.x, leftMissileSprite.targetShape.y);
        DrawText(msg.c_str(), 10, 10, 40, DARKGRAY);

        DrawSprite(heroSprite);

        leftMissileSprite.position = heroSprite.position;
        rightMissileSprite.position = heroSprite.position;

        if (showMissilies)
        {
            DrawSprite(leftMissileSprite);
            DrawSprite(rightMissileSprite);
        }

        //DrawBound(heroSprite, heroBound);

        powerupSprite.position = {300.0f, 700.0f};
        //DrawBound(powerupSprite, testBound);

        if (CheckCollision(heroSprite, heroBound, powerupSprite, testBound))
        {
            //DrawText("Collision", 10, 60, 40, DARKGRAY);
        }

        EndDrawing();
    }
}

int main()
{
    Init();

    MainLoop(); // this is the real game

    Deinit();

    return 0;
}
