#pragma once

#include "animation.h"

#include <initializer_list>
#include <string>
#include <unordered_set>
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

    static void start(Animation* animation);
    static void stop(Animation* animation);

    static std::vector<Animation> animations;
private:
    static std::unordered_set<Animation*> active;
};
