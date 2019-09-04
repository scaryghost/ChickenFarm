#pragma once

struct Vector {
    float x, y;
};

struct Actor {
    Vector position, velocity;

    void tick(float dt);
};