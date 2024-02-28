#ifndef VEC3_H
#define VEC3_H

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

    double length() const
    {
        return InvSqrt64(length_squared());
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

#endif