#include "app/random.h"

using namespace std;

static random_device rd;
mt19937 Random::engine(rd());