#include "all_modules.h"

namespace FroggerGame
{

void ResourcesModule::Load()
{
    std::string f = "sprites.png";

    // Frogger
    dd::vec froggerSz = {25, 25};
    rss.froggerLf[GND].load(f, {{78, 334}, froggerSz}, {}); // Left Ground Frogger
    rss.froggerLf[GND].bounds["hit"].rects.push_back(rss.froggerLf[GND].rect());
    rss.froggerLf[GND].bounds["step"].rects.push_back(rss.froggerLf[GND].rect());

    rss.froggerLf[AIR].load(f, {{112, 336}, froggerSz}, {});// Left Air Frogger
    rss.froggerLf[AIR].bounds["hit"].rects.push_back(rss.froggerLf[AIR].rect());
    rss.froggerLf[AIR].bounds["step"].rects.push_back(rss.froggerLf[AIR].rect());

    rss.froggerRg[GND].load(f, {{9, 333}, froggerSz}, {});  // Right Ground Frogger
    rss.froggerRg[GND].bounds["hit"].rects.push_back(rss.froggerRg[GND].rect());
    rss.froggerRg[GND].bounds["step"].rects.push_back(rss.froggerRg[GND].rect());

    rss.froggerRg[AIR].load(f, {{43, 333}, froggerSz}, {}); // Right Air Frogger
    rss.froggerRg[AIR].bounds["hit"].rects.push_back(rss.froggerRg[AIR].rect());
    rss.froggerRg[AIR].bounds["step"].rects.push_back(rss.froggerRg[AIR].rect());

    rss.froggerUp[GND].load(f, {{11, 365}, froggerSz}, {}); // Up Ground Frogger
    rss.froggerUp[GND].bounds["hit"].rects.push_back(rss.froggerUp[GND].rect());
    rss.froggerUp[GND].bounds["step"].rects.push_back(rss.froggerUp[GND].rect());

    rss.froggerUp[AIR].load(f, {{44, 366}, froggerSz}, {}); // Up Air Frogger
    rss.froggerUp[AIR].bounds["hit"].rects.push_back(rss.froggerUp[AIR].rect());
    rss.froggerUp[AIR].bounds["step"].rects.push_back(rss.froggerUp[AIR].rect());

    rss.froggerDn[GND].load(f, {{79, 365}, froggerSz}, {}); // Down Ground Frogger
    rss.froggerDn[GND].bounds["hit"].rects.push_back(rss.froggerDn[GND].rect());
    rss.froggerDn[GND].bounds["step"].rects.push_back(rss.froggerDn[GND].rect());

    rss.froggerDn[AIR].load(f, {{112, 366}, froggerSz}, {});// Down Air Frogger
    rss.froggerDn[AIR].bounds["hit"].rects.push_back(rss.froggerDn[AIR].rect());
    rss.froggerDn[AIR].bounds["step"].rects.push_back(rss.froggerDn[AIR].rect());


    // Lady
    dd::vec ladySz = {28, 28};
    rss.ladyLf[GND].load(f, {{310, 405}, ladySz}, {});  // Left Ground Lady
    rss.ladyLf[AIR].load(f, {{348, 407}, ladySz}, {});  // Left Air Lady

    rss.ladyRg[GND].load(f, {{232, 405}, ladySz}, {});  // Right Ground Lady
    rss.ladyRg[AIR].load(f, {{270, 407}, ladySz}, {});  // Right Air Lady

    // snake
    dd::vec snakeSz = {38, 16};
    rss.snake[0].load(f, {{184, 220}, snakeSz}, {});    // Snake frame 0
    rss.snake[1].load(f, {{184, 248}, snakeSz}, {});    // Snake frame 1
    rss.snake[2].load(f, {{184, 276}, snakeSz}, {});    // Snake frame 2
    rss.snake[3].load(f, {{184, 301}, snakeSz}, {});    // Snake frame 3

    // cars
    dd::vec carSz = {28, 26};
    rss.cars[LEFT_SLOW].load(f, {{10, 264}, carSz}, {});    // Left Slow Car
    rss.cars[RIGHT_FAST].load(f, {{46, 264}, carSz}, {});   // Right Fast Car
    rss.cars[LEFT_FAST].load(f, {{80, 264}, carSz}, {});    // Left Fast Car

    // tractors
    dd::vec tractorSz = {26, 23};
    rss.tractors[0].load(f, {{10, 300}, tractorSz}, {});    // Tractor frame 0
    rss.tractors[1].load(f, {{41, 300}, tractorSz}, {});    // Tractor frame 1
    rss.tractors[2].load(f, {{72, 300}, tractorSz}, {});    // Tractor frame 2

    // beaver
    dd::vec beaverSz = {35, 20};
    rss.beaver[0].load(f, {{115, 255}, beaverSz}, {});    // Beaver frame 0
    rss.beaver[1].load(f, {{115, 262}, beaverSz}, {});    // Beaver frame 1
    rss.beaver[2].load(f, {{115, 270}, beaverSz}, {});    // Beaver frame 2

    // Fly
    rss.fly.load(f, {{139, 235}, {18, 18}}, {});    // Fly

    // Truck
    rss.truck.load(f, {{106, 302}, {46, 18}}, {});    // Truck

    // Crocodile
    dd::vec crocodileSz = {89, 30};
    rss.crocodile[FED].load(f, {{156, 365}, crocodileSz}, {});    // Crocodile fed
    rss.crocodile[HUNGRY].load(f, {{156, 332}, crocodileSz}, {});    // Crocodile fed

    // Turtle
    dd::vec turtleSz = {31, 22};
    rss.turtle[0].load(f, {{15, 406}, turtleSz}, {});    // Turtle frame 0
    rss.turtle[1].load(f, {{54, 407}, turtleSz}, {});    // Turtle frame 1
    rss.turtle[2].load(f, {{92, 407}, turtleSz}, {});    // Turtle frame 2
    rss.turtleDive[0].load(f, {{133, 407}, turtleSz}, {});    // Turtle Dive frame 0
    rss.turtleDive[1].load(f, {{176, 407}, turtleSz}, {});    // Turtle Dive frame 1

    // Trees
    rss.trees[SMALL].load(f, {{7, 230}, {85, 21}}, {});     // Small Tree
    rss.trees[MID].load(f, {{7, 198}, {117, 21}}, {});      // Mid Tree
    rss.trees[BIG].load(f, {{7, 166}, {178, 21}}, {});      // Big Tree

    // Walkway
    rss.walkway.load(f, {{0, 118}, {400, 36}}, {}); // Walkway

    // Homes Background
    rss.homesBackground.load(f, {{0, 55}, {400, 53}}, {}); // Homes Background

    // Homes
    rss.homes[0] = dd::rect({3, 64}, {51, 39});     // Home 0
    rss.homes[1] = dd::rect({87, 64}, {51, 39});    // Home 1
    rss.homes[2] = dd::rect({172, 64}, {51, 39});   // Home 2
    rss.homes[3] = dd::rect({256, 64}, {51, 39});   // Home 3
    rss.homes[4] = dd::rect({340, 64}, {51, 39});   // Home 4

    rss.riverRect = {0, 0, SCREEN_WIDTH, HEADER_H + HOMES_H + 5.5f * ROW_H};
    rss.landRect = {0, HEADER_H + HOMES_H + 5.5 * ROW_H, SCREEN_WIDTH, 6.5 * ROW_H + FOOTER_H};

    // Home Walls
    rss.homeWalls[0] = dd::rect({-35, 64}, {40, 40});   // Home Wall 0
    rss.homeWalls[1] = dd::rect({50, 64}, {40, 40});    // Home Wall 0
    rss.homeWalls[2] = dd::rect({135, 64}, {40, 40});   // Home Wall 0
    rss.homeWalls[3] = dd::rect({220, 64}, {40, 40});   // Home Wall 0
    rss.homeWalls[4] = dd::rect({305, 64}, {40, 40});   // Home Wall 0
    rss.homeWalls[5] = dd::rect({389, 64}, {40, 40});   // Home Wall 0

    // Frogger Loggo
    rss.froggerLogo.load(f, {{13, 11}, {322, 35}}, {}); // Frogger Loggo

    // Skulls
    rss.skull_1.load(f, {{273, 208}, {36, 40}}, {}); // Skull 1
    rss.skull_2.load(f, {{321, 206}, {36, 40}}, {}); // Skull 2

    rss.music.load("music.mp3");
    rss.extraLife.load("extra_life.wav");
    rss.hit.load("hit.wav");
    rss.jump.load("jump.wav");
    rss.time.load("time.wav");
    rss.drown.load("water_drown.wav");

    // Yellow car (fast car left)
    {
        auto s = cars[LEFT_FAST];
        s.change_anchor(dd::anchors::centered);
        s.bounds["hit"].rects.push_back(s.rect());
        fastLeftCarAnim.add_frame(s);
        fastLeftCarAnim.change_anchor(dd::anchors::centered);
        fastLeftCarAnim.visible = true;
        fastLeftCarAnim.loop = true;
        fastLeftCarAnim.position = {300, 200};
    }

    // Tractor
    {
        for(auto s : tractors)
        {
            s.bounds["hit"].rects.push_back(s.rect());
            s.change_anchor(dd::anchors::centered);
            tractorAnim.add_frame(s);
        }
        tractorAnim.fps(3.0f);
        tractorAnim.change_anchor(dd::anchors::centered);
        tractorAnim.visible = true;
        tractorAnim.loop = true;
    }

    // Slow car left
    {
        auto s = cars[LEFT_SLOW];
        s.change_anchor(dd::anchors::centered);
        s.bounds["hit"].rects.push_back(s.rect());
        slowCarAnim.add_frame(s);
        slowCarAnim.change_anchor(dd::anchors::centered);
        slowCarAnim.visible = true;
        slowCarAnim.loop = true;
    }

    // White car (fast car right)
    {
        auto s = cars[RIGHT_FAST];
        s.change_anchor(dd::anchors::centered);
        s.bounds["hit"].rects.push_back(s.rect());
        fastRightCarAnim.add_frame(s);
        fastRightCarAnim.change_anchor(dd::anchors::centered);
        fastRightCarAnim.visible = true;
        fastRightCarAnim.loop = true;
    }

    // Truck
    {
        auto s = truck;
        s.change_anchor(dd::anchors::centered);
        s.bounds["hit"].rects.push_back(s.rect());
        truckAnim.add_frame(s);
        truckAnim.change_anchor(dd::anchors::centered);
        truckAnim.visible = true;
        truckAnim.loop = true;
    }
}

ResourcesModule rss;
}
