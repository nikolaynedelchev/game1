#include <iostream>
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

void* print_hello(void* /*data*/) {
    printf("Hello from thread!\n");
    return NULL;
}

void test_pthread()
{
//    pthread_t thread_id;
//    pthread_create(&thread_id, NULL, print_hello, NULL);
//    pthread_join(thread_id, NULL);
}

void test_raylib()
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Raylib Force Exit Example");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        if (GuiButton({100.0f, 100.0f, 40.0f, 30.0f}, "Exit"))
        {
            CloseWindow();
        }

        ClearBackground(RAYWHITE);
        DrawText("HELLO WORLD!", 10, 10, 20, DARKGRAY);
        EndDrawing();
    }
}

int main()
{
    test_pthread();
    test_raylib();
    return 0;
}
