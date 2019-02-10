#include "point.h"

void swap(point& p1, point& p2)
{
    auto temp = p1;
    p1        = p2;
    p2        = temp;
}
