/*
生成渐变色图
*/
#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <iostream>
#include <fstream>

using namespace std;

bool hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;//from origin to center
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    return (discriminant >= 0);
}

color ray_color(const ray& r) {
    if (hit_sphere(point3(0,0,-1), 0.5, r))
        return color(1, 0, 0);

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

int main(){

    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    int image_height = static_cast<int>(image_width / aspect_ratio);
    if(image_height<1) image_height=1;

    // Camera

    auto focal_length = 1.0;//焦距
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (static_cast<double>(image_width)/image_height);
    point3 camera_center = point3(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    vec3 viewport_u = vec3(viewport_width, 0, 0);
    vec3 viewport_v = vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    vec3 pixel_delta_u = viewport_u / image_width;
    vec3 pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    point3 viewport_upper_left = camera_center
                            - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    point3 pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Render

    ofstream outfile("C:\\study\\2024spr\\CG\\ray_tracing\\target\\test4.ppm", ios::trunc);
    if (!outfile)
    {
        cerr << "failed to open test4.ppm" << endl;
        return 1;
    }
    outfile << "P3" << endl;
    outfile << image_width << " " << image_height << endl;
    outfile << 255 << endl;

    for (int j = 0; j < image_height; ++j) {
        clog << "\rScanlines remaining: " << (image_height - j) << ' ' << flush;
        for (int i = 0; i < image_width; ++i) {
            point3 pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            vec3 ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r);
            write_color(outfile, pixel_color);
        }
    }

    clog<<"Done."<<endl;
    outfile.close();
    return 0;
}