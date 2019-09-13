#pragma once

#include <set>

struct Actor;

struct RandomController {
    static std::set<Actor*> actors;
    static void tick(float dt);
};