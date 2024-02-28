#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include "ray.h"
#include "vec3.h"

#include <cmath>
#include <limits>
#include <memory>

using std::make_shared;
using std::shared_ptr;

const double infinity = std::numeric_limits<double>::infinity();//double类型无穷大
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees)
{
    return degrees * pi / 180.00;
}

#endif