#include "app/animation.h"

#include "allegro5/bitmap_io.h"

using std::initializer_list;
using std::pair;
using std::string;
using std::vector;

Animation::Animation(
    const string& path, 
    float elapsed, 
    float duration, 
    const initializer_list<pair<float, float>>& offsets
) : bitmap(al_load_bitmap(path.c_str())), 
    offsets{offsets},
    elapsed(elapsed),
    duration(duration) {

}

Animation::~Animation() {
    al_destroy_bitmap(bitmap);
}


/*
bitmap(al_load_bitmap("res/chicken_walk.png")), 
    offsets{{
        {0.f, 96.f}, {32.f, 96.f}, {64.f, 96.f}, {96.f, 96.f}
    }},
    elapsed(0.f),
    duration(0.5f) {
        */