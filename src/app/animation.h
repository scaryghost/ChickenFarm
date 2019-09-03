#pragma once

#include "allegro5/bitmap.h"

#include <cstddef>
#include <vector>
#include <utility>

struct Animation {
    ALLEGRO_BITMAP* bitmap;
    std::vector<std::pair<float, float>> offsets;
    std::size_t pos;
    float elapsed, duration;
};