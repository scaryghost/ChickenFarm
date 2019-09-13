#pragma once

#include "animation.h"

#include <cstddef>
#include <initializer_list>
#include <string>
#include <set>
#include <vector>

class AnimationPlayback {
public:
    static void tick(float delta);
    static void draw();
    
    static Animation* create(
        Actor* actor,
        const std::string& path, 
        float duration, 
        const std::initializer_list<std::pair<float, float>>& offsets
    );

    static void start(std::size_t idx);
    static void stop(std::size_t idx);

    static std::vector<Animation> animations;
private:
    static std::set<std::size_t> active;
};
