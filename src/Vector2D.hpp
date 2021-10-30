#pragma once

#include <iostream>
#include <math.h>

class Vector2D {

public:

    double x;
    double y;

    Vector2D();

    Vector2D(double x, double y);

    Vector2D & Add(const Vector2D & vector);
    Vector2D & Subtract(const Vector2D & vector);
    Vector2D & Divide(const Vector2D & vector);
    Vector2D & Multiply(const Vector2D & vector);
    double Dot(const Vector2D & vector);
    Vector2D & Cross(const Vector2D & vector);
    Vector2D & Normalize();

    friend Vector2D & operator+(Vector2D & v1, const Vector2D & v2);
    friend Vector2D & operator-(Vector2D & v1, const Vector2D & v2);
    friend Vector2D & operator/(Vector2D & v1, const Vector2D & v2);
    friend Vector2D & operator*(Vector2D & v1, const Vector2D & v2);

    Vector2D & operator+=(const Vector2D & vector);
    Vector2D & operator-=(const Vector2D & vector);
    Vector2D & operator/=(const Vector2D & vector);
    Vector2D & operator*=(const Vector2D & vector);

    Vector2D & operator*(const int & i);
    Vector2D & Zero();

    friend std::ostream & operator<<(std::ostream & stream, const Vector2D & vector);

private:
    double norm() {
        return std::sqrt(x*x + y*y);
    }

};