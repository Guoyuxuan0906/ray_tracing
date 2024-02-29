#ifndef VEC3_H
#define VEC3_H

#include "rtweekend.h"
#include <iostream>

float InvSqrt32(float x)
{
    float xhalf = 0.5f * x;
    int i = *(int *)&x;
    i = 0x5f3759df - (i >> 1); // 计算第一个近似根
    x = *(float *)&i;
    x = x * (1.5f - xhalf * x * x); // 牛顿迭代法
    return x;
}

float fast_sqrt32(float number)
{
    return 1.0F / InvSqrt32(number);
}

double InvSqrt64(double number)
{
    long long i;
    double x2, y;
    const double threehalfs = 1.5;

    x2 = number * 0.5;
    y = number;
    i = *(long long *)&y;
    i = 0x5fe6eb50c7b537a9 - (i >> 1);
    y = *(double *)&i;
    y = y * (threehalfs - (x2 * y * y));
    y = y * (threehalfs - (x2 * y * y));

    return y;
}

double fast_sqrt64(double number)
{
    return 1.0 / InvSqrt64(number);
}

class vec3
{
public:
    double vector[3];

    vec3() : vector{0.0, 0.0, 0.0} {}
    vec3(double e0, double e1, double e2) : vector{e0, e1, e2} {}

    double x() const { return vector[0]; }
    double y() const { return vector[1]; }
    double z() const { return vector[2]; }

    vec3 operator-() const { return vec3(-vector[0], -vector[1], -vector[2]); }
    double operator[](int i) const { return vector[i]; }
    double &operator[](int i) { return vector[i]; }

    vec3 &operator+=(const vec3 &v)
    {
        vector[0] += v.vector[0];
        vector[1] += v.vector[1];
        vector[2] += v.vector[2];
        return *this;
    }

    vec3 &operator*=(double t)
    {
        vector[0] *= t;
        vector[1] *= t;
        vector[2] *= t;
        return *this;
    }

    vec3 &operator/=(double t)
    {
        return *this *= 1 / t;
    }

    double length_squared() const
    {
        return vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2];
    }

    bool near_zero()
    {
        auto s = 1e-8;
        return (fabs(vector[0]) < s) && (fabs(vector[1]) < s) && (fabs(vector[2]) < s);
    }

    double length() const
    {
        return fast_sqrt64(length_squared());
    }

    static vec3 random()
    {
        return vec3(random_double(), random_double(), random_double());
    }

    static vec3 random(double min, double max)
    {
        return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }
};

using point3 = vec3; // 同一个东西不同名字

inline std::ostream &operator<<(std::ostream &out, const vec3 &v)
{
    return out << v.vector[0] << ' ' << v.vector[1] << ' ' << v.vector[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v)
{
    return vec3(u.vector[0] + v.vector[0], u.vector[1] + v.vector[1], u.vector[2] + v.vector[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v)
{
    return vec3(u.vector[0] - v.vector[0], u.vector[1] - v.vector[1], u.vector[2] - v.vector[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v)
{
    return vec3(u.vector[0] * v.vector[0], u.vector[1] * v.vector[1], u.vector[2] * v.vector[2]);
}

inline vec3 operator*(double t, const vec3 &v)
{
    return vec3(t * v.vector[0], t * v.vector[1], t * v.vector[2]);
}

inline vec3 operator*(const vec3 &v, double t)
{
    return t * v;
}

inline vec3 operator/(vec3 v, double t)
{
    return (1 / t) * v;
}

inline double dot(const vec3 &u, const vec3 &v)
{
    return u.vector[0] * v.vector[0] + u.vector[1] * v.vector[1] + u.vector[2] * v.vector[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v)
{
    return vec3(u.vector[1] * v.vector[2] - u.vector[2] * v.vector[1],
                u.vector[2] * v.vector[0] - u.vector[0] * v.vector[2],
                u.vector[0] * v.vector[1] - u.vector[1] * v.vector[0]);
}

inline vec3 unit_vector(vec3 v)
{
    return v / v.length();
}

inline vec3 random_in_unit_sphere()
{
    while (true)
    {
        vec3 p = vec3::random(-1, 1);
        if (p.length_squared() < 1)
            return p;
    }
} // 拒绝法，可优化

inline vec3 random_unit_vector()
{
    return unit_vector(random_in_unit_sphere());
} // 只针对球

inline vec3 random_in_unit_disk()
{
    while (true)
    {
        auto p = vec3(random_double(-1, 1), random_double(-1, 1), 0);
        if (p.length_squared() < 1)
            return p;
    }
}

inline vec3 random_on_hemisphere(const vec3 &normal)
{
    vec3 on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere, normal) < 0.0)
        on_unit_sphere = -on_unit_sphere;
    return on_unit_sphere;
}

vec3 reflect(const vec3 &v, const vec3 &n)
{
    return v - 2 * dot(v, n) * n;
}

vec3 refract(const vec3 &uv, const vec3 &n, double etai_over_etat)
{
    auto cos_theta = fmin(dot(-uv, n), 1.0);
    vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
    vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}
#endif