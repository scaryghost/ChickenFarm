#include "app/actor.h"

void Actor::tick(float dt) {
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;
}