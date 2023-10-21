#include <dd.h>
#include "frogger_loader.h"

dd::engine engine;

namespace Frogger
{

float screenWidth = 1440;
float screenHeight = 900;

float gameWidth = 700;
float gameHeight = 900;

float scaleFactor = 1.0f;
float screenOffset = 0.0f;

///////////////////////////////////////////////////////////////////////////////////////
////////////                            Frogger
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

dd::point froggerPosition = {screenWidth / 2.0f, screenHeight / 2.0f};
dd::direction froggerDirection = dd::direction::up;
bool isFroggerMoving = false;
dd::point froggerDestination;
float froggerSpeed = 2.0f; // pixels/frame
float froggerJumpSize = 34.0f;
float froggerJumpFramesLeft = 0.0f;

void UpdateFroggerJumps()
{
    if (isFroggerMoving)
    {
        if (froggerJumpFramesLeft == 0.0f)
        {
            froggerPosition = froggerDestination;
            isFroggerMoving = false;
            return;
        }

        if (froggerDirection == dd::direction::up)
        {
            froggerPosition.y -= froggerSpeed;
        }
        if (froggerDirection == dd::direction::down)
        {
            froggerPosition.y += froggerSpeed;
        }
        if (froggerDirection == dd::direction::left)
        {
            froggerPosition.x -= froggerSpeed;
        }
        if (froggerDirection == dd::direction::right)
        {
            froggerPosition.x += froggerSpeed;
        }


        froggerJumpFramesLeft--;
        return;
    }

    if (engine.key_pressed(dd::keys::UP))
    {
        isFroggerMoving = true;
        froggerJumpFramesLeft = froggerJumpSize / froggerSpeed;
        froggerDestination = froggerPosition;
        froggerDestination.y -= froggerJumpSize;
        froggerDirection = dd::direction::up;
    }
    if (engine.key_pressed(dd::keys::DOWN))
    {
        isFroggerMoving = true;
        froggerJumpFramesLeft = froggerJumpSize / froggerSpeed;
        froggerDestination = froggerPosition;
        froggerDestination.y += froggerJumpSize;
        froggerDirection = dd::direction::down;
    }
    if (engine.key_pressed(dd::keys::LEFT))
    {
        isFroggerMoving = true;
        froggerJumpFramesLeft = froggerJumpSize / froggerSpeed;
        froggerDestination = froggerPosition;
        froggerDestination.x -= froggerJumpSize;
        froggerDirection = dd::direction::left;
    }
    if (engine.key_pressed(dd::keys::RIGHT))
    {
        isFroggerMoving = true;
        froggerJumpFramesLeft = froggerJumpSize / froggerSpeed;
        froggerDestination = froggerPosition;
        froggerDestination.x += froggerJumpSize;
        froggerDirection = dd::direction::right;
    }
}

void UpdateFrogger()
{
    UpdateFroggerJumps();
}

///////////////////////////////////////////////////////////////////////////////////////
////////////                            Background
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

void DrawBackground()
{
    auto homesSprite = GetSprite("homes_background");
    homesSprite.change_anchor(dd::anchors::up_left);
    homesSprite.position = {0, 0};
    homesSprite.draw();
}

///////////////////////////////////////////////////////////////////////////////////////
////////////                            Homes
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

void UpdateHomes()
{

}

void DrawHomes()
{


    auto tree = GetSprite("tree_big");
    tree.position = {0, 0};
    tree.change_anchor(dd::anchors::centered);
    tree.draw();
}


void DrawFrogger()
{
    dd::sprite s;
    if (isFroggerMoving)
    {
        if (froggerDirection == dd::direction::up)
        {
            s = GetSprite("frogger_up_air");
        }
        if (froggerDirection == dd::direction::down)
        {
            s = GetSprite("frogger_down_air");
        }
        if (froggerDirection == dd::direction::left)
        {
            s = GetSprite("frogger_left_air");
        }
        if (froggerDirection == dd::direction::right)
        {
            s = GetSprite("frogger_right_air");
        }
    }
    else
    {
        if (froggerDirection == dd::direction::up)
        {
            s = GetSprite("frogger_up_ground");
        }
        if (froggerDirection == dd::direction::down)
        {
            s = GetSprite("frogger_down_ground");
        }
        if (froggerDirection == dd::direction::left)
        {
            s = GetSprite("frogger_left_ground");
        }
        if (froggerDirection == dd::direction::right)
        {
            s = GetSprite("frogger_right_ground");
        }
    }
    s.change_anchor(dd::anchors::centered);
    s.position = froggerPosition;
    s.draw();
}

void Init()
{
    engine.init(DD_RSS_FOLDER, screenWidth, screenHeight, "FROGGER", false);
    engine.target_fps(60);
    engine.mouse_cursor_hide();

    dd::println("Loading resources...");
    LoadResources();

    auto homesSprite = GetSprite("homes_background");
    scaleFactor = gameWidth / homesSprite.size.x;
    screenOffset = screenWidth / 2.0f - gameWidth / 2.0f;

    dd::println("Resource loaded!");
}

void Deinit()
{
    engine.close();
}

void MainLoop()
{
    dd::camera camera;
    camera.scale = scaleFactor;
    camera.offset.x = screenOffset;

    while ( !engine.should_close() )
    {
        UpdateFrogger();
        UpdateHomes();

        if (engine.key_pressed(dd::keys::A)) camera.offset.x -= 30;
        if (engine.key_pressed(dd::keys::D)) camera.offset.x += 30;
        if (engine.key_pressed(dd::keys::W)) camera.offset.y -= 30;
        if (engine.key_pressed(dd::keys::S)) camera.offset.y += 30;

        if (engine.key_pressed(dd::keys::Q)) camera.scale -= 0.1f;
        if (engine.key_pressed(dd::keys::E)) camera.scale += 0.1f;

        engine.begin_frame();
        engine.clear_frame(dd::colors::dark_purple);
        engine.camera_on(camera);
        //engine.clipping_on(dd::rect({10, 10}, {float(screenWidth - 20), float(screenHeight - 20)}));



        DrawBackground();
        DrawFrogger();
        DrawHomes();
        engine.end_frame();
    }
}

}

int main()
{
    Frogger::Init();

    Frogger::MainLoop(); // this is the real game

    Frogger::Deinit();

    return 0;
}
