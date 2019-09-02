#pragma once

#include "allegro5/bitmap.h"

#include <array>
#include <utility>

class Animation {
public:
    Animation();
    ~Animation();

    void tick(float delta);
    void draw();

private:
    ALLEGRO_BITMAP* bitmap;
    std::array<std::pair<float, float>, 4> offsets;
    float elapsed, duration;
};