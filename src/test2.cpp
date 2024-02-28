/*
调用API接口生成简单彩色ppm文件
*/
#include "color.h"
#include "vec3.h"

#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ofstream outfile("C:\\study\\2024spr\\CG\\ray_tracing\\target\\test2.ppm", ios::trunc);
    if (!outfile)
    {
        cerr << "failed to open test2.ppm" << endl;
        return 1;
    }

    int image_width = 256;
    int image_height = 256;

    outfile << "P3" << endl;
    outfile << image_width << " " << image_height << endl;
    outfile << 255 << endl;

    for (int j = 0; j < image_height; ++j)
    {
        clog << "\rProgress bar: " << j + 1 << "/" << image_height << flush;

        for (int i = 0; i < image_width; ++i)
        {
            auto pixel_color = color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0.2);
            write_color(outfile, pixel_color);
        }
    }

    std::clog << "\nDone.                 \n";
    outfile.close();
    return 0;
}