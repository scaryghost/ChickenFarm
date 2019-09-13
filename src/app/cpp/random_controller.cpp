#include "app/actor.h"
#include "app/animation_playback.h"
#include "app/random_controller.h"
#include "app/random.h"

#include <algorithm>

using namespace std;

set<Actor*> RandomController::actors;

static uniform_int_distribution<> next_orientation(0, 3);
static uniform_real_distribution<float> next_duration(2.f, 4.f);

void RandomController::tick(float dt) {
    for(auto it: actors) {
        it->position.x = min(max(it->position.x + it->velocity.x * dt, 0.f), 1856.f);
        it->position.y = min(max(it->position.y + it->velocity.y * dt, 0.f), 1016.f);

        it->duration -= dt;
        if (it->duration < 0.f) {
            AnimationPlayback::stop(it->current_animation);

            auto orientation = next_orientation(Random::engine);
            it->velocity = Actor::velocities[orientation];
            
            it->current_animation = it->animations[orientation];
            AnimationPlayback::start(it->current_animation);

            it->duration = next_duration(Random::engine);
        }
    }
}