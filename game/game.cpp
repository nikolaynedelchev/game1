#include <engine/tools.h>

struct Game
{
    uint64_t frameNumber = 0;
    float buttonX = 100.0f;
    float buttonY = 100.0f;
};
Game game;
Texture2D testTexture;
Sprite testSprite;

void Init()
{
    int screenWidth = 800;
    int screenHeight = 600;

    //SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(screenWidth, screenHeight, "Raylib Force Exit Example");
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);
    //
    LoadImage("../resources/images/test/coins.png", "coins");
    Sprite_Load(testSprite, {40.0f, 40.0f, 85.0f, 85.0f}, "coins");

    Image myImage = LoadImage("../resources/images/test/coins.png");
    testTexture = LoadTextureFromImage(myImage);

}

void Deinit()
{
    CloseWindow();
}

void MainLoop()
{
    while (!WindowShouldClose())
    {
        game.frameNumber++;
        BeginDrawing();

        game.buttonX += float(GetRandomValue(0, 99) - 50) / 50.0f;
        game.buttonY += float(GetRandomValue(0, 99) - 50) / 100.0f;

        if (GuiButton({game.buttonX, game.buttonY, 40.0f, 30.0f}, "Exit"))
        {
            EndDrawing();
            break;
        }

        if (IsKeyDown(KEY_UP))    {  game.buttonY -= 3.0f;}
        if (IsKeyDown(KEY_DOWN))  {  game.buttonY += 3.0f;}
        if (IsKeyDown(KEY_LEFT))  {  game.buttonX -= 3.0f;}
        if (IsKeyDown(KEY_RIGHT)) {  game.buttonX += 3.0f;}

        ClearBackground(RAYWHITE);
        DrawText("HELLO WORLD!", 10, 10, 20, DARKGRAY);

        // DrawTexturePro(testTexture, {0.0f, 0.0f, 190.0f, 250.0f}, 
        //                             {game.buttonX + 40.0f, game.buttonY + 20.0f, 190.0f, 250.0f}, 
        //                             {0.0f, 0.0f}, 
        //                             0, 
        //                             WHITE);


        // DrawTexturePro(testTexture, {0.0f, 0.0f, 190.0f, 250.0f}, 
        //                             {game.buttonX + 90.0f, game.buttonY + 120.0f, 190.0f, 250.0f}, 
        //                             {0.0f, 0.0f}, 
        //                             0, 
        //                             WHITE);

        testSprite.position.x = game.buttonX + 11;
        testSprite.position.y = game.buttonY + 33;
        Sprite_Draw(testSprite);

        EndDrawing();
    }
}

int main()
{
    test_loader();
    Init();

    MainLoop(); // this is the real game

    Deinit();

    return 0;
}
