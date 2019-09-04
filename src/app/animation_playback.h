#pragma once

#include "animation.h"

#include <initializer_list>
#include <string>
#include <vector>

class AnimationPlayback {
public:
    static void tick(float delta);
    static void draw();
    
    static Animation& create(
        Actor* actor,
        const std::string& path, 
        float duration, 
        const std::initializer_list<std::pair<float, float>>& offsets
    );

private:
    static std::vector<Animation> active, inactive;
};
