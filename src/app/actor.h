#pragma once

#include <vector>

struct Animation;

struct Vector {
    float x, y;
};

struct Actor {
    Vector position, velocity;
    float duration;
    std::vector<Animation*> animations;
    Animation* current_animation;

    void tick(float dt);
};