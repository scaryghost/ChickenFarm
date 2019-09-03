#pragma once

#include "allegro5/bitmap.h"

#include <initializer_list>
#include <string>
#include <vector>
#include <utility>

struct Animation {
    Animation(
        const std::string& path, 
        float elapsed, 
        float duration, 
        const std::initializer_list<std::pair<float, float>>& offsets
    );
    ~Animation();

    ALLEGRO_BITMAP* bitmap;
    std::vector<std::pair<float, float>> offsets;
    float elapsed, duration;
};