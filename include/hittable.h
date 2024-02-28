#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

class hit_record
{
public:
    point3 p;//表示光线撞击点在三维空间中的位置
    vec3 normal;//表示撞击点处的表面法向量，用于计算反射光线、折射光线等
    double t;//表示光线从起点出发到撞击点的距离，这个值通常用于判断多个撞击事件中哪一个最先发生
    bool front_face;

    void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable
{
public:
    virtual ~hittable() = default;

    virtual bool hit(const ray &r, double ray_tmin, double ray_tmax, hit_record &rec) const = 0;
};

#endif