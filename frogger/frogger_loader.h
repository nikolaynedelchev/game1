﻿#pragma once

#include <dd.h>

namespace FroggerGame
{
namespace Rss
{
void LoadResources();
std::vector<std::pair<std::string, dd::sprite>> GetSprites();
dd::sprite GetSprite(const std::string& name);
dd::rect GetRect(const std::string& name);

extern dd::sprite froggerUp[2];
extern dd::sprite froggerDn[2];
extern dd::sprite froggerLf[2];
extern dd::sprite froggerRg[2];

extern dd::sprite ladyLf[2];
extern dd::sprite ladyRg[2];

extern dd::sprite snake[4];
extern dd::sprite cars[3];
extern dd::sprite tractors[3];

extern dd::sprite beaver[3];

extern dd::sprite fly;
extern dd::sprite truck;
extern dd::sprite crocodile[2];

extern dd::sprite turtle[3];
extern dd::sprite turtleDive[2];

extern dd::sprite trees[3];

extern dd::sprite walkway;
extern dd::sprite homesBackground;

extern dd::sprite froggerLogo;

extern dd::rect homes[5];
extern dd::rect homeWalls[6];

extern dd::sprite skull_1;
extern dd::sprite skull_2;

extern dd::sound music;
extern dd::sound music;
extern dd::sound extraLife;
extern dd::sound hit;
extern dd::sound jump;
extern dd::sound time;
extern dd::sound drown;

}
}
