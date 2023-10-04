#include <iostream>
#include <raylib.h>
#include <raygui.h>

struct Game
{
    uint64_t frameNumber = 0;
    float buttonX = 100.0f;
    float buttonY = 100.0f;
};
Game game;

void Init()
{
    int screenWidth = 800;
    int screenHeight = 600;

    //SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(screenWidth, screenHeight, "Raylib Force Exit Example");
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);
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
