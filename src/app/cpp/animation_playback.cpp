#include "app/animation_playback.h"

#include "allegro5/bitmap_draw.h"

using std::vector;

vector<Animation> AnimationPlayback::active, AnimationPlayback::inactive;

void AnimationPlayback::tick(float delta) {
    for(auto& it: active) {
        it.elapsed += delta;
    }
}

void AnimationPlayback::draw() {
    for(auto& it: active) {
        int i = int(it.elapsed / it.duration * 4.f) % 4;
        al_draw_scaled_bitmap(it.bitmap, it.offsets[i].first, it.offsets[i].second, 32, 32, 0, 0, 256, 256, 0);
    }
}