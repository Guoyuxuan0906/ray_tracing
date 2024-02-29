#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>
#include <fstream>

using color = vec3;

inline double linear_to_gamma(double linear_component)
{
    return fast_sqrt64(linear_component);
}

void write_color(std::ostream &out, color pixel_color, int samples_per_pixel)
{
    auto r=pixel_color.x();
    auto g=pixel_color.y();
    auto b=pixel_color.z();

    auto scale=1.0/samples_per_pixel;
    r*=scale;
    g*=scale;
    b*=scale;

    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);
    
    static const interval intensity(0.0000,0.9999);
    out << static_cast<int>(256 * intensity.clamp(r)) << ' '
        << static_cast<int>(256 * intensity.clamp(g)) << ' '
        << static_cast<int>(256 * intensity.clamp(b)) << '\n';
}

#endif