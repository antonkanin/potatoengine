#pragma once

#include "vector3d.hpp"

struct transformation
{
    vector3d position;
    vector3d rotation_vector;
    float    rotation_angle;
    vector3d scale;
};
