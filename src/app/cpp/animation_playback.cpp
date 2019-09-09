#include "app/actor.h"
#include "app/animation_playback.h"

#include "allegro5/bitmap_draw.h"
#include "allegro5/bitmap_io.h"

using namespace std;

vector<Animation> AnimationPlayback::animations;
unordered_set<Animation*> AnimationPlayback::active;

void AnimationPlayback::tick(float delta) {
    for(auto it: active) {
        it->elapsed += delta;
    }
}

void AnimationPlayback::draw() {
    for(auto it: active) {
        int i = int(it->elapsed / it->duration * 4.f) % 4;
        al_draw_scaled_bitmap(it->bitmap, it->offsets[i].first, it->offsets[i].second, 32, 32, it->actor->position.x, it->actor->position.y, 64, 64, 0);
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

void AnimationPlayback::start(Animation* animation) {
    active.insert(animation);
}
void AnimationPlayback::stop(Animation* animation) {
    active.erase(animation);
}