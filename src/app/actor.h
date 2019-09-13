#pragma once

#include <cstddef>
#include <vector>

const std::size_t no_animation = -1;

struct Vector {
    float x, y;
};

struct Actor {
    Vector position, velocity;
    float duration;
    std::vector<std::size_t> animations;
    std::size_t current_animation;

    void tick(float dt);
};