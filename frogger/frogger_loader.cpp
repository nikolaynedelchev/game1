#include "frogger_loader.h"
#include <map>

namespace Frogger
{
dd::sprite froggerUp[2];
dd::sprite froggerDn[2];
dd::sprite froggerLf[2];
dd::sprite froggerRg[2];

dd::sprite ladyLf[2];
dd::sprite ladyRg[2];

dd::sprite snake[4];
dd::sprite cars[3];
dd::sprite tractors[3];

dd::sprite beaver[3];

dd::sprite fly;
dd::sprite truck;
dd::sprite crocodile[2];

dd::sprite turtle[3];
dd::sprite turtleDive[2];

dd::sprite trees[3];

dd::sprite walkway;
dd::sprite homesBackground;

dd::sprite froggerLogo;

dd::rect homes[5];
dd::rect homeWalls[6];

dd::sprite skull_1;
dd::sprite skull_2;

#define SMALL 0
#define MID 1
#define BIG 2
#define FED 0
#define HUNGRY 1
#define GND 0
#define AIR 1
#define LEFT_SLOW 0
#define RIGHT_FAST 1
#define LEFT_FAST 2

void LoadResources()
{
    std::string f = "sprites.png";

    // Frogger
    dd::vec froggerSz = {25, 25};
    froggerLf[GND].load(f, {{78, 334}, froggerSz}, {}); // Left Ground Frogger
    froggerLf[AIR].load(f, {{112, 336}, froggerSz}, {});// Left Air Frogger

    froggerRg[GND].load(f, {{9, 333}, froggerSz}, {});  // Right Ground Frogger
    froggerRg[AIR].load(f, {{43, 333}, froggerSz}, {}); // Right Air Frogger

    froggerUp[GND].load(f, {{11, 365}, froggerSz}, {}); // Up Ground Frogger
    froggerUp[AIR].load(f, {{44, 366}, froggerSz}, {}); // Up Air Frogger

    froggerDn[GND].load(f, {{79, 365}, froggerSz}, {}); // Down Ground Frogger
    froggerDn[AIR].load(f, {{112, 366}, froggerSz}, {});// Down Air Frogger

    // Lady
    dd::vec ladySz = {28, 28};
    ladyLf[GND].load(f, {{310, 405}, ladySz}, {});  // Left Ground Lady
    ladyLf[AIR].load(f, {{348, 407}, ladySz}, {});  // Left Air Lady

    ladyRg[GND].load(f, {{232, 405}, ladySz}, {});  // Right Ground Lady
    ladyRg[AIR].load(f, {{270, 407}, ladySz}, {});  // Right Air Lady

    // snake
    dd::vec snakeSz = {38, 16};
    snake[0].load(f, {{184, 220}, snakeSz}, {});    // Snake frame 0
    snake[1].load(f, {{184, 248}, snakeSz}, {});    // Snake frame 1
    snake[2].load(f, {{184, 276}, snakeSz}, {});    // Snake frame 2
    snake[3].load(f, {{184, 301}, snakeSz}, {});    // Snake frame 3

    // cars
    dd::vec carSz = {28, 26};
    cars[LEFT_SLOW].load(f, {{10, 264}, carSz}, {});    // Left Slow Car
    cars[RIGHT_FAST].load(f, {{46, 264}, carSz}, {});   // Right Fast Car
    cars[LEFT_FAST].load(f, {{80, 264}, carSz}, {});    // Left Fast Car

    // tractors
    dd::vec tractorSz = {26, 23};
    tractors[0].load(f, {{10, 300}, tractorSz}, {});    // Tractor frame 0
    tractors[1].load(f, {{41, 300}, tractorSz}, {});    // Tractor frame 1
    tractors[2].load(f, {{72, 300}, tractorSz}, {});    // Tractor frame 2

    // beaver
    dd::vec beaverSz = {35, 20};
    beaver[0].load(f, {{115, 255}, beaverSz}, {});    // Beaver frame 0
    beaver[1].load(f, {{115, 262}, beaverSz}, {});    // Beaver frame 1
    beaver[2].load(f, {{115, 270}, beaverSz}, {});    // Beaver frame 2

    // Fly
    fly.load(f, {{139, 235}, {18, 18}}, {});    // Fly

    // Truck
    truck.load(f, {{106, 302}, {46, 18}}, {});    // Truck

    // Crocodile
    dd::vec crocodileSz = {89, 30};
    crocodile[FED].load(f, {{156, 365}, crocodileSz}, {});    // Crocodile fed
    crocodile[HUNGRY].load(f, {{156, 332}, crocodileSz}, {});    // Crocodile fed

    // Turtle
    dd::vec turtleSz = {31, 22};
    turtle[0].load(f, {{15, 406}, turtleSz}, {});    // Turtle frame 0
    turtle[1].load(f, {{54, 407}, turtleSz}, {});    // Turtle frame 1
    turtle[2].load(f, {{92, 407}, turtleSz}, {});    // Turtle frame 2
    turtleDive[0].load(f, {{133, 407}, turtleSz}, {});    // Turtle Dive frame 0
    turtleDive[1].load(f, {{176, 407}, turtleSz}, {});    // Turtle Dive frame 1

    // Trees
    trees[SMALL].load(f, {{7, 230}, {85, 21}}, {});     // Small Tree
    trees[MID].load(f, {{7, 198}, {117, 21}}, {});      // Mid Tree
    trees[BIG].load(f, {{7, 166}, {178, 21}}, {});      // Big Tree

    // Walkway
    walkway.load(f, {{0, 119}, {399, 34}}, {}); // Walkway

    // Homes Background
    homesBackground.load(f, {{0, 55}, {399, 53}}, {}); // Homes Background

    // Homes
    homes[0] = dd::rect({3, 64}, {51, 39});     // Home 0
    homes[1] = dd::rect({87, 64}, {51, 39});    // Home 1
    homes[2] = dd::rect({172, 64}, {51, 39});   // Home 2
    homes[3] = dd::rect({256, 64}, {51, 39});   // Home 3
    homes[4] = dd::rect({340, 64}, {51, 39});   // Home 4

    // Home Walls
    homeWalls[0] = dd::rect({-35, 64}, {40, 40});   // Home Wall 0
    homeWalls[1] = dd::rect({50, 64}, {40, 40});    // Home Wall 0
    homeWalls[2] = dd::rect({135, 64}, {40, 40});   // Home Wall 0
    homeWalls[3] = dd::rect({220, 64}, {40, 40});   // Home Wall 0
    homeWalls[4] = dd::rect({305, 64}, {40, 40});   // Home Wall 0
    homeWalls[5] = dd::rect({389, 64}, {40, 40});   // Home Wall 0

    // Frogger Loggo
    froggerLogo.load(f, {{13, 11}, {322, 35}}, {}); // Frogger Loggo

    // Skulls
    skull_1.load(f, {{273, 208}, {36, 40}}, {}); // Skull 1
    skull_2.load(f, {{321, 206}, {36, 40}}, {}); // Skull 2
}

std::vector<std::pair<std::string, dd::sprite>> GetSprites()
{
    std::vector<std::pair<std::string, dd::sprite>> sprites;

    sprites.push_back({"frogger_up_ground", froggerUp[GND]});
    sprites.push_back({"frogger_up_air", froggerUp[AIR]});
    sprites.push_back({"frogger_down_ground", froggerDn[GND]});
    sprites.push_back({"frogger_down_air", froggerDn[AIR]});
    sprites.push_back({"frogger_left_ground", froggerLf[GND]});
    sprites.push_back({"frogger_left_air", froggerLf[AIR]});
    sprites.push_back({"frogger_right_ground", froggerRg[GND]});
    sprites.push_back({"frogger_right_air", froggerRg[AIR]});

    sprites.push_back({"lady_left_ground", ladyLf[GND]});
    sprites.push_back({"lady_left_air", ladyLf[AIR]});
    sprites.push_back({"lady_right_ground", ladyRg[GND]});
    sprites.push_back({"lady_right_air", ladyRg[AIR]});

    sprites.push_back({"snake_0", snake[0]});
    sprites.push_back({"snake_1", snake[1]});
    sprites.push_back({"snake_2", snake[2]});
    sprites.push_back({"snake_3", snake[3]});

    sprites.push_back({"slow_car_left", cars[LEFT_SLOW]});
    sprites.push_back({"fast_car_right", cars[RIGHT_FAST]});
    sprites.push_back({"fast_car_left", cars[LEFT_FAST]});

    sprites.push_back({"tractor_0", tractors[0]});
    sprites.push_back({"tractor_1", tractors[1]});
    sprites.push_back({"tractor_2", tractors[2]});

    sprites.push_back({"beaver_0", beaver[0]});
    sprites.push_back({"beaver_1", beaver[1]});
    sprites.push_back({"beaver_2", beaver[2]});

    sprites.push_back({"fly", fly});

    sprites.push_back({"truck", truck});

    sprites.push_back({"crocodile_fed", crocodile[FED]});
    sprites.push_back({"crocodile_hungry", crocodile[HUNGRY]});

    sprites.push_back({"turtle_0", turtle[0]});
    sprites.push_back({"turtle_1", turtle[1]});
    sprites.push_back({"turtle_2", turtle[2]});

    sprites.push_back({"turtle_dive_0", turtleDive[0]});
    sprites.push_back({"turtle_dive_1", turtleDive[1]});

    sprites.push_back({"tree_small", trees[SMALL]});
    sprites.push_back({"tree_mid", trees[MID]});
    sprites.push_back({"tree_big", trees[BIG]});

    sprites.push_back({"walkway", walkway});

    sprites.push_back({"homes_background", homesBackground});

    sprites.push_back({"frogger_loggo", froggerLogo});

    sprites.push_back({"skull_1", skull_1});
    sprites.push_back({"skull_2", skull_2});
    
    return sprites;
}

dd::sprite GetSprite(const std::string& name)
{
    static std::map<std::string, dd::sprite> s_allSprites;

    if (s_allSprites.empty())
    {
        auto allSprites = GetSprites();
        for(const auto& p : allSprites)
        {
            s_allSprites[p.first] = p.second;
        }
    }
    return s_allSprites[name];
}



static std::map<std::string, dd::rect> s_allRects;
static void PushRects()
{
    s_allRects["homes_0"] = homes[0];
    s_allRects["homes_1"] = homes[1];
    s_allRects["homes_2"] = homes[2];
    s_allRects["homes_3"] = homes[3];
    s_allRects["homes_4"] = homes[4];

    s_allRects["home_walls_0"] = homeWalls[0];
    s_allRects["home_walls_1"] = homeWalls[1];
    s_allRects["home_walls_2"] = homeWalls[2];
    s_allRects["home_walls_3"] = homeWalls[3];
    s_allRects["home_walls_4"] = homeWalls[4];
    s_allRects["home_walls_5"] = homeWalls[5];
}

dd::rect GetRect(const std::string& name)
{
    if (s_allRects.empty())
    {
        PushRects();
    }
    return s_allRects[name];
}

}
