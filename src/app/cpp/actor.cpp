#include "app/actor.h"
#include "app/animation_playback.h"

#include <algorithm>
#include <random>

using namespace std; 

static random_device rd;
static mt19937 engine(rd());
static uniform_int_distribution<> gen_orientation(0, 3);
static uniform_real_distribution<float> gen_duration(2.f, 4.f);
static array<Vector, 4> velocities = {{
    {0.f, -48.f}, {0.f, 48.f}, {48.f, 0.f}, {-48.f, 0.f}
}};


void Actor::tick(float dt) {
    position.x = min(max(position.x + velocity.x * dt, 0.f), 1856.f);
    position.y = min(max(position.y + velocity.y * dt, 0.f), 1016.f);

    duration -= dt;
    if (duration < 0.f) {
        AnimationPlayback::stop(current_animation);

        auto orientation = gen_orientation(engine);
        velocity = velocities[orientation];
        
        current_animation = animations[orientation];
        AnimationPlayback::start(current_animation);

        duration = gen_duration(engine);
    }
}