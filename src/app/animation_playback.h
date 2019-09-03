#pragma once

#include "animation.h"

#include <vector>

class AnimationPlayback {
public:
    static void tick(float delta);
    static void draw();

private:
    static std::vector<Animation> active, inactive;
};
