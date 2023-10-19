#include <dd.h>
#include "frogger_loader.h"

dd::engine engine;

namespace Frogger
{
int screenWidth = 1440;
int screenHeight = 900;


int gameWidth = 784;
int gameHeight = 900;

///////////////////////////////////////////////////////////////////////////////////////
////////////                            Frogger
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

dd::point froggerPosition = {screenWidth / 2.0f, screenHeight / 2.0f};
dd::direction froggerDirection = dd::direction::up;
bool isFroggerMoving = false;
dd::point froggerDestination;
float froggerSpeed = 2.0f; // pixels/frame
float froggerJumpSize = 50.0f;

void UpdateFroggerJumps()
{
    if (isFroggerMoving)
    {
        if (froggerPosition.distance(froggerDestination) <= froggerSpeed)
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
        return;
    }

    if (engine.key_pressed(dd::keys::UP))
    {
        isFroggerMoving = true;
        froggerDestination = froggerPosition;
        froggerDestination.y -= froggerJumpSize;
        froggerDirection = dd::direction::up;
    }
    if (engine.key_pressed(dd::keys::DOWN))
    {
        isFroggerMoving = true;
        froggerDestination = froggerPosition;
        froggerDestination.y += froggerJumpSize;
        froggerDirection = dd::direction::down;
    }
    if (engine.key_pressed(dd::keys::LEFT))
    {
        isFroggerMoving = true;
        froggerDestination = froggerPosition;
        froggerDestination.x -= froggerJumpSize;
        froggerDirection = dd::direction::left;
    }
    if (engine.key_pressed(dd::keys::RIGHT))
    {
        isFroggerMoving = true;
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
////////////                            Homes
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

void UpdateHomes()
{

}

void DrawHomes()
{
    auto homesSprite = GetSprite("homes_background");
    homesSprite.change_anchor(dd::anchors::up_mid);
    homesSprite.position = {screenWidth / 2.0f, 0};
    homesSprite.draw();

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
    dd::println("Resource loaded!");
}

void Deinit()
{
    engine.close();
}

void MainLoop()
{
    dd::camera camera;
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
        engine.clipping_on(dd::rect({10, 10}, {screenWidth - 20, screenHeight - 20}));




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
