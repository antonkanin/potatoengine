#include "game_object.h"

using namespace pt;

const engine& game_object::engine() const
{
    return *engine_;
}
