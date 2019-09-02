#include "app/animation.h"

#include "allegro5/bitmap_io.h"
#include "allegro5/bitmap_draw.h"

Animation::Animation() : 
        bitmap(al_load_bitmap("res/chicken_walk.png")), 
        offsets{{
            {0.f, 96.f}, {32.f, 96.f}, {64.f, 96.f}, {96.f, 96.f}
        }},
        elapsed(0.f),
        duration(0.5f) {

}

Animation::~Animation() {
    al_destroy_bitmap(bitmap);
}

void Animation::tick(float delta) {
    elapsed += delta;
}

#include <iostream>
void Animation::draw() {
    int i = int(elapsed / duration * 4.f) % 4;
    al_draw_scaled_bitmap(bitmap, offsets[i].first, offsets[i].second, 32, 32, 0, 0, 256, 256, 0);
}