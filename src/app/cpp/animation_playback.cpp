#include "app/actor.h"
#include "app/animation_playback.h"

#include "allegro5/bitmap_draw.h"
#include "allegro5/bitmap_io.h"

using namespace std;

vector<Animation> AnimationPlayback::animations;
set<size_t> AnimationPlayback::active;

void AnimationPlayback::tick(float delta) {
    for(auto it: active) {
        animations[it].elapsed += delta;
    }
}

void AnimationPlayback::draw() {
    for(auto it: active) {
        int i = int(animations[it].elapsed / animations[it].duration * 4.f) % 4;
        al_draw_scaled_bitmap(
            animations[it].bitmap, 
            animations[it].offsets[i].first, animations[it].offsets[i].second, 
            32, 32, 
            animations[it].actor->position.x, animations[it].actor->position.y, 
            64, 64, 
            0
        );
    }
}

Animation* AnimationPlayback::create(
    Actor* actor,
    const std::string& path, 
    float duration, 
    const std::initializer_list<std::pair<float, float>>& offsets
) {
    animations.push_back({
        actor,
        al_load_bitmap(path.c_str()),
        offsets,
        active.size(),
        0.f,
        duration
    });

    return &animations.back();
}

void AnimationPlayback::start(size_t idx) {
    if (idx < no_animation) {
        active.insert(idx);
    }
}
void AnimationPlayback::stop(size_t idx) {
    active.erase(idx);
}