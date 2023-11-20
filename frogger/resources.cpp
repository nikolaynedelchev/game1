#include "all_modules.h"

namespace FroggerGame
{

void ResourcesModule::Load()
{
    std::string f = "sprites.png";

    rss.emptySprite.load(f, {{0, 0}, {1, 1}}, {});
    // Frogger
    dd::vec froggerSz = {25, 25};
    dd::rect froggerHit = {8, 8, 9, 9};
    dd::rect froggerStep = {11, 11, 3, 3};
    rss.froggerLf[GND].load(f, {{78, 334}, froggerSz}, {}); // Left Ground Frogger
    rss.froggerLf[GND].anchor = (dd::anchors::centered);
    rss.froggerLf[GND].bounds["hit"].rects.push_back(froggerHit);
    rss.froggerLf[GND].bounds["step"].rects.push_back(froggerStep);

    rss.froggerLf[AIR].load(f, {{112, 336}, froggerSz}, {});// Left Air Frogger
    rss.froggerLf[AIR].anchor = (dd::anchors::centered);
    rss.froggerLf[AIR].bounds["hit"].rects.push_back(froggerHit);
    rss.froggerLf[AIR].bounds["step"].rects.push_back(froggerHit);

    rss.froggerRg[GND].load(f, {{9, 333}, froggerSz}, {});  // Right Ground Frogger
    rss.froggerRg[GND].anchor = (dd::anchors::centered);
    rss.froggerRg[GND].bounds["hit"].rects.push_back(froggerHit);
    rss.froggerRg[GND].bounds["step"].rects.push_back(froggerHit);

    rss.froggerRg[AIR].load(f, {{43, 333}, froggerSz}, {}); // Right Air Frogger
    rss.froggerRg[AIR].anchor = (dd::anchors::centered);
    rss.froggerRg[AIR].bounds["hit"].rects.push_back(froggerHit);
    rss.froggerRg[AIR].bounds["step"].rects.push_back(froggerHit);

    rss.froggerUp[GND].load(f, {{11, 365}, froggerSz}, {}); // Up Ground Frogger
    rss.froggerUp[GND].anchor = (dd::anchors::centered);
    rss.froggerUp[GND].bounds["hit"].rects.push_back(froggerHit);
    rss.froggerUp[GND].bounds["step"].rects.push_back(froggerHit);

    rss.froggerUp[AIR].load(f, {{44, 366}, froggerSz}, {}); // Up Air Frogger
    rss.froggerUp[AIR].anchor = (dd::anchors::centered);
    rss.froggerUp[AIR].bounds["hit"].rects.push_back(froggerHit);
    rss.froggerUp[AIR].bounds["step"].rects.push_back(froggerHit);

    rss.froggerDn[GND].load(f, {{79, 365}, froggerSz}, {}); // Down Ground Frogger
    rss.froggerDn[GND].anchor = (dd::anchors::centered);
    rss.froggerDn[GND].bounds["hit"].rects.push_back(froggerHit);
    rss.froggerDn[GND].bounds["step"].rects.push_back(froggerHit);

    rss.froggerDn[AIR].load(f, {{112, 366}, froggerSz}, {});// Down Air Frogger
    rss.froggerDn[AIR].anchor = (dd::anchors::centered);
    rss.froggerDn[AIR].bounds["hit"].rects.push_back(froggerHit);
    rss.froggerDn[AIR].bounds["step"].rects.push_back(froggerHit);


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
    rss.homes[0] = dd::rect({24, 68}, {5, 39});     // Home 0
    rss.homes[1] = dd::rect({110, 68}, {5, 39});    // Home 1
    rss.homes[2] = dd::rect({195, 68}, {5, 39});   // Home 2
    rss.homes[3] = dd::rect({279, 68}, {5, 39});   // Home 3
    rss.homes[4] = dd::rect({364, 68}, {5, 39});   // Home 4

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
        s.anchor = (dd::anchors::centered);
        s.bounds["hit"].rects.push_back({{0, 0}, s.rect().size()});
        fastLeftCarAnim.add_frame(s);
        fastLeftCarAnim.anchor = (dd::anchors::centered);
        fastLeftCarAnim.visible = true;
        fastLeftCarAnim.loop = true;
        fastLeftCarAnim.position = {300, 200};
    }

    // Tractor
    {
        for(auto s : tractors)
        {
            s.bounds["hit"].rects.push_back({{0, 0}, s.rect().size()});
            s.anchor = (dd::anchors::centered);
            tractorAnim.add_frame(s);
        }
        tractorAnim.fps(3.0f);
        tractorAnim.anchor = (dd::anchors::centered);
        tractorAnim.visible = true;
        tractorAnim.loop = true;
    }

