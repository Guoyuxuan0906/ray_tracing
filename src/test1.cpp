/*
直接输出一张图的ppm文件
*/
#include <iostream>
#include <fstream> // 引入文件操作的头文件
using namespace std;

int main()
{
    ofstream outfile(R"(C:\study\2024spr\CG\ray_tracing\target\test1.ppm)", ios::trunc); 
    if (!outfile)
    {
        cerr << "failed to open test1.ppm" << endl;
        return 1;
    }
    int nx = 256;
    int ny = 256;
    outfile << "P3" << endl;
    outfile << nx << " " << ny << endl;
    outfile << 255 << endl;
    for (int j = ny - 1; j >= 0; j--)
    {
        clog << "Progress bar: " << ny - j << "/" << ny << "\n" << flush;
        for (int i = 0; i < nx; i++)
        {
            float r = float(i) / float(nx);
            float g = float(j) / float(ny);
            float b = 0.2;
            int ir = int(255.99 * r);
            int ig = int(255.99 * g);
            int ib = int(255.99 * b);
            outfile << ir << " " << ig << " " << ib << endl;
        }
    }
    clog << "Done\n";
    outfile.close(); // 关闭文件
    return 0;
}
