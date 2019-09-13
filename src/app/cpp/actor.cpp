#include "app/actor.h"

using namespace std; 

const array<Vector, 4> Actor::velocities = {{
    {0.f, -48.f}, {0.f, 48.f}, {48.f, 0.f}, {-48.f, 0.f}
}};