    // Slow car left
    {
        auto s = cars[LEFT_SLOW];
        s.anchor = (dd::anchors::centered);
        s.bounds["hit"].rects.push_back({{0, 0}, s.rect().size()});
        slowCarAnim.add_frame(s);
        slowCarAnim.anchor = (dd::anchors::centered);
        slowCarAnim.visible = true;
        slowCarAnim.loop = true;
    }

    // White car (fast car right)
    {
        auto s = cars[RIGHT_FAST];
        s.anchor = (dd::anchors::centered);
        s.bounds["hit"].rects.push_back({{0, 0}, s.rect().size()});
        fastRightCarAnim.add_frame(s);
        fastRightCarAnim.anchor = (dd::anchors::centered);
        fastRightCarAnim.visible = true;
        fastRightCarAnim.loop = true;
    }

    // Truck
    {
        auto s = truck;
        s.anchor = (dd::anchors::centered);
        s.bounds["hit"].rects.push_back({{0, 0}, s.rect().size()});
        truckAnim.add_frame(s);
        truckAnim.anchor = (dd::anchors::centered);
        truckAnim.visible = true;
        truckAnim.loop = true;
    }

    // Skull
    {
        auto s = skull_1;
        s.anchor = dd::anchors::centered;
        landDeathAnim.add_frame(s);
        landDeathAnim.loop = false;
        landDeathAnim.fps(0.4);
        landDeathAnim.visible = true;
    }

    //dd::anim smallTreeAnim;
    {
        auto s = trees[SMALL];
        s.anchor = (dd::anchors::centered);
        s.bounds["step"].rects.push_back({{0, 0}, s.rect().size()});
        smallTreeAnim.add_frame(s);
        smallTreeAnim.anchor = (dd::anchors::centered);
        smallTreeAnim.visible = true;
        smallTreeAnim.loop = true;
    }

    //dd::anim midTreeAnim;
    {
        auto s = trees[MID];
        s.anchor = (dd::anchors::centered);
        s.bounds["step"].rects.push_back({{0, 0}, s.rect().size()});
        midTreeAnim.add_frame(s);
        midTreeAnim.anchor = (dd::anchors::centered);
        midTreeAnim.visible = true;
        midTreeAnim.loop = true;
    }
    //dd::anim bigTreeAnim;
    {
        auto s = trees[BIG];
        s.anchor = (dd::anchors::centered);
        s.bounds["step"].rects.push_back({{0, 0}, s.rect().size()});
        bigTreeAnim.add_frame(s);
        bigTreeAnim.anchor = (dd::anchors::centered);
        bigTreeAnim.visible = true;
        bigTreeAnim.loop = true;
    }
    //dd::anim turtleAnim;
    {
        for (auto s : turtle)
        {
            s.anchor = (dd::anchors::centered);
            s.bounds["step"].rects.push_back({{0, 0}, s.rect().size()});
            s.attach(s, {s.size.x, 0});
            turtleAnim.add_frame(s);
        }
        turtleAnim.fps(2.6f);
        turtleAnim.anchor = (dd::anchors::centered);
        turtleAnim.visible = true;
        turtleAnim.loop = true;
    }
    //dd::anim divingTurtleAnim;
    {
        for (auto s : turtle)
        {
            s.anchor = (dd::anchors::centered);
            s.bounds["step"].rects.push_back({{0, 0}, s.rect().size()});
            s.attach(s, {s.size.x, 0});
            divingTurtleAnim.add_frame(s);
        }
        std::vector<dd::sprite> diveFrames;
        for (auto s : turtleDive)
        {
            s.anchor = (dd::anchors::centered);
            s.bounds["step"].rects.push_back({{0, 0}, s.rect().size()});
            s.attach(s, {s.size.x, 0});
            diveFrames.push_back(s);
            divingTurtleAnim.add_frame(s);
        }
        divingTurtleAnim.add_frame(emptySprite);
        divingTurtleAnim.add_frame(diveFrames[1]);
        divingTurtleAnim.add_frame(diveFrames[0]);

        divingTurtleAnim.fps(2.6f);
        divingTurtleAnim.anchor = (dd::anchors::centered);
        divingTurtleAnim.visible = true;
        divingTurtleAnim.loop = true;
    }
    //dd::anim crocodileAnim;
    {
        for (auto s : crocodile)
        {
            s.anchor = (dd::anchors::centered);
            dd::rect crocodileBody = {{0, 0}, s.rect().size()};
            crocodileBody.width -= 23;
            dd::rect crocodileMouth = {{crocodileBody.width, 0}, {23, crocodileBody.height}};

            s.bounds["step"].rects.push_back(crocodileBody);
            s.bounds["hit"].rects.push_back(crocodileMouth);
            crocodileAnim.add_frame(s);
        }
        crocodileAnim.fps(0.4f);
        crocodileAnim.anchor = (dd::anchors::centered);
        crocodileAnim.visible = true;
        crocodileAnim.loop = true;
    }
}

ResourcesModule rss;
}
